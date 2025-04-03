#include <stdio.h>
#include <stdlib.h>

void generate(double x1,double y1,double x2,double y2,int n){
    if(n<2){
        return;
    }
    double dx=(x2-x1)/(n-1);
    double dy=(y2-y1)/(n-1);

    for(int i=0;i<n;i++){
        double x=x1+dx*i;
        double y=y1+dy*i;
        printf("%d %d\n",x,y);
    }
}

int main(){
    double x1,y1,x2,y2;
    int n;
    scanf("%lf %lf", &x1, &y1);
    scanf("%lf %lf", &x2, &y2);
    scanf("%d", &n);
    generate(x1, y1, x2, y2, n);
    return 0;
}
