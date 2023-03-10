#include<stdio.h>
main(){
int mat [3][3];
int i, j;

for (i=0;i<3;i++){
    for(j=0;j<3;j++){
            mat[i][j]= i+j;
    printf("%d \t",mat[i][j]);
}
    printf("\n");
}
}
