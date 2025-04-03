#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Function to compute the greatest common divisor (GCD)
int gcd(int a, int b) {
    return (b == 0) ? abs(a) : gcd(b, a % b);
}

// Function to find and print collinear points
void findCollinearPoints(vector<Point>& points) {
    int n = points.size();

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int dx1 = points[j].x - points[i].x;
            int dy1 = points[j].y - points[i].y;
            int g1 = gcd(dx1, dy1);
            dx1 /= g1;
            dy1 /= g1;

            cout << "Collinear set: (" << points[i].x << ", " << points[i].y << ") (" << points[j].x << ", " << points[j].y << ")";

            for (int k = j + 1; k < n; k++) {
                int dx2 = points[k].x - points[i].x;
                int dy2 = points[k].y - points[i].y;
                int g2 = gcd(dx2, dy2);
                dx2 /= g2;
                dy2 /= g2;

                if (dx1 == dx2 && dy1 == dy2) {
                    cout << " (" << points[k].x << ", " << points[k].y << ")";
                }
            }
            cout << endl;
        }
    }
}

int main() {
    vector<Point> points = {{1, 1}, {2, 2}, {3, 3}, {4, 5}, {5, 6}, {7, 8}, {8, 9}};
    findCollinearPoints(points);
    return 0;
}
