#include <stdio.h>
#include <stdlib.h>

void check_parallel(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4){
    double check=(x2-x1)*(y4-y3)-(y2-y1)*(x4-x3);
    if(check==0){
        printf("Its Parallel");
    }
    else return;
}
int main(){
    double x1,x2,x3,x4,y1,y2,y3,y4;
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
    check_parallel(x1,y1,x2,y2,x3,y3,x4,y4);
}