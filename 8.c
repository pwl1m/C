#include <stdlib.h>
#include <string.h>
#include <ctype.h>
main(){
int j, l;
char strNome[100], strSegundo[100];
char i=0, k=0;

printf("Informe a 1a string: ");
gets(strNome);
printf("Informe a 2a string: ");
gets(strSegundo);

for(j=0, l=0; j<strlen(strNome)+ strlen(strSegundo), l<strlen(strSegundo); j++, l++){
k = strSegundo[l];
i = strNome[j];
printf("%c", i);
printf("%c", k);
}
printf("\n\n");
}
