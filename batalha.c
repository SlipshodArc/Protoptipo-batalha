#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "globais_funcoes.h"


void batalha(int x){
    int continuar=1, vez;
    int vencedor;  // 1 para o jogador, 0 para o inimigo.

    //resetar a barra de especial
    pers.bE = 0;
    enemy.bE = 0;

    //carregar dados do inimigo
    loadEnemy(x);

    //mensagem de come�o da batalha e escolher o elemento que o personagem vai usar
    opc();

    //escolher quem vai come�ar 1-personagem / 2- inimigo
    vez = dado();
    if(vez >6){
        vez = 1;
    }
    else{
        vez = 2;
    }

    //looping de batalha
    while(continuar){
        tela();
        if(vez==1)
            persVez();
        if(vez==2)
            enemyVez();

        vez = trocaVez(vez);
        printf("\n\n\n\n\n\n\n\n");
        continuar = fim(&vencedor);
    }


}


















