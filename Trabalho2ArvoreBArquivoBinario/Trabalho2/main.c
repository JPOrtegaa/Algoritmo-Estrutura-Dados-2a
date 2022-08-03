#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvorebarquivo.h"

int main(){
    FILE *index, *dados;
    arvoreB raiz;
    CabecalhoIndex cab;
    int opcao;
    char arquivoTexto[50];

    index = fopen("ArquivoIndex.bin", "rb+");
    dados = fopen("ArquivoDados.bin", "rb+");

    if(index == NULL){
        index = fopen("ArquivoIndex.bin", "wb+");
        criarCabecalhoIndex(index);
    }

    if(dados == NULL){
        dados = fopen("ArquivoDados.bin", "wb+");
        criarCabecalhoDados(dados);
    }

    printf("Trabalho desenvolvido pelos discentes Joao Ortega e Yuri Bueno!\n");
    printMenu();
    printf("> ");
    scanf("%d%*c", &opcao);
    while(opcao != 0){
        switch(opcao){
        case 1:
            inserirProfissionalManual(index, dados);
            break;
        case 2:
            removerProfissionalManual(index, dados);
            break;
        case 3:
            alterarEnderecoManual(index, dados);
            break;
        case 4:
            alterarTelefoneManual(index, dados);
            break;
        case 5:
            printf("Entre com o nome do arquivo txt (arquivoTexto.txt):\n");
            printf("> ");
            scanf("%[^\n]%*c", arquivoTexto);
            lerArquivoEntrada(arquivoTexto, index, dados);
            break;
        case 6:
            printProfissionalManual(index, dados);
            break;
        case 7:
            cab = leCabecalhoIndex(index);
            if(cab.raiz != -1){
                raiz = leNo(index, cab.raiz);
                printInOrdem(index, dados, raiz);
            }
            else
                printf("Arvore vazia!!\n");
            break;
        case 8:
            cab = leCabecalhoIndex(index);
            if(cab.raiz != -1){
                raiz = leNo(index, cab.raiz);
                printPorNivel(index, raiz);
            }
            else
                printf("Arvore vazia!!\n");
            break;
        case 9:
            printPosLivreDados(dados);
            break;
        case 10:
            printPosLivreIndex(index);
            break;
        default:
            printf("Opcao invalida!!\n");
        }
        printf("\n");
        printMenu();
        printf("> ");
        scanf("%d%*c", &opcao);
    }

    fclose(index);
    fclose(dados);

    return 0;
}
