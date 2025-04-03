#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For INT_MAX

typedef struct {
    int x, y;
} Point;

// Compare function to sort points by X coordinate
int compareX(const void* a, const void* b) {
    return ((Point*)a)->x - ((Point*)b)->x;
}

// Compare function to sort points by Y coordinate
int compareY(const void* a, const void* b) {
    return ((Point*)a)->y - ((Point*)b)->y;
}

// Squared Euclidean Distance (avoiding square root)
int squaredDistance(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Brute Force for small number of points
int bruteForce(Point points[], int n, Point *p1, Point *p2) {
    int minDist = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = squaredDistance(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                *p1 = points[i];
                *p2 = points[j];
            }
        }
    }
    return minDist;
}

// Function to find the minimum distance in the strip
int stripClosest(Point strip[], int size, int d, Point *p1, Point *p2) {
    int minDist = d;
    
    // Sort strip points by Y-coordinate
    qsort(strip, size, sizeof(Point), compareY);

    // Compare each point with next 7 neighbors (theoretical bound)
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < minDist; j++) {
            int dist = squaredDistance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                *p1 = strip[i];
                *p2 = strip[j];
            }
        }
    }
    return minDist;
}

// Recursive function to find closest pair
int closestPairRecursive(Point points[], int n, Point *p1, Point *p2) {
    // If small number of points, use brute force
    if (n <= 3) {
        return bruteForce(points, n, p1, p2);
    }

    // Divide the set into two halves
    int mid = n / 2;
    Point midPoint = points[mid];

    // Recursively find closest pairs in left and right halves
    Point leftP1, leftP2, rightP1, rightP2;
    int dLeft = closestPairRecursive(points, mid, &leftP1, &leftP2);
    int dRight = closestPairRecursive(points + mid, n - mid, &rightP1, &rightP2);

    // Find minimum distance from both halves
    int d = dLeft < dRight ? dLeft : dRight;
    *p1 = (dLeft < dRight) ? leftP1 : rightP1;
    *p2 = (dLeft < dRight) ? leftP2 : rightP2;

    // Create a strip containing points within distance d from mid line
    Point strip[n];
    int stripSize = 0;
    for (int i = 0; i < n; i++) {
        if ((points[i].x - midPoint.x) * (points[i].x - midPoint.x) < d) {
            strip[stripSize++] = points[i];
        }
    }

    // Find the closest pair in the strip
    Point stripP1, stripP2;
    int dStrip = stripClosest(strip, stripSize, d, &stripP1, &stripP2);
    
    // Choose the smallest distance
    if (dStrip < d) {
        *p1 = stripP1;
        *p2 = stripP2;
        d = dStrip;
    }

    return d;
}

// Main function to find closest pair
void closestPair(Point points[], int n) {
    // Sort points by X-coordinate
    qsort(points, n, sizeof(Point), compareX);

    Point p1, p2;
    int minDist = closestPairRecursive(points, n, &p1, &p2);

    printf("Closest pair: (%d, %d) and (%d, %d)\n", p1.x, p1.y, p2.x, p2.y);
    printf("Squared Minimum Distance: %d\n", minDist);
}

// Driver Code
int main() {
    Point points[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(points) / sizeof(points[0]);

    closestPair(points, n);

    return 0;
}
