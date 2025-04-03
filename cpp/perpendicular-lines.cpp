#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Function to compute the dot product of two vectors
int dotProduct(int dx1, int dy1, int dx2, int dy2) {
    return dx1 * dx2 + dy1 * dy2;
}

// Function to check if two line segments are perpendicular
bool arePerpendicular(Point p1, Point p2, Point p3, Point p4) {
    int dx1 = p2.x - p1.x;
    int dy1 = p2.y - p1.y;
    int dx2 = p4.x - p3.x;
    int dy2 = p4.y - p3.y;

    return dotProduct(dx1, dy1, dx2, dy2) == 0;
}

int main() {
    Point p1 = {1, 1}, p2 = {4, 1};
    Point p3 = {2, 2}, p4 = {2, 5};

    if (arePerpendicular(p1, p2, p3, p4)) {
        cout << "The line segments are perpendicular." << endl;
    } else {
        cout << "The line segments are not perpendicular." << endl;
    }

    return 0;
}
