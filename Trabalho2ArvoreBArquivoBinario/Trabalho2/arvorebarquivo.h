#ifndef ARVOREBARQUIVO_H
#define ARVOREBARQUIVO_H

#include <stdio.h>

#define ORDEM 5

// Estrutura do cabecalho do arquivo de dados
typedef struct{
    int topo;  // posicao do topo do arquivo de dados
    int livre; // primeira posicao livre do arquivo de dados
} CabecalhoDados;

// Estrutura de um profissional
typedef struct{
    int codigo;                    // codigo referente ao profissional
    char nome[51];                 // nome do profissional
    char cpf[12];                  // CPF do profissional
    char registroProfissional[50]; // Registro Profissional
    char endereco[101];            // endereco do profissional
    char telefone[15];             // telefone do profissional
} Profissional;

// Estrutura do cabecalho do arquivo de index
typedef struct{
    int raiz;  // posicao da raiz da arvoreB do arquivo de index
    int topo;  // posicao do topo do arquivo de index
    int livre; // primeira posicao livre do arquivo de index
} CabecalhoIndex;

// Estrutura de no de arvoreB
typedef struct no{
    int numChaves;      // numero de chaves referente ao no
    int chave[ORDEM];   // array de inteiros armazenando as chaves do no
    int dados[ORDEM];   // array de inteiros armazenando a posicao dos dados no arquivo de dados
    int filho[ORDEM+1]; // array de inteiros armazenando a posicao dos filhos no arquivo de index
} arvoreB;

// Estrutura de no de fila
struct noFila{
    arvoreB item;        // item eh um no de arvoreB
    struct noFila *prox; // ponteiro para o proximo item da fila
};

// Estrutura de fila
typedef struct{
    struct noFila *inicio; // ponteiro de no de fila para o primeiro no da fila
    struct noFila *fim;    // ponteiro de no de fila para o ultimo no da fila
} Fila;

// Inicializa o cabecalho do arquivo de dados e o escreve no seu respectivo arquivo
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: cabecalho inicializado e salvo no arquivo de dados
void criarCabecalhoDados(FILE *dados);

// Inicializa o cabecalho do arquivo de index e o escreve no seu respectivo arquivo
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: cabecalho inicializar e salvo no arquivo de index
void criarCabecalhoIndex(FILE *index);

// Leitura do cabecalho de dados
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: retorna um cabecalho de dados com as informacoes salvas no arquivo de dados
CabecalhoDados leCabecalhoDados(FILE *dados);

// Leitura do cabecalho de index
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: retorna um cabecalho de index com as informacoes salvas no arquivo de index
CabecalhoIndex leCabecalhoIndex(FILE *index);

// Leitura de um Profissional
// pre-condicao: arquivo de dados deve existir e estar aberto, a posicao deve ser valida
// pos-condicao: retorna um profissional com as informacoes salvas no arquivo de dados
Profissional leProfissional(FILE *dados, int pos);

// Leitura de um no de arvoreB
// pre-condicao: arquivo deve existir e estar aberto, a posicao deve ser valida
// pos-condicao: retorna um no com as informacoes salvas no arquivo de index
arvoreB leNo(FILE *index, int pos);

// Escrita do cabecalho de dados
// pre-condicao: arquivo de dados deve existir e estar aberto, cabecalho deve ser valido
// pos-condicao: armazena a informacao do cabecalho passado no arquivo de dados
void escreveCabecalhoDados(FILE *dados, CabecalhoDados cab);

// Escrita do cabecalho de index
// pre-condicao: arquivo de index deve existir e estar aberto, cabecalho deve ser valido
// pos-condicao: armazena a informacao do cabecalho passado no arquivo de index
void escreveCabecalhoIndex(FILE *index, CabecalhoIndex cab);

// Escrita do Profissional
// pre-condicao: arquivo de dados deve existir e estar aberto, profissional e posicao devem ser validos
// pos-condicao: armazena a informacao do Profissional passado na sua posicao correspondente no arquivo de dados
void escreveProfissional(FILE *dados, Profissional x, int pos);

// Escrita de um no de arvoreB
// pre-condicao: arquivo de index deve existir e estar aberto, no e posicao devem ser validos
// pos-condicao: armazena a informacao do no de arvoreB passado na sua posicao correspondente no arquivo de index
void escreveNo(FILE *index, arvoreB x, int pos);

// Imprime um Profissional conforme a posicao passada
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: mostra as informacoes do Profissional na tela
void printProfissional(FILE *dados, int posDado);

// Insercao de um Profissional no arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: o Profissional passado é salvo no arquivo de dados, na posicao livre ou no topo
void inserirArquivoDados(FILE *dados, Profissional x);

// Cria e inicializa um no de arvoreB
// pre-condicao: nenhuma
// pos-condicao: retorna um no de arvoreB inicializado corretamente
arvoreB criarNo();

// Indica dado um determinado no se ele esta ou nao em overflow
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro
int overflow(arvoreB no);

// Indica dado um determinado no se ele eh folha ou nao
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro
int isFolha(arvoreB no);

// Divide em 2 um no de arvoreB com overflow, as informacoes que serao promovidas sao passadas por referencia
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna o no de arvoreB direito, resultante do split
arvoreB split(arvoreB *x, int *infoMeio, int *dadoMeio);

// Indica se uma determinada chave esta presente neste no e sua posicao eh passada por referencia
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro e passa a posicao da chave por referencia
int buscaPos(arvoreB *raiz, int codigo, int *pos);

// Insere uma nova chave em um no de arvoreB, deslocando as informacoes ja escritas caso necessario
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: chave eh inserida no No de arvoreB passado
void insereDireita(arvoreB *raiz, int codigo, int posDado, int posChave, int filho);

// Procura pelo local correto onde a chave passada deve ser inserida, em seguida a insere
// pre-condicao: arquivo de index deve existir e estar aberto, cabecalho e no devem ser validos
// pos-condicao: insere a nova chave em seu respectivo lugar, salvando corretamente no arquivo de index
void insereArvoreAux(FILE *index, CabecalhoIndex *cab, arvoreB *raiz, int codigo, int posDado);

// Insere um novo no na arvoreB, caso seja necessario cria uma raiz
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: cria um novo no de arvoreB inserindo-o, as novas informacoes sao escritas no arquivo de index
void inserirArvore(FILE *index, int codigo, int posDado);

// Funcao criada para padronizar o nome das funcoes
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: uma nova chave eh inserida na arvoreB e salva no arquivo de index
void inserirArquivoIndex(FILE *index, int codigo, int posDado);

// Funcao principal da insercao, insere uma nova chave na arvoreB no arquivo de index e um novo Profissional no arquivo de dados
// pre-condicao: arquivo de index e de dados devem existir e estar abertos
// pos-condicao: chave e Profissional passados sao inseridos em seus respectivos arquivos e salvos
void inserir(FILE *index, FILE *dados, Profissional x);

// Remove um Profissional do arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: um Profissional eh removido do arquivo de dados
void removerArquivoDados(FILE *dados, int posDado);

// Indica caso um determinado no esteja em overflow
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro
int underflow(arvoreB raiz);

// Retorna o menor elemento dada uma determinada arvoreB
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB deve ser valido
// pos-condicao: retorna um inteiro, chave de menor valor da arvoreB
int menorElemento(FILE *index, arvoreB raiz);

// Remove a chave e seu respectivo dado do no de arvoreB
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: a chave a ser retirada eh sobrescrita pela sua sucessora
void removerAux(arvoreB *raiz, int pos);

// Emprestimo de uma chave adjacente ao filho com underflow
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: alem de fazer a operacao de emprestimo um inteiro eh retornado, 1 caso o emprestimo ocorra, 0 caso contrario
int emprestimo(FILE *index, arvoreB *raiz, int pos, int posNo);

// Concatenacao de uma chave adjacente com o filho com underflow
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: o filho com underflow com seu irmao adjacente sao concatenados
void merge(FILE *index, arvoreB *raiz, int pos, int posNo);

// Funcao principal da remocao de uma chave de arvoreB
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: a chave eh removida do no de arvoreB e sua escrita eh feita no arquivo de index
void removerArvore(FILE *index, arvoreB *raiz, int codigo, int posNo);

// Funcao para inicializar a raiz da arvoreB e realizar a remocao
// pre-condicao: arquivo de index deve existir e estar aberto, cabecalho deve ser valido
// pos-condicao: raiz eh inicializada e a remocao eh feita
void removerArquivoIndex(FILE *index, CabecalhoIndex cab, int codigo);

// Funcao principal de remocao de um profissional, tanto da arvoreB quanto do arquivo de dados
// pre-condicao: arquivo de index e dados devem existir e estar abertos
// pos-condicao: a chave eh removida da arvoreB no arquivo de index, como tambem o Profissional do arquivo de dados
void remover(FILE *index, FILE *dados, int codigo);

// Busca da posicao do dado conforme o codigo de Profissional passado
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: um inteiro eh retornado, a posicao dos dados do Profissional no arquivo de dados
int buscarDadoAux(FILE *index, arvoreB raiz, int codigo);

// Funcao para inicializar a raiz da arvoreB, sua funcao auxiliar retorna a posicao do dado
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: retorna um inteiro, a posicao do dado no arquivo de dados ou -1 caso o codigo passado seja invalido
int buscarDado(FILE *index, int codigo);

// Altera o endereco do Profissional
// pre-condicao: o arquivo de dados deve existir e estar aberto
// pos-condicao: o endereco do Profissional passado eh alterado e escrito no arquivo de dados
void alterarEndereco(FILE *dados, int posDado, char *endereco);

// Altera o telefone do Profissional
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: o telefone do Profissional passado eh alterado e escrito no arquivo de dados
void alterarTelefone(FILE *dados, int posDado, char *telefone);

// Altera o endereco e o telefone de um Profissional, conforme codigo passado
// pre-condicao: o arquivo de index e de dados devem existir e estar aberto, o codigo passado deve ser valido
// pos-condicao: o campo endereco e telefone de um Profissional sao alterados e escritos no arquivo de dados
void alterar(FILE *index, FILE *dados, int codigo, char *endereco, char *telefone);

// Imprime os profissionais na tela em ordem crescente de codigo
// pre-condicao: arquivo de index e dados devem existir e estar aberto, raiz deve ser valida
// pos-condicao: os profissionais sao impressos na tela InOrdem
void printInOrdem(FILE *index, FILE *dados, arvoreB raiz);

// Aloca memoria para estrutura Fila e inicializa seus campos
// pre-condicao: nenhuma
// pos-condicao: um ponteiro de Fila eh retornado
Fila* criarFila();

// Enfileira um no de arvoreB em uma Fila
// pre-condicao: fila passada deve ser valida, bem como o no de arvoreB
// pos-condicao: um no de arvoreB eh armazenado em uma Fila de nos de arvoreB
void enqueue(Fila *fila, arvoreB item);

// Desenfileira um no de arvoreB de uma Fila
// pre-condicao: Fila passada deve ser valida
// pos-condicao: o no de arvoreB retirado eh retornado
struct noFila* dequeue(Fila *fila);

// Imprime as chaves da arvoreB por nivel
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: imprime as chaves de cada no por nivel na tela
void printPorNivel(FILE *index, arvoreB raiz);

// Imprime as posicoes livres do arquivo de index
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: imprime na tela todas as posicoes livres do arquivo de index
void printPosLivreIndex(FILE *index);

// Imprime as posicoes livres do arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: imprime na tela todas as posicoes livres do arquivo de index
void printPosLivreDados(FILE *dados);

// Funcao auxiliar para filtrar os brancos de uma string
// pre-condicao: as strings passadas devem ser validas
// pos-condicao: a string de destino recebe a string filtrada, sem os brancos extras
void eliminaBranco(char *dst, char *branco);

// Leitura do arquivo de texto, suas informacoes sao gravadas nos arquivos de index e dados
// pre-condicao: arquivo de index e dados devem existir e estar aberto, o nome do arquivo deve ser valido
// pos-condicao: as informacoes lidas do arquivo de texto sao gravadas nos arquivos de index e dados
void lerArquivoEntrada(char *fileName, FILE *index, FILE *dados);

// Insercao de um profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: Profissional eh inserido no arquivo de dados e seu codigo armazenado no arquivo de index
void inserirProfissionalManual(FILE *index, FILE *dados);

// Remocao de um profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: remove o codigo do arquivo de index e o Profissional do arquivo de dados
void removerProfissionalManual(FILE *index, FILE *dados);

// Altera o endereco de um Profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: o endereco do Profissional, conforme codigo passado, eh alterado
void alterarEnderecoManual(FILE *index, FILE *dados);

// Altera o telefone de um Profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: o telefone do Profissional, conforme codigo passado, eh alterado
void alterarTelefoneManual(FILE *index, FILE *dados);

// Imprime as informacoes de um Profissional de forma manual
// pre-condicao: arquivos de index e dados devem existir e estar aberto
// pos-condicao: as informacoes do Profissional, conforme codigo passado, sao impressas na tela
void printProfissionalManual(FILE *index, FILE *dados);

// Imprime o menu de operacoes na tela
// pre-condicao: nenhuma
// pos-condicao: as operacoes do menu sao impressas na tela
void printMenu();

#endif // ARVOREBARQUIVO_H
