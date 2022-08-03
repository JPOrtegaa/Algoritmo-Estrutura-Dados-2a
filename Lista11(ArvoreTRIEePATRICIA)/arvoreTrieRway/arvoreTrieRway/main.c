#include <stdio.h>
#include <stdlib.h>

#define ALFABETO 26
#define letraA 65

struct noRTrie{
    struct noRTrie *filho[ALFABETO];
    int valor;
} ;

typedef struct noRTrie* noR;

typedef struct{
    noR raiz;
} arvoreRway;

noR criarNo(){
    noR aux = (noR) malloc(sizeof(struct noRTrie));
    aux->valor = -1;
    for(int i = 0; i < ALFABETO; i++)
        aux->filho[i] = NULL;
    return aux;
}

arvoreRway* criarArvore(){
    arvoreRway *aux = (arvoreRway*) malloc(sizeof(arvoreRway));
    aux->raiz = NULL;
    return aux;
}

void inserir(arvoreRway *arvore, char *str, int valor){
    noR aux = arvore->raiz;
    while(*str){
        if(aux == NULL){
            aux = criarNo();
            aux->filho[*str-letraA] = criarNo();
            arvore->raiz = aux;
        }
        else
            if(aux->filho[*str-letraA] == NULL)
                aux->filho[*str-letraA] = criarNo();
        aux = aux->filho[*str-letraA];
        str++;
    }
    aux->valor = valor;
}

int buscar(arvoreRway *arvore, char *str){
    noR aux = arvore->raiz;
    while(*str){
        if(aux == NULL)
            return -1;
        aux = aux->filho[*str-letraA];
        str++;
    }
    if(aux != NULL)
        return aux->valor;
    return -1;
}

int temFilho(noR raiz){
    for(int i = 0; i < ALFABETO; i++)
        if(raiz->filho[i] != NULL)
            return 1;
    return 0;
}

void removerAux(noR *raiz, char *str){
    if(*str){
        if(*raiz != NULL){
            removerAux(&(*raiz)->filho[*str-letraA], str+1);
            if(!temFilho(*raiz) && (*raiz)->valor == -1){
                free(*raiz);
                *raiz = NULL;
            }
        }
    }
    else{
        if(*raiz != NULL){
            if(!temFilho(*raiz)){
                free(*raiz);
                *raiz = NULL;
            }
            else
                (*raiz)->valor = -1;
        }
    }
}

void remover(arvoreRway *arvore, char *str){
    removerAux(&arvore->raiz, str);
}

void imprimirDicionarioAux(noR raiz, char *base, char *str){
    if(raiz != NULL){
        if(raiz->valor != -1){
            *str = '\0';
            printf("%s\n", base);
        }
        for(int i = 0; i < ALFABETO; i++){
            if(raiz->filho[i] != NULL){
                *str = letraA + i;
                imprimirDicionarioAux(raiz->filho[i], base, str+1);
            }
        }
    }
}

void imprimirDicionario(arvoreRway *arvore){
    char str[50] = "\0";
    imprimirDicionarioAux(arvore->raiz, str, str);
}

int main(){
    arvoreRway *arvore = criarArvore();

    inserir(arvore, "PAI", 1);
    inserir(arvore, "PAIS", 2);
    inserir(arvore, "PATA", 3);
    inserir(arvore, "CAMA", 4);
    inserir(arvore, "RAIO", 5);
    inserir(arvore, "RISO", 6);
    inserir(arvore, "RUA", 7);
    inserir(arvore, "TETO", 8);

    imprimirDicionario(arvore);
    printf("\n");

    printf("string = %d\n", buscar(arvore, "PAI"));

    //remover(arvore, "PAI");
    remover(arvore, "PAIS");
    remover(arvore, "PATA");
    remover(arvore, "CAMA");
    //remover(arvore, "RAIO");
    //remover(arvore, "RISO");
    remover(arvore, "RUA");
    //remover(arvore, "TETO");

    imprimirDicionario(arvore);
    printf("\n");

    printf("string = %d\n", buscar(arvore, "RAIO"));

    printf("FUNCIONA!!\n");

    return 0;
}
