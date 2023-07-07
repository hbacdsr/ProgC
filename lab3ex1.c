#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int min, max, resposta, resultado;
    min = 1;
    max = 9;

    do {
        srand(time(NULL));

        int randomNum1 = min + rand() % (max - min + 1);
        int randomNum2 = min + rand() % (max - min + 1);

        resultado = randomNum1*randomNum2;
        printf("Quanto e a multiplicação de %d por %d\n", randomNum1, randomNum2);

        while (resposta != resultado){
            scanf("%d",&resposta);

            if (!resposta) exit(0);
            else if (resposta == resultado) printf("resposta certa\n");
            else printf("resposta errada tenta outra vez\n");
        }

    } while (resposta == resultado);

    return(0);
}
