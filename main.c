#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

/**Defini��o das constantes*/
//Defini��o das teclas
#define CIMA 72             //Default: 72(Seta para cima)
#define BAIXO 80            //Default: 80(Seta para baixo)
#define ESQUERDA 75         //Default: 75(Seta para a esquerda)
#define DIREITA 77          //Default: 77(Seta para a direita)
#define ENTER 13            //Default: 13(Enter)
#define ESC 27              //Default: 27(Esc)
#define SIM 115             //Default: 115(S)
#define NAO 110             //Default: 110(N)

//Defini��o do tamanho da matriz (ao alterar estes par�metros deve-se alterar tamb�m o mapa)
#define TAM_X 50            //Default: 20
#define TAM_Y 12            //Default: 9

//Defini��o dos tipos de caracteres usados para renderizar
#define CHAO 32             //Default: 32(espa�o)
#define PERSONAGEM 43       //Default: 43(+)
#define PONTO 36            //Default: 36($) - Alternativo: 46(.)
#define PAREDE 178          //Default: 178
#define TRAP 83             //Default: 83(S)

//Defini��o do ponto inicial do personagem
#define INICIAL_X 6
#define INICIAL_Y 3

//Define as cores do mapa
#define COR_PONTOS 14       //Default: 14(Amarelo Claro)
#define COR_PAREDE 9        //Default: 9(Azul Claro)
#define COR_CHAO 9          //Default: 9(Azul Claro)
#define COR_TRAP 14         //Default: 14(Amarelo Claro)
#define COR_PERSONAGEM 12   //Default: 12(Vermelho Claro)
#define COR_FUNDO 7         //Default: 7(Cinza)

//Define as cores dos textos
#define COR_MENU 9          //Default: 9(Azul Claro)
#define COR_VICTORY 2       //Default: 2(Verde)
#define COR_GAMEOVER 12     //Default: 12(Vermelho Claro)
#define COR_APAGAR 12       //Default: 12(Vermelho Claro)
#define COR_CONTINUE 9      //Default: 9(Azul Claro)
#define COR_PONTUACAO 2     //Default: 2(Verde)
#define COR_LEGENDA 1       //Default: 1(Azul)

/*
    Autor do Software: Alexei Bell� Secretti
    E-mail: alexeisecretti@hotmail.com

    Vers�o do c�digo: 3.0.0
    Descri��o: Este software � um jogo do labirinto, onde o objetivo � coletar todos os pontos espalhados pelo mapa e evitar as armadilhas.
*/

/**Cria��o das fun��es*/

void gotoxy(int x,int y)
 {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 }

int LeituraArquivo(int highscore, int objetivo, int zerar)
{
    char textoArquivo[50];
    int numeroArquivo = 0;

    FILE *arquivo;
    arquivo = fopen("Highscore.hgs","a+");

    if(arquivo == NULL)
    {
        fclose(arquivo);

        arquivo = fopen("Highscore.hgs","w+");

        fprintf(arquivo, "1F97AD78451B %d", numeroArquivo);

        fclose(arquivo);
    }
    else
    {
        if(zerar == 1)
        {
            highscore = 0;
        }
        else
        {
            fscanf(arquivo, "%s%d", &textoArquivo, &numeroArquivo);

            if(strcmp(textoArquivo, "1F97AD78451B") == 0)
            {
                if(numeroArquivo > highscore)
                {
                    highscore = numeroArquivo;
                }
                if(highscore > objetivo)
                {
                    highscore = 0;
                }
            }
        }
        fclose(arquivo);

        arquivo = fopen("Highscore.hgs","w+");

        fprintf(arquivo, "1F97AD78451B %d", highscore);

        fclose(arquivo);
    }

    return highscore;
}

void ImprimirGameOver(int pontuacao)
{
    setlocale(LC_ALL, "Portuguese");

    system("cls");
    //Muda a cor das letras
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_GAMEOVER + (COR_FUNDO * 16));

    //Imprime o texto de "GAME OVER"
    printf("\n ");
    ImprimirCantoSuperiorEsquerdo();
    ImprimirParedeHorizontal(25);
    printf(" GAME OVER ");
    ImprimirParedeHorizontal(25);
    ImprimirCantoSuperiorDireito();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" Voc� perdeu porque caiu em uma armadilha.                   ");
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" Tome cuidado pois '%c' s�o os pontos,                        ", PONTO);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" mas '%c' s�o as armadilhas.                                  ", TRAP);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirCantoInferiorEsquerdo();
    ImprimirParedeHorizontal(61);
    ImprimirCantoInferiorDireito();
    printf("\n\n ");

    system("pause");
}

void ConfirmarRetornoMenu()
{
    setlocale(LC_ALL, "Portuguese");

    int tecla = 0;

    while(tecla != 121 || tecla != 110)
    {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_CONTINUE + (COR_FUNDO * 16));

        printf("\n ");
        ImprimirCantoSuperiorEsquerdo();
        ImprimirParedeHorizontal(26);
        printf(" RETORNAR ");
        ImprimirParedeHorizontal(25);
        ImprimirCantoSuperiorDireito();
        printf("\n ");
        ImprimirParedeVertical();
        ImprimirEspacos(61);
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        printf(" Voc� deseja voltar ao menu?                                 ");
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        ImprimirEspacos(61);
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        printf(" %c - Sim                                                     ", toupper(SIM));
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        printf(" %c - N�o                                                     ", toupper(NAO));
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        ImprimirEspacos(61);
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirCantoInferiorEsquerdo();
        ImprimirParedeHorizontal(61);
        ImprimirCantoInferiorDireito();
        printf("\n\n > ");

        tecla = getch();

        //Imprime a tecla digitada pelo usu�rio
        printf("%c\n\n", toupper(tecla));

        if(tecla == SIM)
        {
            //Caso a tecla pressionada corresponder � op��o "Sim", o jogo (fun��o main) � executado novamente desde o come�o
            main();
        }
        else if(tecla == NAO)
        {
            //Caso a tecla corresponder � op��o "N�o", o programa � encerrado
            exit(0);
        }
    }
}

void ConfirmarSaida()
{
    setlocale(LC_ALL, "Portuguese");

    int tecla = 0;

    while(tecla != 121 || tecla != 110)
    {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_CONTINUE + (COR_FUNDO * 16));

        printf("\n ");
        ImprimirCantoSuperiorEsquerdo();
        ImprimirParedeHorizontal(24);
        printf(" CONFIRMA��O ");
        ImprimirParedeHorizontal(24);
        ImprimirCantoSuperiorDireito();
        printf("\n ");
        ImprimirParedeVertical();
        ImprimirEspacos(61);
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        printf(" Voc� realmente deseja sair do jogo?                         ");
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        ImprimirEspacos(61);
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        printf(" %c - Sim                                                     ", toupper(SIM));
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        printf(" %c - N�o                                                     ", toupper(NAO));
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirParedeVertical();
        ImprimirEspacos(61);
        ImprimirParedeVertical();
        printf("\n ");
        ImprimirCantoInferiorEsquerdo();
        ImprimirParedeHorizontal(61);
        ImprimirCantoInferiorDireito();
        printf("\n\n > ");

        tecla = getch();

        //Imprime a tecla digitada pelo usu�rio
        printf("%c\n\n", toupper(tecla));

        if(tecla == NAO)
        {
            //Caso a tecla pressionada corresponder � op��o "N�o", o jogo (fun��o main) � executado novamente desde o come�o
            main();
        }
        else if(tecla == SIM)
        {
            //Caso a tecla corresponder � op��o "Sim", o programa � encerrado
            exit(0);
        }
    }
}

void ImprimirEspacos(int tamanho)
{
    int cont = 0;

    while(cont < tamanho)
    {
        printf(" ");

        cont++;
    }
}

void ImprimirLinhas(int tamanho)
{
    int cont = 0;

    while(cont < tamanho)
    {
        printf("\n");

        cont++;
    }
}

void ImprimirParedeHorizontal(int largura)
{
    int contador = 0;

    while(contador < largura)
    {
        setlocale(LC_ALL, "C");
        printf("%c", 205);
        setlocale(LC_ALL, "Portuguese");

        contador++;
    }
}

void ImprimirParedeVertical()
{
    setlocale(LC_ALL, "C");
    printf("%c", 186);
    setlocale(LC_ALL, "Portuguese");
}

void ImprimirCantoSuperiorEsquerdo()
{
    setlocale(LC_ALL, "C");
    printf("%c", 201);
    setlocale(LC_ALL, "Portuguese");
}

void ImprimirCantoSuperiorDireito()
{
    setlocale(LC_ALL, "C");
    printf("%c", 187);
    setlocale(LC_ALL, "Portuguese");
}

void ImprimirCantoInferiorEsquerdo()
{
    setlocale(LC_ALL, "C");
    printf("%c", 200);
    setlocale(LC_ALL, "Portuguese");
}

void ImprimirCantoInferiorDireito()
{
    setlocale(LC_ALL, "C");
    printf("%c", 188);
    setlocale(LC_ALL, "Portuguese");
}

void ImprimirDerivacaoDireita()
{
    setlocale(LC_ALL, "C");
    printf("%c", 204);
    setlocale(LC_ALL, "Portuguese");
}

void ImprimirDerivacaoEsquerda()
{
    setlocale(LC_ALL, "C");
    printf("%c", 185);
    setlocale(LC_ALL, "Portuguese");
}

void ImprimirMenu(int max_pontos)
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_MENU + (COR_FUNDO * 16));

    printf("\n ");
    ImprimirCantoSuperiorEsquerdo();
    ImprimirParedeHorizontal(24);
    printf(" INFORMA��ES ");
    ImprimirParedeHorizontal(24);
    ImprimirCantoSuperiorDireito();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" Objetivo do jogo: Coletar os pontos espalhados pelo mapa.   ");
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" Para mover o personagem use as setas do teclado.            ");
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" Vers�o do jogo: 3.0.0                                       ");
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" Maior pontua��o atingida: %d                               ", max_pontos);
    if(max_pontos < 10)
    {
        printf(" ");
    }
    if(max_pontos < 100)
    {
        printf(" ");
    }
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirDerivacaoDireita();
    ImprimirParedeHorizontal(27);
    printf(" MENU ");
    ImprimirParedeHorizontal(28);
    ImprimirDerivacaoEsquerda();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" J - Jogar                                                   ");
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" A - Apagar pontua��o m�xima                                 ");
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    printf(" S - Sair                                                    ");
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirParedeVertical();
    ImprimirEspacos(61);
    ImprimirParedeVertical();
    printf("\n ");
    ImprimirCantoInferiorEsquerdo();
    ImprimirParedeHorizontal(61);
    ImprimirCantoInferiorDireito();
}

void ImprimirLegenda(int pontos)
{
    //Imprime a pontua��o abaixo do mapa
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PONTUACAO + COR_FUNDO * 16);
    printf("\n\n   Pontua��o: %d\n\n", pontos);

    //Imprime a legenda abaixo da pontua��o
    setlocale(LC_ALL, "C");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_LEGENDA + COR_FUNDO * 16);
    printf("   Legenda:\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PAREDE + COR_FUNDO * 16);
    printf("   %c", PAREDE);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_LEGENDA + COR_FUNDO * 16);
    printf(" - Parede\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PONTOS + COR_FUNDO * 16);
    printf("   %c", PONTO);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_LEGENDA + COR_FUNDO * 16);
    printf(" - Ponto\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PERSONAGEM + COR_FUNDO * 16);
    printf("   %c", PERSONAGEM);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_LEGENDA + COR_FUNDO * 16);
    printf(" - Personagem\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_TRAP + COR_FUNDO * 16);
    printf("   %c", TRAP);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_LEGENDA + COR_FUNDO * 16);
    printf(" - ?\n\n");
    printf("   Para voltar ao menu pressione ESC\n\n   ");
}

void ImprimirPonto(int estado)
{
    switch(estado)
    {
    case 0:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_CHAO + (COR_FUNDO * 16));
        printf("%c", CHAO);
        break;

    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PERSONAGEM + (COR_FUNDO * 16));
        printf("%c", PERSONAGEM);

        break;
    case 2:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PONTOS + (COR_FUNDO * 16));
        printf("%c", PONTO);

        break;
    case 3:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PAREDE + (COR_FUNDO * 16));
        printf("%c", PAREDE);
        break;

    case 4:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_TRAP + (COR_FUNDO * 16));
        printf("%c", TRAP);
        break;
    }
    setlocale(LC_ALL, "Portuguese");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    /**Cria��o e incializa��o das vari�veis*/
    //Matriz do mapa -> 0 - Ch�o | 1 - Personagem (em desuso) | 2 - Ponto | 3 - Parede | 4 - Armadilha
    int pos[TAM_X][TAM_Y] =
    {
        3,3,3,3,3,3,3,3,3,3,3,3,
        3,4,3,2,2,2,2,2,2,3,4,3,
        3,2,3,2,3,3,3,3,2,3,2,3,
        3,2,3,2,3,2,2,4,2,3,2,3,
        3,2,2,2,3,2,3,3,2,2,2,3,
        3,2,3,3,3,2,2,2,2,3,2,3,
        3,2,3,0,3,3,3,3,3,3,2,3,
        3,2,3,2,2,2,2,2,2,2,2,3,
        3,2,3,2,3,3,3,3,3,3,3,3,
        3,4,3,2,3,2,2,2,2,2,2,3,
        3,3,3,2,3,2,3,3,3,3,2,3,
        3,4,3,2,3,2,3,2,2,2,2,3,
        3,2,3,2,3,2,3,2,3,3,3,3,
        3,2,3,2,3,2,3,2,2,2,2,3,
        3,2,3,2,3,2,3,3,3,3,2,3,
        3,2,2,2,2,2,4,2,2,2,2,3,
        3,3,3,3,3,3,3,2,3,3,4,3,
        3,2,4,2,2,2,2,2,2,2,2,3,
        3,2,3,2,3,3,3,3,3,3,2,3,
        3,2,3,2,3,4,2,2,2,2,2,3,
        3,2,3,2,3,3,3,3,3,3,2,3,
        3,2,3,2,2,2,2,2,2,3,2,3,
        3,2,3,3,3,3,3,3,2,3,2,3,
        3,2,2,2,2,2,4,3,2,3,2,3,
        3,2,3,3,3,3,3,3,2,3,2,3,
        3,2,2,2,2,2,2,2,2,3,2,3,
        3,3,3,3,3,3,3,3,3,3,2,3,
        3,2,2,2,2,2,2,2,2,2,2,3,
        3,2,3,3,3,3,3,3,3,3,3,3,
        3,2,3,2,2,2,2,2,2,2,2,3,
        3,2,3,2,3,3,3,3,3,3,2,3,
        3,2,3,2,3,4,2,2,2,2,2,3,
        3,2,3,2,3,3,3,3,3,3,3,3,
        3,2,2,2,2,2,2,2,2,4,4,3,
        3,3,3,3,3,3,3,3,2,3,3,3,
        3,2,2,2,2,2,4,3,2,3,4,3,
        3,2,3,2,3,2,4,3,2,3,2,3,
        3,2,3,2,3,2,3,3,2,3,2,3,
        3,2,3,2,3,2,2,2,2,3,2,3,
        3,2,3,2,3,3,3,3,2,3,2,3,
        3,2,3,2,4,3,4,3,2,2,2,3,
        3,2,3,3,3,3,2,3,3,3,3,3,
        3,2,2,2,2,3,2,2,2,2,2,3,
        3,3,3,3,2,3,3,3,3,3,2,3,
        3,2,2,2,2,2,2,2,2,3,2,3,
        3,2,3,3,3,3,3,3,2,3,2,3,
        3,2,2,2,2,2,2,3,2,3,2,3,
        3,3,3,3,3,3,2,3,2,3,2,3,
        3,4,2,2,2,2,2,3,2,2,2,3,
        3,3,3,3,3,3,3,3,3,3,3,3,
    };

    //Vari�veis gerais
    //Contadores
    int cont_x = 0, cont_y = 0, pontos = 0, objetivo = 0;
    //Coordenadas x e y do personagem
    int pos_x = 0, pos_y = 0;
    //Coordenadas x e y da posi��o anterior do personagem
    int anterior_x = 1, anterior_y = 1;
    //Vari�veis "bin�rias" de aux�lio
    int max_pontos = 0, tecla = 0, tecla_aux = 0;

    /**Prepara��o para o programa*/
    //Definindo a quantidade de pontos presentes na fase e armazenando na vari�vel "objetivo"
    while(cont_y < TAM_Y)
    {
        while(cont_x < TAM_X)
        {
            if(pos[cont_x][cont_y] == 2)
            {
                objetivo++;
            }

            cont_x++;
        }
        cont_x = 0;

        cont_y++;
    }
    cont_y = 0;

    //Colocando o personagem no ponto inicial
    pos_x = INICIAL_X;
    pos_y = INICIAL_Y;

    //Prepara a tela para impimir o programa
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (COR_FUNDO * 16));

    /**Cria��o do Menu*/
    while(tecla != 106)
    {
        max_pontos = LeituraArquivo(0, objetivo, 0);

        ImprimirMenu(max_pontos);

        /**Leitura da tecla pressionada no menu*/
        printf("\n\n > ");

        tecla = getch();

        //Imprime a tecla digitada pelo usu�rio
        printf("%c\n", toupper(tecla), tecla);

        if(tecla == 97)
        {
            system("cls");

            tecla_aux = 0;

            while(tecla_aux != SIM && tecla_aux != NAO)
            {
                system("cls");

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_APAGAR + (COR_FUNDO * 16));

                printf("\n ");
                ImprimirCantoSuperiorEsquerdo();
                ImprimirParedeHorizontal(27);
                printf(" APAGAR ");
                ImprimirParedeHorizontal(26);
                ImprimirCantoSuperiorDireito();
                printf("\n ");
                ImprimirParedeVertical();
                ImprimirEspacos(61);
                ImprimirParedeVertical();
                printf("\n ");
                ImprimirParedeVertical();
                printf(" Voc� realmente deseja apagar seu recorde de pontua��o?      ");
                ImprimirParedeVertical();
                printf("\n ");
                ImprimirParedeVertical();
                ImprimirEspacos(61);
                ImprimirParedeVertical();
                printf("\n ");
                ImprimirParedeVertical();
                printf(" %c - Sim                                                     ", toupper(SIM));
                ImprimirParedeVertical();
                printf("\n ");
                ImprimirParedeVertical();
                printf(" %c - N�o                                                     ", toupper(NAO));
                ImprimirParedeVertical();
                printf("\n ");
                ImprimirParedeVertical();
                ImprimirEspacos(61);
                ImprimirParedeVertical();
                printf("\n ");
                ImprimirCantoInferiorEsquerdo();
                ImprimirParedeHorizontal(61);
                ImprimirCantoInferiorDireito();
                printf("\n\n > ");

                tecla_aux = getch();

                //Imprime a tecla digitada pelo usu�rio (retorno visual)
                printf("%c\n\n", toupper(tecla_aux));

                if(tecla_aux == SIM)
                {
                    max_pontos = LeituraArquivo(0, objetivo, 1);
                }
            }
        }
        else if(tecla == 115)
        {
            ConfirmarSaida();
        }
    }

    //Limpa a tela para iniciar a renderiza��o
    system("cls");

    //Informa a posi��o do personagem para a matriz de renderiza��o
    pos[pos_x][pos_y] = 1;

    /**Renderiza��o da matriz*/
    //Insere um espa�amento acima da matriz
    printf("\n\n");

    //Renderiza��o da matriz
    while(cont_y < TAM_Y)
    {
        ImprimirEspacos(29);

        while(cont_x < TAM_X)
        {
            setlocale(LC_ALL, "C");

            //Imprime o caractere referente ao estado da posi��o da linha que est� sendo analisada
            ImprimirPonto(pos[cont_x][cont_y]);

            cont_x++;
        }
        cont_x = 0;
        cont_y++;

        //Pula para a pr�xima linha
        printf("\n");
    }
    cont_y = 0;

    ImprimirLegenda(pontos);

    /**Estrutura do jogo*/
    while(1 == 1)
    {
        /**Compara��o da pontua��o com o objetivo*/
        //Verifica se o objetivo foi alcan�ado e em caso afirmativo mostra a mensagem de "VOC� VENCEU O JOGO"
        if(pontos == objetivo)
        {
            setlocale(LC_ALL, "Portuguese");

            system("cls");

            //Muda a cor do fundo para cinza e a cor das letras para verde
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_VICTORY + (COR_FUNDO * 16));

            printf("\n ");
            ImprimirCantoSuperiorEsquerdo();
            ImprimirParedeHorizontal(26);
            printf(" VIT�RIA ");
            ImprimirParedeHorizontal(26);
            ImprimirCantoSuperiorDireito();
            printf("\n ");
            ImprimirParedeVertical();
            ImprimirEspacos(61);
            ImprimirParedeVertical();
            printf("\n ");
            ImprimirParedeVertical();
            printf(" Parab�ns!                                                   ");
            ImprimirParedeVertical();
            printf("\n ");
            ImprimirParedeVertical();
            ImprimirEspacos(61);
            ImprimirParedeVertical();
            printf("\n ");
            ImprimirParedeVertical();
            printf(" Voc� ganhou o jogo coletando todos os pontos.               ");
            ImprimirParedeVertical();
            printf("\n ");
            ImprimirParedeVertical();
            ImprimirEspacos(61);
            ImprimirParedeVertical();
            printf("\n ");
            ImprimirCantoInferiorEsquerdo();
            ImprimirParedeHorizontal(61);
            ImprimirCantoInferiorDireito();
            printf("\n\n ");

            max_pontos = LeituraArquivo(pontos, objetivo, 0);

            system("pause");

            ConfirmarRetornoMenu();

            exit(0);
        }

        /**Leitura das teclas para a movimenta��o*/
        //Leitura das teclas (getch), movimenta��o do personagem e contagem de pontos
        switch(getch())
        {
        case CIMA:
            if(pos[pos_x][pos_y - 1] != 3 && pos_y - 1 >= 0)
            {
                //Verifica se a posi��o para onde o personagem est� tentado se mover � uma parede, uma armadilha ou outra coisa
                if(pos[pos_x][pos_y - 1] == 2 || pos[pos_x][pos_y - 1] == 0)
                {
                    //Aumenta a pontua��o caso a pr�xima posi��o seja um ponto
                    if(pos[pos_x][pos_y - 1] == 2)
                    {
                        pontos++;
                    }

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PONTUACAO + (COR_FUNDO * 16));
                    gotoxy(14, 16);
                    printf("%d", pontos);
                    gotoxy(pos_x + 29, pos_y + 2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_CHAO + (COR_FUNDO * 16));
                    printf("%c", CHAO);
                    gotoxy(pos_x + 29, pos_y + 1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PERSONAGEM + (COR_FUNDO * 16));
                    printf("%c", PERSONAGEM);
                    gotoxy(3, 26);

                    pos[pos_x][pos_y] = 0;
                }
                else if(pos[pos_x][pos_y - 1] == 4)
                {
                    //Chama a fun��o "ImprimirGameOver" caso for uma armadilha
                    ImprimirGameOver(pontos);

                    //Verifica se a pontua��o marcada � maior que o recorde
                    if(pontos > max_pontos)
                    {
                        //Em caso afirmativo, define o recorde como a pontua��o atual
                        max_pontos = pontos;
                    }

                    //Manda a fun��o "LeituraArquivo" comparar o recorde atual com o recorde armazenado no arquivo "Highscore.hgs", com o par�metro reset em 0
                    max_pontos = LeituraArquivo(max_pontos, objetivo, 0);

                    ConfirmarRetornoMenu();
                }

                //Movimenta o personagem
                pos_y--;
            }
            break;

        case BAIXO:
            if(pos[pos_x][pos_y + 1] != 3 && pos_y + 1 < TAM_Y)
            {
                if(pos[pos_x][pos_y + 1] == 2 || pos[pos_x][pos_y + 1] == 0)
                {
                    if(pos[pos_x][pos_y + 1] == 2)
                    {
                        pontos++;
                    }

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PONTUACAO + (COR_FUNDO * 16));
                    gotoxy(14, 16);
                    printf("%d", pontos);
                    gotoxy(pos_x + 29, pos_y + 2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_CHAO + (COR_FUNDO * 16));
                    printf("%c", CHAO);
                    gotoxy(pos_x + 29, pos_y + 3);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PERSONAGEM + (COR_FUNDO * 16));
                    printf("%c", PERSONAGEM);
                    gotoxy(3, 26);

                    pos[pos_x][pos_y] = 0;
                }
                else if(pos[pos_x][pos_y + 1] == 4)
                {
                    ImprimirGameOver(pontos);

                    if(pontos > max_pontos)
                    {
                        max_pontos = pontos;
                    }

                    max_pontos = LeituraArquivo(max_pontos, objetivo, 0);

                    ConfirmarRetornoMenu();
                }

                pos_y++;
            }
            break;

        case DIREITA:
            if(pos[pos_x + 1][pos_y] != 3 && pos_x + 1 < TAM_X)
            {
                if(pos[pos_x + 1][pos_y] == 2 || pos[pos_x + 1][pos_y] == 0)
                {
                    if(pos[pos_x + 1][pos_y] == 2)
                    {
                        pontos++;
                    }

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PONTUACAO + (COR_FUNDO * 16));
                    gotoxy(14, 16);
                    printf("%d", pontos);
                    gotoxy(pos_x + 29, pos_y + 2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_CHAO + (COR_FUNDO * 16));
                    printf("%c", CHAO);
                    gotoxy(pos_x + 30, pos_y + 2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PERSONAGEM + (COR_FUNDO * 16));
                    printf("%c", PERSONAGEM);
                    gotoxy(3, 26);

                    pos[pos_x][pos_y] = 0;
                }
                else if(pos[pos_x + 1][pos_y] == 4)
                {
                    ImprimirGameOver(pontos);

                    if(pontos > max_pontos)
                    {
                        max_pontos = pontos;
                    }

                    max_pontos = LeituraArquivo(max_pontos, objetivo, 0);

                    ConfirmarRetornoMenu();
                }

                pos_x++;
            }
            break;

        case ESQUERDA:
            if(pos[pos_x - 1][pos_y] != 3 && pos_x - 1 >= 0)
            {
                if(pos[pos_x - 1][pos_y] == 2 || pos[pos_x - 1][pos_y] == 0)
                {
                    if(pos[pos_x - 1][pos_y] == 2)
                    {
                        pontos++;
                    }

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PONTUACAO + (COR_FUNDO * 16));
                    gotoxy(14, 16);
                    printf("%d", pontos);
                    gotoxy(pos_x + 29, pos_y + 2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_CHAO + (COR_FUNDO * 16));
                    printf("%c", CHAO);
                    gotoxy(pos_x + 28, pos_y + 2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COR_PERSONAGEM + (COR_FUNDO * 16));
                    printf("%c", PERSONAGEM);
                    gotoxy(3, 26);

                    pos[pos_x][pos_y] = 0;
                }
                else if(pos[pos_x - 1][pos_y] == 4)
                {
                    ImprimirGameOver(pontos);

                    if(pontos > max_pontos)
                    {
                        max_pontos = pontos;
                    }

                    max_pontos = LeituraArquivo(max_pontos, objetivo, 0);

                    ConfirmarRetornoMenu();
                }

                pos_x--;
            }
            break;

        case ESC:
            if(pontos > max_pontos)
            {
                max_pontos = pontos;
            }

            max_pontos = LeituraArquivo(max_pontos, objetivo, 0);

            main();
            break;
        }
    }
}
