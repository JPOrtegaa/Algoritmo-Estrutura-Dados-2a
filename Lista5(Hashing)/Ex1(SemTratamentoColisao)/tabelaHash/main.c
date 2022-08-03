#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 1000

typedef struct{
    int matricula;
    char nome[50];
} Registro;

typedef struct{
    int k; // chave
    Registro reg;
    int ocupado;
} Slot;

typedef Slot TabelaHash[TAM]; // Slot tabelaHash[TAM];

int funcaoHash(int k){
    return k % TAM;
}

void inicializaTabelaHash(TabelaHash tabela){
    int i;
    Registro inicializa;
    inicializa.matricula = 0;
    strcpy(inicializa.nome, "\0");
    for(i = 0; i < TAM; i++){
        tabela[i].k = 0;
        tabela[i].reg = inicializa;
        tabela[i].ocupado = 0;
    }
}

void inserir(TabelaHash tabela, int k, Registro reg){
    int hash = funcaoHash(k);
    if(!tabela[hash].ocupado){ // se nao estiver ocupado o slot, insira!
        tabela[hash].k = k;
        tabela[hash].reg = reg;
        tabela[hash].ocupado = 1;
    }
    else
        printf("posicao ocupada!!\n");
}

int buscar(TabelaHash tabela, int k){
    int hash = funcaoHash(k);
    if(tabela[hash].ocupado)
        return hash;
    return -1;
}

void remover(TabelaHash tabela, int k){
    int hash = funcaoHash(k);
    tabela[hash].k = 0;
    tabela[hash].reg.matricula = 0;
    strcpy(tabela[hash].reg.nome, "\0");
    tabela[hash].ocupado = 0;
}

void printTabelaHash(TabelaHash tabela){
    int i;
    for(i = 0; i < TAM; i++)
        if(tabela[i].ocupado == 1){
            printf("slotTabela = %d\n", i);
            printf("chave (matricula) = %d\n", tabela[i].k);
            printf("nome = [%s]\n", tabela[i].reg.nome);
            printf("matricula = %d\n", tabela[i].reg.matricula);
        }
}

int main(){
    TabelaHash tabela; // TabelaHash = Slot tabela[TAM]!!
    Registro eu;
    eu.matricula = 120932;
    strcpy(eu.nome, "Joao Pedro Ortega");

    inicializaTabelaHash(tabela);
    inserir(tabela, 120932, eu);
    inserir(tabela, 120932, eu);
    printTabelaHash(tabela);
    printf("chave %d = pos %d\n", 120932, buscar(tabela, 120932));
    remover(tabela, 120932);
    printf("chave %d = pos %d\n", 120932, buscar(tabela, 120932));

    return 0;
}
