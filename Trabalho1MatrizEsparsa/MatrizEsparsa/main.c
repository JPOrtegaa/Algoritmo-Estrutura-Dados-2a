#include "matrizEsparsa.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int opcao;
    printf("Bem vindo ao calculador de Matriz Esparsa!!");
    printf("   Desenvolvido por Gustavo Queiroz e Joao Ortega\n");
    printMenu();
    scanf("%d", &opcao);
    while(opcao){
        switch(opcao){
            case 1:
                execOperacaoManual();
                break;
            case 2:
                execArquivoOperacao();
                break;
            default:
                printf("Opcao invalida!!\n");
                break;
        }
        printMenu();
        scanf("%d", &opcao);
    }

    return 0;
}
