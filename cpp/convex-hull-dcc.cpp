#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Cross product to check orientation
int crossProduct(Point A, Point B, Point C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

// Sorting comparator for x-coordinates
bool compareX(Point p1, Point p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}

// Merge two convex hulls
vector<Point> mergeHulls(vector<Point> &leftHull, vector<Point> &rightHull) {
    int n1 = leftHull.size(), n2 = rightHull.size();

    // Find upper tangent
    int i = n1 - 1, j = 0;
    bool found = false;
    while (!found) {
        found = true;
        while (crossProduct(leftHull[i], rightHull[j], rightHull[(j + 1) % n2]) > 0)
            j = (j + 1) % n2, found = false;
        while (crossProduct(rightHull[j], leftHull[i], leftHull[(i - 1 + n1) % n1]) < 0)
            i = (i - 1 + n1) % n1, found = false;
    }
    int upperI = i, upperJ = j;

    // Find lower tangent
    i = n1 - 1, j = 0;
    found = false;
    while (!found) {
        found = true;
        while (crossProduct(leftHull[i], rightHull[j], rightHull[(j - 1 + n2) % n2]) < 0)
            j = (j - 1 + n2) % n2, found = false;
        while (crossProduct(rightHull[j], leftHull[i], leftHull[(i + 1) % n1]) > 0)
            i = (i + 1) % n1, found = false;
    }
    int lowerI = i, lowerJ = j;

    // Merge convex hulls
    vector<Point> mergedHull;
    for (int idx = upperI; idx != lowerI; idx = (idx + 1) % n1)
        mergedHull.push_back(leftHull[idx]);
    mergedHull.push_back(leftHull[lowerI]);
    for (int idx = lowerJ; idx != upperJ; idx = (idx + 1) % n2)
        mergedHull.push_back(rightHull[idx]);
    mergedHull.push_back(rightHull[upperJ]);

    return mergedHull;
}

// Divide and Conquer Convex Hull
vector<Point> convexHullDC(vector<Point> &points, int left, int right) {
    if (right - left + 1 <= 3) { // Base case
        vector<Point> baseHull;
        for (int i = left; i <= right; i++)
            baseHull.push_back(points[i]);
        sort(baseHull.begin(), baseHull.end(), compareX);
        return baseHull;
    }

    int mid = left + (right - left) / 2;
    vector<Point> leftHull = convexHullDC(points, left, mid);
    vector<Point> rightHull = convexHullDC(points, mid + 1, right);
    return mergeHulls(leftHull, rightHull);
}

vector<Point> convexHull(vector<Point> &points) {
    sort(points.begin(), points.end(), compareX);
    return convexHullDC(points, 0, points.size() - 1);
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}, {30, 40}, {35, 45}, {25, 25}};
    vector<Point> hull = convexHull(points);

    cout << "Convex Hull Points:\n";
    for (auto p : hull)
        cout << "(" << p.x << ", " << p.y << ")\n";
    return 0;
}
