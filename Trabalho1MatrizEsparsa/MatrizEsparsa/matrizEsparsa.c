#include "matrizEsparsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aloca memoria e inicializa o ponteiro para celula cabeca dentro do tipo Matriz, esta funcao esta dentro de inicializarMatriz
// pre-condicao: tipo Matriz tem que estar alocado para mexer com os elementos dentro dele
// pos-condicao: retorna um ponteiro para celula alocado e inicializado
struct celula* inicializarCabecaMatriz(){
    struct celula *aux = (struct celula *) malloc(sizeof(struct celula));
    aux->linha = -1;
    aux->coluna = -1;
    aux->direita = NULL;
    aux->abaixo = NULL;
    return aux;
}

// Aloca memoria e inicializa o tipo Matriz e tambem o ponteiro para celula cabeca
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para Matriz alocado e inicializado
Matriz* inicializarMatriz(){
    Matriz *aux = (Matriz *) malloc(sizeof(Matriz));
    aux->cabeca = inicializarCabecaMatriz();
    aux->totalLinha  = 0;
    aux->totalColuna = 0;
    return aux;
}

// Aloca memoria e inicializa o tipo celula para ser a cabeca de uma coluna, esta funcao esta dentro de criarCabecasColunas
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para celula alocado e inicializado com os devidos valore para cabeca de coluna
struct celula* inicializarCabecaColuna(){
    struct celula *aux = (struct celula *) malloc(sizeof(struct celula));
    aux->direita = NULL;
    aux->abaixo = NULL;
    aux->coluna = -1;
    return aux;
}

// Cria celula, somente as cabecas de coluna, esta funcao esta dentro de criarCabecasMatriz
// pre-condicao: tipo Matriz e a celula cabeca tem que estar alocado
// pos-condicao: ao termino desta funcao o tipo Matriz tem as celulas cabeca para cada coluna
void criarCabecasColunas(Matriz *x){
    int i;
    struct celula *p;
    p = x->cabeca;
    for(i = 0; i < x->totalColuna; i++){
        p->direita = inicializarCabecaColuna();
        p = p->direita;
        p->abaixo = p;
    }
    p->direita = x->cabeca; // garantir circularidade horizontal da lista!!
}

// Aloca memoria e inicializa o tipo celula para ser a cabeca de uma linha, esta funcao esta dentro de criarCabecasLinhas
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para celula alocado e inicializado com os devidos valores para cabeca de linha
struct celula* inicializarCabecaLinha(){
    struct celula *aux = (struct celula *) malloc(sizeof(struct celula));
    aux->direita = NULL;
    aux->abaixo = NULL;
    aux->linha = -1;
    return aux;
}

// Cria celula, somente as cabecas de linha, esta funcao esta dentro de criarCabecasMatriz
// pre-condicao: tipo Matriz e a celula cabeca tem que estar alocado
// pos-condicao: ao termino desta funcao o tipo Matriz tem as celulas cabeca para cada linha
void criarCabecasLinhas(Matriz *x){
    int i;
    struct celula *p;
    p = x->cabeca;
    for(i = 0; i < x->totalLinha; i++){
        p->abaixo = inicializarCabecaLinha();
        p = p->abaixo;
        p->direita = p;
    }
    p->abaixo = x->cabeca; // garantir circularidade vertical da lista!!
}

// Cria celulas, as quais sao as cabecas de cada linha e cada coluna, conforme o numero de linhas e colunas informado, esta funcao esta dentro de lerMatriz
// pre-condicao: tipo Matriz e a celula cabeca tem que estar alocado
// pos-condicao: ao termino desta funcao o tipo Matriz tem as celulas cabeca para cada linha e coluna
void criarCabecasMatriz(Matriz *x){
    criarCabecasColunas(x);
    criarCabecasLinhas(x);
}

// Cria a celula para o novo elemento lido da matriz, esta funcao esta dentro de montarMatriz
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para celula alocado e inicializado corretamento conforme linha, coluna e valor
struct celula* criarCelula(int linha, int coluna, int valor){
    struct celula *aux = (struct celula *) malloc(sizeof(struct celula));
    aux->direita = NULL;
    aux->abaixo = NULL;
    aux->linha = linha;
    aux->coluna = coluna;
    aux->valor = valor;
    return aux;
}

// Encadeia o elemento na sua linha correspondente, esta funcao esta dentro de montarMatriz
// pre-condicao: tipo Matriz tem que estar alocado e as cabecas de linha e colunas criados
// pos-condicao: elemento encadeado corretamente na lista da deteminada linha
void encadearLinha(struct celula *cabecaMatriz, struct celula *aux){
    int i;
    struct celula *p, *cabecaLinha;
    p = cabecaMatriz;
    for(i = 0; i < aux->linha; i++) // encontra cabecaLinha!!
        p = p->abaixo;
    cabecaLinha = p;
    while(p->direita->linha != -1) // encontra lugar onde deve ser encadeado!!
        p = p->direita;
    p->direita = aux;
    aux->direita = cabecaLinha; // garantir circularidade horizontal da lista!!
}

// Encadeia o elemento na sua coluna correspondente, esta funcao esta dentro de montarMatriz
// pre-condicao: tipo Matriz tem que estar alocado e as cabecas de linha e colunas criados
// pos-condicao: elemento encadeado corretamente na lista da determinada coluna
void encadearColuna(struct celula *cabecaMatriz, struct celula *aux){
    int i;
    struct celula *p, *cabecaColuna;
    p = cabecaMatriz;
    for(i = 0; i < aux->coluna; i++) // encontra cabecaColuna!!
        p = p->direita;
    cabecaColuna = p;
    while(p->abaixo->coluna != -1) // encontra lugar onde deve ser encadeado!!
        p = p->abaixo;
    p->abaixo = aux;
    aux->abaixo = cabecaColuna; // garantir circularidade vertical da lista!!
}

// Cria e encadeia as celulas dos elementos da matriz no seu devido lugar
// pre-condicao: tipo Matriz tem que estar alocado e as cabecas de linhas e colunas criados
// pos-condicao: tipo Matriz encadeado com os elementos lidos, tanto na direcao das linhas quanto na das colunas esta encadeado
void montarMatriz(Matriz *x, int linha, int coluna, int valor){
    struct celula *aux = criarCelula(linha, coluna, valor);
    encadearLinha(x->cabeca, aux);
    encadearColuna(x->cabeca, aux);
}

// Retorna o valor de uma determinada celula, esta funcao esta dentro da somaMatriz, subtraiMatriz, multiplicaMatriz, transpostaMatriz, isSimetrica
// pre-condicao: a Matriz precisa estar alocada e montada corretamente, a celula precisa existir
// pos-condicao: retorna um inteiro, o valor contido na celula
int valorCelula(Matriz *x, int linha, int coluna){
    int i;
    struct celula *p = x->cabeca;
    for(i = 0; i < linha; i++)
        p = p->abaixo;
    p = p->direita; // fazer este ponteiro apontar para uma celula que nao seja cabeca de linha!!
    while(p->linha != -1){
        if(p->linha == linha && p->coluna == coluna)
            return p->valor;
        p = p->direita;
    }
    return 0;
}

// Testa se tal celula existe em uma Matriz, dado a linha e a coluna, esta funcao esta dentro da somaMatriz, subtraiMatriz, multiplicaMatriz, transpostaMatriz, isSimetrica
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: retorna um inteiro, caso seja 1 a celula existe, caso 0 nao existe
int existeCelula(Matriz *x, int linha, int coluna){
    int i;
    struct celula *p = x->cabeca;
    for(i = 0; i < linha; i++)
        p = p->abaixo;
    p = p->direita; // fazer este ponteiro apontar para uma celula que nao seja cabeca de linha!!
    while(p->linha != -1){
        if(p->linha == linha && p->coluna == coluna)
            return 1;
        p = p->direita;
    }
    return 0;
}

// Soma duas matrizes
// pre-condicao: as duas Matrizes precisam estar alocadas e montadas corretamente
// pos-condicao: retorna um ponteiro para Matriz, o resultado da soma realizada
Matriz* somaMatriz(Matriz *x, Matriz *y){
    Matriz *resultado;
    int i, j, valorSoma = 0;
    if(x->totalLinha != y->totalLinha || x->totalColuna != y->totalColuna){
        printf("Matrizes nao sao de mesma ordem!!\n\n");
        return NULL;
    }
    resultado = inicializarMatriz();
    resultado->totalLinha = x->totalLinha;
    resultado->totalColuna = x->totalColuna;
    criarCabecasMatriz(resultado);
    for(i = 1; i <= resultado->totalLinha; i++){
        for(j = 1; j <= resultado->totalColuna; j++){
            if(existeCelula(x, i, j) && existeCelula(y, i, j)){
                valorSoma = valorCelula(x, i, j) + valorCelula(y, i, j);
                montarMatriz(resultado, i, j, valorSoma);
            }
            else
                if(existeCelula(x, i, j)){
                    valorSoma = valorCelula(x, i, j);
                    montarMatriz(resultado, i, j, valorSoma);
                }
            else
                if(existeCelula(y, i, j)){
                    valorSoma = valorCelula(y, i, j);
                    montarMatriz(resultado, i, j, valorSoma);
                }
        }
    }
    return resultado;
}

// Subtrai duas matrizes
// pre-condicao: as duas Matrizes precisam estar alocadas e montadas corretamente
// pos-condicao: retorna um ponteiro para Matriz, o resultado da subtracao realizada
Matriz* subtraiMatriz(Matriz *x, Matriz *y){
    Matriz *resultado;
    int i, j, valorSubtracao = 0;
    if(x->totalLinha != y->totalLinha || x->totalColuna != y->totalColuna){
        printf("Matrizes nao sao de mesma ordem!!\n\n");
        return NULL;
    }
    resultado = inicializarMatriz();
    resultado->totalLinha = x->totalLinha;
    resultado->totalColuna = x->totalColuna;
    criarCabecasMatriz(resultado);
    for(i = 1; i <= resultado->totalLinha; i++){
        for(j = 1; j <= resultado->totalColuna; j++){
            if(existeCelula(x, i, j) && existeCelula(y, i, j)){
                valorSubtracao = valorCelula(x, i, j) - valorCelula(y, i, j);
                montarMatriz(resultado, i, j, valorSubtracao);
            }
            else
                if(existeCelula(x, i, j)){
                    valorSubtracao = valorCelula(x, i, j);
                    montarMatriz(resultado, i, j, valorSubtracao);
                }
            else
                if(existeCelula(y, i, j)){
                    valorSubtracao = -valorCelula(y, i, j);
                    montarMatriz(resultado, i, j, valorSubtracao);
                }
        }
    }
    return resultado;
}

// Multiplica duas matrizes
// pre-condicao: as duas Matrizes precisam estar alocadas e montadas corretamente
// pos-condicao: retorna um ponteiro para Matriz, o resultado da multiplicacao realizada
Matriz* multiplicaMatriz(Matriz *x, Matriz *y){
    Matriz* resultado;
    int i, j, k, valorMultiplicacao;
    if(x->totalColuna != y->totalLinha){
        printf("Matrizes incompativeis para multiplicacao!!\n\n");
        return NULL;
    }
    resultado = inicializarMatriz();
    resultado->totalLinha = x->totalLinha;
    resultado->totalColuna = y->totalColuna;
    criarCabecasMatriz(resultado);
    for(i = 1; i <= x->totalLinha; i++)
        for(j = 1; j <= y->totalColuna; j++){
            valorMultiplicacao = 0;
            for(k = 1; k <= x->totalColuna; k++)
                if(existeCelula(x, i, k) && existeCelula(y, k, j)) // somente este caso eh relevante para a multiplicacao, caso uma celula nao exista nao ha a necessidade de somar 0!!
                    valorMultiplicacao += valorCelula(x, i, k) * valorCelula(y, k, j);
            if(valorMultiplicacao)
                montarMatriz(resultado, i, j, valorMultiplicacao);
        }
    return resultado;
}

// Transposta de uma matriz
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: retorna um ponteiro para Matriz, a transposta da Matriz passada como argumento
Matriz* transpostaMatriz(Matriz *x){
    Matriz* resultado;
    int i, j;
    if(x->totalLinha == 0 || x->totalColuna == 0){
        printf("Matriz invalida!! (0 linhas ou colunas)\n\n");
        return NULL;
    }
    resultado = inicializarMatriz();
    resultado->totalLinha = x->totalColuna;
    resultado->totalColuna = x->totalLinha;
    criarCabecasMatriz(resultado);
    for(i = 1; i <= x->totalLinha; i++)
        for(j = 1; j <= x->totalColuna; j++){
            if(existeCelula(x, i, j)){
                montarMatriz(resultado, j, i, valorCelula(x, i, j));
            }
        }
    return resultado;
}

// Testa se uma matriz eh simetrica
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: retorna um inteiro, caso seja 1 a matriz eh simetrica, caso 0 nao eh simetrica
int isSimetrica(Matriz *x){
    Matriz *transposta;
    int i, j;
    if(x->totalLinha != x->totalColuna){
        printf("Nao eh matriz quadrada!!\n\n");
        return 0;
    }
    transposta = transpostaMatriz(x);
    printf("Matriz(%dx%d):\n", x->totalLinha, x->totalColuna);
    printMatriz(x);
    printf("\nMatriz Transposta(%dx%d):\n", transposta->totalLinha, transposta->totalColuna);
    printMatriz(transposta);
    printf("\n");
    for(i = 1; i <= x->totalLinha; i++)
        for(j = 1; j <= x->totalColuna; j++){
            if(existeCelula(x, i, j) && existeCelula(transposta, i, j)){
                if(valorCelula(x, i, j) != valorCelula(transposta, i, j)){
                    deletaMatriz(transposta);
                    return 0;
                }
            }
            else
                if(existeCelula(x, i, j)){
                    deletaMatriz(transposta);
                    return 0;
                }
            else
                if(existeCelula(transposta, i, j)){
                    deletaMatriz(transposta);
                    return 0;
                }
        }
    deletaMatriz(transposta);
    return 1;
}

// Printa a Matriz passada como argumento
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: ao termino da funcao eh mostrado na tela a Matriz
void printMatriz(Matriz *x){
    int i, j;
    for(i = 1; i <= x->totalLinha; i++){
        for(j = 1; j <= x->totalColuna; j++){
            if(existeCelula(x, i, j))
                printf("%5d", valorCelula(x, i, j));
            else
                printf("%5d", 0);
        }
        printf("\n");
    }
}

// Funcao auxiliar para realizar a soma de matrizes no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da soma das duas matrizes
void executaSoma(Matriz *x, Matriz *y, Matriz *resultado){
    int i;
    char nomeArquivo[100];
    FILE *f;
    x = inicializarMatriz();
    y = inicializarMatriz();
    for(i = 0; i < 2; i++){
        printf("Entre com o nome do arquivo da matriz %d: 'nomeDoArquivo.txt'\n", i+1);
        printf("> ");
        scanf("%*c%[^\n]", nomeArquivo);
        f = fopen(nomeArquivo, "r");
        if(f == NULL){
            printf("Arquivo nao encontrado!\n");
            break;
        }
        if(i)
            lerMatriz(f, y);
        else
            lerMatriz(f, x);
        fclose(f);
    }
    if(f != NULL){
        printf("Matriz 1(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\nMatriz 2(%dx%d):\n", y->totalLinha, y->totalColuna);
        printMatriz(y);
        printf("\n");
        resultado = somaMatriz(x, y);
        if(resultado != NULL){
            printf("Matriz Resultado(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
        deletaMatriz(y);
    }
    else{
        free(x->cabeca);
        free(x);
        free(y->cabeca);
        free(y);
    }
}

// Funcao auxiliar para realizar a subtracao de matrizes no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da subtracao das duas matrizes
void executaSubtracao(Matriz *x, Matriz *y, Matriz *resultado){
    int i;
    char nomeArquivo[100];
    FILE *f;
    x = inicializarMatriz();
    y = inicializarMatriz();
    for(i = 0; i < 2; i++){
        printf("Entre com o nome do arquivo da matriz %d: 'nomeDoArquivo.txt'\n", i+1);
        printf("> ");
        scanf("%*c%[^\n]", nomeArquivo);
        f = fopen(nomeArquivo, "r");
        if(f == NULL){
            printf("Arquivo nao encontrado!\n");
            break;
        }
        if(i)
            lerMatriz(f, y);
        else
            lerMatriz(f, x);
        fclose(f);
    }
    if(f != NULL){
        printf("Matriz 1(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\nMatriz 2(%dx%d):\n", y->totalLinha, y->totalColuna);
        printMatriz(y);
        printf("\n");
        resultado = subtraiMatriz(x, y);
        if(resultado != NULL){
            printf("Matriz Resultado(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
        deletaMatriz(y);
    }
    else{
        free(x->cabeca);
        free(x);
        free(y->cabeca);
        free(y);
    }
}

// Funcao auxiliar para realizar a multiplicacao de matrizes no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da multiplicacao das duas matrizes
void executaMultiplicacao(Matriz *x, Matriz *y, Matriz *resultado){
    int i;
    char nomeArquivo[100];
    FILE *f;
    x = inicializarMatriz();
    y = inicializarMatriz();
    for(i = 0; i < 2; i++){
        printf("Entre com o nome do arquivo da matriz %d: 'nomeDoArquivo.txt'\n", i+1);
        printf("> ");
        scanf("%*c%[^\n]", nomeArquivo);
        f = fopen(nomeArquivo, "r");
        if(f == NULL){
            printf("Arquivo nao encontrado!\n");
            break;
        }
        if(i)
            lerMatriz(f, y);
        else
            lerMatriz(f, x);
        fclose(f);
    }
    if(f != NULL){
        printf("Matriz 1(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\nMatriz 2(%dx%d):\n", y->totalLinha, y->totalColuna);
        printMatriz(y);
        printf("\n");
        resultado = multiplicaMatriz(x, y);
        if(resultado != NULL){
            printf("Matriz Resultado(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
        deletaMatriz(y);
    }
    else{
        free(x->cabeca);
        free(x);
        free(y->cabeca);
        free(y);
    }
}

// Funcao auxiliar para realizar a transposta de uma matriz no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz passada como argumento
void executaTransposta(Matriz *x, Matriz *resultado){
    char nomeArquivo[100];
    FILE *f;
    x = inicializarMatriz();
    printf("Entre com o nome do arquivo da matriz: 'nomeDoArquivo.txt'\n");
    printf("> ");
    scanf("%*c%[^\n]", nomeArquivo);
    f = fopen(nomeArquivo, "r");
    if(f != NULL){
        lerMatriz(f, x);
        fclose(f);
        printf("Matriz(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\n");
        resultado = transpostaMatriz(x);
        if(resultado != NULL){
            printf("Matriz Transposta(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
    }
    else{
        printf("Arquivo nao encontrado!\n");
        free(x->cabeca);
        free(x);
    }
}

// Funcao auxiliar para testar se uma matriz eh simetrica no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz e se ela eh simetrica
void executaSimetrica(Matriz *x){
    char nomeArquivo[100];
    FILE *f;
    x = inicializarMatriz();
    printf("Entre com o nome do arquivo da matriz: 'nomeDoArquivo.txt'\n");
    printf("> ");
    scanf("%*c%[^\n]", nomeArquivo);
    f = fopen(nomeArquivo, "r");
    if(f != NULL){
        lerMatriz(f, x);
        fclose(f);
        if(isSimetrica(x))
            printf("simetrica: SIM\n");
        else
            printf("simetrica: NAO\n");
        printf("\n");
        deletaMatriz(x);
    }
    else{
        printf("Arquivo nao encontrado!\n");
        free(x->cabeca);
        free(x);
    }
}

// Menu para realizar as operacoes de forma manual, escolher a operacao e realizar a operacao desejada
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao uma operacao eh realizada e o seu resultado mostrado na tela
void execOperacaoManual(){
    Matriz *x, *y, *resultado;
    x = NULL;    y = NULL;    resultado = NULL;
    int opcao;
    printf("1 - Soma\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Transposta\n");
    printf("5 - Simetrica\n");
    printf("> ");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            executaSoma(x, y, resultado);
            break;
        case 2:
            executaSubtracao(x, y, resultado);
            break;
        case 3:
            executaMultiplicacao(x, y, resultado);
            break;
        case 4:
            executaTransposta(x, resultado);
            break;
        case 5:
            executaSimetrica(x);
            break;
        default:
            printf("Opcao invalida!!\n");
            break;
    }
}

// Ler as informacoes da matriz armazenadas em um arquivo
// pre-condicao: tipo Matriz precisa estar alocado
// pos-condicao: ao termino desta funcao a Matriz esta com sua estrutura completa, agora com as celulas dos elementos
void lerMatriz(FILE *f, Matriz *x){
    char aux, str[50] = "\0";
    int linha, coluna, valor;
    fscanf(f, "%dx%d%*c", &x->totalLinha, &x->totalColuna);
    criarCabecasMatriz(x);
    while(strcmp(str, "fim")){
        fscanf(f, "%c", &aux);
        if(aux != 'f'){
            fseek(f, -1, SEEK_CUR);
            fscanf(f, "%d,%d,%d%*c", &linha, &coluna, &valor);
            montarMatriz(x, linha, coluna, valor);
        }
        else{
            fseek(f, -1, SEEK_CUR);
            fscanf(f, "%s", str);
        }
    }
}

// Funcao auxiliar para realizar a soma de matrizes no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da soma das duas matrizes
void executaSomaOperacao(FILE *f, Matriz *x, Matriz *y, Matriz *resultado){
        x = inicializarMatriz();
        y = inicializarMatriz();
        lerMatriz(f, x);
        lerMatriz(f, y);
        printf("Matriz 1(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\nMatriz 2(%dx%d):\n", y->totalLinha, y->totalColuna);
        printMatriz(y);
        printf("\n");
        resultado = somaMatriz(x, y);
        if(resultado != NULL){
            printf("Matriz Resultado(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
        deletaMatriz(y);
}

// Funcao auxiliar para realizar a subtracao de matrizes no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da subtracao das duas matrizes
void executaSubtracaoOperacao(FILE *f, Matriz *x, Matriz *y, Matriz *resultado){
        x = inicializarMatriz();
        y = inicializarMatriz();
        lerMatriz(f, x);
        lerMatriz(f, y);
        printf("Matriz 1(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\nMatriz 2(%dx%d):\n", y->totalLinha, y->totalColuna);
        printMatriz(y);
        printf("\n");
        resultado = subtraiMatriz(x, y);
        if(resultado != NULL){
            printf("Matriz Resultado(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
        deletaMatriz(y);
}

// Funcao auxiliar para realizar a multiplicacao de matrizes no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da multiplicacao das duas matrizes
void executaMultiplicacaoOperacao(FILE *f, Matriz *x, Matriz *y, Matriz *resultado){
        x = inicializarMatriz();
        y = inicializarMatriz();
        lerMatriz(f, x);
        lerMatriz(f, y);
        printf("Matriz 1(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\nMatriz 2(%dx%d):\n", y->totalLinha, y->totalColuna);
        printMatriz(y);
        printf("\n");
        resultado = multiplicaMatriz(x, y);
        if(resultado != NULL){
            printf("Matriz Resultado(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
        deletaMatriz(y);
}

// Funcao auxiliar para realizar a transposta de uma matriz no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz passada como argumento
void executaTranspostaOperacao(FILE *f, Matriz *x, Matriz *resultado){
        x = inicializarMatriz();
        lerMatriz(f, x);
        printf("Matriz(%dx%d):\n", x->totalLinha, x->totalColuna);
        printMatriz(x);
        printf("\n");
        resultado = transpostaMatriz(x);
        if(resultado != NULL){
            printf("Matriz Transposta(%dx%d):\n", resultado->totalLinha, resultado->totalColuna);
            printMatriz(resultado);
            printf("\n");
            deletaMatriz(resultado);
        }
        deletaMatriz(x);
}

// Funcao auxiliar para testar se uma matriz eh simetrica no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz e se ela eh simetrica
void executaSimetricaOperacao(FILE *f, Matriz *x){
        x = inicializarMatriz();
        lerMatriz(f, x);
        if(isSimetrica(x))
            printf("simetrica: SIM\n");
        else
            printf("simetrica: NAO\n");
        printf("\n");
        deletaMatriz(x);
}

// Menu para realizar uma operacao conforme a leitura de um arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao uma operacao eh realizada e o seu resultado mostrado na tela
void execArquivoOperacao(){
    char fnm[100], operacao[100];
    Matriz *x, *y, *resultado;
    x = NULL;   y = NULL;   resultado = NULL;
    FILE *f;
    printf("Entre com o nome do arquivo: 'nomeDoArquivo.txt'\n");
    printf("> ");
    scanf("%*c%[^\n]", fnm);
    f = fopen(fnm, "r");
    if(f != NULL){
        fscanf(f, "%s", operacao);
        if(!strcmp(operacao, "soma"))
            executaSomaOperacao(f, x, y, resultado);
        else
            if(!strcmp(operacao, "subtracao"))
                executaSubtracaoOperacao(f, x, y, resultado);
        else
            if(!strcmp(operacao, "multiplicacao"))
                executaMultiplicacaoOperacao(f, x, y, resultado);
        else
            if(!strcmp(operacao, "transposta"))
                executaTranspostaOperacao(f, x, resultado);
        else
            if(!strcmp(operacao, "simetrica"))
                executaSimetricaOperacao(f, x);
        else
            printf("Operacao invalida!\n");
        fclose(f);
    }
    else
        printf("Arquivo nao encontrado!\n");
}

// Deleta todas as celulas em que se encontram os elementos da matriz
// pre-condicao: a celula cabeca precisa estar alocada
// pos-condicao: as celulas nas quais se encontram os elementos da Matriz sao liberadas
void deletaElementos(struct celula *cabeca){
    struct celula *p, *cabecaLinha;
    p = cabeca->abaixo;
    while(p != cabeca){ // retirando as celulas que contem elementos da matriz e encadeando corretamente!!
        cabecaLinha = p;
        p = p->direita;
        while(p != cabecaLinha){
            cabecaLinha->direita = p->direita;
            free(p);
            p = cabecaLinha->direita;
        }
        p = p->abaixo;
    }
    p = cabeca->direita;
    while(p != cabeca){ // retirando a parte dos elementos da matriz a partir das colunas, ja foi liberado, basta somente encadear corretamente!!
        p->abaixo = p;
        p = p->direita;
    }
}

// Deleta todas as celulas de cabeca de linha e coluna
// pre-condicao: a celula cabeca precisa estar alocada
// pos-condicao: as celulas de cabeca de linha e coluna da Matriz sao liberadas
void deletaCabecas(struct celula *cabeca){
    struct celula *p;
    p = cabeca->direita;
    while(p != cabeca){ // retirando as celulas de cabeca de coluna e encadeando corretamente!!
        cabeca->direita = p->direita;
        free(p);
        p = cabeca->direita;
    }
    p = cabeca->abaixo;
    while(p != cabeca){ // retirando as celulas de cabeca de linha e encadeando corretamente!!
        cabeca->abaixo = p->abaixo;
        free(p);
        p = cabeca->abaixo;
    }
}

// Deleta todas celulas da matriz, exceto a cabeca da Matriz, a cabeca da Matriz eh libera na funcao deletaMatriz
// pre-condicao: a celula cabeca precisa estar alocada
// pos-condicao: as celulas presentes na matriz, tanto cabecas de linha e coluna quanto os elementos sao liberados
void deletaCelulas(struct celula *cabeca){
    deletaElementos(cabeca);
    deletaCabecas(cabeca);
}

// Ao fim de cada funcao 'executa' esta funcao eh chamada para liberar a memoria alocada pelas matrizes utilizadas em cada operacao
// pre-condicao: a matriz e suas celulas precisam estar alocadas
// pos-condicao: ao termino desta funcao a memoria alocada previamente eh liberada, prevenindo o vazamento de memoria (memory leaking)
void deletaMatriz(Matriz *x){
    deletaCelulas(x->cabeca);
    free(x->cabeca);
    free(x);
}

// Mostra o Menu Principal na tela
// pre-condicao: nenhuma
// pos-condicao: mostra o Menu Principal na tela
void printMenu(){
    printf("MENU:\n");
    printf("1 - Executar Operacao Manualmente\n");
    printf("2 - Executar Arquivo\n");
    printf("0 - Finalizar Programa\n");
    printf("> ");
}
