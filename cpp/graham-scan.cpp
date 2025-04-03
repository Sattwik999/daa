#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Point {
    int x, y;
};

// Global variable to store the pivot point for sorting
Point minYPoint;

// Function to determine orientation of the triplet (a, b, c)
// Returns:
// 0 → collinear
// 1 → counterclockwise
// -1 → clockwise
int orientation(Point a, Point b, Point c) {
    int val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val == 0) return 0;   // Collinear
    return (val > 0) ? 1 : -1; // Counterclockwise (CCW) or Clockwise (CW)
}

// Squared distance between two points (avoids unnecessary sqrt calculations)
int squaredDistance(Point a, Point b) {
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

// Comparator function for sorting points by polar angle w.r.t minYPoint
bool compare(Point p1, Point p2) {
    int orient = orientation(minYPoint, p1, p2);
    if (orient == 0)
        return squaredDistance(minYPoint, p1) < squaredDistance(minYPoint, p2); // Keep farthest
    return orient > 0; // Counterclockwise should come first
}

// Function to find the point with the lowest y-coordinate (left-most if tied)
Point findMinYPoint(vector<Point>& points) {
    Point minPoint = points[0];
    for (const auto& p : points) {
        if (p.y < minPoint.y || (p.y == minPoint.y && p.x < minPoint.x)) {
            minPoint = p;
        }
    }
    return minPoint;
}

// Convex Hull using Graham’s Scan
vector<Point> convexHull(vector<Point>& points) {
    if (points.size() < 3) return points; // Convex hull requires at least 3 points

    // Find the lowest point (or left-most if tied)
    minYPoint = findMinYPoint(points);

    // Sort points based on polar angle with minYPoint
    sort(points.begin(), points.end(), compare);

    // Remove duplicate angles by keeping the farthest point
    vector<Point> uniquePoints;
    uniquePoints.push_back(points[0]);
    for (size_t i = 1; i < points.size(); i++) {
        while (i < points.size() - 1 && orientation(minYPoint, points[i], points[i + 1]) == 0)
            i++; // Skip all but the last collinear point
        uniquePoints.push_back(points[i]);
    }

    // Stack to store convex hull points
    stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);

    for (size_t i = 2; i < points.size(); i++) {
        Point top = hull.top();
        hull.pop();

        // Remove points that create a clockwise turn
        while (!hull.empty() && orientation(hull.top(), top, points[i]) <= 0) {
            top = hull.top();
            hull.pop();
        }

        hull.push(top);
        hull.push(points[i]);
    }

    // Convert stack to vector for output
    vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }
    reverse(result.begin(), result.end()); // To maintain counterclockwise order
    return result;
}

int main() {
    vector<Point> points = {
        {0, 3}, {1, 1}, {2, 2}, {3, 1}, {4, 3}, {2, 4}
    };

    vector<Point> hull = convexHull(points);

    cout << "Convex Hull Points:\n";
    for (const auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
