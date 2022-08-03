#include <stdio.h>
#include <stdlib.h>

struct no{
    char info;
    struct no *prox;
};

typedef struct{
    struct no *topo;
} Pilha;

Pilha *inicializar(){
    Pilha *aux = (Pilha *) malloc(sizeof(Pilha));
    aux->topo = NULL;
    return aux;
}

int pilhaVazia(Pilha *stk){
    return (stk->topo == NULL);
}

void push(Pilha *stk, char x){
    struct no *aux = (struct no *) malloc(sizeof(struct no));
    aux->info = x;
    if(stk->topo == NULL){
        aux->prox = NULL;
        stk->topo = aux;
    }
    else{
        aux->prox = stk->topo;
        stk->topo = aux;
    }
}

void pop(Pilha *stk){
    struct no *aux;
    if(stk->topo == NULL)
        printf("Pilha nao tem mais elementos para retirar!!\n");
    else{
        aux = stk->topo;
        stk->topo = stk->topo->prox;
        free(aux);
    }
}

void imprimePilha(Pilha *stk){
    struct no *aux;
    if(stk->topo == NULL)
        printf("Pilha vazia!!\n");
    aux = stk->topo;
    while(aux != NULL){
        printf("%c\n", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int analisaParentesis(char str[]){
    Pilha *stk = inicializar();
    while(*str){
        if(*str == '(')
            push(stk, '(');
        if(*str == ')'){
            if(pilhaVazia(stk))
                return 0;
            pop(stk);
        }
        *str++;
    }
    return pilhaVazia(stk);
}

int main(){
    char str[50]  = "(a+b) x ((c+d) - 5)";
    char str2[50] = "(((a-b) x c) - (7 + d))";
    char str3[50] = "(((a+b) - c)";
    char str4[50] = "(5+a)) + 7)";

    if(analisaParentesis(str))
        printf("%s 		tem balanceamente de parentesis!!\n", str);
    else
        printf("%s      nao tem balanceamento de parentesis!!\n", str);

    if(analisaParentesis(str2))
        printf("%s 	tem balanceamente de parentesis!!\n", str2);
    else
        printf("%s  nao tem balanceamento de parentesis!!\n", str2);

    if(analisaParentesis(str3))
        printf("%s 			tem balanceamente de parentesis!!\n", str3);
    else
        printf("%s 			nao tem balanceamento de parentesis!!\n", str3);

    if(analisaParentesis(str4))
        printf("%s 			tem balanceamente de parentesis!!\n", str4);
    else
        printf("%s 			nao tem balanceamento de parentesis!!\n", str4);
    printf("\n");


    return 0;
}
