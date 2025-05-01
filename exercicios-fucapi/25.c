#include <stdio.h>
#include <stdlib.h>

main (void){
int M[3][3];
int i,j,dp,ds;

dp= 0; //soma da diag princ
ds= 0; //soma da diag sec

for(i=0;i<3;i++){
  for(j=0;j<3;j++){

   printf("Insira M[%d][%d]:",i,j);
   scanf("%d",&M[i][j]);

if (i==j){
	dp= dp+M[i][j];}

if (i+j==2){
	ds= ds+M[i][j];}
    } //for j
}   //for i
 //Imprimindo as somas:
 printf("\nA soma da diagonal principal e: %d",dp);
 printf("\nA soma da daigonal secundaria e: %d",ds);

 printf("\n");
 printf("\n");
 //Mostrando a matriz:
 for(i=0;i<3;i++){
  for(j=0;j<3;j++){
   printf(" M[%d][%d]= %d \n",i,j,M[i][j]);

}
 }
printf("\n");
 printf("Diagonal Principal\n");
 for(i=0;i<3;i++){
  for(j=0;j<3;j++){
if(i==j){
   printf(" M[%d][%d]= %d \n",i,j,M[i][j]);


}}}
printf("\n");
printf("Diagonal Secundaria\n");
 for(i=0;i<3;i++){
  for(j=0;j<3;j++){
if(i+j==2){
   printf(" M[%d][%d]= %d \n",i,j,M[i][j]);


}}}
printf("\n");

for(i=0;i<3;i++){
  for(j=0;j<3;j++){
do{ printf(" M[%d][%d]= %d \n",i,j,M[i][j]);}
while {(M[i][j]==M[i][j]);}

}}}

