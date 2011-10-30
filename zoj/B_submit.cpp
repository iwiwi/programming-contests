#include <stdio.h>
#include <math.h>

main(){
  double v;
  for(;scanf("%lf",&v)>0;){
    printf("%f\n",3.93977310788605405989*pow(v,2.0/3.0));
  }
}
