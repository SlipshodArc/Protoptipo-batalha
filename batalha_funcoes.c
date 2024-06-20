#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "globais_funcoes.h"

void tela(){
    system("cls");
    char texto[200];

    //imprimir titulo
    FILE *f;
    f = fopen("title.txt","r");
    while(!feof(f)){
        printf("\t\t\t\t\t");
        fgets(texto, 200, f);
        printf("%s",texto);
    }
    fclose(f);

    printf("\n\n\n");

    //imprimir info do personagem e inimigo
    printf("            |           ");
    printf("%s", pers.nome);
    printf("                     VS                %s",enemy.nome);
    printf("\n");
    printf("          O |     ");
    printf(">-------------------------<\t\t\t     >---------------------------<");
    printf("\n");
    printf("         /|\\T              ");
    printf("HP: %d \t\t\t\t\t      HP: %d ",pers.vida, enemy.vida);
    printf("\n");
    printf("          >\\             ");
    printf("Especial: %d \t\t\t\t\t    Especial: %d ",pers.bE, enemy.bE);

}


//---------------------------------------------------------------------------------------------------------------


void opc(){
    int dad, certeza=0;
    printf("\n\n\n\n");
    printf("\t\t\t\tVOCE ENCONTROU UM INIMIGO\n\n\n\n");

    dad = dado();

    if(dad<=6){
        printf("\tComo voce tirou %d (valor <=6) no dado, ",dad);
        printf("voce nao conseguiu identificar o tipo do seu inimigo!\n");
    }
    else{
        printf("\tComo voce tirou %d (valor >6) no dado, ",dad);
        printf("o seu inimigo eh do tipo: ");
        if(enemy.tipo == 1)
            printf("Chamas");
        if(enemy.tipo == 2)
            printf("Cinzas");
        if(enemy.tipo == 3)
            printf("Luz");
        if(enemy.tipo == 4)
            printf("Sombras");
    }


    printf("\n\n\tEscolha o elemento que voce usara: \n");
    printf("\n \t>Chamas  [1]");
    printf("\n \t>Cinzas  [2]");
    printf("\n \t>Luz     [3]");
    printf("\n \t>Sombras [4]");

    do{
    printf("\n\n\tSeu elemento: ");
    scanf("%d",&pers.tipo);

    while(pers.tipo < 1 || pers.tipo >4){
        printf("\n\tElemento invalido, escolha novamente: ");
        scanf("%d",&pers.tipo);
    }
    printf("\n\t>Digite 1 para continuar");
    printf("\n\t          OU");
    printf("\n\t>Digite 0 para trocar seu elemento\n\n\t-Sua opcao: ");
    scanf("%d",&certeza);
    }while(certeza == 0);

}



//---------------------------------------------------------------------------------------------------------------



void loadEnemy(int x){
    char cwd[200] = {"C:\\projeto_c\\Jogos\\Prototipo batalha\\inimigos\\"};
    char num[5];
    sprintf(num, "%d", x);

    strcat(cwd, num);
    strcat(cwd, ".txt");



    //preencher dados do inimigo
    FILE *f;
    f = fopen(cwd, "r");
    fscanf(f, "%100[^\n]", enemy.nome);
    fscanf(f, "%d %d %d", &enemy.vida, &enemy.pAtq,  &enemy.tipo);
    fclose(f);

}



//---------------------------------------------------------------------------------------------------------------



int trocaVez(int vez){
    if(vez==1)
        return 2;

    if(vez==2)
        return 1;
}



//---------------------------------------------------------------------------------------------------------------



void persVez(){
    int acao, acaoAtq, acaoInv, dad,  dano=0, voltar=1, temp;
    char c;

    printf("\n\n\n\n\n");
    printf("\t\t\t\t\t\t       Sua vez   \n");
    printf("\t\t\t\t\t\t>------------------<\n\n");

    printf("\t\t--> Escolha sua ação\n\n");
    printf("\t\t    > Atacar    [1]\n");
    printf("\t\t    > Usar item [2]\n\n");
    printf("\t\t       -> ");
    scanf("%d", &acao);

    system("cls");

    if(acao==1){
        tela();
        printf("\n\n\n\n\n");
        printf("\t\t\t\t\t\t       Sua vez   \n");
        printf("\t\t\t\t\t\t>------------------<\n\n");

        printf("\t\t--> Escolha um ataque: \n\n");
        printf("\t\t    > Normal    [1]\n");
        printf("\t\t    > Especial  [2] -15 especial\n\n");

        while(voltar){
            printf("\t\t       -> ");
            scanf("%d", &acaoAtq);

            dad = dado();
            if(acaoAtq == 1){
                dano = dad + (pers.pAtq / 2);
                dad = dado();
                pers.bE = pers.bE + dad + 5;
                voltar = 0;
            }

            if(acaoAtq == 2){
                if(pers.bE >=15){
                    dano = dad + (pers.pAtq * 2) ;
                    voltar = 0;
                }
                else{
                    printf("\n\n\n\t\tVoce nao pode lançar um ataque especial, pois seu especial é menor que 15\n\n");
                }

            }
        }


        enemy.vida = enemy.vida - dano;


        system("cls");
        printf("\n\n\n\t\t\t\t\tVoce causou %d de dano no seu inimigo\n\n\n\n", dano);
        printf("Aperter ENTER para continuar");
        c = getchar();
        c = getchar();

    }

    if(acao ==2){
        system("cls");
        tela();
        while(voltar){
            printf("\n\n\n");
            printf("\t\t--> Escolha um item: \n\n");
            printf("\t\t    > Poção de cura  [1]\n");
            printf("\t\t    > Outro          [2] \n\n");
            printf("\t\t       -> ");
            scanf("%d",&acaoInv);
            if(acaoInv == 1){
                if(pers.vida == pers.vidaMax){
                    system("cls");
                    printf("\n\n\nJa está com vida máxima!\n\n\n");
                    printf("Aperter ENTER para continuar");
                    c = getchar();
                    c = getchar();
                    voltar = 0;
                }
                if(pers.pocao>0){
                    voltar = 0;
                    pers.pocao--;
                    pers.vida = pers.vida + 50;
                    if(pers.vida>100){
                            temp = pers.vida - pers.vidaMax;
                            pers.vida = pers.vida - temp;
                    }
                }
                else{
                    printf("Voce nao tem poção! ");
                    system("cls");
                }
            }
            else{
                voltar = 0;
            }
        }

    }



}



//---------------------------------------------------------------------------------------------------------------

int verTipo(){



}


void enemyVez(){
    printf("\n\nINIMIGO");


}

