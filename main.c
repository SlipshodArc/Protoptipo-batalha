#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "globais_funcoes.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    srand(time(NULL));

    //preencher dados do personagem
    pers.vida = 50;
    pers.pAtq = 15;
    pers.chamas = 1;
    pers.luz = 1;
    pers.sombras = 1;
    pers.cinzas = 1;
    pers.vidaMax = 100;
    pers.pocao = 3;
    strcpy(pers.nome, "SlipshodArc");



    batalha(1);



    printf("\n\n\n\n");

    return 0;
}
