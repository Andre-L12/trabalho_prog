#include <stdio.h>
#include <stdlib.h>
#define MAX_CARROS_PISTA 10
#define MAX_COLISAO 20
#define MAX_PISTA 12
#define MAX_LINHAS_MATRIZ ((MAX_PISTA*3)-1)
#define MAX_COLUNAS_MATRIZ 100
#define MAX_LINHA_DESENHO 2
#define MAX_COLUNA_DESENHO 3

// STRUCS
typedef struct
{
    int vidas;
    int x;
    int y;
    int altura_maxima;
    int maximo_atropelamento;
    int min_atropelamento;
} tgalinha;

typedef struct
{
    int x;
} tcarro;

typedef struct
{
    char direcao;
    int velocidade;
    int num_carros;
    tcarro posicao_carros[MAX_CARROS_PISTA];
} tpista;

typedef struct
{
    int id_pista;
    int id_carro;
    int interacao;
    int x;
    int y;
} tcolisao;

typedef struct
{
    int animacao;
    int pontuacao;
    int n_colisoes;
    int n_movimentoS;
    int n_movimentosW;
    int interacoes;
    int largura_mapa;
    int qtd_pistas;
    int linhas;
    tgalinha galinha;
    tcolisao colisoes[MAX_COLISAO];
    tpista pistas[MAX_PISTA];
    char matriz[MAX_LINHAS_MATRIZ][MAX_COLUNAS_MATRIZ];
    char desenho_galinha[MAX_LINHA_DESENHO][MAX_COLUNA_DESENHO];
    char desenho_carro[4][MAX_LINHA_DESENHO][MAX_COLUNA_DESENHO];
    int heatmap[MAX_LINHAS_MATRIZ][MAX_COLUNAS_MATRIZ];
    int p;
    int f;
} tjogo;

// FUNCOES TCOLISAO
int obtemPistaColisao(tcolisao colisao)
{
    return colisao.id_pista;
}
int obtemCarroColisao(tcolisao colisao)
{
    return colisao.id_carro;
}
int obtemInteracaoColisao(tcolisao colisao)
{
    return colisao.interacao;
}
int obtemXColisao(tcolisao colisao)
{
    return colisao.x;
}
int obtemYColisao(tcolisao colisao)
{
    return colisao.y;
}
tcolisao Lecolisao(int p, int c, int i, int x, int y)
{
    tcolisao colisao;
    colisao.id_pista = p;
    colisao.id_carro = c;
    colisao.interacao = i;
    colisao.x = x;
    colisao.y = y;
    return colisao;
}
void AdicionaColisao(tcolisao colisao, tcolisao *colisoes, int n)
{
    colisoes[n] = colisao;
}

// FUNCOES TGALINHA
int obtemXGalinha(tgalinha galinha)
{
    return galinha.x;
}
int obtemYGalinha(tgalinha galinha)
{
    return galinha.y;
}
int obtemVidasGalinha(tgalinha galinha)
{
    return galinha.vidas;
}
int obtemMaximaAlturaGalinha(tgalinha galinha)
{
    return galinha.altura_maxima;
}
int obtemMaxAtropelamento(tgalinha galinha)
{
    return galinha.maximo_atropelamento;
}
int obtemMinAtropelamento(tgalinha galinha)
{
    return galinha.min_atropelamento;
}
tgalinha atualizaYGalinha(tgalinha galinha, int y)
{
    galinha.y = y;
    return galinha;
}
tgalinha atualizaXGalinha(tgalinha galinha, int x)
{
    galinha.x= x;
    return galinha;
}
tgalinha diminuiVidaGalinha(tgalinha galinha)
{
    galinha.vidas--;
    return galinha;
}
tgalinha moveGalinha(tgalinha galinha, int x)
{
    galinha.y = galinha.y + x;
    return galinha;
}
tgalinha moveGalinhaX(tgalinha galinha, int x)
{
    galinha.x = galinha.x + x;
    return galinha;
}
tgalinha atualizaMaximaGalinha(tgalinha galinha, int y)
{
    if (y < galinha.altura_maxima)
    {
        galinha.altura_maxima = y;
    }
    return galinha;
}
tgalinha atualizaMaxMinColisaoGalinha(tgalinha galinha, int y)
{
    if (y > galinha.min_atropelamento)
    {
        galinha.min_atropelamento = y;
    }
    if (y < galinha.maximo_atropelamento)
    {
        galinha.maximo_atropelamento = y;
    }
    return galinha;
}
tgalinha iniciaGalinha(int vidas, int x, int y, int altura_maxima, int maximo_atropelamento, int min_atropelamento)
{
    tgalinha galinha;
    galinha.vidas = vidas;
    galinha.x = x;
    galinha.y = y;
    galinha.altura_maxima = altura_maxima;
    galinha.maximo_atropelamento = maximo_atropelamento;
    galinha.min_atropelamento = min_atropelamento;
    return galinha;
}

// FUNCOES TCARRO
int obtemXCarro(tcarro carro)
{
    return carro.x;
}
tcarro moveCarro(tcarro carro, int x, int set)
{
    if (set)
    {
        carro.x = x; // muda para o valor valor x
    }
    else
    {
        carro.x = carro.x + x; // soma valor x
    }
    return carro;
}
tcarro leCarro(int x)
{
    tcarro carro;
    carro.x = x;
    return carro;
}

// FUNCOES TPISTA
char obtemDirecaoPista(tpista pista)
{
    return pista.direcao;
}
int obtemVelocidadePista(tpista pista)
{
    return pista.velocidade;
}
int obtemNumCarrosPista(tpista pista)
{
    return pista.num_carros;
}
int obtemXCarroPista(tpista pista, int i)
{
    return obtemXCarro(pista.posicao_carros[i]);
}
tpista moveCarroPista(tpista pista,int larguraMapa,int set)
{
    int posicao_carro,i;
    for ( i = 0; i < pista.num_carros; i++)
    {
        if(pista.direcao=='D'){
        posicao_carro=((obtemXCarro(pista.posicao_carros[i])+pista.velocidade)%larguraMapa);
        }else{
        posicao_carro=(((obtemXCarro(pista.posicao_carros[i])+(pista.velocidade*-1))%larguraMapa)+larguraMapa)%larguraMapa;
        }
        pista.posicao_carros[i] = moveCarro(pista.posicao_carros[i], posicao_carro, set); //move os caros com base na velocidade da pista
    }
    return pista;
}
tpista diminuiVelocidadePista(tpista pista)
{
    pista.velocidade--;
    return pista;
}
tpista iniciaPista(char direcao, int velocidade, int num_carros, tcarro posicao_carros[num_carros])
{
    tpista pista;
    int i;
    pista.direcao = direcao;
    pista.velocidade = velocidade;
    pista.num_carros = num_carros;
    for (i = 0; i < num_carros; i++)
    {
        pista.posicao_carros[i] = posicao_carros[i];
    }
    return pista;
}

// FUNCOES TJOGO
int ObtemAnimacaoJogo(tjogo jogo)
{
    return jogo.animacao;
}
int ObtemLarguraMapaJogo(tjogo jogo)
{
    return jogo.largura_mapa;
}
int ObtemQtdPistasJogo(tjogo jogo)
{
    return jogo.qtd_pistas;
}
int ObtemInteracoesJogo(tjogo jogo)
{
    return jogo.interacoes;
}
int ObtemPontuacaoJogo(tjogo jogo)
{
    return jogo.pontuacao;
}

void InicializarMatriz(int linhas, int colunas, char matriz[linhas][colunas], tjogo jogo, int x)
{
    int i, j, p, k, m;
    for (i = 0; i < linhas; i++) // preenche matriz base;
    {
        if (!((1 + i) % 3))
        {
            for (j = 0; j < colunas; j++)
            {
                if (!((j + 1) % 3))
                {
                    matriz[i][j] = ' ';
                }
                else
                {
                    matriz[i][j] = '-'; // coloca os traços
                }
            }
        }
        else
        {
            for (j = 0; j < colunas; j++)
            {
                matriz[i][j] = ' '; // preenche com espaço
            }
        }
    } // preenche galinha
    for (i = 0; i < MAX_LINHA_DESENHO; i++)
    {
        for (j = 0; j < MAX_COLUNA_DESENHO; j++)
        {
            int posY = obtemYGalinha(jogo.galinha) + i - 1; // linha da galinha corrigida
            int posX = obtemXGalinha(jogo.galinha) + j - 1; // centraliza no X

            // Só desenha se estiver dentro dos limites
            if (posY >= 0 && posY < linhas && posX >= 0 && posX < jogo.largura_mapa)
            {
                matriz[posY][posX] = jogo.desenho_galinha[i][j];
            }
        }
    } // preenche com carros
    for (p = 0; p < jogo.qtd_pistas; p++)
    {
        if (obtemDirecaoPista(jogo.pistas[p]) != '0')
        {
            int linha_carro = p * 3;
            for (k = 0; k < obtemNumCarrosPista(jogo.pistas[p]); k++)
            {
                if (x == 0)
                {
                    for (i = 0; i < MAX_LINHA_DESENHO; i++)
                    {
                        for (j = 0; j < MAX_COLUNA_DESENHO; j++)
                        {
                            int posY = linha_carro + i; //linha dos carros
                            int posX = (obtemXCarroPista(jogo.pistas[p], k) + (j - 1) + jogo.largura_mapa) % jogo.largura_mapa;//coluna com loop -aparece no outro lado
                            matriz[posY][posX] = jogo.desenho_carro[0][i][j]; 
                        }
                    }
                }
                else
                {
                    // impresão das diferentes fantasias
                    m = jogo.interacoes % 4;
                    for (i = 0; i < MAX_LINHA_DESENHO; i++)
                    {
                        for (j = 0; j < MAX_COLUNA_DESENHO; j++)
                        {
                            int posY = linha_carro + i;
                            int posX = (obtemXCarroPista(jogo.pistas[p], k) + (j - 1) + jogo.largura_mapa) % jogo.largura_mapa;
                            matriz[posY][posX] = jogo.desenho_carro[m][i][j];
                        }
                    }
                }
            }
        }
    }
}
void InicilizarHeatmap(tjogo jogo)
{
    int i, j;
    for (i = 0; i < jogo.linhas; i++)
    {
        for (j = 0; j < jogo.largura_mapa; j++)
        {
            jogo.heatmap[i][j] = 0; // inicia tudo como 0
        }
    }
}

// - previsao movimento galinha.
int ObtemPosicaoInicialJogo(tjogo jogo)
{
    int posicao_inicial = jogo.linhas - 1; //calcula a posicao inicial 
    return posicao_inicial;
}
int MovimentaGalinhaJogoY(tjogo jogo, char movimento)
{
    if (movimento == 'w')
    {
        jogo.galinha = moveGalinha(jogo.galinha, -3);
    }
    else if (movimento == 's')
    {
        if (obtemYGalinha(jogo.galinha) + 3 <= jogo.linhas)
        {
            jogo.galinha = moveGalinha(jogo.galinha, 3);
        }
    }
    return obtemYGalinha(jogo.galinha);
}
int MovimentaGalinhaJogoX(tjogo jogo, char movimento)
{
     if(movimento =='a'){
        jogo.galinha = moveGalinhaX(jogo.galinha,-1);
    }
    else if(movimento =='d'){
        jogo.galinha = moveGalinhaX(jogo.galinha,1);
    }
    return obtemXGalinha(jogo.galinha);
}

// - perguntas jogo
int VidaGalinhaAcabou(tjogo jogo)
{
    if (obtemVidasGalinha(jogo.galinha) != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int GalinhaAtravesou(tjogo jogo)
{
    int pista_galinha = obtemYGalinha(jogo.galinha) / 3;
    if (pista_galinha == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// - atualizacoes do jogo
tjogo AtulizaPontucaoJogo(tjogo jogo, int x)
{
    jogo.pontuacao += x;
    return jogo;
}
tjogo MovimentaCarros(tjogo jogo,int p)
{   
    int i;
    jogo.p=jogo.p*p;

    if(jogo.p ==1){
        for (i = 0; i < ObtemQtdPistasJogo(jogo); i++)
        {
            jogo.pistas[i]=moveCarroPista(jogo.pistas[i],jogo.largura_mapa,1);

        }
    }
    return jogo;
}
tjogo AumentaInteracao(tjogo jogo, char movimento)
{   int x=1;
    jogo.interacoes++;//conta iteracoes
    if (movimento == 's')
    {
        jogo.n_movimentoS++;//conta s
    }
    else if (movimento == 'w')
    {
        jogo.n_movimentosW++;//conta w
    }
    else if(movimento=='p'){
        x=-1;
    }
    jogo = MovimentaCarros(jogo,x);//movimenta os carros pos cada iteracao
    return jogo;
}
tjogo IncrementaHeatmapGalinha(tjogo jogo)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int y = obtemYGalinha(jogo.galinha) + i - 1;
            int x = obtemXGalinha(jogo.galinha) + j - 1;
            if (y >= 0 && y < jogo.linhas && x >= 0 && x < jogo.largura_mapa)
            {
                if (jogo.heatmap[y][x] != -1 && jogo.heatmap[y][x] < 99)
                {
                    jogo.heatmap[y][x]++; // incrementa 1  nas posicoes da galinha
                }
            }
        }
    }
    return jogo;
}
tjogo OrdenaColisao(tjogo jogo)
{
    int i, j, menor;
    tcolisao aux;
    for (i = 0; i < jogo.n_colisoes - 1; i++)
    {
        menor = i;
        for (j = i + 1; j < jogo.n_colisoes; j++)
        {   //condicional para trocar de posicao as colisoes do ranking de acordo com o script do trabalho
            if (obtemPistaColisao(jogo.colisoes[j]) < obtemPistaColisao(jogo.colisoes[menor]) ||
                (obtemPistaColisao(jogo.colisoes[j]) == obtemPistaColisao(jogo.colisoes[menor]) &&
                     obtemCarroColisao(jogo.colisoes[j]) < obtemCarroColisao(jogo.colisoes[menor]) ||
                 obtemPistaColisao(jogo.colisoes[j]) == obtemPistaColisao(jogo.colisoes[menor]) &&
                     obtemCarroColisao(jogo.colisoes[j]) == obtemCarroColisao(jogo.colisoes[menor]) &&
                     obtemInteracaoColisao(jogo.colisoes[j]) > obtemInteracaoColisao(jogo.colisoes[menor])))
            {
                menor = j;
            }
        }
        // só troca no fim
        if (menor != i)
        {
            aux = jogo.colisoes[i];
            jogo.colisoes[i] = jogo.colisoes[menor];
            jogo.colisoes[menor] = aux;
        }
    }
    return jogo;
}
tjogo AtualizaMatriz(tjogo jogo)
{
    InicializarMatriz(jogo.linhas, jogo.largura_mapa, jogo.matriz, jogo, jogo.animacao);
    return jogo;
}
tjogo AtualizaVetorColisoes(tjogo jogo, int x, int pista_galinha, int animacao)
{
    int j, c = 0, col, l;
    for (j = 0; j < obtemNumCarrosPista(jogo.pistas[pista_galinha]); j++)
    {
        int pCarro = obtemXCarroPista(jogo.pistas[pista_galinha], j);
        if (pCarro == x || pCarro + 2 == x || pCarro - 2 == x || pCarro - 1 == x || pCarro + 1 == x)
        {
            // adiciona uma colisao no vetor de colisao
            tcolisao colisao = Lecolisao(pista_galinha + 1, j + 1, jogo.interacoes, x + 1, (pista_galinha * 3) + 1);
            AdicionaColisao(colisao, jogo.colisoes, jogo.n_colisoes);

            // diminui velocidade pista galinha
            if (animacao && (obtemVelocidadePista(jogo.pistas[pista_galinha]) > 1))
            {
                jogo.pistas[pista_galinha] = diminuiVelocidadePista(jogo.pistas[pista_galinha]);
            }

            // marca linha da colisao
            l = pista_galinha * 3;
            for (int col = 0; col < jogo.largura_mapa; col++)
            {
                jogo.heatmap[l][col] = -1;
                jogo.heatmap[l + 1][col] = -1;
            }
            jogo.n_colisoes++;
            return jogo;
        }
    }
}

// verifica colisao
int colisao(tjogo jogo, int x, int pista_galinha)
{
    int j, c = 0;
    for (j = 0; j < obtemNumCarrosPista(jogo.pistas[pista_galinha]); j++)
    {
        int pCarro = obtemXCarroPista(jogo.pistas[pista_galinha], j);
        if (pCarro == x || pCarro + 2 == x || pCarro - 2 == x || pCarro - 1 == x || pCarro + 1 == x)
        {
            c = 1;
            break;
        }
    }
    if (c == 1)
        return 1;
    else
        return 0;
}

// IMPRESOES
void Cabecalho(tjogo jogo)
{
    printf("Pontos: %d | Vidas: %d | Iteracoes: %d\n", jogo.pontuacao, obtemVidasGalinha(jogo.galinha), ObtemInteracoesJogo(jogo));
}
// - Imprime a matriz na tela
void imprimeMatriz(int l, int c, char matriz[l][c])
{
    int i, j;
    printf("|");
    for (i = 0; i < c; i++)
    {
        printf("-");
    }
    printf("|");
    printf("\n"); // TOPO MATRIZ
    for (i = 0; i < l; i++)
    {
        printf("|"); // ESQUEDA MATRIZ
        for (j = 0; j < c; j++)
        {
            printf("%c", matriz[i][j]);
        }
        printf("|"); // DIREITO MATRIZ
        printf("\n");
    }
    printf("|");
    for (i = 0; i < c; i++)
    {
        printf("-");
    }
    printf("|");
    printf("\n"); // FINAL MATRIZ
}
// - imprime em um arquivo file
void imprimeMatrizInicializacao(int l, int c, char matriz[l][c], FILE *pInicialização)
{
    int i, j;
    fprintf(pInicialização, "|");
    for (i = 0; i < c; i++)
    {
        fprintf(pInicialização, "-");
    }
    fprintf(pInicialização, "|");
    fprintf(pInicialização, "\n"); // TOPO MATRIZ

    for (i = 0; i < l; i++)
    {
        fprintf(pInicialização, "|"); // ESQUERDO MATRIZ
        for (j = 0; j < c; j++)
        {
            fprintf(pInicialização, "%c", matriz[i][j]);
        }
        fprintf(pInicialização, "|"); // DIREITO MATRIZ
        fprintf(pInicialização, "\n");
    }

    fprintf(pInicialização, "|");
    for (i = 0; i < c; i++)
    {
        fprintf(pInicialização, "-");
    }
    fprintf(pInicialização, "|");
    fprintf(pInicialização, "\n"); // FINAL MATRIZ
}
// - Imprime estado atual do jogo - cabeçalho e matriz
void ImprimeEstado(tjogo jogo)
{
    Cabecalho(jogo);
    imprimeMatriz(jogo.linhas, jogo.largura_mapa, jogo.matriz);
}
void ImprimeColisao(tcolisao colisao, FILE *pranking)
{
    fprintf(pranking, "%d,%d,%d\n", colisao.id_pista, colisao.id_carro, colisao.interacao);
}

// ARQUIVOS
void ImprimeInicializacao(tjogo jogo, char *diretorio)
{
    FILE *pInicialização;
    char caminhoInicializacao[1000];
    sprintf(caminhoInicializacao, "%s/saida/inicializacao.txt", diretorio);
    pInicialização = fopen(caminhoInicializacao, "w");
    if (!pInicialização)
    {
        printf("erro ao criar inicialização em:%s\n", caminhoInicializacao);
        return;
    }
    imprimeMatrizInicializacao(jogo.linhas, jogo.largura_mapa, jogo.matriz, pInicialização);
    fprintf(pInicialização, "A posicao central da galinha iniciara em (%d %d).", obtemXGalinha(jogo.galinha) + 1, obtemYGalinha(jogo.galinha));
    fclose(pInicialização);
}
void ImprimeResumo(tjogo jogo, char *diretorio)
{
    FILE *pResumo;
    int i;
    char caminhoResumo[1000];
    sprintf(caminhoResumo, "%s/saida/resumo.txt", diretorio);
    pResumo = fopen(caminhoResumo, "w");
    if (!pResumo)
    {
        printf("erro ao criar arquivo saida em:%s\n", caminhoResumo);
        return;
    }
    for (i = 0; i < jogo.n_colisoes; i++)
    {
        fprintf(pResumo, "[%d] Na pista %d o carro %d atropelou a galinha na posicao (%d,%d).\n", jogo.colisoes[i].interacao, jogo.colisoes[i].id_pista, jogo.colisoes[i].id_carro, jogo.colisoes[i].x, jogo.colisoes[i].y);
    }
    fprintf(pResumo, "[%d] Fim de jogo", ObtemInteracoesJogo(jogo));
    fclose(pResumo);
}
void ImprimeRanking(tjogo jogo, char *diretorio)
{
    jogo = OrdenaColisao(jogo);
    FILE *pRanking;
    char caminhoRanking[1000];
    sprintf(caminhoRanking, "%s/saida/ranking.txt", diretorio);
    pRanking = fopen(caminhoRanking, "w");
    if (!pRanking)
    {
        printf("erro ao criar arquivo saida em:%s\n", caminhoRanking);
        return;
    }
    int i;

    fprintf(pRanking, "id_pista,id_carro,iteracao\n");
    for (i = 0; i < jogo.n_colisoes; i++)
    {
        ImprimeColisao(jogo.colisoes[i], pRanking);
    }
    fclose(pRanking);
}
void ImprimeEstatistica(tjogo jogo, char *diretorio)
{
    FILE *pEstatistica;
    char caminhoEstatistica[1000];
    sprintf(caminhoEstatistica, "%s/saida/estatistica.txt", diretorio);
    pEstatistica = fopen(caminhoEstatistica, "w");
    if (!pEstatistica)
    {
        printf("erro ao criar arquivo saida em:%s\n", caminhoEstatistica);
        return;
    }
    int linhas = (jogo.qtd_pistas * 3);
    int maxAltura = linhas - obtemMaximaAlturaGalinha(jogo.galinha);
    int maxAtro = linhas - obtemMaxAtropelamento(jogo.galinha);
    int minAtro = linhas - obtemMinAtropelamento(jogo.galinha);
    fprintf(pEstatistica, "Numero total de movimentos: %d\n", jogo.n_movimentosW + jogo.n_movimentoS);
    fprintf(pEstatistica, "Altura maxima que a galinha chegou: %d\n", maxAltura);
    if (jogo.n_colisoes == 0)
    {
        fprintf(pEstatistica, "Altura maxima que a galinha foi atropelada: 0\n");
        fprintf(pEstatistica, "Altura minima que a galinha foi atropelada: 0\n");
    }
    else
    {
        fprintf(pEstatistica, "Altura maxima que a galinha foi atropelada: %d\n", maxAtro);
        fprintf(pEstatistica, "Altura minima que a galinha foi atropelada: %d\n", minAtro);
    }
    fprintf(pEstatistica, "Numero de movimentos na direcao oposta: %d\n", jogo.n_movimentoS);
    fclose(pEstatistica);
}
void ImprimeHeatmap(tjogo jogo, char *diretorio)
{
    FILE *pMapaCalor;
    char caminhoMapaCalor[1000];
    sprintf(caminhoMapaCalor, "%s/saida/heatmap.txt", diretorio);
    pMapaCalor = fopen(caminhoMapaCalor, "w");
    if (!pMapaCalor)
    {
        printf("erro ao criar arquivo saida em:%s\n", caminhoMapaCalor);
        return;
    }
    for (int i = 0; i < jogo.linhas; i++)
    {
        for (int j = 0; j < jogo.largura_mapa; j++)
        {
            if (jogo.heatmap[i][j] == -1)
                fprintf(pMapaCalor, " * "); // imprime pista da morte
            else
                fprintf(pMapaCalor, "%2d ", jogo.heatmap[i][j]); // imprime outras posicoes
        }
        fprintf(pMapaCalor, "\n");
    }
    fclose(pMapaCalor);
}

// FUNCOES BASICAS
tjogo Lejogo(int argc, char *diretorio)
{ // verificacoes
    if (argc <= 1)
    {
        printf("ERRO: Informe o diretorio com os arquivos de configuracao.\n");
        exit(1);
    }
    tjogo jogo;
    FILE *pConfig_inicial;
    FILE *pPersonagens;
    char caminhoConfig[1000];
    char caminhoPerson[1000];
    sprintf(caminhoConfig, "%s/config_inicial.txt", diretorio);
    sprintf(caminhoPerson, "%s/personagens.txt", diretorio);
    pConfig_inicial = fopen(caminhoConfig, "r");
    if (!pConfig_inicial)
    {
        printf("Não foi possivel achar o arquivo de personagens no caminho:%s\n", caminhoConfig);
        exit(1);
    }
    pPersonagens = fopen(caminhoPerson, "r");
    if (!pPersonagens)
    {
        printf("Não foi possivel achar o arquivo de personagens no caminho:%s", caminhoPerson);
        exit(1);
    }
    int i, j, p;
    char inicio;
    // inicializa variaveis jogo
    fscanf(pConfig_inicial, "%d", &jogo.animacao);
    fscanf(pConfig_inicial, "%d %d", &jogo.largura_mapa, &jogo.qtd_pistas);
    jogo.linhas = (jogo.qtd_pistas * 3) - 1;
    jogo.interacoes = 0;
    jogo.pontuacao = 0;
    jogo.n_colisoes = 0;
    jogo.n_movimentoS = 0;
    jogo.n_movimentosW = 0;
    jogo.p=1;
    jogo.f=0;

    fgetc(pConfig_inicial);
    // pega pistas
    for (i = 0; i < jogo.qtd_pistas; i++)
    {
        inicio = fgetc(pConfig_inicial);
        int velocidade, num_carros;
        if (inicio == 'E' || inicio == 'D')
        {
            fscanf(pConfig_inicial, "%d", &velocidade);
            fscanf(pConfig_inicial, "%d", &num_carros);
            tcarro posicao_carros[num_carros];
            for (j = 0; j < num_carros; j++)
            {
                int x;
                fscanf(pConfig_inicial, "%d", &x);
                posicao_carros[j] = leCarro(x - 1); // guarda posição do carro correta
            }
            jogo.pistas[i] = iniciaPista(inicio, velocidade, num_carros, posicao_carros);
            fgetc(pConfig_inicial); // pega último barra n pista
        }
        else if (inicio == 'G')
        {
            int xg, vidas, p, x;
            fscanf(pConfig_inicial, "%d", &x);
            fscanf(pConfig_inicial, "%d", &vidas);
            xg = x - 1; // guarda posição correta galinha;
            p = jogo.linhas - 1;
            tcarro posicao_carros[0];
            jogo.galinha = iniciaGalinha(vidas, xg, p, p, p, 0);
            jogo.pistas[i] = iniciaPista('0', 0, 0, posicao_carros);
        }
        else
        {
            tcarro posicao_carros[0];
            jogo.pistas[i] = iniciaPista('0', 0, 0, posicao_carros);
        }
    }
    // pega desenhos - galinha e animigos
    fscanf(pPersonagens, "%*[\r\n]");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fscanf(pPersonagens, "%c", &jogo.desenho_galinha[i][j]); // galinha
        }
        fscanf(pPersonagens, "%*[\r\n]");
    }
    for (p = 0; p < 4; p++)
    {
        fscanf(pPersonagens, "%*[\r\n]");
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 3; j++)
            {
                fscanf(pPersonagens, "%c", &jogo.desenho_carro[p][i][j]); // inimigos
            }
            fscanf(pPersonagens, "%*[\r\n]");
        }
    }
    InicializarMatriz(jogo.linhas, jogo.largura_mapa, jogo.matriz, jogo, 0);
    ImprimeInicializacao(jogo, diretorio);
    fclose(pConfig_inicial);
    fclose(pPersonagens);
    return jogo;
}
tjogo RealizaJogo(tjogo jogo)
{
    char movimento;
    ImprimeEstado(jogo);
    do
    {
        do 
        {
            scanf("%c", &movimento);
            if (movimento == '\n')
                continue;
        } while (movimento != 'w' && movimento != 's' && movimento != ' ' && movimento != 'p'
            && movimento != 'f' && movimento != 'a' && movimento != 'd');// so recebe os movimentos w s ' '
        // aumenta interacao - movimenta carros - conta movimentos w s
        jogo = AumentaInteracao(jogo, movimento);
        jogo = IncrementaHeatmapGalinha(jogo);
        int y = MovimentaGalinhaJogoY(jogo, movimento); // preve o movimento
        int x = MovimentaGalinhaJogoX(jogo, movimento);
        int pista_galinha = y / 3;
        if (colisao(jogo, x, pista_galinha)) // verifica colisao
        {
            jogo = AtualizaVetorColisoes(jogo, x, pista_galinha, jogo.animacao); // guarda as informacoes da colisao
            jogo.galinha = atualizaMaxMinColisaoGalinha(jogo.galinha, y);
            jogo.galinha = diminuiVidaGalinha(jogo.galinha);
            y = ObtemPosicaoInicialJogo(jogo);
            jogo = AtulizaPontucaoJogo(jogo, -ObtemPontuacaoJogo(jogo));
        }
        else
        {
            if (movimento == 'w') // verifica se é para frente bem sucedido.
            {
                jogo = AtulizaPontucaoJogo(jogo, 1);
                jogo.galinha = atualizaMaximaGalinha(jogo.galinha, y);
            }
        }
        jogo.galinha = atualizaYGalinha(jogo.galinha, y);
        jogo.galinha= atualizaXGalinha(jogo.galinha,x);
        jogo = AtualizaMatriz(jogo);
        if (GalinhaAtravesou(jogo))
        {
            jogo = AtulizaPontucaoJogo(jogo, 10);
        }
        ImprimeEstado(jogo);

    } while (!VidaGalinhaAcabou(jogo) && !GalinhaAtravesou(jogo));
    jogo = IncrementaHeatmapGalinha(jogo); // atualiza o headmap para ultima posicao da galinha
    return jogo;
}
void ResultadoJogo(tjogo jogo, char *diretorio)
{
    if (GalinhaAtravesou(jogo))
    {
        printf("Parabens! Voce atravessou todas as pistas e venceu!\n");
    }
    else if (VidaGalinhaAcabou(jogo))
    {
        printf("Voce perdeu todas as vidas! Fim de jogo.\n");
    }
    // gera os arquivos
    ImprimeResumo(jogo, diretorio);
    ImprimeRanking(jogo, diretorio);
    ImprimeEstatistica(jogo, diretorio);
    ImprimeHeatmap(jogo, diretorio);
}

int main(int argc, char *argv[])
{
    // INICIA JOGO  - ler aquivos e imprime inicialização
    tjogo jogo;
    jogo = Lejogo(argc, argv[1]);
    // REALIZA JOGO - faz todo o jogo e valta com o ultimo estado do jogo
    jogo = RealizaJogo(jogo);
    // IMPRIME RESULTADO JOGO - vitoria ou derrota e gera arquivos;
    ResultadoJogo(jogo, argv[1]);
    return 0;
}