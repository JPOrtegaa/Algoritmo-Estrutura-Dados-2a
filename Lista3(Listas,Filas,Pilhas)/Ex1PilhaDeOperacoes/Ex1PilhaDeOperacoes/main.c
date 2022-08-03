#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no *prox;
};

typedef struct{
    struct no *topo;
} Pilha;

Pilha* inicializarPilha(){
    Pilha *aux = (Pilha *) malloc(sizeof(Pilha));
    aux->topo = NULL;
    return aux;
}

void push(Pilha *stk, int x){
    struct no *aux;
    aux = (struct no *) malloc(sizeof(struct no));
    aux->info = x;
    if(stk->topo == NULL){ // insercao do primeiro elemento!!
        aux->prox = NULL;
        stk->topo = aux;
    }
    else{ // empilhando os elementos!!
        aux->prox = stk->topo;
        stk->topo = aux;
    }
}

void pop(Pilha *stk){
    struct no *aux;
    aux = stk->topo;
    if(stk->topo == NULL) // caso nao tenha mais elementos na pilha!!
        printf("Pilha nao tem mais elementos para retirar!!\n");
    else{
        stk->topo = stk->topo->prox;
        free(aux);
    }
}

void imprimirPilha(Pilha *stk){
    struct no *p = stk->topo;
    if(p == NULL)
        printf("Pilha vazia!!\n");
    while(p != NULL){
        printf("%d\n", p->info);
        p = p->prox;
    }
}

int isOperacao(char c){
    return (c == '+' || c == '-' || c == 'x' || c == '/');
}

int isNumero(char c){
    return (c >= '0' && c <= '9');
}

int pilhaDeOperacoes(Pilha *stk, char str[]){
    int aux = 0;
    while(*str){
        printf("*str = %c\n", *str);
        if(isNumero(*str))
            push(stk, *str - '0');
        if(isOperacao(*str)){
            if(*str == '+'){
                aux = stk->topo->prox->info + stk->topo->info;
            }
            if(*str == '-'){
                aux = stk->topo->prox->info - stk->topo->info;
            }
            if(*str == 'x'){
                aux = stk->topo->prox->info * stk->topo->info;
            }
            if(*str == '/'){
                aux = stk->topo->prox->info / stk->topo->info;
            }
            pop(stk);
            pop(stk);
            push(stk, aux);
        }
        *str++;
    }
    return aux;
}

int main(){
    Pilha *stk = inicializarPilha();
    char str[50] = "24+31-/4x";
    int resposta;

    resposta = pilhaDeOperacoes(stk, str);

    printf("resposta = %d\n", resposta);

    return 0;
}
