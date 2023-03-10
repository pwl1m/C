#include<stdio.h>
//se o indice da linha e igual ao indice da coluna entao o conteudo da posicao recebe i+j
main(){
int mat [5][5];
int i, j;

for (i=0;i<5;i++){
    for(j=0;j<5;j++){

if (mat[i]==mat[j])
    mat[i][j]= i+j;
else mat[i][j]=i*j;
     //       mat[i][j]= i+j;
    printf("%d \t",mat[i][j]);
}
    printf("\n");
}}

/*
if (i==j){
    mat[i][j]= i+j;
    printf("%d \t",mat[i][j]);
}
else mat[i][j]= i*j;{
    printf("%d \t",mat[i][j]);
}
     //       mat[i][j]= i+j;
*/
