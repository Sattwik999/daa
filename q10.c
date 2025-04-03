#include <stdio.h>

typedef struct {
    int x, y;
} Point;

// Function to compute the orientation of three points
int orientation(Point p,Point q,Point r){
    double or=(p.x-q.x)*(r.y-q.y)-(r.x-q.x)*(p.y-q.y);
    if(or==0) return 0;
    return(or>0)?1:2;
}

// Function to check if the polygon is convex
void isConvexPolygon(Point points[], int n) {
    if (n < 3) {
        printf("A polygon must have at least 3 vertices.\n");
        return;
    }

    int firstOrientation = 0;  // To store the first nonzero orientation
    for (int i = 0; i < n; i++) {
        // Get three consecutive points (loop back to the start)
        Point p1 = points[i];
        Point p2 = points[(i + 1) % n];
        Point p3 = points[(i + 2) % n];

        int orient = orientation(p1, p2, p3);
        if (orient != 0) { // Ignore collinear points
            if (firstOrientation == 0) {
                firstOrientation = orient; // Store first valid orientation
            } else if (orient != firstOrientation) {
                printf("The polygon is NOT convex.\n");
                return;
            }
        }
    }

    printf("The polygon is convex.\n");
}

// Main function
int main() {
    Point points[] = {{0, 0}, {4, 0}, {4, 4}, {2, 6}, {0, 4}};
    int n = sizeof(points) / sizeof(points[0]);

    isConvexPolygon(points, n);
    return 0;
}
