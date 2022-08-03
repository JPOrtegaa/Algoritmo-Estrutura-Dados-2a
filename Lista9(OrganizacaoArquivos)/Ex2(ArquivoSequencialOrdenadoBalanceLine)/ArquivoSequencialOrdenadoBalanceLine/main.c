#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    char nome[100];
    int idade;
    char endereco[200];
    char cidade[100];
    char CEP[14];
    char telefone[14];
    char CPF[14];
} Cliente;

void escreveDado(FILE *dados, Cliente *x){
    Cliente i;
    //int flag = 1;
    fseek(dados, 0, SEEK_SET);
    while(fread(&i, sizeof(Cliente), 1, dados) == 1){
        if(i.nome[0] == '\0')
            break;
        if(strcmp(x->nome, i.nome) < 0){
            fseek(dados, -1 * (int)sizeof(Cliente), SEEK_CUR); // volte um Cliente!!
            fwrite(x, sizeof(Cliente), 1, dados);
            *x = i;
        }
    }
    fwrite(x, sizeof(Cliente), 1, dados);
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

void lerEntrada(char *fileName, FILE *dados){
    FILE *f = fopen(fileName, "r");
    Cliente *x = (Cliente*) malloc(sizeof(Cliente));
    if(f != NULL){
        while(fscanf(f, "%[^;];", x->nome) != EOF){
            fscanf(f, "%d;", &x->idade);
            fscanf(f, "%[^;];", x->endereco);
            fscanf(f, "%[^;];", x->cidade);
            fscanf(f, "%[^;];", x->CEP);
            fscanf(f, "%[^;];", x->telefone);
            fscanf(f, "%s%*c", x->CPF); // consumir '\n'!!
            escreveDado(dados, x);
        }
        fclose(f);
    }
    free(x);
}

int main(){
    Cliente *x = (Cliente*) malloc(sizeof(Cliente));
    FILE *dados = NULL;

    printf("size = %d\n", -(int)sizeof(Cliente));

    //dados = fopen("dados.bin", "rb+");
    if(dados == NULL)
        dados = fopen("dados.bin", "wb+");

    lerEntrada("entrada.txt", dados);

    fseek(dados, 0, SEEK_SET);
    fread(x, sizeof(Cliente), 1, dados);
    printCliente(x);
    fread(x, sizeof(Cliente), 1, dados);
    printCliente(x);
    fread(x, sizeof(Cliente), 1, dados);
    printCliente(x);
    /*fseek(dados, -2 * (int)sizeof(Cliente), SEEK_CUR);
    fread(x, sizeof(Cliente), 1, dados);
    printCliente(x);*/



    fclose(dados);
    free(x);

    return 0;
}
