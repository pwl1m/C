#include<stdio.h>
#include<stdlib.h>
#include<string.h>
main(){
int i,c,conta=0,contc=0;
char v[50];

scanf("%s",v);
c=strlen(v);
printf("numero de letras %d",c);

for(i=0;v[i]!='\0';i++){
    if((v[i]=='a')||(v[i]=='A')||(v[i]=='e')||(v[i]=='E')||(v[i]=='I')||(v[i]=='i')||(v[i]=='o')||(v[i]=='O')||(v[i]=='u')||(v[i]=='U')){
        conta++;}
    if((v[i]=='b')||(v[i]=='c')||(v[i]=='d')||(v[i]=='f')||(v[i]=='g')||(v[i]=='h')||
       (v[i]=='j')||(v[i]=='l')||(v[i]=='m')||(v[i]=='n')||(v[i]=='p')||(v[i]=='q')||
       (v[i]=='r')||(v[i]=='s')||(v[i]=='t')||(v[i]=='v')||(v[i]=='x')||(v[i]=='z')){
        contc++;}
}
printf("\n vogais = %d",conta);
printf("\n consoantes = %d",contc);
}
