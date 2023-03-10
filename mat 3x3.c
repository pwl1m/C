#include<stdio.h>
main(){
int mat [3][3];
int i, j,n;

printf("digite o valor para multiplicar \t");
scanf("%d",&n);

for (i=0;i<3;i++){
    for(j=0;j<3;j++){
        scanf("%d",&mat[i][j]);
        mat[i][j]=mat[i][j]*n;
}}

for (i=0;i<3;i++){
    for(j=0;j<3;j++){
        printf("%d \t",mat[i][j]);
        }
        printf("\n");
        }
}
