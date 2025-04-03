#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x,y;
}point;

typedef struct{
    point p1,p2;
}segment;

int onSegment(point p, point q, point r) {
    if (q.x <= (p.x > r.x ? p.x : r.x) && q.x >= (p.x < r.x ? p.x : r.x) &&
        q.y <= (p.y > r.y ? p.y : r.y) && q.y >= (p.y < r.y ? p.y : r.y))
        return 1;

    return 0;
}
int orientation(point p,point q,point r){
    double or = (p.y-q.y)*(r.x-q.x)-(p.x-q.x)*(r.y-q.y);
    if(or==0) return 0;
    return (or>0)?1:2;
}

int checkintersect(segment s1,segment s2){
    point p1=s1.p1,q1=s1.p2;
    point p2=s2.p1,q2=s2.p2;

    int o1=orientation(p2,q2,p1);
    int o2=orientation(p2,q2,q1);
    int o3=orientation(p1,q1,p2);
    int o4=orientation(p1,q1,q2);

    if(o1!=o2 && o3!=o4){
        return 1;
    }

    if(o1==0 && onSegment(p2,p1,q2)) return 1;
    if(o2==0 && onSegment(p2,q1,q2)) return 1;
    if(o3==0 && onSegment(p1,p2,q1)) return 1;
    if(o4==0 && onSegment(p1,q2,q1)) return 1;

    return 0;
}

void findIntersections(segment segments[], int n) {
    printf("Intersecting Segments:\n");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (checkintersect(segments[i], segments[j])) {
                printf("Segment %d (%.2lf, %.2lf) - (%.2lf, %.2lf) intersects with Segment %d (%.2lf, %.2lf) - (%.2lf, %.2lf)\n",
                       i + 1, segments[i].p1.x, segments[i].p1.y, segments[i].p2.x, segments[i].p2.y,
                       j + 1, segments[j].p1.x, segments[j].p1.y, segments[j].p2.x, segments[j].p2.y);
            }
        }
    }
}

// Main function
int main() {
    int n;
    printf("Enter number of line segments: ");
    scanf("%d", &n);

    segment segments[n];
    printf("Enter segments as x1 y1 x2 y2:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf", &segments[i].p1.x, &segments[i].p1.y,
              &segments[i].p2.x, &segments[i].p2.y);
    }

    findIntersections(segments, n);

    return 0;
}


