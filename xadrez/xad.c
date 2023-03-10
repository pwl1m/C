#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#define LINHA 3
#define COLUNA 3
#define PLAYER 1
#define CPU 2
void atualiza_jogo(void);
int atualiza_tabuleiro(int x, int y);
void jogada_cpu(void);
void jogada_player(void);
char vencedor(void);
void jogada(int a);
void jogada_cantos(int c);
int defesa(void);
int ataque(void);
int y,jogador,cont_jogadas=0,escolha;
char tabuleiro[LINHA][COLUNA]={' ',' ',' ',' ',' ',' ',' ',' ',' '},coluna,x;
void atualiza_jogo(){
 system("cls");
 printf("Jogo da Velha inteligente \n\n");
 printf(" A B C\n\n");
 printf("1 %c | %c | %c \n",tabuleiro[0][0],tabuleiro[0][1],tabuleiro[0][2]);
 printf(" --- --- ---\n");  printf("2 %c | %c | %c \n",tabuleiro[1][0],tabuleiro[1][1],tabuleiro[1][2]);
 printf(" --- --- ---\n");
 printf("3 %c | %c | %c \n\n\n",tabuleiro[2][0],tabuleiro[2][1],tabuleiro[2][2]);
}
int atualiza_tabuleiro(int x,int y){
 if(jogador == PLAYER){
 tabuleiro[x][y] = 'x';
 jogador = CPU;
 return 0;
 }
 if(jogador == CPU){
 if(tabuleiro[x][y] != ' ') return 1;
 else{
 tabuleiro[x][y] = 'o';
 jogador = PLAYER;
 return 0;
 }
 }
}
void jogada_player(){
 printf("\nPlayer 1\n");
 printf("Coluna: ");
 scanf("%s",&x);
 printf("Linha: ");
 scanf("%d",&y);
 y--;  if(x=='A'||x=='a') coluna=0;
 if(x=='B'||x=='b') coluna=1;
 if(x=='C'||x=='c') coluna=2;
 if (tabuleiro[y][coluna] != ' ') {
 printf("\nJogada inválida.\n");
 jogada_player();
 }
 else atualiza_tabuleiro(y,coluna);
}
void jogada_cpu(){
 int c;
 if(cont_jogadas == 2){
 if(tabuleiro[1][1] != ' '){
 srand(time(NULL));
 c = rand()%3;
 jogada_cantos(c);
 return;
 }
 if(tabuleiro[0][0] != ' ' || tabuleiro[0][1] != ' ' || tabuleiro[0][2] != ' ' ||
 tabuleiro[1][0] != ' ' || tabuleiro[1][2] != ' ' ||
 tabuleiro[2][0] != ' ' || tabuleiro[2][1] != ' ' || tabuleiro[2][2] != ' '){
 atualiza_tabuleiro(1,1);
 return;
 }  }
 if (!ataque() || !defesa()) return;
 else{
 while(1) {
 x = rand() % 3;
 y = rand() % 3;
 if (!atualiza_tabuleiro(x,y)) return;
 }
 }
}
void jogada_cantos(int a){
 switch (a){
 case 0:
 atualiza_tabuleiro(0,0);
 break;
 case 1:
 atualiza_tabuleiro(0,2);
 break;
 case 2:
 atualiza_tabuleiro(2,0);
 break;
 case 3:
 atualiza_tabuleiro(2,2);
 break;
 }
} int defesa(){
 int i;
 //estratégias de defesa
 for (i = 0; i < 3; i++) {
 //linhas
 if (tabuleiro[i][0] == 'x' && tabuleiro[i][2] == 'x')
 if (!atualiza_tabuleiro(i, 1)) return 0;
 if (tabuleiro[i][0] == 'x' && tabuleiro[i][1] == 'x')
 if (!atualiza_tabuleiro(i, 2)) return 0;
 if (tabuleiro[i][1] == 'x' && tabuleiro[i][2] == 'x')
 if (!atualiza_tabuleiro(i, 0)) return 0;
 //colunas
 if (tabuleiro[0][i] == 'x' && tabuleiro[2][i] == 'x')
 if (!atualiza_tabuleiro(1, i)) return 0;
 if (tabuleiro[0][i] == 'x' && tabuleiro[1][i] == 'x')
 if (!atualiza_tabuleiro(2, i)) return 0;
 if (tabuleiro[1][i] == 'x' && tabuleiro[2][i] == 'x')
 if (!atualiza_tabuleiro(0, i)) return 0;
 }
 //para as diagonais
 if (tabuleiro[0][0] == 'x' && tabuleiro[2][2] == 'x')
 if (!atualiza_tabuleiro(1, 1)) return 0;
 if (tabuleiro[0][2] == 'x' && tabuleiro[2][0] == 'x')
 if (!atualiza_tabuleiro(1, 1)) return 0;
 if (tabuleiro[0][2] == 'x' && tabuleiro[1][1] == 'x')
 if (!atualiza_tabuleiro(2, 0)) return 0;
 if (tabuleiro[2][2] == 'x' && tabuleiro[1][1] == 'x')
 if (!atualiza_tabuleiro(0, 0)) return 0;
 if (tabuleiro[2][0] == 'x' && tabuleiro[1][1] == 'x')  if (!atualiza_tabuleiro(0, 2)) return 0;
 if (tabuleiro[0][0] == 'x' && tabuleiro[1][1] == 'x')
 if (!atualiza_tabuleiro(2, 2)) return 0;
 //triangulacao
 if (tabuleiro[0][0] == 'x' && tabuleiro[1][2] || tabuleiro[0][2] == 'x' && tabuleiro[1][0])
 if (!atualiza_tabuleiro(2, 1)) return 0;
 if (tabuleiro[2][0] == 'x' && tabuleiro[1][2] || tabuleiro[2][2] == 'x' && tabuleiro[1][0])
 if (!atualiza_tabuleiro(0, 1)) return 0;
 if (tabuleiro[2][0] == 'x' && tabuleiro[0][1] || tabuleiro[2][2] == 'x' && tabuleiro[0][1])
 if (!atualiza_tabuleiro(1, 0)) return 0;
 if (tabuleiro[1][0] == 'x' && tabuleiro[2][1] || tabuleiro[0][2] == 'x' && tabuleiro[2][1])
 if (!atualiza_tabuleiro(1, 2)) return 0;
 if ((tabuleiro[2][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[1][0] == 'x' &&
tabuleiro[1][1] == 'x'))
 if (!atualiza_tabuleiro(2, 0) || !atualiza_tabuleiro(0, 2)) return 0;
 if ((tabuleiro[0][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[2][0] == 'x' &&
tabuleiro[1][1] == 'x'))
 if (!atualiza_tabuleiro(0, 0) || !atualiza_tabuleiro(2, 2)) return 0;
 // outras jogadas perigosas :p
 if (tabuleiro[2][1] == 'x' && tabuleiro[1][2] == 'x')
 if (!atualiza_tabuleiro(2, 2)) return 0;
 if (tabuleiro[2][1] == 'x' && tabuleiro[1][0] == 'x')
 if (!atualiza_tabuleiro(2, 0)) return 0;
 if (tabuleiro[1][0] == 'x' && tabuleiro[0][1] == 'x')
 if (!atualiza_tabuleiro(0, 0)) return 0;
 if (tabuleiro[0][1] == 'x' && tabuleiro[1][2] == 'x')
 if (!atualiza_tabuleiro(0, 2)) return 0;  return 1;
}
int ataque(){
 int j;
 for (j = 0; j < 3; j++) {
 //linhas
 if (tabuleiro[j][0] == 'o' && tabuleiro[j][2] == 'o')
 if (!atualiza_tabuleiro(j, 1)) return 0;
 if (tabuleiro[j][0] == 'o' && tabuleiro[j][1] == 'o')
 if (!atualiza_tabuleiro(j, 2)) return 0;
 if (tabuleiro[j][1] == 'o' && tabuleiro[j][2] == 'o')
 if (!atualiza_tabuleiro(j, 0)) return 0;
 //colunas
 if (tabuleiro[0][j] == 'o' && tabuleiro[2][j] == 'o')
 if (!atualiza_tabuleiro(1, j)) return 0;
 if (tabuleiro[0][j] == 'o' && tabuleiro[1][j] == 'o')
 if (!atualiza_tabuleiro(2, j)) return 0;
 if (tabuleiro[1][j] == 'o' && tabuleiro[2][j] == 'o')
 if (!atualiza_tabuleiro(0, j)) return 0;
 }
 //para as diagonais
 if (tabuleiro[0][0] == 'o' && tabuleiro[2][2] == 'o')
 if (!atualiza_tabuleiro(1, 1)) return 0;
 if (tabuleiro[0][2] == 'o' && tabuleiro[2][0] == 'o')
 if (!atualiza_tabuleiro(1, 1)) return 0;
 if (tabuleiro[0][2] == 'o' && tabuleiro[1][1] == 'o'){
 if (!atualiza_tabuleiro(2, 0)) return 0;  }
 if (tabuleiro[2][2] == 'o' && tabuleiro[1][1] == 'o')
 if (!atualiza_tabuleiro(0, 0)) return 0;
 if (tabuleiro[2][0] == 'o' && tabuleiro[1][1] == 'o')
 if (!atualiza_tabuleiro(0, 2)) return 0;
 if (tabuleiro[0][0] == 'o' && tabuleiro[1][1] == 'o')
 if (!atualiza_tabuleiro(2, 2)) return 0;
 if ((tabuleiro[2][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[1][0] == 'x' &&
tabuleiro[1][1] == 'x'))
 if (!atualiza_tabuleiro(2, 0) || !atualiza_tabuleiro(0, 2)) return 0;
 if ((tabuleiro[0][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[2][0] == 'x' &&
tabuleiro[1][1] == 'x'))
 if (!atualiza_tabuleiro(0, 0) || !atualiza_tabuleiro(2, 2)) return 0;
 // outras jogadas perigosas :p
 if (tabuleiro[2][1] == 'x' && tabuleiro[1][2] == 'x')
 if (!atualiza_tabuleiro(2, 2)) return 0;
 if (tabuleiro[2][1] == 'x' && tabuleiro[1][0] == 'x')
 if (!atualiza_tabuleiro(2, 0)) return 0;
 if (tabuleiro[1][0] == 'x' && tabuleiro[0][1] == 'x')
 if (!atualiza_tabuleiro(0, 0)) return 0;
 if (tabuleiro[0][1] == 'x' && tabuleiro[1][2] == 'x')
 if (!atualiza_tabuleiro(0, 2)) return 0;
 return 1;
}
char vencedor(){
 int i;  char a = (jogador == CPU) ? 'x' : 'o';
 for (i = 0; i < 3; i++)
 if (tabuleiro[i][0] == a && tabuleiro[i][1] == a && tabuleiro[i][2] == a) return a;
 for (i = 0; i < 3; i++)
 if (tabuleiro[0][i] == a && tabuleiro[1][i] == a && tabuleiro[2][i] == a) return a;
 if (tabuleiro[2][0] == a && tabuleiro[1][1] == a && tabuleiro[0][2] == a) return a;
 if (tabuleiro[0][0] == a && tabuleiro[1][1] == a && tabuleiro[2][2] == a) return a;
 return 'c';
}
void limpa(){
int i,j;
 for(i=0;i<3;i++){
 for(j=0;j<3;j++){
 tabuleiro[i][j]=' ';
 }
 }
 system("cls");
}
void main(){
char status;
jogador = PLAYER;
do{
 limpa();
 jogador = PLAYER;
while(1){
 if(jogador == PLAYER){  atualiza_jogo();
 jogada_player();
 status = vencedor();
 cont_jogadas++;
 if (status == 'x')
 break;
 }
 if(jogador == CPU){
 atualiza_jogo();
 jogada_cpu();
 status = vencedor();
 cont_jogadas++;
 if (status == 'o')
 break;
 }
 if(cont_jogadas==8){
 break;
 }
}
 atualiza_jogo();
 if (status=='x') printf("Player 1 Venceu\n");
 else if (status=='o') printf("CPU Venceu\n");
 else printf("\nVelhou\n");
 printf("\nJogar Denovo?\n");
 printf("1-SIM | 2-NAO :");
 scanf("%d", &escolha);
}while(escolha!=2);
}
