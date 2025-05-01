#include<stdio.h>
#include<stdlib.h>
#include<string.h>

main(){
int i,c,conta=0;
char texto[50];

scanf("%s",texto);
c=strlen(texto);
printf("numero de letras %d",c);

for(i=0;texto[i]!='\0';i++){
    if((texto[i]=='a')||(texto[i]=='A')){
        conta++;}
    }
printf("\nletra a = %d",conta);}
