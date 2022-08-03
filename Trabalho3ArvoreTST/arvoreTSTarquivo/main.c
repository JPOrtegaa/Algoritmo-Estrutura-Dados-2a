#include "arvoreTSTarquivo.h"
#include <stdio.h>

int main(){
    arvoreTST raiz = NULL;
    int opcao = 0;

    printf("Arvore TST implementada pelos discentes Joao Ortega e Matheus Souza!\n");
    printMenu();
    printf("> ");
    scanf("%d%*c", &opcao);
    while(opcao != 0){
        switch(opcao){
        case 1:
            executaLerArquivoInsercao(&raiz);
            break;
        case 2:
            if(raiz != NULL)
                executaConsultarPalavra(raiz);
            else
                printf("Arvore vazia!!");
            printf("\n\n");
            break;
        case 3:
            if(raiz != NULL)
                imprimirDicionario(raiz);
            else
                printf("Arvore vazia!!\n\n");
            break;
        case 4:
            executaLerArquivoRemocao(&raiz);
            break;
        case 5:
            if(raiz != NULL)
                executaConsultarSemelhante(raiz);
            else
                printf("Arvore vazia!!");
            printf("\n\n");
            break;
        default:
            printf("Opcao invalida!!\n\n");
        }
        printMenu();
        printf("> ");
        scanf("%d%*c", &opcao);
    }

    return 0;
}
