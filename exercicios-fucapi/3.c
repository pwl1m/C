#include<stdio.h>
main(){
int i,n,a,j;

a=0;

printf("digite um numero\n");
scanf("%d",&n);

for (i=0;i<n;i++){
j=0;
    while (j<=i){
    printf("*");
    j++;}
    printf("\n");
}

}
