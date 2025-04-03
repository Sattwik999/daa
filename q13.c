#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x, y;
} Point;

// Function to compare points based on x-coordinate (for sorting)
int compareX(const void* a, const void* b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x == p2->x) ? (p1->y - p2->y) : (p1->x - p2->x);
}

// Function to find orientation
// 0 = collinear, 1 = clockwise, 2 = counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Function to merge two convex hulls
void mergeHulls(Point leftHull[], int leftSize, Point rightHull[], int rightSize, Point mergedHull[], int *mergedSize) {
    int i = leftSize - 1;  // Rightmost point of left hull
    int j = 0;             // Leftmost point of right hull

    // Find upper tangent
    while (1) {
        int updated = 0;
        while (orientation(leftHull[i], rightHull[j], rightHull[(j + 1) % rightSize]) == 2) {
            j = (j + 1) % rightSize;
            updated = 1;
        }
        while (orientation(rightHull[j], leftHull[i], leftHull[(i - 1 + leftSize) % leftSize]) == 1) {
            i = (i - 1 + leftSize) % leftSize;
            updated = 1;
        }
        if (!updated) break;
    }
    int upperI = i, upperJ = j;

    // Find lower tangent
    i = leftSize - 1;
    j = 0;
    while (1) {
        int updated = 0;
        while (orientation(leftHull[i], rightHull[j], rightHull[(j - 1 + rightSize) % rightSize]) == 1) {
            j = (j - 1 + rightSize) % rightSize;
            updated = 1;
        }
        while (orientation(rightHull[j], leftHull[i], leftHull[(i + 1) % leftSize]) == 2) {
            i = (i + 1) % leftSize;
            updated = 1;
        }
        if (!updated) break;
    }
    int lowerI = i, lowerJ = j;

    // Merge points between upper and lower tangents
    *mergedSize = 0;
    i = upperI;
    do {
        mergedHull[(*mergedSize)++] = leftHull[i];
        i = (i + 1) % leftSize;
    } while (i != lowerI);

    j = lowerJ;
    do {
        mergedHull[(*mergedSize)++] = rightHull[j];
        j = (j + 1) % rightSize;
    } while (j != upperJ);
}

// Recursive function to compute convex hull
void convexHullRec(Point points[], int left, int right, Point hull[], int *hullSize) {
    if (right - left + 1 <= 2) { // Base case: If there are 1 or 2 points, return them
        *hullSize = 0;
        for (int i = left; i <= right; i++) {
            hull[(*hullSize)++] = points[i];
        }
        return;
    }

    int mid = (left + right) / 2;

    // Left and right convex hulls
    Point leftHull[right - left + 1], rightHull[right - left + 1];
    int leftSize, rightSize;

    convexHullRec(points, left, mid, leftHull, &leftSize);
    convexHullRec(points, mid + 1, right, rightHull, &rightSize);

    // Merge convex hulls
    mergeHulls(leftHull, leftSize, rightHull, rightSize, hull, hullSize);
}

// Function to compute convex hull using Divide and Conquer
void convexHull(Point points[], int n) {
    qsort(points, n, sizeof(Point), compareX); // Sort points by x-coordinate

    Point hull[n]; // Array to store convex hull points
    int hullSize;

    convexHullRec(points, 0, n - 1, hull, &hullSize);

    // Print convex hull
    printf("Convex Hull Points:\n");
    for (int i = 0; i < hullSize; i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }
}

// Driver function
int main() {
    Point points[] = {{1, 1}, {2, 5}, {3, 3}, {5, 3}, {6, 6}, {7, 2}, {8, 5}, {9, 1}};
    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);

    return 0;
}
