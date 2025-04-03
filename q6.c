#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct{
    double x;
    double y;
}point;

double pol_ang(point p){
    return atan2(p.y,p.x);
}
void sort(point p[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(pol_ang(p[i])>pol_ang(p[j])){
                double tx=p[i].x,ty=p[i].y;
                p[i].x=p[j].x;p[i].y=p[j].y;
                p[j].x=tx;p[j].y=ty;
            }
        }
    }
}

int main(){
    int n;scanf("%d",&n);
    point p[n];
    for(int i=0;i<n;i++){
        scanf("%lf %lf",&p[i].x,&p[i].y);
    }
    sort(p,n);
    for(int i=0;i<n;i++){
        printf("%lf %lf \n",p[i].x,p[i].y);
    }
}