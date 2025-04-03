#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Cross product to determine orientation
int crossProduct(Point A, Point B, Point C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

// Sorting comparator for convex hull (by x, then by y)
bool compare(Point p1, Point p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}

// Compute Convex Hull using Monotone Chain Algorithm (O(n log n))
vector<Point> convexHull(vector<Point> &points) {
    int n = points.size();
    if (n < 2) return points;

    sort(points.begin(), points.end(), compare);
    vector<Point> hull;

    // Lower hull
    for (auto &p : points) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    // Upper hull
    int lowerHullSize = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lowerHullSize && crossProduct(hull[hull.size() - 2], hull.back(), points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    hull.pop_back(); // Last point repeats the first point
    return hull;
}

// Squared distance (avoiding sqrt for efficiency)
int squaredDist(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Find farthest pair using Rotating Calipers (O(n))
pair<Point, Point> farthestPair(vector<Point> &hull) {
    int m = hull.size();
    if (m < 2) return {hull[0], hull[0]};

    int maxDist = 0;
    pair<Point, Point> maxPair;
    int j = 1; // Start opposite point for calipers

    for (int i = 0; i < m; i++) {
        while (squaredDist(hull[i], hull[j]) < squaredDist(hull[i], hull[(j + 1) % m]))
            j = (j + 1) % m;
        if (squaredDist(hull[i], hull[j]) > maxDist) {
            maxDist = squaredDist(hull[i], hull[j]);
            maxPair = {hull[i], hull[j]};
        }
    }
    return maxPair;
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}, {30, 40}};
    vector<Point> hull = convexHull(points);
    pair<Point, Point> result = farthestPair(hull);

    cout << "Farthest pair: (" << result.first.x << ", " << result.first.y << ") and ("
         << result.second.x << ", " << result.second.y << ")" << endl;
    return 0;
}
