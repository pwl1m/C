#include<stdio.h>
main(){
int mat [3][3],vet[3],mat2 [3][3];
int i, j;

for (i=0;i<3;i++){      scanf("%d",&vet[i]);        }       printf("\n");
for (i=0;i<3;i++){      printf("%d \t",vet[i]);     }       printf("\n");printf("\n");


for (i=0;i<3;i++){for(j=0;j<3;j++){     scanf("%d",&mat[i][j]);

        mat2[j][i]=mat[i][j]+vet[i];
}}
printf("\n");

for (i=0;i<3;i++){for(j=0;j<3;j++){     printf("%d \t",mat2[i][j]);     }   printf("\n");}
}
