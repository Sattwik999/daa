#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x, y;
} Point;

Point p0; // Global variable to store the bottom-most point

// Function to swap two points
void swap(Point *p1, Point *p2) {
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Function to calculate squared Euclidean distance
int squaredDist(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Function to determine orientation of three points
int orientation(Point p, Point q, Point r) {
    int val = (p.y - q.y) * (r.x - q.x) - (p.x - q.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 2 : 1; // Clockwise or Counterclockwise
}

// Comparator function for sorting points
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (squaredDist(p0, *p1) < squaredDist(p0, *p2)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

// Function to find the convex hull using Graham's scan
void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull not possible with less than 3 points.\n");
        return;
    }

    // Step 1: Find the bottom-most point (or left-most if tie)
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minIdx].y || (points[i].y == points[minIdx].y && points[i].x < points[minIdx].x)) {
            minIdx = i;
        }
    }
    swap(&points[0], &points[minIdx]);
    p0 = points[0];
    
    // Step 2: Sort points based on polar angle with p0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Step 3: Remove collinear points (keeping only the farthest one)
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++; 
        points[m++] = points[i];
    }
    for(int i=0;i<m;i++){
        printf("%d %d\n",points[i].x,points[i].y);
    }
    if (m < 3) {
        printf("Convex hull not possible after removing collinear points.\n");
        return;
    }

    // Step 4: Build convex hull using a stack
    Point stack[m];
    int top = 0;
    stack[top++] = points[0];
    stack[top++] = points[1];
    stack[top++] = points[2];

    for (int i = 3; i < m; i++) {
        while (top > 1 && orientation(stack[top - 2], stack[top - 1], points[i]) != 2)
            top--; 
        stack[top++] = points[i];
    }

    // Print convex hull points
    printf("Convex Hull:\n");
    for (int i = 0; i < top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

// Main function
int main() {
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {3, 1}, {4, 3}, {2, 4}

};
    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);
    return 0;
}
