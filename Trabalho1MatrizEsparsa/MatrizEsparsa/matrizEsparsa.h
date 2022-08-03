#ifndef MATRIZESPARSA_H_INCLUDED
#define MATRIZESPARSA_H_INCLUDED

#include <stdio.h>

// estrutura celula
struct celula{
    int linha;              // inteiro que mostra em qual linha esta a celula
    int coluna;             // inteiro que mostra em qual coluna esta a celula
    int valor;              // inteiro que armazena o valor da celula
    struct celula *direita; // ponteiro para proxima celula a direita
    struct celula *abaixo;  // ponteiro para proxima celula abaixo
};

// estrutura Matriz que faz o uso de struct celula para montar a matriz
typedef struct{
    struct celula *cabeca; // ponteiro para a cabeca da Matriz
    int totalLinha;        // inteiro armazenando total de linhas da Matriz
    int totalColuna;       // inteiro armazenando total de colunas da Matriz
} Matriz;

// Aloca memoria e inicializa o tipo Matriz e tambem o ponteiro para celula cabeca
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para Matriz alocado e inicializado
Matriz* inicializarMatriz();

// Aloca memoria e inicializa o ponteiro para celula cabeca dentro do tipo Matriz, esta funcao esta dentro de inicializarMatriz
// pre-condicao: tipo Matriz tem que estar alocado para mexer com os elementos dentro dele
// pos-condicao: retorna um ponteiro para celula alocado e inicializado
struct celula* inicializarCabecaMatriz();

// Ler as informacoes da matriz armazenadas em um arquivo
// pre-condicao: tipo Matriz precisa estar alocado
// pos-condicao: ao termino desta funcao a Matriz esta com sua estrutura completa, agora com as celulas dos elementos
void lerMatriz(FILE *f, Matriz *x);

// Cria celulas, as quais sao as cabecas de cada linha e cada coluna, conforme o numero de linhas e colunas informado, esta funcao esta dentro de lerMatriz
// pre-condicao: tipo Matriz e a celula cabeca tem que estar alocado
// pos-condicao: ao termino desta funcao o tipo Matriz tem as celulas cabeca para cada linha e coluna
void criarCabecasMatriz(Matriz *x);

// Cria celula, somente as cabecas de linha, esta funcao esta dentro de criarCabecasMatriz
// pre-condicao: tipo Matriz e a celula cabeca tem que estar alocado
// pos-condicao: ao termino desta funcao o tipo Matriz tem as celulas cabeca para cada linha
void criarCabecasLinhas(Matriz *x);

// Cria celula, somente as cabecas de coluna, esta funcao esta dentro de criarCabecasMatriz
// pre-condicao: tipo Matriz e a celula cabeca tem que estar alocado
// pos-condicao: ao termino desta funcao o tipo Matriz tem as celulas cabeca para cada coluna
void criarCabecasColunas(Matriz *x);

// Aloca memoria e inicializa o tipo celula para ser a cabeca de uma linha, esta funcao esta dentro de criarCabecasLinhas
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para celula alocado e inicializado com os devidos valores para cabeca de linha
struct celula* inicializarCabecaLinha();

// Aloca memoria e inicializa o tipo celula para ser a cabeca de uma coluna, esta funcao esta dentro de criarCabecasColunas
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para celula alocado e inicializado com os devidos valore para cabeca de coluna
struct celula* inicializarCabecaColuna();

// Cria e encadeia as celulas dos elementos da matriz no seu devido lugar
// pre-condicao: tipo Matriz tem que estar alocado e as cabecas de linhas e colunas criados
// pos-condicao: tipo Matriz encadeado com os elementos lidos, tanto na direcao das linhas quanto na das colunas esta encadeado
void montarMatriz(Matriz *x, int linha, int coluna, int valor);

// Cria a celula para o novo elemento lido da matriz, esta funcao esta dentro de montarMatriz
// pre-condicao: nenhuma
// pos-condicao: retorna um ponteiro para celula alocado e inicializado corretamento conforme linha, coluna e valor
struct celula* criarCelula(int linha, int coluna, int valor);

// Encadeia o elemento na sua linha correspondente, esta funcao esta dentro de montarMatriz
// pre-condicao: tipo Matriz tem que estar alocado e as cabecas de linha e colunas criados
// pos-condicao: elemento encadeado corretamente na lista da deteminada linha
void encadearLinha(struct celula *cabecaMatriz, struct celula *aux);

// Encadeia o elemento na sua coluna correspondente, esta funcao esta dentro de montarMatriz
// pre-condicao: tipo Matriz tem que estar alocado e as cabecas de linha e colunas criados
// pos-condicao: elemento encadeado corretamente na lista da determinada coluna
void encadearColuna(struct celula *cabecaMatriz, struct celula *aux);

// Soma duas matrizes
// pre-condicao: as duas Matrizes precisam estar alocadas e montadas corretamente
// pos-condicao: retorna um ponteiro para Matriz, o resultado da soma realizada
Matriz* somaMatriz(Matriz *x, Matriz *y);

// Subtrai duas matrizes
// pre-condicao: as duas Matrizes precisam estar alocadas e montadas corretamente
// pos-condicao: retorna um ponteiro para Matriz, o resultado da subtracao realizada
Matriz* subtraiMatriz(Matriz *x, Matriz *y);

// Multiplica duas matrizes
// pre-condicao: as duas Matrizes precisam estar alocadas e montadas corretamente
// pos-condicao: retorna um ponteiro para Matriz, o resultado da multiplicacao realizada
Matriz* multiplicaMatriz(Matriz *x, Matriz *y);

// Transposta de uma matriz
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: retorna um ponteiro para Matriz, a transposta da Matriz passada como argumento
Matriz* transpostaMatriz(Matriz *x);

// Testa se uma matriz eh simetrica
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: retorna um inteiro, caso seja 1 a matriz eh simetrica, caso 0 nao eh simetrica
int isSimetrica(Matriz *x);

// Testa se tal celula existe em uma Matriz, dado a linha e a coluna, esta funcao esta dentro da somaMatriz, subtraiMatriz, multiplicaMatriz, transpostaMatriz, isSimetrica
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: retorna um inteiro, caso seja 1 a celula existe, caso 0 nao existe
int existeCelula(Matriz *x, int linha, int coluna);

// Retorna o valor de uma determinada celula, esta funcao esta dentro da somaMatriz, subtraiMatriz, multiplicaMatriz, transpostaMatriz, isSimetrica
// pre-condicao: a Matriz precisa estar alocada e montada corretamente, a celula precisa existir
// pos-condicao: retorna um inteiro, o valor contido na celula
int valorCelula(Matriz *x, int linha, int coluna);

// Printa a Matriz passada como argumento
// pre-condicao: a Matriz precisa estar alocada e montada corretamente
// pos-condicao: ao termino da funcao eh mostrado na tela a Matriz
void printMatriz(Matriz *x);

// Menu para realizar as operacoes de forma manual, escolher a operacao e realizar a operacao desejada
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao uma operacao eh realizada e o seu resultado mostrado na tela
void execOperacaoManual();

// Funcao auxiliar para realizar a soma de matrizes no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da soma das duas matrizes
void executaSoma(Matriz *x, Matriz *y, Matriz *resultado);

// Funcao auxiliar para realizar a subtracao de matrizes no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da subtracao das duas matrizes
void executaSubtracao(Matriz *x, Matriz *y, Matriz *resultado);

// Funcao auxiliar para realizar a multiplicacao de matrizes no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da multiplicacao das duas matrizes
void executaMultiplicacao(Matriz *x, Matriz *y, Matriz *resultado);

// Funcao auxiliar para realizar a transposta de uma matriz no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz passada como argumento
void executaTransposta(Matriz *x, Matriz *resultado);

// Funcao auxiliar para testar se uma matriz eh simetrica no menu de Operacao Manual
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz e se ela eh simetrica
void executaSimetrica(Matriz *x);

// Menu para realizar uma operacao conforme a leitura de um arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao uma operacao eh realizada e o seu resultado mostrado na tela
void execArquivoOperacao();

// Funcao auxiliar para realizar a soma de matrizes no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da soma das duas matrizes
void executaSomaOperacao(FILE *f, Matriz *x, Matriz *y, Matriz *resultado);

// Funcao auxiliar para realizar a subtracao de matrizes no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da subtracao das duas matrizes
void executaSubtracaoOperacao(FILE *f, Matriz *x, Matriz *y, Matriz *resultado);

// Funcao auxiliar para realizar a multiplicacao de matrizes no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela o resultado da multiplicacao das duas matrizes
void executaMultiplicacaoOperacao(FILE *f, Matriz *x, Matriz *y, Matriz *resultado);

// Funcao auxiliar para realizar a transposta de uma matriz no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz passada como argumento
void executaTranspostaOperacao(FILE *f, Matriz *x, Matriz *resultado);

// Funcao auxiliar para testar se uma matriz eh simetrica no menu Executar Arquivo
// pre-condicao: nenhuma
// pos-condicao: ao termino desta funcao eh mostrado na tela a transposta da matriz e se ela eh simetrica
void executaSimetricaOperacao(FILE *f, Matriz *x);

// Ao fim de cada funcao 'executa' esta funcao eh chamada para liberar a memoria alocada pelas matrizes utilizadas em cada operacao
// pre-condicao: a matriz e suas celulas precisam estar alocadas
// pos-condicao: ao termino desta funcao a memoria alocada previamente eh liberada, prevenindo o vazamento de memoria (memory leaking)
void deletaMatriz(Matriz *x);

// Deleta todas celulas da matriz, exceto a cabeca da Matriz, a cabeca da Matriz eh libera na funcao deletaMatriz
// pre-condicao: a celula cabeca precisa estar alocada
// pos-condicao: as celulas presentes na matriz, tanto cabecas de linha e coluna quanto os elementos sao liberados
void deletaCelulas(struct celula *cabeca);

// Deleta todas as celulas em que se encontram os elementos da matriz
// pre-condicao: a celula cabeca precisa estar alocada
// pos-condicao: as celulas nas quais se encontram os elementos da Matriz sao liberadas
void deletaElementos(struct celula *cabeca);

// Deleta todas as celulas de cabeca de linha e coluna
// pre-condicao: a celula cabeca precisa estar alocada
// pos-condicao: as celulas de cabeca de linha e coluna da Matriz sao liberadas
void deletaCabecas(struct celula *cabeca);

// Mostra o Menu Principal na tela
// pre-condicao: nenhuma
// pos-condicao: mostra o Menu Principal na tela
void printMenu();


#endif // MATRIZESPARSA_H_INCLUDED
