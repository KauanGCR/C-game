#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define MAX_LINHA 12
#define MAX_COLUNA 12
#define MAX_BOMBAS 6

int main()
{
    srand(time(NULL));
    int x, y; //coordenadas
    int ox = rand() % (MAX_COLUNA - 2) + 1, oy = rand() % (MAX_LINHA - 2) + 1; //definindo a posição inicial aleatória da saída
    int mx = rand() % (MAX_COLUNA - 2) + 1, my = rand() % (MAX_LINHA - 2) + 1; //definindo a posição inicial aleatória do monstro
    int px = 1, py = 1; //definindo a posição inicial do jogador
    int perdeu = 0; // declarando uma variável que irá definir se o jogador perdeu
    int vitorias = 0; //declarando uma variável que irá definir o número de vitórias
    int dificuldade = 1; //declarando uma variável que irá definir a dificuldade
    int movimentoRealizado = 1; //declarando uma variável que irá dizer se um movimento foi realizado
    int bombaprint = 0; //declarando uma variável que irá definir se uma bomba foi gerada ou não
    int direcao; //declarando uma variável que irá definir a direção que monstro se move
    char personagem; //declarando uam variável que irá definir o caractere do personagem
    char comando; //declarando uma variável que irá receber o comando do usuário
    int bombasx[MAX_BOMBAS], bombasy[MAX_BOMBAS]; //declarando uma variável com vetores ques irão conter as posições aleatórias das bombas

    for (int i = 0; i < MAX_BOMBAS; i++)
    {
        bombasx[i] = rand() % (MAX_COLUNA - 2) + 1; // Posição inicial aleatória para as minas
        bombasy[i] = rand() % (MAX_LINHA - 2) + 1;
    }

    //contexto do jogo
    printf("Voce eh um aventureiro que se perdeu em uma masmorra\n");
    printf("e precisa encontrar um caminho de volta para casa...\n");
    printf("BOA SORTE!\n\n");

    //o programa irá pedir para o jogador escolher o caractere do seu personagem
    printf("Escolha o icone do seu personagem: \n");
    scanf("%c", &personagem);

    for (;;)
    {
        //sempre que um movimento, válido(1) ou inválido(2), for registrado, o mapa será atualizado
        if(movimentoRealizado==1 || movimentoRealizado==2)
        {
            system("CLS");

            //escrevendo o mapa na tela
            printf("Masmorra: Andar %i/5 - dificuldade: %i\n\n", dificuldade, dificuldade);
            for (y = 0; y < MAX_LINHA; y++)
            {
                for (x = 0; x < MAX_COLUNA; x++)
                {
                    for(int i = 0; i < MAX_BOMBAS; i++)
                    {
                        if(x == bombasx[i] && y == bombasy[i])
                        {
                            printf("*");
                            bombaprint = 1;
                        }
                    }
                    if (y == 0 || x == 0 || x == MAX_COLUNA - 1 || y == MAX_LINHA - 1)
                        printf("#");
                    else if (x == px && y == py && bombaprint==0)
                        printf("%c", personagem);
                    else if (x == mx && y == my && bombaprint==0)
                        printf("M");
                    else if (x == ox && y == oy && bombaprint==0)
                        printf("@");
                    else if (bombaprint==0)
                        printf(".");
                    bombaprint=0;
                }
                printf("\n");
            }
            printf("\n");

            //instruções para o jogador
            printf("Voce precisa chegar ate a saida!\n");
            printf("Cuidado com o monstro e as bombas.\n");
            printf("Comandos: W (cima)\tD (direita)\tS (baixo)\tA (esquerda)\n\n");
            printf("Jogador: %c\nMonstro: M\nSaida: @\nBombas: *\n", personagem);
            //agurdando o próximo movimento
            movimentoRealizado=0;
        }
        //o sistema irá registrar qualquer comando do jogador assim que uma tecla for pressionada
        if (kbhit())
        {
            comando = getch();
        //movimento computado
            movimentoRealizado = 1;
        //o programa irá verificar se o comando é válido(1) e então mover o personagem de acordo
            switch (comando)
            {
            case 'w':
            case 'W':
                py -= 1;
                if (py < 1)
                {
                    py = 1;
                    movimentoRealizado = 0;
                }
                break;
            case 's':
            case 'S':
                py += 1;
                if (py >= MAX_LINHA - 1)
                {
                    py = MAX_LINHA - 2;
                    movimentoRealizado = 0;
                }
                break;
            case 'a':
            case'A':
                    px -= 1;
                if (px < 1)
                {
                    px = 1;
                    movimentoRealizado = 0;
                }
                break;
            case 'd':
            case 'D':
                px += 1;
                if (px >= MAX_COLUNA - 1)
                {
                    px = MAX_COLUNA - 2;
                    movimentoRealizado = 0;
                }
                break;

            //se o comando registrado for inválido(2), o programa irá solicitar outro
            default:
                movimentoRealizado = 2;
                printf("Comando invalido!\n");
                system("PAUSE");
            }
                //sempre que um movimento for registrado, o monstro se moverá de acordo com a posição do jogador
                if (movimentoRealizado == 1)
                {
                    //se o monstro estiver no mesmo eixo Y do jogador, se moverá em direção a ele
                    if(py==my && px<mx)
                    {
                        direcao=0;
                    }

                    else if(py==my && px>mx)
                    {
                        direcao=1;
                    }

                    //se o monstro estiver no mesmo eixo X do jogador, se moverá em direção a ele
                    else if(px==mx && py<my)
                    {
                        direcao=2;
                    }

                    else if(px==mx && py>my)
                    {
                        direcao=3;
                    }

                    //caso contrário, o monstro se moverá aleatoriamente
                    else
                    {
                        direcao=rand() % 4;
                    }

                    switch (direcao)
                    {
                    case 0:
                        mx -= dificuldade;
                        if (mx < 1)
                        {
                            mx = 1;
                        }
                        break;

                    case 1:
                        mx += dificuldade;
                        if (mx >= MAX_COLUNA - 1)
                        {
                            mx = MAX_COLUNA - 2;
                        }
                        break;

                    case 2:
                        my -= dificuldade;
                        if (my < 1)
                        {
                            my = 1;
                        }
                        break;

                    case 3:
                        my += dificuldade;
                        if (my >= MAX_LINHA - 1)
                        {
                            my = MAX_LINHA - 2;
                        }
                        break;
                    }
                }

            //se as coordenadas das bombas e jogador coinciderem, o jogador perde
            for (int i = 0; i < MAX_BOMBAS; i++)
            {
                if(px == bombasx[i] && py == bombasy[i])
                {
                    system("CLS");
                    printf("\nFIM DE JOGO\n");
                    printf("\nVOCE EXPLODIU...\n");
                    perdeu=1;
                }
            }

            //se as coordenadas do monstro e jogador coinciderem, o jogador perde
            if (px == mx && py == my)
            {
                system("CLS");
                printf("\nFIM DE JOGO\n");
                printf("\nO MONSTRO TE ALCANCOU...\n");
                perdeu=1;
            }

            //se o jogador passar de 5 andares, ele termina o jogo
            else if (px == ox && py == oy && vitorias == 4)
            {
                system("CLS");
                printf("\nPARABENS, VOCE VENCEU!\n");
                break;
            }

            //se as coordenadas da saída e jogador coinciderem, o jogador avança para o próximo andar
            else if (px == ox && py == oy)
            {
                printf("\nVOCE AVANCOU PARA O PROXIMO ANDAR!\n");
                system("PAUSE");
                vitorias++;
                dificuldade++;
                px = 1, py = 1;
                ox = rand() % (MAX_COLUNA - 2) + 1, oy = rand() % (MAX_LINHA - 2) +
                        1;
                mx = rand() % (MAX_COLUNA - 2) + 1, my = rand() % (MAX_LINHA - 2) +
                        1;
                for (int i = 0; i < MAX_BOMBAS; i++)
                {
                    bombasx[i] = rand() % (MAX_COLUNA - 2) + 1;
                    bombasy[i] = rand() % (MAX_LINHA - 2) + 1;
                }
            }

            //se o jogador perdeu o programa é encerrado
            if (perdeu!=0)
            {
                break;
            }
        }
    }

    system("PAUSE");
    return 0;
}
