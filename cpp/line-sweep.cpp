#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a point in 2D space
struct Point {
    int x, y;   // Coordinates
    bool isLeft; // Indicates if this is the left endpoint of a segment
    int index;   // Index of the segment this point belongs to

    // Comparison operator to sort points based on x-coordinates
    // If x-coordinates are the same, sort based on y-coordinates
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

// Structure to represent a line segment
struct Segment {
    Point p1, p2; // Two endpoints of the segment
};

// Function to check the orientation of three points
int orientation(Point a, Point b, Point c) {
    int val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

// Function to check if point q lies on segment pr
bool onSegment(Point p, Point q, Point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

// Function to check if two segments intersect
bool doIntersect(const Segment& s1, const Segment& s2) {
    Point p1 = s1.p1, q1 = s1.p2;
    Point p2 = s2.p1, q2 = s2.p2;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case: if orientations are different, segments intersect
    if (o1 != o2 && o3 != o4) return true;

    // Special cases: Check collinear cases where they overlap
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // No intersection
}

// Function to determine if any two segments in a set intersect
bool anySegmentsIntersect(vector<Segment>& segments) {
    vector<Point> points; // List of segment endpoints

    // Process all segments and extract their endpoints
    for (int i = 0; i < segments.size(); i++) {
        Point left = segments[i].p1, right = segments[i].p2;

        // Ensure left is the smaller x-coordinate endpoint
        if (left.x > right.x) swap(left, right);

        left.isLeft = true;   // Mark left endpoint
        right.isLeft = false; // Mark right endpoint
        left.index = right.index = i; // Associate with segment index

        points.push_back(left);
        points.push_back(right);
    }

    // Sort all endpoints based on x-coordinates (and y-coordinates if needed)
    sort(points.begin(), points.end());

    set<Segment*> activeSet; // Stores currently active segments

    // Sweep line algorithm to detect intersections
    for (int i = 0; i < points.size(); i++) {
        int idx = points[i].index; // Get the segment index

        if (points[i].isLeft) {
            // Insert the segment into the active set
            activeSet.insert(&segments[idx]);

            // Check for intersections with all other active segments
            for (auto s : activeSet) {
                if (s != &segments[idx] && doIntersect(*s, segments[idx])) {
                    return true; // Intersection found
                }
            }
        } else {
            // Remove the segment from the active set as we move past its right endpoint
            activeSet.erase(&segments[idx]);
        }
    }
    return false; // No intersections found
}

int main() {
    // Define a set of line segments
    vector<Segment> segments = {{{1, 1}, {4, 4}}, {{1, 4}, {4, 1}}, {{2, 3}, {5, 6}}};

    // Check for intersections and print the result
    cout << (anySegmentsIntersect(segments) ? "Segments intersect!" : "No intersections.") << endl;
    return 0;
}
