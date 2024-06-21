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
    printf("  Mana: %d \t\t\t\t\t      Mana: %d ",pers.bE, enemy.bE);
    printf("\n\t\t\t ");
    printf("  Poção: %d \t\t\t\t\t      Poção: %d ",pers.pocao, enemy.pocao);
    printf("\n\t\t\t ");
    printf("  Poção Tanque: %d \t\t\t\t      Poção Tanque: %d ",pers.bufferVida, enemy.bufferVida);
    printf("\n\t\t\t ");
    printf("  Poção Força: %d \t\t\t\t      Poção Força: %d ",pers.bufferAtq, enemy.bufferVida);

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
    char cwd[200] = {"C:\\Users\\user\\Desktop\\Faculdade\\Fire Tale\\Protoptipo-batalha\\inimigos\\"};
    char num[5];
    sprintf(num, "%d", x);

    strcat(cwd, num);
    strcat(cwd, ".txt");



    //preencher dados do inimigo
    FILE *f;
    f = fopen(cwd, "r");
    fscanf(f, "%100[^\n]", enemy.nome);
    fscanf(f, "%d %d %d %d %d %d %d %d", &enemy.vida, &enemy.pAtq,  &enemy.tipo, &enemy.pocao, &enemy.vidaMax, &enemy.defesa, &enemy.bufferVida, &enemy.bufferAtq);
    enemy.buffer = 0;
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
    int acao, acaoAtq, acaoInv, dad,  dano=0, voltar=1, temp, crit = 1, esquiva = 0;
    pers.guard = 0;
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
        int tipo;
        while(voltar){
        tela();
        printf("\n\n\n\n\n");
        printf("\t\t\t\t\t\t       Sua vez   \n");
        printf("\t\t\t\t\t\t>------------------<\n\n");

        printf("\t\t--> Escolha um ataque: \n\n");
        printf("\t\t    > Normal    [1]\n");
        printf("\t\t    > Especial  [2]\n\n");


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
                dano = poderzinho(pers.tipo);
                tipo = verTipo(pers.tipo, enemy.tipo);

                if(tipo){
                    dano = (dano*5)/4;
                }

                if(dano != 0)
                    voltar = 0;

            }
        }

        crit = critico();

        if(crit == 1){
            dano = dano*2;
        }

        dano = (dano + (pers.buffer*2)) - ((dado()/3 + enemy.defesa/3) + enemy.guard);
        pers.buffer = 0;

        esquiva = critico();

        if(esquiva == 0){
        enemy.vida = enemy.vida - dano;


        system("cls");
        if(crit == 1){
            printf("\n\n\n\t\t\t\t\t   Acerto critico!!\n\n");
        }
        if(tipo == 1 && acaoAtq == 2){
            printf("\n\n\n\t\t\t\t\t     SEU ATAQUE EH SUPER EFETIVO!\n\n\n");
        }
        printf("\n\n\n\t\t\t\t\tVoce causou %d de dano no seu inimigo\n\n\n\n", dano);
        printf("Aperte ENTER para continuar");
        c = getchar();

    } else {

            if(acaoAtq == 1){
                pers.bE = pers.bE - 5 - dad;
            }
        system("cls");
        printf("\n\n\n\t\t\t\t  Ele se esquivou do seu ataque!\n\n\n\n");
        printf("Aperte ENTER para continuar");
        c = getchar();
    }
    }

    if(acao ==2){
        system("cls");
        tela();
        while(voltar){
            printf("\n\n\n");
            printf("\t\t--> Escolha um item: \n\n");
            printf("\t\t    > Poção de cura  [1]\n");
            printf("\t\t    > Poção Tanque   [2] \n");
            printf("\t\t    > Poção Força    [3]\n");
            printf("\t\t    > Escudo         [4]\n\n");
            printf("\t\t       -> ");
            scanf("%d",&acaoInv);
            if(acaoInv == 1){
                if(pers.vida == pers.vidaMax){
                    system("cls");
                    printf("\n\n\nJa está com vida máxima!\n\n\n");
                    printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                    voltar = 0;
                }
                if(pers.pocao>0){
                    system("cls");
                    printf("\n\nVocê se sente revigorado!!!\n\n");
                    printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                    voltar = 0;
                    pers.pocao--;
                    pers.vida = pers.vida + 50;
                    if(pers.vida>100){
                            temp = pers.vida - pers.vidaMax;
                            pers.vida = pers.vida - temp;
                    }
                }
                else{
                    printf("\n\nVocê não tem poção de vida! ");
                    printf("\n\nAperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                    system("cls");
                }
            }
            if(acaoInv == 2){
                if(pers.bufferVida > 0){
                    voltar = 0;
                    pers.bufferVida--;
                    pers.vida = pers.vida + (pers.vidaMax/2);
                    system("cls");
                    printf("\n\nVocê se sente mais forte!\n\n");
                    printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                } else {
                    printf("\n\nVocê não tem poção Tanque!!\n\n");
                    printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                    system("cls");
                }
            }

            if(acaoInv == 3){
                if(pers.bufferAtq > 0){
                    voltar = 0;
                    pers.bufferAtq--;
                    pers.buffer = pers.pAtq;
                    system("cls");
                    printf("\n\nVocê sente que seu próximo ataque será poderoso!!!\n\n");
                    printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                } else {

                    printf("\n\nVocê não tem poção de Força!\n\n");
                    printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                    system("cls");
                }
            }

            if(acaoInv == 4){
                voltar = 0;
                printf("\n\nVocê decide se proteger!\n\n");
                printf("Aperte ENTER para continuar");
                c = getchar();
                c = getchar();
                pers.guard = pers.defesa;
                system("cls");
            }

            if(acaoInv > 4){
                system("cls");
                voltar = 0;
                printf("\n\nOh, não! Ele foi mais rápido!");
                printf("\n\nVocê perdeu a vez!\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
            }
        }

    }



}



//---------------------------------------------------------------------------------------------------------------

int verTipo(int tipo1, int tipo2){
    if(tipo1 == 1 && tipo2 == 2)
        return 1;
    if(tipo1 == 2 && tipo2 == 3)
        return 1;
    if(tipo1 == 3 && tipo2 == 4)
        return 1;
    if(tipo1 == 4 && tipo2 == 1)
        return 1;

    return 0;
}

//---------------------------------------------------------------------------------------------------------------

void enemyVez(){
    int acao, acaoAtq, acaoInv, dad,  dano=0, voltar=1, temp, crit = 0, esquiva = 0;
    enemy.guard = 0;
    char c;

    printf("\n\n\n\n\n");
    printf("\t\t\t\t\t       Vez do %s   \n", enemy.nome);
    printf("\t\t\t\t\t      >---------------------------<\n\n");

    printf("\t\t--> Escolha sua ação\n\n");
    printf("\t\t    > Atacar    [1]\n");
    printf("\t\t    > Usar item [2]\n\n");
    printf("\t\t       -> ");

    acao = dado();

    if(acao > 4){
    printf("1");
    acao = 1;
    _sleep(1300);
    system("cls");

    } else {

    printf("2");
    acao = 2;
    _sleep(1300);
    system("cls");
    }

    if(acao==1){
        int tipo;
        tela();
        printf("\n\n\n\n\n");
        printf("\t\t\t\t\t       Vez do %s   \n", enemy.nome);
        printf("\t\t\t\t\t      >---------------------------<\n\n");

        printf("\t\t--> Escolha um ataque: \n\n");
        printf("\t\t    > Normal    [1]\n");
        printf("\t\t    > Especial  [2]\n\n");

        while(voltar){
            printf("\t\t       -> ");

            if(enemy.bE >= 15){
            acaoAtq = dado();

            if(acaoAtq >= 1 && acaoAtq <= 4){
                acaoAtq = 2;
            } else {
                acaoAtq = 1;
            }

            printf("%d", acaoAtq);
            _sleep(1300);

            dad = dado();
            if(acaoAtq == 1){
                dano = dad + (enemy.pAtq / 2);
                dad = dado();
                enemy.bE = enemy.bE + dad + 5;
                voltar = 0;
            }

            if(acaoAtq == 2){
                dano = poderzinhoBot(enemy.tipo);
                tipo = verTipo(enemy.tipo, pers.tipo);

                if(tipo){
                    dano = (dano*5)/4;
                }

                if(dano != 0)
                    voltar = 0;

            }

            } else {
                printf("1");
                _sleep(1300);
                dad = dado();
                dano = dad + (enemy.pAtq / 2);
                dad = dado();
                enemy.bE = enemy.bE + dad + 5;
                voltar = 0;
            }

            crit = critico();

            if(crit == 1){
                dano = dano*2;
            }

        dano = (dano + (enemy.buffer * 2)) - ((dado()/3 + pers.defesa/3) + pers.guard);

        esquiva = critico();

        if(esquiva == 0){

        pers.vida = pers.vida - dano;


        system("cls");
        if(crit == 1){
            printf("\n\n\n\t\t\t\t\t Acerto critico!!\n\n\n");
        }
        if(tipo == 1 && acaoAtq == 2){
            printf("\n\n\n\t\t\t\t\t  O ATAQUE EH SUPER EFETIVO!\n\n\n");
        }
        printf("\n\n\n\t\t\t\t\tEle causou %d de dano em voce\n\n\n\n", dano);
        _sleep(1300);

        } else {
            if(acaoAtq == 1){
                enemy.bE = enemy.bE - 5 - dad;
            }
        system("cls");
        printf("\n\n\n\t\t\t\t\t  Voce se esquivou do ataque!!");
        _sleep(1500);
        }
    }

}
if(acao ==2){
        system("cls");
        tela();
        while(voltar){
            printf("\n\n\n");
            printf("\t\t--> Escolha um item: \n\n");
            printf("\t\t    > Poção de cura  [1]\n");
            printf("\t\t    > Poção Tanque   [2] \n");
            printf("\t\t    > Poção Força    [3]\n");
            printf("\t\t    > Escudo         [4]\n\n");
            printf("\t\t       -> ");

            acaoInv = (dado()%12) + 1;

                //criando chances maiores dele usar guard.
            if(acaoInv >= 1 && acaoInv <= 2){
                acaoInv = 1;
            } else if(acaoInv >= 3 && acaoInv <= 5){
                acaoInv = 2;
            } else if(acaoInv >= 6 && acaoInv <= 8){
                acaoInv = 3;
            } else
                acaoInv = 4;

                //Tirar casos em que ele não tem poções específicas.
            if(acaoInv == 1 && enemy.vida >= enemy.vidaMax || acaoInv == 1 && enemy.pocao == 0 ){
                acaoInv = 2;
            }
            if(acaoInv == 2 && enemy.bufferVida == 0){
                acaoInv = 3;
            }
            if(acaoInv == 3 && enemy.bufferAtq == 0){
                acaoInv = 4;
            }

            printf("%d", acaoInv);
            _sleep(1300);

            if(acaoInv == 1){
                if(enemy.pocao>0){
                    system("cls");
                    printf("\n\nSeu adversário parece se sentir revigorado!");
                    _sleep(2000);
                    voltar = 0;
                    enemy.pocao--;
                    enemy.vida = enemy.vida + 30;
                    if(enemy.vida>enemy.vidaMax){
                            enemy.vida = enemy.vidaMax;
                    }
                }
        }
            if(acaoInv == 2){
                system("cls");
                printf("\n\nSeu adversário parece estar maior!!");
                _sleep(2000);
                enemy.bufferVida--;
                enemy.vida = enemy.vida + (enemy.vidaMax/2);
                voltar = 0;
            }

            if(acaoInv == 3){
                    system("cls");
                    printf("\n\nSeu adversário parece estar se preparando para um ataque poderoso!!");
                    _sleep(2000);
                enemy.bufferAtq--;
                enemy.buffer = enemy.pAtq;
                voltar = 0;
            }

            if(acaoInv == 4){
                    system("cls");
                    printf("\n\nSeu adversário está se protegendo!!");
                    _sleep(2000);
                enemy.guard = enemy.defesa;
                voltar = 0;
            }

    }

}
}

//---------------------------------------------------------------------------------------------------------------

int fim(int *vencedor){
    if(enemy.vida <= 0){
        printf("Voce venceu!");
        *vencedor = 1;
        return 0;
    } else
    if(pers.vida <= 0){
        printf("Voce perdeu!");
        *vencedor = 0;
        return 0;
    } else
    return 1;
}

//---------------------------------------------------------------------------------------------------------------

int critico(){
    int crit1, crit2;

    crit1 = dado();
    crit2 = dado();

    if(crit1 == crit2){
        return 1;
    } else
    return 0;
}

//----------------------------------------------------------------------------------------------------------------

int poderzinho(tipo1){
    int voltar = 1, dano = 0, hab;
    char c;
    while(voltar){
            system("cls");
            tela();

        if(tipo1 == 1){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Chama: \n\n");
            printf("\t\t    > Bola de Fogo         [1] (15 Especial)\n");
            printf("\t\t    > Rajada Incendiária   [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");

            scanf("%d", &hab);

            if(hab == 1)
                if (pers.bE >= 15){
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                pers.bE = pers.bE - 15;
                system("cls");
                printf("\n\nO local fica mais quente e uma esfera calorosa surge entre suas palmas\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();


            } else {

                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 2)
            if(pers.bE >= 60){
                dano = (pers.pAtq * 2) + dado()*3;
                pers.bE = pers.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nA temperatura está aumentando, você se sente ardente\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();

            } else {
                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 3){
                voltar = 0;
                dano = 0;
            }
        }

            if(tipo1 == 2){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Cinzas: \n\n");
            printf("\t\t    > Decadência           [1] (15 Especial)\n");
            printf("\t\t    > Fim Inevitável       [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");

            scanf("%d", &hab);

            if(hab == 1)
                if (pers.bE >= 15){
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                pers.bE = pers.bE - 15;
                system("cls");
                printf("\n\nO cheiro de podridão toma conta do ambiente\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
            } else {

                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 2)
            if(pers.bE >= 60){
                dano = (pers.pAtq * 2) + dado()*3;
                pers.bE = pers.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nO Cenário se distorce com tamanho poder, nem a sombras pode escapar do fim\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();

            } else {
                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 3){
                voltar = 0;
                dano = 0;
            }
        }

            if(tipo1 == 3){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Luz: \n\n");
            printf("\t\t    > Aurora Boreal        [1] (15 Especial)\n");
            printf("\t\t    > Centelha Final       [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");

            scanf("%d", &hab);

            if(hab == 1)
                if (pers.bE >= 15){
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                pers.bE = pers.bE - 15;
                system("cls");
                printf("\n\nA luz queima todos que buscam a destruição\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
            } else {

                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 2)
            if(pers.bE >= 60){
                dano = (pers.pAtq * 2) + dado()*3;
                pers.bE = pers.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nOs Deuses lhe deram as bençãos para isso, não faça eles se arrependerem\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();

            } else {
                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 3){
                voltar = 0;
                dano = 0;
            }
        }

                    if(tipo1 == 4){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Sombras: \n\n");
            printf("\t\t    > Aura Sombria         [1] (15 Especial)\n");
            printf("\t\t    > Buraco Negro         [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");

            scanf("%d", &hab);

            if(hab == 1)
                if (pers.bE >= 15){
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                pers.bE = pers.bE - 15;
                system("cls");
                printf("\n\nAs sombras se mexem, quase como se tivessem vida prórpia\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
            } else {

                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 2)
            if(pers.bE >= 60){
                dano = (pers.pAtq * 3) + dado()*2;
                pers.bE = pers.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nNenhuma luz escapa das trevas\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();

            } else {
                printf("\n\nVocê não tem Mana o suficiente.\n\n");
                printf("Aperte ENTER para continuar");
                    c = getchar();
                    c = getchar();
                voltar = 0;
                dano = 0;
            }

            if(hab == 3){
                voltar = 0;
                dano = 0;
            }
        }


    }
    return dano;
}

int poderzinhoBot(tipo1){
    int voltar = 1, dano = 0, hab;
    char c;
    while(voltar){
            system("cls");
            tela();

        if(tipo1 == 1){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Chama: \n\n");
            printf("\t\t    > Bola de Fogo         [1] (15 Especial)\n");
            printf("\t\t    > Rajada Incendiária   [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");

            if(enemy.bE >= 15 && enemy.bE < 60){

                printf("1");
                _sleep(1300);
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                enemy.bE = enemy.bE - 15;
                system("cls");
                printf("\n\nO local fica mais quente e uma esfera ardende sai de sua boca\n\n");
                _sleep(2000);

                } else {
                printf("2");
                _sleep(2000);
                dano = (enemy.pAtq * 3) + dado()*2;
                enemy.bE = enemy.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nA temperatura está aumentando, você sente seu corpo queimar\n\n");
                _sleep(2000);

                }
        }

            if(tipo1 == 2){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Cinzas: \n\n");
            printf("\t\t    > Decadência           [1] (15 Especial)\n");
            printf("\t\t    > Fim Inevitável       [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");


            if(enemy.bE >= 15 && enemy.bE < 60){

            printf("1");
            _sleep(1300);
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                enemy.bE = enemy.bE - 15;
                system("cls");
                printf("\n\nO cheiro de podridão toma conta do ambiente\n\n");
            _sleep(2000);

            } else {

            printf("2");
            _sleep(1300);
                dano = (enemy.pAtq * 3) + dado()*2;
                enemy.bE = enemy.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nO Cenário se distorce com tamanho poder, nem as sombras podem escapar do fim\n\n");
            _sleep(2000);
            }


        }

            if(tipo1 == 3){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Luz: \n\n");
            printf("\t\t    > Aurora Boreal        [1] (15 Especial)\n");
            printf("\t\t    > Centelha Final       [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");

            if(enemy.bE >= 15 && enemy.bE < 60){

            printf("1");
            _sleep(1300);
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                enemy.bE = enemy.bE - 15;
                system("cls");
                printf("\n\nA luz queima todos que buscam a destruição\n\n");
            _sleep(2000);
            } else {

            printf("2");
            _sleep(1300);
                dano = (enemy.pAtq * 3) + dado()*2;
                enemy.bE = enemy.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nOs Deuses desaprovam a criatura, mas eles não se arrependem\n\n");
            _sleep(2000);

        }
            }

                    if(tipo1 == 4){

            printf("\n\n\n");
            printf("\t\t--> Escolha uma habilidade do tipo Sombras: \n\n");
            printf("\t\t    > Aura Sombria         [1] (15 Especial)\n");
            printf("\t\t    > Buraco Negro         [2] (60 Especial) \n");
            printf("\t\t    > Voltar               [3]\n");
            printf("\t\t       -> ");

            if(enemy.bE >= 15 && enemy.bE < 60){

            printf("1");
            _sleep(1300);
                dano = ((pers.pAtq * 3)/2) + dado();
                voltar = 0;
                enemy.bE = enemy.bE - 15;
                system("cls");
                printf("\n\nAs sombras se mexem, quase como se tivessem vida prórpia\n\n");
            _sleep(2000);
            } else {

            printf("2");
            _sleep(1300);
                dano = (enemy.pAtq * 3) + dado()*2;
                enemy.bE = enemy.bE - 60;
                voltar = 0;
                system("cls");
                printf("\n\nNenhuma luz escapa das trevas\n\n");
            _sleep(2000);
        }


    }
    }
    return dano;
}
