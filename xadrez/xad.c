// Importação de bibliotecas
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

// Define as variáveis estáticas
#define LINHA 3
#define COLUNA 3
#define PLAYER 1
#define CPU 2

// declaração do 'protótipo' das funções utulizadas
// lembrando que void, char ou int é o tipo de dado que será retornado
void atualiza_jogo(void);
int atualiza_tabuleiro(int x, int y);
void jogada_cpu(void);
void jogada_player(void);
char vencedor(void);
void jogada(int a);
void jogada_cantos(int c);
int defesa(void);
int ataque(void);


// declaração de variáveis
int y,jogador,cont_jogadas=0;
char tabuleiro[LINHA][COLUNA]={' ',' ',' ',' ',' ',' ',' ',' ',' '},coluna,x;


// programa
// função main
void main(){
    // variável status servirá para saber se há vencedor (player ou cpu) ou se o jogo empatou ('velhou')
    char status;
    // inicio o jogo com jogada do player
    jogador = PLAYER;

    while(1){
        if(jogador == PLAYER){
            cont_jogadas++;
            atualiza_jogo();
            jogada_player();
            status = vencedor();
            if (status == 'x')
                break;
        }
        if(jogador == CPU){
            cont_jogadas++;
            jogada_cpu();
            status = vencedor();
            if (status == 'o') break;
        }
        if(cont_jogadas==8) break;
    }

    atualiza_jogo();

    if (status == 'x')
        printf("Player 1 Venceu :)\n");
    else if (status == 'o')
        printf("CPU Venceu :)\n");
    else
        printf("\nVELHOU!\n");

    getch();
}

// função que serve para atualizar a tela com a última jogada
void atualiza_jogo(){

    system("cls");
    printf("Jogo da Velha inteligente \n\n");
    printf("    A   B   C\n\n");
    printf("1   %c | %c | %c \n",tabuleiro[0][0],tabuleiro[0][1],tabuleiro[0][2]);
    printf("   --- --- ---\n");
    printf("2   %c | %c | %c \n",tabuleiro[1][0],tabuleiro[1][1],tabuleiro[1][2]);
    printf("   --- --- ---\n");
    printf("3   %c | %c | %c \n\n\n",tabuleiro[2][0],tabuleiro[2][1],tabuleiro[2][2]);
}

// função que servirá para atualizar um campo, no tabuleiro, com o valor de 'x' para o player e com 'o' para a cpu
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
// função que sinaliza a jogada do player
void jogada_player(){

    printf("\nPlayer 1\n");
    printf("Coluna: ");
    scanf("%s",&x);
    printf("Linha: ");
    scanf("%d",&y);
    y--;

    if(x=='A'||x=='a') coluna=0;
    if(x=='B'||x=='b') coluna=1;
    if(x=='C'||x=='c') coluna=2;


    if (tabuleiro[y][coluna] != ' ') {
        printf("\nJogada inválida.\n");
        jogada_player();
    }
    else atualiza_tabuleiro(y,coluna);
}

// função que sinaliza a jogada da cpu
void jogada_cpu(){

    int c;
    //se primeira jogada é no centro, coloca 'o' em um dos cantos
    // contador está sinalizando 2 pq é incrementado a cada jogada, nesse caso, a primeira jogada é sempre do player, logo, a segunda será da cpu

    if(cont_jogadas == 2){
        if(tabuleiro[1][1] != ' '){
            srand(time(NULL));
            c = rand()%3;
            jogada_cantos(c);
            return;
        }
    //se primeira jogada é em um dos cantos, coloca 'o' no meio
    //basicamente isso foi feito para defesa - 'velhar' o jogo, caso a cpu não ganhe
        if(tabuleiro[0][0] != ' ' || tabuleiro[0][1] != ' ' || tabuleiro[0][2] != ' ' ||
           tabuleiro[1][0] != ' ' || tabuleiro[1][2] != ' ' ||
           tabuleiro[2][0] != ' ' || tabuleiro[2][1] != ' ' || tabuleiro[2][2] != ' '){
              atualiza_tabuleiro(1,1);
              return;
        }
    }
    //a cada jogada da cpu, testo a lógica para defender e atacar. Caso não se encaixe em nenhuma jogada pré-definida, joga aleatoriamente
    if (!ataque() || !defesa()) return;
    else{
        while(1) {
            x = rand() % 3;
            y = rand() % 3;
            if (!atualiza_tabuleiro(x,y)) return;
        }
    }
}


// função que sinaliza jogada nos cantos do tabuleiro, para defesa e ataque
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

}
// função que sinaliza a lógica para defender o jogo da cpu contra o player
int defesa(){

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
    if (tabuleiro[2][0] == 'x' && tabuleiro[1][1] == 'x')
        if (!atualiza_tabuleiro(0, 2)) return 0;
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

    // aqui algumas estratégias de defesa - é preferível defender que atacar e ficar vulnerável
    if ((tabuleiro[2][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[1][0] == 'x' && tabuleiro[1][1] == 'x'))
        if (!atualiza_tabuleiro(2, 0) || !atualiza_tabuleiro(0, 2)) return 0;
    if ((tabuleiro[0][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[2][0] == 'x' && tabuleiro[1][1] == 'x'))
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

// função que sinaliza a lógica para defender o atacar o jogo do player
int ataque(){

    int j;
    //estratégias de ataque
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
        if (!atualiza_tabuleiro(2, 0)) return 0;
    }

    if (tabuleiro[2][2] == 'o' && tabuleiro[1][1] == 'o')
        if (!atualiza_tabuleiro(0, 0)) return 0;
    if (tabuleiro[2][0] == 'o' && tabuleiro[1][1] == 'o')
        if (!atualiza_tabuleiro(0, 2)) return 0;
    if (tabuleiro[0][0] == 'o' && tabuleiro[1][1] == 'o')
        if (!atualiza_tabuleiro(2, 2)) return 0;

     // aqui algumas estratégias de defesa - é preferível defender que atacar e ficar vulnerável
    if ((tabuleiro[2][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[1][0] == 'x' && tabuleiro[1][1] == 'x'))
        if (!atualiza_tabuleiro(2, 0) || !atualiza_tabuleiro(0, 2)) return 0;
    if ((tabuleiro[0][2] == 'x' && tabuleiro[1][1] == 'x') || (tabuleiro[2][0] == 'x' && tabuleiro[1][1] == 'x'))
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

// função que verifica, a cada jogada, se há ou não vencedor
char vencedor(){

    int i;
    char a = (jogador == CPU) ? 'x' : 'o'; // 'a' varia de acordo com quem o chama

    for (i = 0; i < 3; i++)
        if (tabuleiro[i][0] == a && tabuleiro[i][1] == a && tabuleiro[i][2] == a) return a;
    for (i = 0; i < 3; i++)
        if (tabuleiro[0][i] == a && tabuleiro[1][i] == a && tabuleiro[2][i] == a) return a;

    if (tabuleiro[2][0] == a && tabuleiro[1][1] == a && tabuleiro[0][2] == a) return a;
    if (tabuleiro[0][0] == a && tabuleiro[1][1] == a && tabuleiro[2][2] == a) return a;

    return 'c';
}
