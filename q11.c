#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

Point p0; // Reference point for sorting

// Swap two points
void swap(Point *p1, Point *p2) {
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Compute squared Euclidean distance (avoiding floating point calculations)
int squaredDist(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Compute orientation
int orientation(Point p,Point q,Point r){
    double or=(p.x-q.x)*(r.y-q.y)-(r.x-q.x)*(p.y-q.y);
    if(or==0) return 0;
    return(or>0)?1:2;
}

// Sorting comparator
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (squaredDist(p0, *p1) < squaredDist(p0, *p2)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

// Compute convex hull using Graham's scan
int convexHull(Point points[], int n, Point hull[]) {
    if (n < 3) return 0;

    // Find bottom-most point
    int minIdx = 0;
    for (int i = 1; i < n; i++)
        if (points[i].y < points[minIdx].y || 
            (points[i].y == points[minIdx].y && points[i].x < points[minIdx].x))
            minIdx = i;
    
    swap(&points[0], &points[minIdx]);
    p0 = points[0];

    // Sort by polar angle
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Remove collinear points
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++; 
        points[m++] = points[i];
    }
    
    // Stack to store convex hull
    int top = 0;
    hull[top++] = points[0];
    hull[top++] = points[1];
    hull[top++] = points[2];

    for (int i = 3; i < m; i++) {
        while (top > 1 && orientation(hull[top - 2], hull[top - 1], points[i]) != 2)
            top--; 
        hull[top++] = points[i];
    }
    return top; // Return number of points in hull
}

// Find the farthest pair using Rotating Calipers
void farthestPair(Point hull[], int h) {
    int maxDist = 0;
    Point p1, p2;

    int j = 1;
    for (int i = 0; i < h; i++) {
        // Move j to maximize distance
        while (squaredDist(hull[i], hull[(j + 1) % h]) > squaredDist(hull[i], hull[j]))
            j = (j + 1) % h;

        if (squaredDist(hull[i], hull[j]) > maxDist) {
            maxDist = squaredDist(hull[i], hull[j]);
            p1 = hull[i];
            p2 = hull[j];
        }
    }

    // Print the farthest pair
    printf("Farthest Pair: (%d, %d) and (%d, %d)\n", p1.x, p1.y, p2.x, p2.y);
}

// Main function
int main() {
    Point points[] = {{0, 0}, {1, 6}, {2, 3}, {5, 1}, {7, 4}, {9, 6}, {8, 9}, {3, 8}};
    int n = sizeof(points) / sizeof(points[0]);

    Point hull[n];
    int h = convexHull(points, n, hull);

    if (h > 1)
        farthestPair(hull, h);
    else
        printf("Farthest pair cannot be determined.\n");

    return 0;
}
