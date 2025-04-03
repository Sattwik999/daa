#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;

    // Overload operator for printing points
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

// Function to determine orientation of the triplet (a, b, c)
// Returns:
//  0 → collinear
//  >0 → counterclockwise
//  <0 → clockwise
int ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Squared distance between two points (avoids unnecessary sqrt calculations)
int squaredDistance(Point a, Point b) {
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

// Finds the point with the lowest y-coordinate (left-most if tied)
Point getMinY(vector<Point>& points) {
    Point minPoint = points[0];
    for (const auto& p : points) {
        if (p.y < minPoint.y || (p.y == minPoint.y && p.x < minPoint.x)) {
            minPoint = p;
        }
    }
    return minPoint;
}

// Convex Hull using Jarvis March (Gift Wrapping Algorithm)
vector<Point> convexHull(vector<Point>& points) {
    if (points.size() < 3) return {}; // Convex hull requires at least 3 points

    vector<Point> hull;
    Point startingPoint = getMinY(points);
    Point prevVertex = startingPoint;

    while (true) {
        hull.push_back(prevVertex);
        Point candidate = points[0];

        for (const auto& point : points) {
            if (point.x == prevVertex.x && point.y == prevVertex.y) continue;

            int orient = ccw(prevVertex, candidate, point);

            if (orient < 0 || (orient == 0 && squaredDistance(prevVertex, candidate) < squaredDistance(prevVertex, point))) {
                candidate = point;
            }
        }

        if (candidate.x == startingPoint.x && candidate.y == startingPoint.y) break; // Completed loop
        prevVertex = candidate;
    }

    return hull;
}

int main() {
    vector<Point> points = {
        {0, 3}, {1, 1}, {2, 2}, {3, 1}, {4, 3}, {2, 4}
    };

    vector<Point> hull = convexHull(points);

    cout << "Convex Hull Points:\n";
    for (const auto& p : hull) {
        cout << p << "\n";
    }

    return 0;
}
