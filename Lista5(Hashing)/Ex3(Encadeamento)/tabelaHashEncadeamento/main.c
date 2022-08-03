#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 1000

typedef struct{
    int matricula;
    char nome[50];
} Registro;

typedef struct slot{
    int k; // chave
    Registro reg;
    struct slot *prox;
} Slot;

typedef Slot TabelaHash[TAM]; // Slot tabelaHash[TAM];

int funcaoHash(int k){
    return k % TAM;
}

void inicializaTabelaHash(Slot *tabela[]){
    int i;
    for(i = 0; i < TAM; i++)
        tabela[i] = NULL;
}

Slot* criarSlot(int k, Registro reg){
    Slot *aux = (Slot*) malloc(sizeof(Slot));
    aux->k = k;
    aux->reg = reg;
    aux->prox = NULL;
    return aux;
}

void inserir(Slot *tabelaHash[], int k, Registro reg){
    int hash = funcaoHash(k);
    Slot *aux = tabelaHash[hash];
    if(tabelaHash[hash] == NULL)
        tabelaHash[hash] = criarSlot(k, reg);
    else{
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = criarSlot(k, reg);
    }
}

int buscar(Slot *tabela[], int k){
    int hash = funcaoHash(k);
    Slot *aux = tabela[hash];
    while(aux != NULL && aux->k != k)
        aux = aux->prox;
    if(aux == NULL)
        return -1;
    else
        return hash;
}

void remover(Slot *tabela[], int k){
    int hash = funcaoHash(k);
    Slot *aux, *ant;
    aux = ant = tabela[hash];
    if(tabela[hash]->k == k){
        tabela[hash] = tabela[hash]->prox;
        free(aux);
    }
    else{
        aux = aux->prox;
        while(aux != NULL && aux->k != k){
            ant = aux;
            aux = aux->prox;
        }
        if(aux != NULL){
            ant->prox = aux->prox;
            free(aux);
        }
    }
}

void printTabelaHash(Slot *tabela[]){
    int i;
    Slot *aux;
    for(i = 0; i < TAM; i++){
        aux = tabela[i];
        while(aux != NULL){
            printf("slotTabela = %d\n", i);
            printf("chave (matricula) = %d\n", aux->k);
            printf("nome = [%s]\n", aux->reg.nome);
            printf("matricula = %d\n", aux->reg.matricula);
            aux = aux->prox;
        }
    }
}

int main(){
    Slot *tabelaHash[TAM];
    Registro eu;
    eu.matricula = 120932;
    strcpy(eu.nome, "Joao Pedro Ortega");
    Registro outro;
    outro.matricula = 130932;
    strcpy(outro.nome, "Gustavo Queiroz");
    Registro outro2;
    outro2.matricula = 140932;
    strcpy(outro2.nome, "Xande Torresini");

    inicializaTabelaHash(tabelaHash);
    inserir(tabelaHash, 120932, eu);
    inserir(tabelaHash, 130932, outro);
    inserir(tabelaHash, 140932, outro2);
    printTabelaHash(tabelaHash);

    printf("chave %d = pos %d\n", 130932, buscar(tabelaHash, 130932));

    remover(tabelaHash, 130932);
    printf("chave %d = pos %d\n\n\n", 140932, buscar(tabelaHash, 140932));
    printTabelaHash(tabelaHash);

    return 0;
}
