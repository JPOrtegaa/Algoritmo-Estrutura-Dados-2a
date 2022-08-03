#ifndef ARVORETSTARQUIVO_H
#define ARVORETSTARQUIVO_H

// Estrutura de no para arvore TST
typedef struct noTST{
    char letra;          // letra armazenada neste no
    int valor;           // valor caso seja uma palavra
    struct noTST *menor; // ponteiro para noTST menor que esta letra (lexicografico)
    struct noTST *igual; // ponteiro para noTST igual a esta letra (lexicografico)
    struct noTST *maior; // ponteiro para noTST maior que esta letra (lexicografico)
} noTST;

typedef noTST* arvoreTST; // define para um ponteiro de noTST

// Verifica se a string contem apenas letras, sem caracteres especiais, alem de a transformar para maiusculo
// Pre-condicao: ponteiro para char deve ser uma região de memória válida
// Pos-condicao: retorna um inteiro
int verificaPalavra(char *str);

// Realiza a leitura de um arquivo conforme o nome passado e carrega a arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido, bem como o nome do arquivo
// Pos-condicao: feita a leitura e a arvoreTST eh preenchida conforme o arquivo passado
void lerArquivoInsercao(arvoreTST *raiz, char *fileName);

// Insere uma nova palavra na arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: a string eh inserida na arvoreTST e seu ultimo caracter preenchido com o valor passado
void inserir(arvoreTST *raiz, char *str, int valor);

// Busca o valor correspondente a palavra passada na arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido, bem como o ponteiro para char
// Pos-condicao: retorna um inteiro correspondente a palavra procurada na arvoreTST
int buscar(arvoreTST raiz, char *str);

// Realiza a leitura de um arquivo conforme o nome passado e remove palavras da arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido, bem como o nome do arquivo
// Pos-condicao: feita a leitura a arvoreTST eh atualizada removendo as palavras presentes no arquivo de remocao
void lerArquivoRemocao(arvoreTST *raiz, char *fileName);

// Busca o inicio da palavra de maior tamanho lexicografico
// Pre-condicao: o ponteiro de noTST passado deve ser valido
// Pos-condicao: retorna um ponteiro de noTST contendo a maior palavra lexicografica
arvoreTST maiorElemento(arvoreTST raiz);

// Busca o inicio da palavra de menor tamanho lexicografico
// Pre-condicao: o ponteiro de noTST passado deve ser valido
// Pos-condicao: retorna um ponteiro de noTST contendo a menor palavra lexicografica
arvoreTST menorElemento(arvoreTST raiz);

// Remove o caracter repetido
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: o caracter repetido eh removido da arvoreTST
void removeRepetido(arvoreTST *raiz, char c);

// Remove uma palavra da arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: a arvoreTST eh atualizada com a remocao da palavra passada
void remover(arvoreTST *raiz, char *str);

// Imprime todas as palavras presentes na arvoreTST
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como os ponteiros para char
// Pos-condicao: todas as palavras presentes na arvoreTST sao impressas
void imprimirDicionarioAux(arvoreTST raiz, char *base, char *str);

// Imprime todas as palavras presentes na arvoreTST
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: todas as palavras presentes na arvoreTST sao impressas
void imprimirDicionario(arvoreTST raiz);

// Busca o noTST correspondente a palavra passada
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: retorna um ponteiro de noTST correspondente ao ultimo caracter da palavra
arvoreTST buscaPalavra(arvoreTST raiz, char *palavra);

// Imprime na tela todas as palavras que tenham o prefixo passado
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como os de char e de int
// Pos-condicao: eh impresso na tela todas as palavras presentes na arvoreTST que tenham o mesmo prefixo passado
void consultarPalavraAux(arvoreTST raiz, char *base, char *str, int *count);

// Imprime na tela todas as palavras que tenham o prefixo passado
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como o de char
// Pos-condicao: eh impresso na tela todas as palavras presentes na arvoreTST que tenham o mesmo prefixo passado
void consultarPalavra(arvoreTST raiz, char *palavra);

// Seleciona o menor inteiro entre os 3 passados
// Pre-condicao: os inteiros passados devem ser validos
// Pos-condicao: retorna um inteiro, o menor entre os 3 passados como argumento
int menor(int x, int y, int z);

// Conta as diferencas entre duas cadeias de caracteres
// Pre-condicao: os ponteiros para char devem ser validos
// Pos-condicao: retorna um inteiro o qual eh o numero de diferencas entre as duas strings
int contaDiferencas(char *str1, char *str2);

// Imprime na tela as palavras da arvoreTST que tenham uma quantidade de diferenca menor ou igual a palavra passada
// Pre-condicao: o ponteiro de noTST deve ser valido, bem como os de char
// Pos-condicao: as palavras com quantidade de diferenca menor ou igual a palavra passada sao impressas na tela
void consultarSemelhante(arvoreTST raiz, char *palavra, int qtdDiferenca, char *str, char *base);

// Imprime na tela o menu principal do programa
// Pre-condicao: nenhuma
// Pos-condicao: imprime na tela o menu com as opcoes de operacao
void printMenu();

// Realiza a leitura do arquivo de insercao
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: realiza a leitura das palavras presentes no arquivo de insercao e preenche a arvoreTST
void executaLerArquivoInsercao(arvoreTST *raiz);

// Realiza a consulta das palavras presentes na arvore que contenham o prefixo passado
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: imprime na tela todas as palavras presentes na arvoreTST que contenham o prefixo passado
void executaConsultarPalavra(arvoreTST raiz);

// Realiza a leitura do arquivo de remocao e deleta as palavras que estejam presentes na arvoreTST
// Pre-condicao: o ponteiro de arvoreTST deve ser valido
// Pos-condicao: a arvoreTST eh atualizada com as remocoes definidas pelo arquivo lido
void executaLerArquivoRemocao(arvoreTST *raiz);

// Realiza a consulta de palavras semelhantes
// Pre-condicao: o ponteiro de noTST deve ser valido
// Pos-condicao: imprime na tela as palavras que tenham quantidade de diferenca menor ou igual a palavra passada
void executaConsultarSemelhante(arvoreTST raiz);

#endif // ARVORETSTARQUIVO_H
