#include <stdio.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point p1, p2;
} Segment;

// Function to check the orientation of three points
int orientation(Point p,Point q,Point r){
    double or=(p.x-q.x)*(r.y-q.y)-(r.x-q.x)*(p.y-q.y);
    if(or==0) return 0;
    return(or>0)?1:2;
}

// Function to check if point q lies on segment pr
int onSegment(Point p, Point q, Point r) {
    if (q.x <= (p.x > r.x ? p.x : r.x) && q.x >= (p.x < r.x ? p.x : r.x) &&
        q.y <= (p.y > r.y ? p.y : r.y) && q.y >= (p.y < r.y ? p.y : r.y))
        return 1;
    return 0;
}

// Function to check if two segments intersect
int doIntersect(Segment s1, Segment s2) {
    Point p1 = s1.p1, q1 = s1.p2;
    Point p2 = s2.p1, q2 = s2.p2;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case: If orientations differ, the segments intersect
    if (o1 != o2 && o3 != o4)
        return 1;

    // Special cases: Checking collinearity and overlap
    if (o1 == 0 && onSegment(p1, p2, q1)) return 1;
    if (o2 == 0 && onSegment(p1, q2, q1)) return 1;
    if (o3 == 0 && onSegment(p2, p1, q2)) return 1;
    if (o4 == 0 && onSegment(p2, q1, q2)) return 1;

    return 0;
}

// Function to check if a polygon is simple
void isSimplePolygon(Point points[], int n) {
    if (n < 3) {
        printf("A polygon cannot be formed with less than 3 points.\n");
        return;
    }

    // Create all edges of the polygon
    Segment segments[n];
    for (int i = 0; i < n - 1; i++) {
        segments[i].p1 = points[i];
        segments[i].p2 = points[i + 1];
    }
    // Closing edge
    segments[n - 1].p1 = points[n - 1];
    segments[n - 1].p2 = points[0];

    // Check for intersection between non-adjacent edges
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (j != i + 1 && !(i == 0 && j == n - 1)) { // Skip adjacent edges
                if (doIntersect(segments[i], segments[j])) {
                    printf("Not a simple polygon. Intersecting edges found.\n");
                    return;
                }
            }
        }
    }

    printf("The given points form a simple polygon.\n");
}

// Main function
int main() {
    Point points[] = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    int n = sizeof(points) / sizeof(points[0]);

    isSimplePolygon(points, n);
    return 0;
}
