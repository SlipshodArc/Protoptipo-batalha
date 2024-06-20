#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "globais_funcoes.h"


void batalha(int x){
    int continuar=1, vez;

    //resetar a barra de especial
    pers.bE = 0;
    enemy.bE = 0;

    //carregar dados do inimigo
    loadEnemy(x);

    //mensagem de começo da batalha e escolher o elemento que o personagem vai usar
    opc();

    //escolher quem vai começar 1-personagem / 2- inimigo
    /*
    vez = dado();
    if(vez >6){
        vez = 1;
    }
    else{
        vez = 2;
    }
    */
    vez = 1;

    //looping de batalha
    while(continuar){
        tela();
        if(vez==1)
            persVez();
        if(vez==2)
            enemyVez();

        //vez = trocaVez();
        printf("\n\n\n\n\n\n\n\n");
    }


}


















