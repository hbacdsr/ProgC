#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    int a=1,b=9,resposta=0,result=0;
while (resposta == result){
    srand(time(NULL));
    int randomNum1 = a + rand() % (b - a + 1);
    int randomNum = a + rand() % (b - a + 1);
    result =randomNum*randomNum1;
            printf("Qaunto e a multipllicação de %d por %d\n",randomNum,randomNum1);
    while (resposta != result){
        scanf("%d",&resposta);
        if (resposta == 0){
        exit(0);
        }
        else if (resposta == result){
        printf("resposta certa\n");
        }
        else {
            printf("resposta errada tenta outra vez\n");

        }
}
}
    return(0);
}