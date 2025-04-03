#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void check(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4){
    double m1=(y2-y1)/(x2-x1);
    double m2=(y4-y3)/(x4-x3);
    if ((x2 - x1 == 0 && y4 - y3 == 0) || (y2 - y1 == 0 && x4 - x3 == 0)) {
        printf("The line segments are perpendicular.\n");
        return;
    }
    if ((x2 - x1 == 0) || (x4 - x3 == 0)) {
        printf("The line segments are not perpendicular.\n");
        return;
    }
    if(m1*m2==-1){
        printf("the lines are perpendiculer");
    }
    else{
        printf("the lines are not perpenediculer");
    }
}
int main() {
    double x1, y1, x2, y2, x3, y3, x4, y4;

    printf("Enter P1 (x1 y1): ");
    scanf("%lf %lf", &x1, &y1);
    
    printf("Enter P2 (x2 y2): ");
    scanf("%lf %lf", &x2, &y2);
    
    printf("Enter P3 (x3 y3): ");
    scanf("%lf %lf", &x3, &y3);
    
    printf("Enter P4 (x4 y4): ");
    scanf("%lf %lf", &x4, &y4);

    check(x1, y1, x2, y2, x3, y3, x4, y4);

    return 0;
}