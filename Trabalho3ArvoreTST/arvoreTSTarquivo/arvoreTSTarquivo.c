#include "arvoreTSTarquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Verifica se a string contem apenas letras, sem caracteres especiais, alem de a transformar para maiusculo
// Pre-condicao: ponteiro para char deve ser uma região de memória válida
// Pos-condicao: retorna um inteiro
int verificaPalavra(char *str){
    if(*str != '\0'){
        while(*str){
            if(!(*str >= 'A' && *str <= 'Z') && !(*str >= 'a' && *str <= 'z'))
                return 0;
            if(*str >= 'a' && *str <= 'z')
                *str -= 32;
            str++;
        }
        return 1;
    }
    return 0;
}

// Realiza a leitura de um arquivo conforme o nome passado e carrega a arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido, bem como o nome do arquivo
// Pos-condicao: feita a leitura e a arvoreTST eh preenchida conforme o arquivo passado
void lerArquivoInsercao(arvoreTST *raiz, char *fileName){
    FILE *f = fopen(fileName, "r");
    int index = 0;
    char str[50];
    if(f != NULL){
        while(fscanf(f, "%s", str) != EOF)
            if(verificaPalavra(str))
                inserir(raiz, str, index++);
        fclose(f);
        printf("Arquivo carregado com sucesso!!\n\n");
    }
    else
        printf("Arquivo nao encontrado!\n\n");
}

// Insere uma nova palavra na arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: a string eh inserida na arvoreTST e seu ultimo caracter preenchido com o valor passado
void inserir(arvoreTST *raiz, char *str, int valor){
    if(*raiz == NULL){
        *raiz = (noTST*) malloc(sizeof(noTST));
        (*raiz)->letra = *str;
        (*raiz)->menor = NULL;
        (*raiz)->igual = NULL;
        (*raiz)->maior = NULL;
        if(*(str+1) == '\0')
            (*raiz)->valor = valor;
        else{
            (*raiz)->valor = -1;
            inserir(&(*raiz)->igual, str+1, valor);
        }
    }
    else{
        if(*str < (*raiz)->letra)
            inserir(&(*raiz)->menor, str, valor);
        else
            if(*str > (*raiz)->letra)
                inserir(&(*raiz)->maior, str, valor);
            else
                if(*(str+1) == '\0')
                    (*raiz)->valor = valor;
                else
                    inserir(&(*raiz)->igual, str+1, valor);
    }
}

// Busca o valor correspondente a palavra passada na arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido, bem como o ponteiro para char
// Pos-condicao: retorna um inteiro correspondente a palavra procurada na arvoreTST
int buscar(arvoreTST raiz, char *str){
    if(raiz != NULL){
        if(*str < raiz->letra)
            return buscar(raiz->menor, str);
        if(*str > raiz->letra)
            return buscar(raiz->maior, str);
        if(*str == raiz->letra){
            if(*(str+1) == '\0')
                return raiz->valor;
            else
                return buscar(raiz->igual, str+1);
        }
    }
    return -1;
}

// Realiza a leitura de um arquivo conforme o nome passado e remove palavras da arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido, bem como o nome do arquivo
// Pos-condicao: feita a leitura a arvoreTST eh atualizada removendo as palavras presentes no arquivo de remocao
void lerArquivoRemocao(arvoreTST *raiz, char *fileName){
    FILE *f = fopen(fileName, "r");
    char str[50];
    if(f != NULL){
        while(fscanf(f, "%s", str) != EOF)
            if(verificaPalavra(str))
                remover(raiz, str);
        fclose(f);
        printf("Arquivo carregado com sucesso!!\n\n");
    }
    else
        printf("Arquivo nao encontrado!!\n\n");
}

// Busca o inicio da palavra de maior tamanho lexicografico
// Pre-condicao: o ponteiro de noTST passado deve ser valido
// Pos-condicao: retorna um ponteiro de noTST contendo a maior palavra lexicografica
arvoreTST maiorElemento(arvoreTST raiz){
    if(raiz != NULL)
        if(raiz->maior != NULL)
            return maiorElemento(raiz->maior);
    return raiz;
}

// Busca o inicio da palavra de menor tamanho lexicografico
// Pre-condicao: o ponteiro de noTST passado deve ser valido
// Pos-condicao: retorna um ponteiro de noTST contendo a menor palavra lexicografica
arvoreTST menorElemento(arvoreTST raiz){
    if(raiz != NULL)
        if(raiz->menor != NULL)
            return menorElemento(raiz->menor);
    return raiz;
}

// Remove o caracter repetido
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: o caracter repetido eh removido da arvoreTST
void removeRepetido(arvoreTST *raiz, char c){
    if(raiz != NULL){
        if(c < (*raiz)->letra)
            removeRepetido(&(*raiz)->menor, c);
        else
            if(c > (*raiz)->letra)
                removeRepetido(&(*raiz)->maior, c);
            else{
                if((*raiz)->menor != NULL)
                    *raiz = (*raiz)->menor;
                else
                    if((*raiz)->maior != NULL)
                        *raiz = (*raiz)->maior;
                    else
                        *raiz = NULL;
            }
    }
}

// Remove uma palavra da arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: a arvoreTST eh atualizada com a remocao da palavra passada
void remover(arvoreTST *raiz, char *str){
    if(*raiz != NULL){
        if(*str < (*raiz)->letra)
            remover(&(*raiz)->menor, str);
        else
            if(*str > (*raiz)->letra)
                remover(&(*raiz)->maior, str);
            else
                if(*(str+1) == '\0') // talvez colocar (*raiz)->valor != -1!!
                    (*raiz)->valor = -1;
                else
                    remover(&(*raiz)->igual, str+1);
        if(((*raiz)->menor == NULL && (*raiz)->igual == NULL && (*raiz)->maior == NULL) && (*raiz)->valor == -1){
            free(*raiz);
            *raiz = NULL;
        }
        else{
            if(((*raiz)->valor == -1) && ((*raiz)->igual == NULL)){ // rotacoes
                arvoreTST aux;
                if((*raiz)->menor != NULL){ // maior dos menores
                    aux = maiorElemento((*raiz)->menor);
                    if(aux->letra != (*raiz)->menor->letra){
                        removeRepetido(&(*raiz)->menor, aux->letra);
                        aux->menor = (*raiz)->menor;
                    }
                    aux->maior = (*raiz)->maior;
                    free(*raiz);
                    *raiz = aux;
                }
                else{ // menor dos maiores
                    aux = menorElemento((*raiz)->maior);
                    if(aux->letra != (*raiz)->maior->letra){
                        removeRepetido(&(*raiz)->maior, aux->letra);
                        aux->maior = (*raiz)->maior;
                    }
                    aux->menor = (*raiz)->menor;
                    free(*raiz);
                    *raiz = aux;
                }
            }
        }
    }
}

// Imprime todas as palavras presentes na arvoreTST
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como os ponteiros para char
// Pos-condicao: todas as palavras presentes na arvoreTST sao impressas
void imprimirDicionarioAux(arvoreTST raiz, char *base, char *str){
    if(raiz != NULL){
        imprimirDicionarioAux(raiz->menor, base, str);
        *str = raiz->letra;
        if(raiz->valor != -1){
            *(str+1) = '\0';
            printf("%s\n", base);
        }
        imprimirDicionarioAux(raiz->igual, base, str+1);
        imprimirDicionarioAux(raiz->maior, base, str);
    }
}

// Imprime todas as palavras presentes na arvoreTST
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: todas as palavras presentes na arvoreTST sao impressas
void imprimirDicionario(arvoreTST raiz){
    char str[50];
    imprimirDicionarioAux(raiz, str, str);
}

// Busca o noTST correspondente a palavra passada
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: retorna um ponteiro de noTST correspondente ao ultimo caracter da palavra
arvoreTST buscaPalavra(arvoreTST raiz, char *palavra){
    if(raiz != NULL){
        if(*palavra < raiz->letra)
            return buscaPalavra(raiz->menor, palavra);
        if(*palavra > raiz->letra)
            return buscaPalavra(raiz->maior, palavra);
        if(*(palavra + 1) == '\0')
            return raiz;
        return buscaPalavra(raiz->igual, palavra+1);
    }
    return NULL;
}

// Imprime na tela todas as palavras que tenham o prefixo passado
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como os de char e de int
// Pos-condicao: eh impresso na tela todas as palavras presentes na arvoreTST que tenham o mesmo prefixo passado
void consultarPalavraAux(arvoreTST raiz, char *base, char *str, int *count){
    if(raiz != NULL){
        if(*count < 10){
            consultarPalavraAux(raiz->menor, base, str, count);
            *str = raiz->letra;
            if(raiz->valor != -1){
                *(str+1) = '\0';
                if(*count == 0)
                    printf("%s", base);
                else
                    printf(", %s", base);
                (*count)++;
            }
            consultarPalavraAux(raiz->igual, base, str+1, count);
            consultarPalavraAux(raiz->maior, base, str, count);
        }
    }
}

// Imprime na tela todas as palavras que tenham o prefixo passado
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como o de char
// Pos-condicao: eh impresso na tela todas as palavras presentes na arvoreTST que tenham o mesmo prefixo passado
void consultarPalavra(arvoreTST raiz, char *palavra){
    int count = 0;
    char str[50] = "\0";
    raiz = buscaPalavra(raiz, palavra);
    if(raiz != NULL){
        if(raiz->valor != -1){
            printf("%s", palavra);
            count++;
        }
        if(verificaPalavra(palavra)){
            strcpy(str, palavra);
            consultarPalavraAux(raiz->igual, str, str+strlen(str), &count);
        }
    }
}

// Seleciona o menor inteiro entre os 3 passados
// Pre-condicao: os inteiros passados devem ser validos
// Pos-condicao: retorna um inteiro, o menor entre os 3 passados como argumento
int menor(int x, int y, int z){
    return (x < y ? (x < z ? x : z) : (y < z ? y : z));
}

// Conta as diferencas entre duas cadeias de caracteres
// Pre-condicao: os ponteiros para char devem ser validos
// Pos-condicao: retorna um inteiro o qual eh o numero de diferencas entre as duas strings
int contaDiferencas(char *str1, char *str2){
    int i, j, n, m;
    n = strlen(str1); m = strlen(str2);
    int mat[n+1][m+1]; // 1° linha e coluna para inicializacao da matriz!!

    for(i = 0; i < n+1; i++)
        mat[i][0] = i;
    for(j = 0; j < m+1; j++)
        mat[0][j] = j;

    for(i = 1; i < n+1; i++)
        for(j = 1; j < m+1; j++)
            mat[i][j] = menor(mat[i-1][j] + 1, mat[i][j-1] + 1,
                        mat[i-1][j-1] + ((str1[i-1] == str2[j-1]) ? 0 : 1));

    return mat[n][m];
}

// Imprime na tela as palavras da arvoreTST que tenham uma quantidade de diferenca menor ou igual a palavra passada
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como os de char
// Pos-condicao: as palavras com quantidade de diferenca menor ou igual a palavra passada sao impressas na tela
void consultarSemelhante(arvoreTST raiz, char *palavra, int qtdDiferenca, char *str, char *base){
    if(raiz != NULL){
        consultarSemelhante(raiz->menor, palavra, qtdDiferenca, str, base);
        *str = raiz->letra;
        if(raiz->valor != -1){
            *(str+1) = '\0';
            if(contaDiferencas(base, palavra) <= qtdDiferenca)
                printf("%s ", base);
        }
        consultarSemelhante(raiz->igual, palavra, qtdDiferenca, str+1, base);
        consultarSemelhante(raiz->maior, palavra, qtdDiferenca, str, base);
    }
}

// Imprime na tela o menu principal do programa
// Pre-condicao: nenhuma
// Pos-condicao: imprime na tela o menu com as opcoes de operacao
void printMenu(){
    printf("-------------------------------------------------------------------------\n"
           "1 -> Carregar arquivo de palavras\n"
           "2 -> Consultar palavra\n"
           "3 -> Imprimir dicionario\n"
           "4 -> Carregar arquivo de stopwords\n"
           "5 -> Consultar semelhante\n"
           "0 -> Fechar programa\n"
           "-------------------------------------------------------------------------\n");
}

// Realiza a leitura do arquivo de insercao
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: realiza a leitura das palavras presentes no arquivo de insercao e preenche a arvoreTST
void executaLerArquivoInsercao(arvoreTST *raiz){
    char fileName[50];
    printf("Entre com o nome do arquivo (nomeArquivo.txt)\n");
    printf("> ");
    scanf("%[^\n]%*c", fileName);
    lerArquivoInsercao(raiz, fileName);
}

// Realiza a consulta das palavras presentes na arvore que contenham o prefixo passado
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: imprime na tela todas as palavras presentes na arvoreTST que contenham o prefixo passado
void executaConsultarPalavra(arvoreTST raiz){
    char palavra[50];
    printf("Entre com a palavra a ser consultada:\n");
    printf("> ");
    scanf("%s", palavra);
    if(verificaPalavra(palavra))
        consultarPalavra(raiz, palavra);
    else
        printf("Palavra invalida!!\n\n");
}

// Realiza a leitura do arquivo de remocao e deleta as palavras que estejam presentes na arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: a arvoreTST eh atualizada com as remocoes definidas pelo arquivo lido
void executaLerArquivoRemocao(arvoreTST *raiz){
    char fileName[50];
    printf("Entre com o nome do arquivo (nomeArquivo.txt)\n");
    printf("> ");
    scanf("%[^\n]%*c", fileName);
    lerArquivoRemocao(raiz, fileName);
}

// Realiza a consulta de palavras semelhantes
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: imprime na tela as palavras que tenham quantidade de diferenca menor ou igual a palavra passada
void executaConsultarSemelhante(arvoreTST raiz){
    char palavra[50], str[50] = "\0";
    int qtdDiferenca;

    printf("Entre com a palavra a ser consultada:\n");
    printf("> ");
    scanf("%s", palavra);

    if(!verificaPalavra(palavra))
        printf("Palavra invalida!!");
    else{
        printf("Entre com a quantidade de diferencas (max: 3)\n");
        printf("> ");
        scanf("%d", &qtdDiferenca);
        if(qtdDiferenca <= 3)
            consultarSemelhante(raiz, palavra, qtdDiferenca, str, str);
        else
            printf("Quantidade de diferencas maxima invalida!!");
    }
}
