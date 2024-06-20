#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "globais_funcoes.h"


int dado(){
    int min = 1, max=12, num;

    //[0,max]
    num = rand() % (max - min + 1);

    //[min,max]
    num = num + min;

    return num;
}
