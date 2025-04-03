#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a point in 2D space
struct Point {
    int x, y;   // Coordinates
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

// Function to find the intersection point of two segments
tuple<bool, Point> getIntersectionPoint(Point p1, Point q1, Point p2, Point q2) {
    int a1 = q1.y - p1.y;
    int b1 = p1.x - q1.x;
    int c1 = a1 * p1.x + b1 * p1.y;

    int a2 = q2.y - p2.y;
    int b2 = p2.x - q2.x;
    int c2 = a2 * p2.x + b2 * p2.y;

    int det = a1 * b2 - a2 * b1;

    if (det == 0) return {false, {0, 0}}; // Parallel lines, no intersection

    Point intersection;
    intersection.x = (b2 * c1 - b1 * c2) / det;
    intersection.y = (a1 * c2 - a2 * c1) / det;

    if (onSegment(p1, intersection, q1) && onSegment(p2, intersection, q2))
        return {true, intersection};

    return {false, {0, 0}};
}

int isInsidePentagon(Point pentagon[], Point testPoint) {
    int firstOrientation = orientation(pentagon[0], pentagon[1], testPoint);

    // Check orientation with all sides
    for (int i = 1; i < 5; i++) {
        int nextOrientation = orientation(pentagon[i], pentagon[(i + 1) % 5], testPoint);
        if (nextOrientation != firstOrientation && nextOrientation != 0) {
            return 0; // Outside the pentagon
        }
    }
    return 1; // Inside the pentagon
}

int main() {
    // Define input points representing line segments
    vector<Point> points = {{1, 1}, {4, 4}, {1, 4}, {4, 1}, {2, 3}, {5, 6}};

    // Check for intersections and print the intersection point if found
    for (size_t i = 0; i < points.size(); i += 2) {
        for (size_t j = i + 2; j < points.size(); j += 2) {
            auto [intersects, intersection] = getIntersectionPoint(points[i], points[i + 1], points[j], points[j + 1]);
            if (intersects) {
                cout << "Segments intersect at (" << intersection.x << ", " << intersection.y << ")" << endl;
            }
        }
    }
    return 0;
}
