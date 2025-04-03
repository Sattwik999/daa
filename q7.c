#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void check_triangle(double x1,double y1,double x2,double y2,double x3,double y3){
    double area = (double) (x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2))/2;
    if(area !=0){
        printf("They are forming a triangle");
    }
    else{
        printf("Nope babe");
    }
    printf("%lf\n",fabs(area));
}

int main(){
    double x1,x2,x3,y1,y2,y3;
    scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3);
    check_triangle(x1,y1,x2,y2,x3,y3);
}