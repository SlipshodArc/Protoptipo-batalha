#ifndef GLOBAIS_FUNCOES_H_INCLUDED
#define GLOBAIS_FUNCOES_H_INCLUDED

    typedef struct _pers{
        char nome[100];
        int vida, vidaMax, pAtq, bE;
        int tipo;
        int pocao;
        int chamas, luz, cinzas, sombras; //armazenar se tem ou nao o tipo
        int defesa;
        int bufferVida, bufferAtq;
        int buffer;
        int guard;
        /*
        1 - chamas
        2 - cinzas
        3 - luz
        4 - sombras
        */
    }Pers;

    Pers pers;

    typedef struct _enemy{
        char nome[100];
        int vida, pAtq, bE;
        int tipo;
        int pocao;
        int vidaMax;
        int defesa;
        int bufferVida, bufferAtq, buffer;
        int guard;
    }Enemy;

    Enemy enemy;

    int dado();
    void batalha(int x);

    void loadEnemy(int x);
    void tela();
    void opc();
    int trocaVez(int vez);
    void persVez();
    void enemyVez();
    int fim(int *vencedor);
    int critico();
    int poderzinho(tipo1);
    int poderzinhoBot(tipo1);

#endif // GLOBAIS_FUNCOES_H_INCLUDED
