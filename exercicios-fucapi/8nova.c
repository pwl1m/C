#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define strlen 200
main(){
char c[strlen];
char a[strlen];
char b[strlen];

printf("Digite uma palavra: ");
gets(a);

printf("Digite uma palavra: ");
gets(b);

c=strcat(a,b);

printf("%s",c)

}
