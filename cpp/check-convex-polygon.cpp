#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Function to check the orientation of three points
int orientation(Point a, Point b, Point c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    return (val > 0) ? 1 : (val < 0 ? -1 : 0);
}

// Function to check if the polygon is convex
bool isConvexPolygon(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return false;

    int prevOrientation = 0;
    for (int i = 0; i < n; i++) {
        int o = orientation(points[i], points[(i + 1) % n], points[(i + 2) % n]);
        if (o != 0) {
            if (prevOrientation == 0) {
                prevOrientation = o;
            } else if (o != prevOrientation) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<Point> points = {{0, 0}, {4, 0}, {4, 3}, {2, 5}, {0, 3}};

    if (isConvexPolygon(points)) {
        cout << "The polygon is convex." << endl;
    } else {
        cout << "The polygon is not convex." << endl;
    }

    return 0;
}
