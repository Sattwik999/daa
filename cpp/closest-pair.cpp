#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Compare function for sorting by x-coordinate
bool compareX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

// Compare function for sorting by y-coordinate
bool compareY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

// Function to compute squared distance (avoiding sqrt for efficiency)
int squaredDist(const Point &p1, const Point &p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Brute-force method for small datasets (n <= 3)
pair<Point, Point> bruteForce(vector<Point> &points, int left, int right, int &minDist) {
    pair<Point, Point> minPair;
    minDist = INT_MAX;
    for (int i = left; i < right; i++) {
        for (int j = i + 1; j <= right; j++) {
            int dist = squaredDist(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                minPair = {points[i], points[j]};
            }
        }
    }
    return minPair;
}

// Closest pair in the strip region
pair<Point, Point> closestInStrip(vector<Point> &strip, int size, int minDist) {
    pair<Point, Point> minPair;
    sort(strip.begin(), strip.end(), compareY);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < minDist; j++) {
            int dist = squaredDist(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                minPair = {strip[i], strip[j]};
            }
        }
    }
    return minPair;
}

// Recursive function to find closest pair
pair<Point, Point> closestPairRec(vector<Point> &points, int left, int right, int &minDist) {
    if (right - left + 1 <= 3)
        return bruteForce(points, left, right, minDist);

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    int leftDist, rightDist;
    pair<Point, Point> leftPair = closestPairRec(points, left, mid, leftDist);
    pair<Point, Point> rightPair = closestPairRec(points, mid + 1, right, rightDist);

    if (leftDist < rightDist) {
        minDist = leftDist;
    } else {
        minDist = rightDist;
    }

    pair<Point, Point> minPair = (leftDist < rightDist) ? leftPair : rightPair;

    // Build the strip
    vector<Point> strip;
    for (int i = left; i <= right; i++) {
        if ((points[i].x - midPoint.x) * (points[i].x - midPoint.x) < minDist)
            strip.push_back(points[i]);
    }

    pair<Point, Point> stripPair = closestInStrip(strip, strip.size(), minDist);
    if (!stripPair.first.x && !stripPair.second.x && !stripPair.first.y && !stripPair.second.y)
        return minPair;

    return stripPair;
}

// Main function to find the closest pair of points
pair<Point, Point> closestPair(vector<Point> &points) {
    sort(points.begin(), points.end(), compareX);
    int minDist;
    return closestPairRec(points, 0, points.size() - 1, minDist);
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    pair<Point, Point> result = closestPair(points);
    cout << "Closest pair: (" << result.first.x << ", " << result.first.y << ") and ("
         << result.second.x << ", " << result.second.y << ")" << endl;
    return 0;
}
