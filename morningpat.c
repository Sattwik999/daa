#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

// Function to compute orientation (clockwise, counterclockwise, collinear)
int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : -1; // Clockwise or Counterclockwise
}

// Function to check if point 'p' lies on segment 'pq'
int isOnSegment(Point p, Point q, Point r) {
    return (r.x >= fmin(p.x, q.x) && r.x <= fmax(p.x, q.x) &&
            r.y >= fmin(p.y, q.y) && r.y <= fmax(p.y, q.y));
}

// Function to find intersection of two line segments
int findIntersection(Point p1, Point p2, Point p3, Point p4, Point *intersection) {
    double denominator = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

    if (denominator == 0) return 0; // Parallel or coincident

    intersection->x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) / denominator;
    intersection->y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) / denominator;

    // Check if intersection lies on both line segments
    if (isOnSegment(p1, p2, *intersection) && isOnSegment(p3, p4, *intersection))
        return 1;

    return 0;
}
int isInsidePentagon(Point pentagon[], Point testPoint) {
    int firstOrientation = orientation(pentagon[0], pentagon[1], testPoint);
    
    // Check orientation with all sides
    for (int i = 1; i < 5; i++) {
        int nextOrientation = orientation(pentagon[i], pentagon[(i + 1) % 5], testPoint);
        if (nextOrientation != firstOrientation && nextOrientation != 0) {
            return 0; // Outside the pentagon
        }
    }
    return 1; // Inside the pentagon
}
// Function to check if a point is inside a pentagon using the ray-casting method
// int isInsidePentagon(Point pentagon[], Point p) {
//     int count = 0;
//     Point extreme = {10000, p.y}; // A point outside the pentagon for ray-casting
//     for (int i = 0; i < 5; i++) {
//         Point a = pentagon[i];
//         Point b = pentagon[(i + 1) % 5];

//         Point intersection;
//         if (findIntersection(a, b, p, extreme, &intersection)) {
//             count++;
//         }
//     }
//     return (count % 2 == 1); // Odd count means inside
// }

// Main function
int main() {
    // Define pentagon vertices
    Point pentagon[5] = {
        {1, 1}, {5, 2}, {6, 5}, {3, 7}, {0, 5}
    };

    // Define two line segments
    Point A = {2, 2}, B = {6, 6};
    Point C = {4, 0}, D = {4, 8};
    Point intersection;

    // Find intersection
    if (findIntersection(A, B, C, D, &intersection)) {
        printf("Intersection at: (%.2f, %.2f)\n", intersection.x, intersection.y);

        // Check if the intersection is inside the pentagon
        if (isInsidePentagon(pentagon, intersection)) {
            printf("Intersection point is inside the pentagon.\n");
        } else {
            printf("Intersection point is outside the pentagon.\n");
        }
    } else {
        printf("No intersection (parallel or non-overlapping segments).\n");
    }

    return 0;
}
