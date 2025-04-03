#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Function to check if two segments (p1p2 and p3p4) intersect
bool doIntersect(Point p1, Point p2, Point p3, Point p4) {
    auto orientation = [](Point a, Point b, Point c) {
        int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        return (val > 0) ? 1 : (val < 0 ? -1 : 0);
    };

    int o1 = orientation(p1, p2, p3);
    int o2 = orientation(p1, p2, p4);
    int o3 = orientation(p3, p4, p1);
    int o4 = orientation(p3, p4, p2);

    if (o1 != o2 && o3 != o4) return true;
    return false;
}

// Function to check if given points form a simple polygon
bool isSimplePolygon(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return false;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (j == (i + 1) % n || j == (i - 1 + n) % n) continue;
            if (doIntersect(points[i], points[(i + 1) % n], points[j], points[(j + 1) % n])) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<Point> points = {{0, 0}, {4, 0}, {4, 3}, {2, 5}, {0, 3}};

    if (isSimplePolygon(points)) {
        cout << "The points form a simple polygon." << endl;
    } else {
        cout << "The points do not form a simple polygon." << endl;
    }

    return 0;
}
