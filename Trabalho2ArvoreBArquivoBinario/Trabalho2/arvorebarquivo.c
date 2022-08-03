#include "arvorebarquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa o cabecalho do arquivo de dados e o escreve no seu respectivo arquivo
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: cabecalho inicializado e salvo no arquivo de dados
void criarCabecalhoDados(FILE *dados){
    CabecalhoDados cab;
    cab.topo = 0;
    cab.livre = -1;
    fseek(dados, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoDados), 1, dados);
}

// Inicializa o cabecalho do arquivo de index e o escreve no seu respectivo arquivo
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: cabecalho inicializar e salvo no arquivo de index
void criarCabecalhoIndex(FILE *index){
    CabecalhoIndex cab;
    cab.raiz = -1;
    cab.topo = 0;
    cab.livre = -1;
    fseek(index, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoIndex), 1, index);
}

// Leitura do cabecalho de dados
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: retorna um cabecalho de dados com as informacoes salvas no arquivo de dados
CabecalhoDados leCabecalhoDados(FILE *dados){
    CabecalhoDados cab;
    fseek(dados, 0, SEEK_SET);
    fread(&cab, sizeof(CabecalhoDados), 1, dados);
    return cab;
}

// Leitura do cabecalho de index
// pre-condicao: arquivo deve existir e estar aberto
// pos-condicao: retorna um cabecalho de index com as informacoes salvas no arquivo de index
CabecalhoIndex leCabecalhoIndex(FILE *index){
    CabecalhoIndex cab;
    fseek(index, 0, SEEK_SET);
    fread(&cab, sizeof(CabecalhoIndex), 1, index);
    return cab;
}

// Leitura de um Profissional
// pre-condicao: arquivo de dados deve existir e estar aberto, a posicao deve ser valida
// pos-condicao: retorna um profissional com as informacoes salvas no arquivo de dados
Profissional leProfissional(FILE *dados, int pos){
    Profissional x;
    fseek(dados, sizeof(CabecalhoDados) + pos*sizeof(Profissional), SEEK_SET);
    fread(&x, sizeof(Profissional), 1, dados);
    return x;
}

// Leitura de um no de arvoreB
// pre-condicao: arquivo deve existir e estar aberto, a posicao deve ser valida
// pos-condicao: retorna um no com as informacoes salvas no arquivo de index
arvoreB leNo(FILE *index, int pos){
    arvoreB x;
    fseek(index, sizeof(CabecalhoIndex), SEEK_SET);
    fseek(index, pos*sizeof(arvoreB), SEEK_CUR);
    fread(&x, sizeof(arvoreB), 1, index);

    return x;
}

// Escrita do cabecalho de dados
// pre-condicao: arquivo de dados deve existir e estar aberto, cabecalho deve ser valido
// pos-condicao: armazena a informacao do cabecalho passado no arquivo de dados
void escreveCabecalhoDados(FILE *dados, CabecalhoDados cab){
    fseek(dados, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoDados), 1, dados);
}

// Escrita do cabecalho de index
// pre-condicao: arquivo de index deve existir e estar aberto, cabecalho deve ser valido
// pos-condicao: armazena a informacao do cabecalho passado no arquivo de index
void escreveCabecalhoIndex(FILE *index, CabecalhoIndex cab){
    fseek(index, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoIndex), 1, index);
}

// Escrita do Profissional
// pre-condicao: arquivo de dados deve existir e estar aberto, profissional e posicao devem ser validos
// pos-condicao: armazena a informacao do Profissional passado na sua posicao correspondente no arquivo de dados
void escreveProfissional(FILE *dados, Profissional x, int pos){
    fseek(dados, sizeof(CabecalhoDados), SEEK_SET);
    fseek(dados, pos*sizeof(Profissional), SEEK_CUR);
    fwrite(&x, sizeof(Profissional), 1, dados);
}

// Escrita de um no de arvoreB
// pre-condicao: arquivo de index deve existir e estar aberto, no e posicao devem ser validos
// pos-condicao: armazena a informacao do no de arvoreB passado na sua posicao correspondente no arquivo de index
void escreveNo(FILE *index, arvoreB x, int pos){
    fseek(index, sizeof(CabecalhoIndex), SEEK_SET);
    fseek(index, pos*sizeof(arvoreB), SEEK_CUR);
    fwrite(&x, sizeof(arvoreB), 1, index);
}

// Imprime um Profissional conforme a posicao passada
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: mostra as informacoes do Profissional na tela
void printProfissional(FILE *dados, int posDado){
    Profissional x = leProfissional(dados, posDado);
    printf("\nCodigo = %d\n", x.codigo);
    printf("Nome = [%s]\n", x.nome);
    printf("CPF = [%s]\n", x.cpf);
    printf("Registro Profissional = [%s]\n", x.registroProfissional);
    printf("Endereco = [%s]\n", x.endereco);
    printf("Telefone = [%s]\n\n", x.telefone);
}

// Insercao de um Profissional no arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: o Profissional passado é salvo no arquivo de dados, na posicao livre ou no topo
void inserirArquivoDados(FILE *dados, Profissional x){
    CabecalhoDados cab = leCabecalhoDados(dados);
    if(cab.livre == -1){
        escreveProfissional(dados, x, cab.topo);
        cab.topo++;
    }
    else{
        Profissional vazio = leProfissional(dados, cab.livre);
        escreveProfissional(dados, x, cab.livre);
        cab.livre = vazio.codigo;
    }
    escreveCabecalhoDados(dados, cab);
}

// Cria e inicializa um no de arvoreB
// pre-condicao: nenhuma
// pos-condicao: retorna um no de arvoreB inicializado corretamente
arvoreB criarNo(){
    arvoreB no;
    int i;
    no.numChaves = 0;
    for(i = 0; i < ORDEM; i++)
        no.chave[i] = no.dados[i] = no.filho[i] = -1;
    no.filho[i] = -1;

    return no;
}

// Indica dado um determinado no se ele esta ou nao em overflow
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro
int overflow(arvoreB no){
    return (no.numChaves == ORDEM);
}

// Indica dado um determinado no se ele eh folha ou nao
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro
int isFolha(arvoreB no){
    return (no.filho[0] == -1);
}

// Divide em 2 um no de arvoreB com overflow, as informacoes que serao promovidas sao passadas por referencia
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna o no de arvoreB direito, resultante do split
arvoreB split(arvoreB *x, int *infoMeio, int *dadoMeio){
    arvoreB y = criarNo();
    int i, metade = x->numChaves / 2;
    x->numChaves = metade;
    y.numChaves = metade;
    *infoMeio = x->chave[metade];
    *dadoMeio = x->dados[metade];
    y.filho[0] = x->filho[metade + 1];
    for(i = 0; i < y.numChaves; i++){
        y.chave[i] = x->chave[metade + i + 1];
        y.dados[i] = x->dados[metade + i + 1];
        y.filho[i + 1] = x->filho[metade + i + 2];
    }
    return y;
}

// Indica se uma determinada chave esta presente neste no e sua posicao eh passada por referencia
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro e passa a posicao da chave por referencia
int buscaPos(arvoreB *raiz, int codigo, int *pos){
    for(*pos = 0; *pos < raiz->numChaves; (*pos)++){
        if(codigo == raiz->chave[*pos])
            return 1;
        if(codigo < raiz->chave[*pos])
            break;
    }
    return 0;
}

// Insere uma nova chave em um no de arvoreB, deslocando as informacoes ja escritas caso necessario
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: chave eh inserida no No de arvoreB passado
void insereDireita(arvoreB *raiz, int codigo, int posDado, int posChave, int filho){
    int i;
    for(i = raiz->numChaves; i > posChave; i--){
        raiz->chave[i] = raiz->chave[i-1];
        raiz->dados[i] = raiz->dados[i-1];
        raiz->filho[i+1] = raiz->filho[i];
    }
    raiz->chave[i] = codigo;
    raiz->dados[i] = posDado;
    raiz->filho[i+1] = filho;
    raiz->numChaves++;
}

// Procura pelo local correto onde a chave passada deve ser inserida, em seguida a insere
// pre-condicao: arquivo de index deve existir e estar aberto, cabecalho e no devem ser validos
// pos-condicao: insere a nova chave em seu respectivo lugar, salvando corretamente no arquivo de index
void insereArvoreAux(FILE *index, CabecalhoIndex *cab, arvoreB *raiz, int codigo, int posDado){
    int posChave;
    if(!buscaPos(raiz, codigo, &posChave)){
        if(isFolha(*raiz))
            insereDireita(raiz, codigo, posDado, posChave, -1);
        else{
            arvoreB filho = leNo(index, raiz->filho[posChave]);
            insereArvoreAux(index, cab, &filho, codigo, posDado);
            if(overflow(filho)){
                int infoMeio, dadoMeio;
                arvoreB aux = split(&filho, &infoMeio, &dadoMeio);
                if(cab->livre == -1){
                    escreveNo(index, aux, cab->topo++);
                    insereDireita(raiz, infoMeio, dadoMeio, posChave, cab->topo-1);
                }
                else{
                    arvoreB vazio = leNo(index, cab->livre);
                    escreveNo(index, aux, cab->livre);
                    insereDireita(raiz, infoMeio, dadoMeio, posChave, cab->livre);
                    cab->livre = vazio.chave[0];
                }
            }
            escreveNo(index, filho, raiz->filho[posChave]);
        }
    }
}

// Insere um novo no na arvoreB, caso seja necessario cria uma raiz
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: cria um novo no de arvoreB inserindo-o, as novas informacoes sao escritas no arquivo de index
void inserirArvore(FILE *index, int codigo, int posDado){
    CabecalhoIndex cab = leCabecalhoIndex(index);
    arvoreB raiz, novaRaiz, aux, vazio;
    int infoMeio, dadoMeio;
    if(cab.raiz == -1){ // caso arvoreB seja vazia!!
        raiz = criarNo();
        raiz.chave[0] = codigo;
        raiz.dados[0] = posDado;
        raiz.numChaves++;
        if(cab.livre == -1){
            cab.raiz = cab.topo;
            cab.topo++;
        }
        else{
            vazio = leNo(index, cab.livre);
            cab.raiz = cab.livre;
            cab.livre = vazio.chave[0];
        }
        escreveNo(index, raiz, cab.raiz);
    }
    else{
        raiz = leNo(index, cab.raiz);
        insereArvoreAux(index, &cab, &raiz, codigo, posDado);
        if(overflow(raiz)){
            aux = split(&raiz, &infoMeio, &dadoMeio);
            novaRaiz = criarNo();
            novaRaiz.chave[0] = infoMeio;
            novaRaiz.dados[0] = dadoMeio;
            novaRaiz.filho[0] = cab.raiz;
            novaRaiz.numChaves++;
            escreveNo(index, raiz, cab.raiz);
            if(cab.livre == -1){
                novaRaiz.filho[1] = cab.topo;
                escreveNo(index, aux, cab.topo++);
            }
            else{
                vazio = leNo(index, cab.livre); // no auxiliar para armazenar a posicao do proximo livre!!
                novaRaiz.filho[1] = cab.livre;
                escreveNo(index, aux, cab.livre);
                cab.livre = vazio.chave[0];
            }
            if(cab.livre == -1){
                cab.raiz = cab.topo++;
                escreveNo(index, novaRaiz, cab.raiz);
            }
            else{
                vazio = leNo(index, cab.livre); // no auxiliar para armazenar a posicao do proximo livre!!
                cab.raiz = cab.livre;
                escreveNo(index, novaRaiz, cab.raiz);
                cab.livre = vazio.chave[0];
            }
        }
        else // somente eh necessario escrever a raiz!!
            escreveNo(index, raiz, cab.raiz);
    }
    escreveCabecalhoIndex(index, cab);
}

// Funcao criada para padronizar o nome das funcoes
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: uma nova chave eh inserida na arvoreB e salva no arquivo de index
void inserirArquivoIndex(FILE *index, int codigo, int posDado){
    inserirArvore(index, codigo, posDado);
}

// Funcao principal da insercao, insere uma nova chave na arvoreB no arquivo de index e um novo Profissional no arquivo de dados
// pre-condicao: arquivo de index e de dados devem existir e estar abertos
// pos-condicao: chave e Profissional passados sao inseridos em seus respectivos arquivos e salvos
void inserir(FILE *index, FILE *dados, Profissional x){
    CabecalhoDados cabDados = leCabecalhoDados(dados);
    CabecalhoIndex cabIndex = leCabecalhoIndex(index);

    if(cabIndex.raiz == -1 || buscarDado(index, x.codigo) == -1){
        if(cabDados.livre == -1)
            inserirArquivoIndex(index, x.codigo, cabDados.topo);
        else
            inserirArquivoIndex(index, x.codigo, cabDados.livre);
        inserirArquivoDados(dados, x);
    }
}

// Remove um Profissional do arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: um Profissional eh removido do arquivo de dados
void removerArquivoDados(FILE *dados, int posDado){
    CabecalhoDados cab = leCabecalhoDados(dados);
    Profissional x = leProfissional(dados, posDado);
    if(cab.livre == -1){
        cab.livre = posDado; // talvez x.codigo!!
        x.codigo = -1;
    }
    else{
        x.codigo = cab.livre;
        cab.livre = posDado;
    }
    escreveProfissional(dados, x, posDado);
    escreveCabecalhoDados(dados, cab);
}

// Indica caso um determinado no esteja em overflow
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: retorna um inteiro
int underflow(arvoreB raiz){
    return (raiz.numChaves < (ORDEM-1)/2 ? 1 : 0);
}

// Retorna o menor elemento dada uma determinada arvoreB
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB deve ser valido
// pos-condicao: retorna um inteiro, chave de menor valor da arvoreB
int menorElemento(FILE *index, arvoreB raiz){
    if(isFolha(raiz))
        return raiz.chave[0];
    if(raiz.filho[0] != -1)
        return menorElemento(index, leNo(index, raiz.filho[0]));
    return -1;
}

// Remove a chave e seu respectivo dado do no de arvoreB
// pre-condicao: no de arvoreB passado deve ser valido
// pos-condicao: a chave a ser retirada eh sobrescrita pela sua sucessora
void removerAux(arvoreB *raiz, int pos){
    int i;
    for(i = pos; i < raiz->numChaves-1; i++){
        raiz->chave[i] = raiz->chave[i+1];
        raiz->dados[i] = raiz->dados[i+1];
        raiz->filho[i] = raiz->filho[i+1];
    }
    raiz->filho[i] = raiz->filho[i+1];
    raiz->numChaves--;
}

// Emprestimo de uma chave adjacente ao filho com underflow
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: alem de fazer a operacao de emprestimo um inteiro eh retornado, 1 caso o emprestimo ocorra, 0 caso contrario
int emprestimo(FILE *index, arvoreB *raiz, int pos, int posNo){
    arvoreB filho, irmaoEsq, irmaoDir;
    int posChave;
    filho = leNo(index, raiz->filho[pos]);
    irmaoEsq = leNo(index, raiz->filho[pos-1]);
    irmaoDir = leNo(index, raiz->filho[pos+1]);
    if(pos-1 >= 0){
        if(irmaoEsq.numChaves > (ORDEM-1)/2){
            insereDireita(&filho, raiz->chave[pos-1], raiz->dados[pos-1], 0, -1);
            escreveNo(index, filho, raiz->filho[pos]);
            posChave = irmaoEsq.numChaves-1;
            raiz->chave[pos-1] = irmaoEsq.chave[posChave];
            raiz->dados[pos-1] = irmaoEsq.dados[posChave];
            escreveNo(index, *raiz, posNo);
            removerAux(&irmaoEsq, posChave);
            escreveNo(index, irmaoEsq, raiz->filho[pos-1]);
            return 1;
        }
    }
    if(pos+1 <= raiz->numChaves){
        if(irmaoDir.numChaves > (ORDEM-1)/2){
            insereDireita(&filho, raiz->chave[pos], raiz->dados[pos], filho.numChaves, -1);
            escreveNo(index, filho, raiz->filho[pos]);
            raiz->chave[pos] = irmaoDir.chave[0];
            raiz->dados[pos] = irmaoDir.dados[0];
            escreveNo(index, *raiz, posNo);
            removerAux(&irmaoDir, 0);
            escreveNo(index, irmaoDir, raiz->filho[pos+1]);
            return 1;
        }
    }
    return 0;
}

// Concatenacao de uma chave adjacente com o filho com underflow
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: o filho com underflow com seu irmao adjacente sao concatenados
void merge(FILE *index, arvoreB *raiz, int pos, int posNo){
    arvoreB filho, irmaoEsq, irmaoDir;
    CabecalhoIndex cab = leCabecalhoIndex(index);
    filho = leNo(index, raiz->filho[pos]);
    irmaoEsq = leNo(index, raiz->filho[pos-1]);
    irmaoDir = leNo(index, raiz->filho[pos+1]);
    if(pos-1 >= 0){
        insereDireita(&filho, raiz->chave[pos-1], raiz->dados[pos-1], 0, filho.filho[0]);
        for(int i = 0; i < irmaoEsq.numChaves; i++)
            insereDireita(&filho, irmaoEsq.chave[i], irmaoEsq.dados[i], i, irmaoEsq.filho[i+1]);
        filho.filho[0] = irmaoEsq.filho[0]; // em cima acontece shift right!!
        escreveNo(index, filho, raiz->filho[pos]);
        if(cab.livre == -1){
            cab.livre = raiz->filho[pos-1];
            irmaoEsq.chave[0] = -1;
        }
        else{
            irmaoEsq.chave[0] = cab.livre;
            cab.livre = raiz->filho[pos-1];
        }
        irmaoEsq.numChaves = 0; // talvez tirar!!!
        escreveNo(index, irmaoEsq, raiz->filho[pos-1]);
        removerAux(raiz, pos-1);
        escreveNo(index, *raiz, posNo);
    }
    else
        if(pos+1 <= raiz->numChaves){
            insereDireita(&irmaoDir, raiz->chave[pos], raiz->dados[pos], 0, irmaoDir.filho[0]);
            for(int i = 0; i < filho.numChaves; i++)
                insereDireita(&irmaoDir, filho.chave[i], filho.dados[i], i, filho.filho[i+1]);
            irmaoDir.filho[0] = filho.filho[0];
            escreveNo(index, irmaoDir, raiz->filho[pos+1]);
            if(cab.livre == -1){
                cab.livre = raiz->filho[pos];
                filho.chave[0] = -1;
            }
            else{
                filho.chave[0] = cab.livre;
                cab.livre = raiz->filho[pos];
            }
            filho.numChaves = 0; // talvez tirar!!
            escreveNo(index, filho, raiz->filho[pos]);
            removerAux(raiz, pos);
            escreveNo(index, *raiz, posNo);
        }
    escreveCabecalhoIndex(index, cab);
}

// Funcao principal da remocao de uma chave de arvoreB
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: a chave eh removida do no de arvoreB e sua escrita eh feita no arquivo de index
void removerArvore(FILE *index, arvoreB *raiz, int codigo, int posNo){
    int i, sucessor;
    arvoreB filho;
    filho.numChaves = -1;
    for(i = 0; i < raiz->numChaves; i++){
        if(codigo == raiz->chave[i] || codigo < raiz->chave[i])
            break;
    }
    if(i < raiz->numChaves && codigo == raiz->chave[i]){
        if(isFolha(*raiz)){
            removerAux(raiz, i);
            escreveNo(index, *raiz, posNo);
        }
        else{
            arvoreB filhoDireita = leNo(index, raiz->filho[i+1]);
            sucessor = menorElemento(index, filhoDireita);
            raiz->dados[i] = buscarDado(index, sucessor);
            raiz->chave[i] = sucessor;
            escreveNo(index, *raiz, posNo);
            removerArvore(index, &filhoDireita, sucessor, raiz->filho[i+1]);
            if(underflow(filhoDireita)){
                if(!emprestimo(index, raiz, i+1, posNo)){
                    merge(index, raiz, i+1, posNo);
                }
            }
        }
    }
    else{
        filho = leNo(index, raiz->filho[i]);
        removerArvore(index, &filho, codigo, raiz->filho[i]);
    }
    if(!isFolha(*raiz)){
        if(filho.numChaves != -1 && underflow(filho)){
            if(!emprestimo(index, raiz, i, posNo)){
                merge(index, raiz, i, posNo);
            }
        }
    }
    if(raiz->numChaves == 0){
        CabecalhoIndex cab = leCabecalhoIndex(index);
        if(cab.livre == -1){
            raiz->chave[0] = -1;
            cab.livre = posNo;
        }
        else{
            raiz->chave[0] = cab.livre;
            cab.livre = posNo;
        }
        cab.raiz = raiz->filho[0];
        escreveNo(index, *raiz, posNo);
        escreveCabecalhoIndex(index, cab);
    }
}

// Funcao para inicializar a raiz da arvoreB e realizar a remocao
// pre-condicao: arquivo de index deve existir e estar aberto, cabecalho deve ser valido
// pos-condicao: raiz eh inicializada e a remocao eh feita
void removerArquivoIndex(FILE *index, CabecalhoIndex cab, int codigo){
    arvoreB raiz = leNo(index, cab.raiz);
    removerArvore(index, &raiz, codigo, cab.raiz);
}

// Funcao principal de remocao de um profissional, tanto da arvoreB quanto do arquivo de dados
// pre-condicao: arquivo de index e dados devem existir e estar abertos
// pos-condicao: a chave eh removida da arvoreB no arquivo de index, como tambem o Profissional do arquivo de dados
void remover(FILE *index, FILE *dados, int codigo){
    CabecalhoIndex cabIndex = leCabecalhoIndex(index);
    int posDado = -1;

    if(cabIndex.raiz != -1)
        posDado = buscarDado(index, codigo);

    if(posDado != -1){
        removerArquivoIndex(index, cabIndex, codigo);
        removerArquivoDados(dados, posDado);
    }
    else
        printf("Codigo invalido!!\n");

}

// Busca da posicao do dado conforme o codigo de Profissional passado
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: um inteiro eh retornado, a posicao dos dados do Profissional no arquivo de dados
int buscarDadoAux(FILE *index, arvoreB raiz, int codigo){
    int i;
    for(i = 0; i < raiz.numChaves; i++){
        if(raiz.chave[i] == codigo)
            return raiz.dados[i];
        if(codigo < raiz.chave[i])
            break;
    }
    if(raiz.filho[i] != -1)
        return buscarDadoAux(index, leNo(index, raiz.filho[i]), codigo);
    else
        return -1;
}

// Funcao para inicializar a raiz da arvoreB, sua funcao auxiliar retorna a posicao do dado
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: retorna um inteiro, a posicao do dado no arquivo de dados ou -1 caso o codigo passado seja invalido
int buscarDado(FILE *index, int codigo){
    CabecalhoIndex cab = leCabecalhoIndex(index);
    if(cab.raiz != -1){
        arvoreB raiz = leNo(index, cab.raiz);
        return buscarDadoAux(index, raiz, codigo);
    }
    return -1;
}

// Altera o endereco do Profissional
// pre-condicao: o arquivo de dados deve existir e estar aberto
// pos-condicao: o endereco do Profissional passado eh alterado e escrito no arquivo de dados
void alterarEndereco(FILE *dados, int posDado, char *endereco){
    Profissional x = leProfissional(dados, posDado);
    strcpy(x.endereco, endereco);
    escreveProfissional(dados, x, posDado);
}

// Altera o telefone do Profissional
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: o telefone do Profissional passado eh alterado e escrito no arquivo de dados
void alterarTelefone(FILE *dados, int posDado, char *telefone){
    Profissional x = leProfissional(dados, posDado);
    strcpy(x.telefone, telefone);
    escreveProfissional(dados, x, posDado);
}

// Altera o endereco e o telefone de um Profissional, conforme codigo passado
// pre-condicao: o arquivo de index e de dados devem existir e estar aberto, o codigo passado deve ser valido
// pos-condicao: o campo endereco e telefone de um Profissional sao alterados e escritos no arquivo de dados
void alterar(FILE *index, FILE *dados, int codigo, char *endereco, char *telefone){
    int posDado = buscarDado(index, codigo);
    if(posDado != -1){
        if(strcmp(endereco, "")) // caso seja diferente de uma string vazia, insira!!
            alterarEndereco(dados, posDado, endereco);
        if(strcmp(telefone, "")) // caso seja diferente de uma string vazia, insira!!
            alterarTelefone(dados, posDado, telefone);
    }
    else
        printf("Codigo invalido!!\n");
}

// Imprime os profissionais na tela em ordem crescente de codigo
// pre-condicao: arquivo de index e dados devem existir e estar aberto, raiz deve ser valida
// pos-condicao: os profissionais sao impressos na tela InOrdem
void printInOrdem(FILE *index, FILE *dados, arvoreB raiz){
    int i;
    if(isFolha(raiz))
        for(i = 0; i < raiz.numChaves; i++)
            printProfissional(dados, raiz.dados[i]);
    else{
        for(i = 0; i < raiz.numChaves; i++){
            printInOrdem(index, dados, leNo(index, raiz.filho[i]));
            printProfissional(dados, raiz.dados[i]);
        }
        printInOrdem(index, dados, leNo(index, raiz.filho[i]));
    }
}

// Aloca memoria para estrutura Fila e inicializa seus campos
// pre-condicao: nenhuma
// pos-condicao: um ponteiro de Fila eh retornado
Fila* criarFila(){
    Fila *aux = (Fila*) malloc(sizeof(Fila));
    aux->inicio = aux->fim = NULL;
    return aux;
}

// Enfileira um no de arvoreB em uma Fila
// pre-condicao: fila passada deve ser valida, bem como o no de arvoreB
// pos-condicao: um no de arvoreB eh armazenado em uma Fila de nos de arvoreB
void enqueue(Fila *fila, arvoreB item){
    struct noFila *aux = (struct noFila*) malloc(sizeof(struct noFila));
    aux->item = item;
    aux->prox = NULL;
    if(fila->inicio == NULL)
        fila->inicio = fila->fim = aux;
    else{
        fila->fim->prox = aux;
        fila->fim = aux;
    }
}

// Desenfileira um no de arvoreB de uma Fila
// pre-condicao: Fila passada deve ser valida
// pos-condicao: o no de arvoreB retirado eh retornado
struct noFila* dequeue(Fila *fila){
    struct noFila *aux;
    aux = fila->inicio;
    if(fila->inicio != NULL)
        fila->inicio = fila->inicio->prox;
    return aux;
}

// Imprime as chaves da arvoreB por nivel
// pre-condicao: arquivo de index deve existir e estar aberto, o no de arvoreB passado deve ser valido
// pos-condicao: imprime as chaves de cada no por nivel na tela
void printPorNivel(FILE *index, arvoreB raiz){
    Fila *fila = criarFila();
    int i;
    struct noFila *aux;
    arvoreB vazio;
    vazio.numChaves = -1;
    enqueue(fila, raiz);
    enqueue(fila, vazio);
    while(fila->inicio != NULL){
        aux = dequeue(fila);
        if(aux->item.numChaves != -1){
            printf("[");
            for(i = 0; i < aux->item.numChaves; i++){
                if(i == aux->item.numChaves-1)
                    printf("%d", aux->item.chave[i]);
                else
                    printf("%d ", aux->item.chave[i]);
                if(aux->item.filho[i] != -1)
                    enqueue(fila, leNo(index, aux->item.filho[i]));
            }
            printf("] ");
            if(aux->item.filho[i] != -1)
                enqueue(fila, leNo(index, aux->item.filho[i]));
        }
        else{
            printf("\n");
            if(fila->inicio != NULL)
                enqueue(fila, vazio);
        }
        free(aux);
    }
    free(fila);
}

// Imprime as posicoes livres do arquivo de index
// pre-condicao: arquivo de index deve existir e estar aberto
// pos-condicao: imprime na tela todas as posicoes livres do arquivo de index
void printPosLivreIndex(FILE *index){
    CabecalhoIndex cab = leCabecalhoIndex(index);
    arvoreB vazio = leNo(index, cab.livre);
    printf("Posicao livre = %d\n", cab.livre);
    if(cab.livre != -1)
        while(vazio.chave[0] != -1){
            printf("Posicao livre = %d\n", vazio.chave[0]);
            vazio = leNo(index, vazio.chave[0]);
        }
}

// Imprime as posicoes livres do arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: imprime na tela todas as posicoes livres do arquivo de index
void printPosLivreDados(FILE *dados){
    CabecalhoDados cab = leCabecalhoDados(dados);
    Profissional vazio = leProfissional(dados, cab.livre);
    printf("Posicao livre = %d\n", cab.livre);
    if(cab.livre != -1)
        while(vazio.codigo != -1){
            printf("Posicao livre = %d\n", vazio.codigo);
            vazio = leProfissional(dados, vazio.codigo);
        }
}

// Funcao auxiliar para filtrar os brancos de uma string
// pre-condicao: as strings passadas devem ser validas
// pos-condicao: a string de destino recebe a string filtrada, sem os brancos extras
void eliminaBranco(char *dst, char *branco){
    while(*branco){
        if(*branco == ' ')
            if(*(branco + 1) == ' ')
                break;
        *dst++ = *branco++;
    }
    *dst = '\0';
}

// Leitura do arquivo de texto, suas informacoes sao gravadas nos arquivos de index e dados
// pre-condicao: arquivo de index e dados devem existir e estar aberto, o nome do arquivo deve ser valido
// pos-condicao: as informacoes lidas do arquivo de texto sao gravadas nos arquivos de index e dados
void lerArquivoEntrada(char *fileName, FILE *index, FILE *dados){
    char operacao, teste, branco[200];
    Profissional aux;
    FILE *f;
    f = fopen(fileName, "r");
    if(f != NULL){
        while(fscanf(f, " %c ;", &operacao) != EOF){
            switch(operacao){
            case 'I': // insercao!!
                fscanf(f, " %d ;", &aux.codigo);
                fscanf(f, " %[^;];", branco);
                eliminaBranco(aux.nome, branco);
                fscanf(f, " %[^;];", branco);
                eliminaBranco(aux.cpf, branco);
                fscanf(f, " %[^;];", branco);
                eliminaBranco(aux.registroProfissional, branco);
                fscanf(f, " %[^;];", branco);
                eliminaBranco(aux.endereco, branco);
                fscanf(f, " %s \n", aux.telefone);
                inserir(index, dados, aux);
                break;
            case 'A': // alteracao!!
                fscanf(f, " %d ;", &aux.codigo);
                fscanf(f, " %c", &teste);
                if(teste != ';'){
                    fseek(f, -1, SEEK_CUR);
                    fscanf(f, "%[^;];", branco);
                    eliminaBranco(aux.endereco, branco);
                }
                else
                    strcpy(aux.endereco, "");
                fscanf(f, " %c", &teste);
                if(fscanf(f, "%c", &teste) != EOF && !(teste >= '0' && teste <= '9')){
                    fseek(f, -2, SEEK_CUR);
                    strcpy(aux.telefone, "");
                }
                else{
                    if(!feof(f)){
                        fseek(f, -2, SEEK_CUR);
                        fscanf(f, "%s \n", aux.telefone);
                    }
                    else
                        strcpy(aux.telefone, "");
                }
                alterar(index, dados, aux.codigo, aux.endereco, aux.telefone);
                break;
            case 'R': // remocao!!
                fscanf(f, " %d \n", &aux.codigo);
                remover(index, dados, aux.codigo);
                break;
            default:
                printf("Operacao invalida!!\n");
            }
        }
        printf("\nLeitura de arquivo concluida!!\n");
        fclose(f);
    }
    else
        printf("\nArquivo invalido!!\n");
}

// Insercao de um profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: Profissional eh inserido no arquivo de dados e seu codigo armazenado no arquivo de index
void inserirProfissionalManual(FILE *index, FILE *dados){
    Profissional x;
    printf("Entre com o codigo:\n");
    printf("> ");
    scanf("%d%*c", &x.codigo);

    printf("Entre com o nome:\n");
    printf("> ");
    scanf("%[^\n]%*c", x.nome);

    printf("Entre com o CPF:\n");
    printf("> ");
    scanf("%s%*c", x.cpf);

    printf("Entre com o Registro Profissional:\n");
    printf("> ");
    scanf("%[^\n]%*c", x.registroProfissional);

    printf("Entre com o endereco:\n");
    printf("> ");
    scanf("%[^\n]%*c", x.endereco);

    printf("Entre com o telefone:\n");
    printf("> ");
    scanf("%s%*c", x.telefone);

    inserir(index, dados, x);
}

// Remocao de um profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: remove o codigo do arquivo de index e o Profissional do arquivo de dados
void removerProfissionalManual(FILE *index, FILE *dados){
    int codigo;
    printf("Entre com o codigo do profissional:\n");
    printf("> ");
    scanf("%d%*c", &codigo);

    remover(index, dados, codigo);
}

// Altera o endereco de um Profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: o endereco do Profissional, conforme codigo passado, eh alterado
void alterarEnderecoManual(FILE *index, FILE *dados){
    int codigo, posDado;
    char endereco[101];
    printf("Entre com o codigo do profissional:\n");
    printf("> ");
    scanf("%d%*c", &codigo);

    posDado = buscarDado(index, codigo);

    if(posDado != -1){
        printf("Entre com o novo endereco:\n");
        printf("> ");
        scanf("%[^\n]%*c", endereco);
        alterarEndereco(dados, buscarDado(index, codigo), endereco);
        printf("\nEndereco atualizado!!\n");
    }
    else
        printf("Codigo invalido!!\n");
}

// Altera o telefone de um Profissional de forma manual
// pre-condicao: arquivo de index e dados devem existir e estar aberto
// pos-condicao: o telefone do Profissional, conforme codigo passado, eh alterado
void alterarTelefoneManual(FILE *index, FILE *dados){
    int codigo, posDado;
    char telefone[15];
    printf("Entre com o codigo do profissional:\n");
    printf("> ");
    scanf("%d%*c", &codigo);

    posDado = buscarDado(index, codigo);

    if(posDado != -1){
        printf("Entre com o novo telefone:\n");
        printf("> ");
        scanf("%[^\n]%*c", telefone);
        alterarTelefone(dados, buscarDado(index, codigo), telefone);
        printf("\nTelefone atualizado!!\n");
    }
    else
        printf("Codigo invalido!!\n");
}

// Imprime as informacoes de um Profissional de forma manual
// pre-condicao: arquivos de index e dados devem existir e estar aberto
// pos-condicao: as informacoes do Profissional, conforme codigo passado, sao impressas na tela
void printProfissionalManual(FILE *index, FILE *dados){
    int codigo, posDado;
    printf("Entre com o codigo do profissional:\n");
    printf("> ");
    scanf("%d%*c", &codigo);

    posDado = buscarDado(index, codigo);
    if(posDado != -1)
        printProfissional(dados, posDado);
    else
        printf("Codigo invalido!!\n");
}

// Imprime o menu de operacoes na tela
// pre-condicao: nenhuma
// pos-condicao: as operacoes do menu sao impressas na tela
void printMenu(){
    printf(" 1 - Inserir Profissional\n");
    printf(" 2 - Remover Profissional\n");
    printf(" 3 - Alterar Endereco\n");
    printf(" 4 - Alterar Telefone\n");
    printf(" 5 - Carregar Arquivo Texto\n");
    printf(" 6 - Informacoes do Profissional\n");
    printf(" 7 - Listar Profissionais (InOrdem)\n");
    printf(" 8 - Imprimir Arvore (Por nivel)\n");
    printf(" 9 - Imprimir Posicoes Livres (Arquivo Dados)\n");
    printf("10 - Imprimir Posicoes Livres (Arquivo Index)\n");
    printf(" 0 - Fechar Programa\n");
    printf("----------------------------------------------------------\n");
}

