#include <stdio.h>
#include <stdlib.h>

void clockwise_check(double x1,double y1,double x2,double y2,double qx,double qy){
    double px=(x2-x1);
    double py=(y2-y1);

    double xq=(qx-x1);
    double yq=(qy-y1);

    double cross_prod=px*yq-py*xq;
    if(cross_prod<0){
        printf("Yes it is clockwise.");
    }
    else if(cross_prod==0){
        printf("Lies on the same line");
    }
    else{
        printf("Its Clockwise");
    }
}

int main(){
    double x1, y1, x2, y2, xq, yq;

    printf("Enter P1 (x1 y1): ");
    scanf("%lf %lf", &x1, &y1);
    printf("Enter P2 (x2 y2): ");
    scanf("%lf %lf", &x2, &y2);
    printf("Enter Q (xq yq): ");
    scanf("%lf %lf", &xq, &yq);

    clockwise_check(x1, y1, x2, y2, xq, yq);

    return 0;
}