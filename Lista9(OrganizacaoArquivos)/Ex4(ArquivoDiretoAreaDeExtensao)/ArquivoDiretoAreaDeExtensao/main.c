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
    int elo; // link para arquivo de extensao!!
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
    x->elo = -1;
    for(i = 0; i < tamArquivo; i++)
        escreveCliente(dados, x, i);
    free(x);
}

int procuraRegistroDisponivel(FILE *extensao, int tamArquivo){
    Cliente *x;
    int i;
    for(i = 0; i < tamArquivo; i++){
        x = leCliente(extensao, i);
        if(x->idade == -1)
            return i;
    }
    free(x);
    return -1;
}

void inserir(FILE *dados, FILE *extensao, Cliente *x, int tamArquivo){
    int hash, slot, flag = 0, pos;
    Cliente *aux;
    hash = hashString(x->nome, tamArquivo);
    aux = leCliente(dados, hash);
    if(aux->idade != -1){
        slot = procuraRegistroDisponivel(extensao, tamArquivo);
        if(slot != -1){
            while(aux->elo != -1){
                pos = aux->elo; // posicao do elo atual!!
                aux = leCliente(extensao, aux->elo);
                flag = 1;
            }
            aux->elo = slot;
            if(flag)
                escreveCliente(extensao, aux, pos);
            else
                escreveCliente(dados, aux, hash);
            escreveCliente(extensao, x, slot);
        }
        else
            printf("Nao ha mais espaco disponivel!!\n");
    }
    else
        escreveCliente(dados, x, hash);
    free(aux);
}

int getSlotExtensao(FILE *dados, FILE *extensao, char *nome, int tamArquivo){
    int hash, slot = -1;
    Cliente *x, *ant;
    hash = hashString(nome, tamArquivo);
    x = leCliente(dados, hash);
    while(strcmp(x->nome, nome) && x->elo != -1){
        ant = x;
        x = leCliente(extensao, x->elo);
    }
    if(!strcmp(x->nome, nome))
        slot = ant->elo;
    free(x);
    free(ant);
    return slot;
}

void remover(FILE *dados, FILE *extensao, char *nome, int tamArquivo){
    int hash;
    Cliente *x, *aux;
    hash = hashString(nome, tamArquivo);
    x = leCliente(dados, hash);
    if(!strcmp(x->nome, nome)){
        x->idade = -1;
        if(x->elo != -1){
            aux = leCliente(extensao, x->elo);
            escreveCliente(dados, aux, hash);
            escreveCliente(extensao, x, x->elo);
            free(aux);
        }
        else
            escreveCliente(dados, x, hash);
    }
    else{
        while(strcmp(x->nome, nome) && x->elo != -1){
            aux = x;
            x = leCliente(extensao, x->elo);
        }
        if(!strcmp(x->nome, nome)){
            x->idade = -1;
            escreveCliente(extensao, x, aux->elo);
            aux->elo = x->elo;
            if(!strcmp(aux->nome, leCliente(dados, hashString(aux->nome, tamArquivo))->nome)) // ver se eh do arquivo de dados!!
                escreveCliente(dados, aux, hashString(aux->nome, tamArquivo));
            else
                escreveCliente(extensao, aux, getSlotExtensao(dados, extensao, aux->nome, tamArquivo));
        }
        free(aux);
    }
    free(x);
}


void alterar(FILE *dados, FILE *extensao, char *nome, int tamArquivo, Cliente alterar){
    int hash;
    hash = hashString(nome, tamArquivo);
    Cliente *x;
    x = leCliente(dados, hash);
    while(strcmp(x->nome, nome) && x->elo != -1)
        x = leCliente(extensao, x->elo);
    if(!strcmp(x->nome, nome)){
        if(strcmp(alterar.nome, "\0")){
            int idade = x->idade;
            remover(dados, extensao, x->nome, tamArquivo);
            strcpy(x->nome, alterar.nome);
            inserir(dados, extensao, x, tamArquivo);
            x->idade = idade;
            x->elo = -1;
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

        // Escrita!!
        if(!strcmp(x->nome, leCliente(dados, hashString(x->nome, tamArquivo))->nome)) // caso seja no arquivo Dados!!
            escreveCliente(dados, x, hash);
        else
            escreveCliente(extensao, x, getSlotExtensao(dados, extensao, x->nome, tamArquivo)); // caso seja no arquivo Extensao!!
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

void printClientes(FILE *dados, FILE *extensao, int tamArquivo){
    Cliente *x;
    int i;
    for(i = 0; i < tamArquivo; i++){
        x = leCliente(dados, i);
        if(x->idade != -1){
            printCliente(x);
            while(x->elo != -1){
                x = leCliente(extensao, x->elo);
                printCliente(x);
            }
        }
    }
    free(x);
}

void lerEntrada(char *fileName, FILE *dados, FILE *extensao, int tamArquivo){
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
            x->elo = -1;
            switch(operacao){
            case 'I':
                inserir(dados, extensao, x, tamArquivo);
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
    FILE *dados, *extensao;
    int tamArquivo = 10;

    Cliente alterarModelo;
    strcpy(alterarModelo.nome, "JaoSa");
    strcpy(alterarModelo.CEP, "\0");
    alterarModelo.idade = 17;
    strcpy(alterarModelo.CPF, "\0");
    strcpy(alterarModelo.cidade, "\0");
    strcpy(alterarModelo.endereco, "\0");
    strcpy(alterarModelo.telefone, "\0");

    dados = fopen("dados.bin", "wb+");
    inicializaArquivo(dados, tamArquivo); // Arquivo Dados!!

    extensao = fopen("extensao.bin", "wb+");
    inicializaArquivo(extensao, tamArquivo); // Arquivo Extensao!!

    lerEntrada("entrada.txt", dados, extensao, tamArquivo);

    printf("hash = %d\n", hashString("Joao Ortega", tamArquivo));
    printf("hash = %d\n", hashString("Arthur Silva", tamArquivo));
    printf("hash = %d\n", hashString("Maria Joaquina", tamArquivo));
    printf("hash = %d\n", hashString("Bruno Laz", tamArquivo));
    printf("hash = %d\n", hashString("JaoSa", tamArquivo));

    printf("strcmp = %d\n", strcmp("Joao Ortega", "Bruno Laz"));

    printClientes(dados, extensao, tamArquivo);

    remover(dados, extensao, "Jao Silav", tamArquivo);
    alterar(dados, extensao, "Bruno Laz", tamArquivo, alterarModelo);

    printClientes(dados, extensao, tamArquivo);

    fclose(dados);
    fclose(extensao);

    return 0;
}
