#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    char nome[100];
    int idade;
    char endereco[200];
    char cidade[100];
    char CEP[12];
    char telefone[12];
    char CPF[12];
} Cliente;

int hashString(char *str, int tamArquivo){
    int count = 0;
    while(*str)
        count += *str++;
    return count % tamArquivo;
}

void escreveCliente(FILE *dados, Cliente *x, int pos){
    fseek(dados, pos * sizeof(Cliente), SEEK_SET);
    fwrite(x, sizeof(Cliente), 1, dados);
}

Cliente* leCliente(FILE *dados, int pos){
    Cliente *x = (Cliente*) malloc(sizeof(Cliente));
    fseek(dados, pos * sizeof(Cliente), SEEK_SET);
    fread(x, sizeof(Cliente), 1, dados);
    return x;
}

void inicializaArquivo(FILE *dados, int tamArquivo){
    int i;
    Cliente *x = (Cliente *) malloc(sizeof(Cliente));
    x->idade = -1;
    for(i = 0; i < tamArquivo; i++)
        escreveCliente(dados, x, i);
    free(x);
}

void inserir(FILE *dados, Cliente *x, int tamArquivo){
    int i, hash;
    Cliente *aux;
    hash = hashString(x->nome, tamArquivo);
    for(i = 0; i < tamArquivo; i++){
        aux = leCliente(dados, hash + i);
        if(aux->idade == -1){ // campo idade usado para verificar se um registro eh valido ou nao!!
            escreveCliente(dados, x, (hash + i) % tamArquivo);
            break;
        }
    }
    free(aux);
}

void remover(FILE *dados, char *nome, int tamArquivo){
    int i, hash;
    Cliente *x = NULL;
    hash = hashString(nome, tamArquivo);
    for(i = 0; i < tamArquivo; i++){
        x = leCliente(dados, (hash + i) % tamArquivo);
        if(!strcmp(x->nome, nome)){
            x->idade = -1;
            escreveCliente(dados, x, (hash + i) % tamArquivo);
            break;
        }
    }
    free(x);
}

void alterar(FILE *dados, char *nome, int tamArquivo, Cliente alterar){
    int i, hash;
    hash = hashString(nome, tamArquivo);
    Cliente *x = NULL;
    for(i = 0; i < tamArquivo; i++){
        x = leCliente(dados, (hash + i) % tamArquivo);
        if(!strcmp(nome, x->nome))
            break;
    }
    if(x->idade != -1 && (!strcmp(x->nome, nome))){
        if(strcmp(alterar.nome, "\0")){
            int idade = x->idade;
            remover(dados, x->nome, tamArquivo);
            strcpy(x->nome, alterar.nome);
            inserir(dados, x, tamArquivo);
            x->idade = idade;
            hash = hashString(x->nome, tamArquivo);
        }
        if(alterar.idade != -1)
            x->idade = alterar.idade;
        if(strcmp(alterar.endereco, "\0"))
            strcpy(x->endereco, alterar.endereco);
        if(strcmp(alterar.cidade, "\0"))
            strcpy(x->cidade, alterar.cidade);
        if(strcmp(alterar.CEP, "\0"))
            strcpy(x->CEP, alterar.CEP);
        if(strcmp(alterar.telefone, "\0"))
            strcpy(x->telefone, alterar.telefone);
        if(strcmp(alterar.CPF, "\0"))
            strcpy(x->CPF, alterar.CPF);
        escreveCliente(dados, x, (hash + i) % tamArquivo);
    }
    free(x);
}

void printCliente(Cliente *x){
    printf("Nome: %s\n", x->nome);
    printf("Idade: %d\n", x->idade);
    printf("Endereco: %s\n", x->endereco);
    printf("Cidade: %s\n", x->cidade);
    printf("CEP: %s\n", x->CEP);
    printf("Telefone: %s\n", x->telefone);
    printf("CPF: %s\n\n", x->CPF);
}

void printClientes(FILE *dados, int tamArquivo){
    Cliente *x;
    int i;
    for(i = 0; i < tamArquivo; i++){
        x = leCliente(dados, i);
        if(x->idade != -1)
            printCliente(x);
    }
    free(x);
}

void lerEntrada(char *fileName, FILE *dados, int tamArquivo){
    FILE *f = fopen(fileName, "r");
    Cliente *x = (Cliente*) malloc(sizeof(Cliente));
    char operacao;
    if(f != NULL){
        while(fscanf(f, "%c;", &operacao) != EOF){
            fscanf(f, "%[^;];", x->nome);
            fscanf(f, "%d;", &x->idade);
            fscanf(f, "%[^;];", x->endereco);
            fscanf(f, "%[^;];", x->cidade);
            fscanf(f, "%[^;];", x->CEP);
            fscanf(f, "%[^;];", x->telefone);
            fscanf(f, "%s%*c", x->CPF); // consumir '\n'!!
            switch(operacao){
            case 'I':
                inserir(dados, x, tamArquivo);
                break;
            default:
                printf("Operacao invalida!!\n");
            }
        }
        fclose(f);
    }
    free(x);
}

int main(){
    FILE *dados;
    int tamArquivo = 10;

    Cliente alterarModelo;
    strcpy(alterarModelo.nome, "Jao");
    strcpy(alterarModelo.CEP, "\0");
    alterarModelo.idade = 17;
    strcpy(alterarModelo.CPF, "\0");
    strcpy(alterarModelo.cidade, "\0");
    strcpy(alterarModelo.endereco, "\0");
    strcpy(alterarModelo.telefone, "\0");

    dados = fopen("dados.bin", "wb+");
    inicializaArquivo(dados, tamArquivo);

    lerEntrada("entrada.txt", dados, tamArquivo);

    printf("hash = %d\n", hashString("Joao Ortega", tamArquivo));
    printf("hash = %d\n", hashString("Arthur Silva", tamArquivo));
    printf("hash = %d\n", hashString("Maria Joaquina", tamArquivo));
    printf("hash = %d\n", hashString("Bruno Laz", tamArquivo));

    printClientes(dados, tamArquivo);

    remover(dados, "Bruno Laz", tamArquivo);

    alterar(dados, "Joao Ortega", tamArquivo, alterarModelo);

    printClientes(dados, tamArquivo);

    fclose(dados);

    return 0;
}
