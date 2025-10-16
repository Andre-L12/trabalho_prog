#include <stdio.h>
//strucs
typedef struct
{
    int vidas;
    int x;
    int y;
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
    tcarro posicao_carros[10];

} tpista;
typedef struct 
{
    int id_pista;
    int id_carro;
    int interacao;
}tcolisao;
typedef struct
{
    int animacao;
    int pontuacao;
    tgalinha galinha;
    int largura_mapa;
    int qtd_pistas;
    tpista pistas[12];
    char matriz[35][100];
    char desenho_galinha[2][3];
    char desenho_carro[2][3];
    int interacoes;
    int n_colisoes;
    tcolisao colisoes[1000];

} tjogo;

//le colisao
tcolisao Lecolisao(int p,int c,int i){
    tcolisao colisao;
    colisao.id_pista=p;
    colisao.id_carro=c;
    colisao.interacao=i;
    return colisao;
}
void AdicionaColisao(tcolisao colisao, tcolisao *colisoes,int n){
    colisoes[n]=colisao;
}
tjogo OrdenaColisao(tjogo jogo){
     int i, j, menor;
    tcolisao aux;

    for (i = 0; i < jogo.n_colisoes - 1; i++) {
        menor = i;
        for (j = i + 1; j < jogo.n_colisoes; j++) {
            if (jogo.colisoes[j].id_pista < jogo.colisoes[menor].id_pista ||
                (jogo.colisoes[j].id_pista == jogo.colisoes[menor].id_pista &&
                 jogo.colisoes[j].id_carro < jogo.colisoes[menor].id_carro) ||
                (jogo.colisoes[j].id_pista == jogo.colisoes[menor].id_pista &&
                 jogo.colisoes[j].id_carro == jogo.colisoes[menor].id_carro &&
                 jogo.colisoes[j].interacao > jogo.colisoes[menor].interacao)) 
            {
                menor = j;
            }
        }

        // só troca no fim, quando achou de fato o "menor"
        if (menor != i) {
            aux = jogo.colisoes[i];
            jogo.colisoes[i] = jogo.colisoes[menor];
            jogo.colisoes[menor] = aux;
        }
    }

    return jogo;
    
}


//funções galinha
int obtemXGalinha(tgalinha galinha){
    return galinha.x;
}
int obtemYGalinha(tgalinha galinha){
    return galinha.y;
}
int obtemVidasGalinha(tgalinha galinha){
    return galinha.vidas;
}
tgalinha atualizaYgalinha(tgalinha galinha,int y){
    galinha.y=y;
    return galinha;
}
tgalinha diminuiVidaGalinha(tgalinha galinha){
    galinha.vidas--;
    return galinha;
}
tgalinha moveGalinha(tgalinha galinha,int x){
    galinha.y=galinha.y+x;
    return galinha;
}

//função carro
int obtemXCarro(tcarro carro){
    return carro.x;
}

//função pista 
char obtemDirecaoPista(tpista pista){
    return pista.direcao;
}
int obtemVelocidadePista(tpista pista){
    return pista.velocidade;
}
int obtemNumCarrosPista(tpista pista){
    return pista.num_carros;
}
int obtemXCarroPista(tpista pista,int i){
    return obtemXCarro(pista.posicao_carros[i]);
}

//função jogo galinha
int ObtemXGalinhaJogo(tjogo jogo)
{
    return obtemXGalinha(jogo.galinha);
}
int ObtemYGalinhaJogo(tjogo jogo)
{
     return obtemYGalinha(jogo.galinha);
}
int ObtemVidasGalinhaJogo(tjogo jogo){
    return obtemVidasGalinha(jogo.galinha);
}

//função jogo carro
int ObtemXCarroPistaJogo(tjogo jogo,int i,int j){
    return obtemXCarroPista(jogo.pistas[i],j);
}

//função geral jogo
int ObtemAnimacaoJogo(tjogo jogo){
    return jogo.animacao;
}
int ObtemLarguraMapaJogo(tjogo jogo){
    return jogo.largura_mapa;
}
int ObtemQtdPistasJogo(tjogo jogo){
    return jogo.qtd_pistas;
}
int ObtemInteracoesJogo(tjogo jogo){
    return jogo.interacoes;
}
int ObtemPontuacao(tjogo jogo){
    return jogo.pontuacao;
}
//perguntas jogo
int vidaGalinhaAcabou(tjogo jogo){
    if (obtemVidasGalinha(jogo.galinha) != 0){
        return 0;
    }else{
        return 1;
    }
}
int galinhaAtravesou(tjogo jogo)
{
    int pista_galinha = obtemYGalinha(jogo.galinha)/ 3;
    if (pista_galinha == 0){
        return 1;
    }
    else{
        return 0;
    }
}
//atualizacoes do jogo
tjogo AtulizaPontucao(tjogo jogo,int x){
    jogo.pontuacao+=x;
    return jogo;
}
tjogo AtualizaGalinha(tjogo jogo, int y)
{
    jogo.galinha=atualizaYgalinha(jogo.galinha,y);
    return jogo;
}
tjogo DiminuiVida(tjogo jogo)
{
    jogo.galinha=diminuiVidaGalinha(jogo.galinha);
    jogo.n_colisoes++;
    return jogo;
}
tjogo movimentaCarros(tjogo jogo){
    int i, j, p;
    for (i = 0; i < ObtemQtdPistasJogo(jogo); i++){
        if (obtemDirecaoPista(jogo.pistas[i]) == 'E'){
            for (j = 0; j < obtemNumCarrosPista(jogo.pistas[i]); j++){
                for (p = 0; p < obtemVelocidadePista(jogo.pistas[i]); p++){
                    jogo.pistas[i].posicao_carros[j].x--;
                    if (jogo.pistas[i].posicao_carros[j].x < 0){
                        jogo.pistas[i].posicao_carros[j].x = ObtemLarguraMapaJogo(jogo)-1;
                    }
                }
            }
        }
        else if (obtemDirecaoPista(jogo.pistas[i])== 'D'){
            for (j = 0; j < obtemNumCarrosPista(jogo.pistas[i]); j++){
                for (p = 0; p < obtemVelocidadePista(jogo.pistas[i]); p++){
                    jogo.pistas[i].posicao_carros[j].x++;
                    if (jogo.pistas[i].posicao_carros[j].x > ObtemLarguraMapaJogo(jogo)-1){
                        jogo.pistas[i].posicao_carros[j].x = 0;
                    }
                }
            }
        }
    }
    return jogo;
}
tjogo aumentaInteracao(tjogo jogo)
{
    jogo.interacoes++;
    return jogo;
}
//atualiza o estado atual da matriz
void inicializarMatriz(int linhas, int colunas, char matriz[linhas][colunas], tjogo jogo,int x);
tjogo atualizaMatriz(tjogo jogo){
    int linhas = (jogo.qtd_pistas * 3) - 1;
    inicializarMatriz(linhas, jogo.largura_mapa, jogo.matriz, jogo,0);
    return jogo;   
}
//volta a posição inicial da galinha
int voltaInicio(tjogo jogo)
{
    int posicao_inicial = (jogo.qtd_pistas * 3) - 2;
    return posicao_inicial;
}
//verifica colisao
int colisao(tjogo jogo, int x, int pista_galinha,FILE *pResumo,FILE *pRanking)
{
    int i, j, c = 0;
    for (i = 0; i < jogo.qtd_pistas; i++){
        if (i == pista_galinha){
            for (j = 0; j < obtemNumCarrosPista(jogo.pistas[i]); j++){ 
                int pCarro=obtemXCarroPista(jogo.pistas[i],j);
                if (pCarro == x||pCarro+2 == x||pCarro-2 == x ||pCarro-1 == x||pCarro+1 == x){
                    c = 1;
                    fprintf(pResumo,"[%d] Na pista %d o carro %d atropelou a galinha na posicao (%d,%d).\n",jogo.interacoes,pista_galinha+1,j+1,x+1,(pista_galinha*3)+1);
                    //tcolisao colisao=Lecolisao(pista_galinha+1,j+1,jogo.interacoes);
                    //AdicionaColisao(colisao,jogo.colisoes,jogo.n_colisoes);
                    break;  
                }
            }
        }
    }
    if (c == 1){
        return 1;
    }
    else{
        return 0;
    }
}
tjogo AtualizaVetorColisoes(tjogo jogo, int x, int pista_galinha,FILE *pResumo,FILE *pRanking){
    int i, j, c = 0;
    for (i = 0; i < jogo.qtd_pistas; i++){
        if (i == pista_galinha){
            for (j = 0; j < obtemNumCarrosPista(jogo.pistas[i]); j++){ 
                int pCarro=obtemXCarroPista(jogo.pistas[i],j);
                if (pCarro == x||pCarro+2 == x||pCarro-2 == x ||pCarro-1 == x||pCarro+1 == x){
                    c = 1;
                    tcolisao colisao=Lecolisao(pista_galinha+1,j+1,jogo.interacoes);
                    AdicionaColisao(colisao,jogo.colisoes,jogo.n_colisoes);
                    break;  
                }
            }
        }
    }return jogo;
}
//volta um interio da posição da galinha
int movimentaGalinha(tjogo jogo, char movimento)
{
    if (movimento == 'w'){
        jogo.galinha=moveGalinha(jogo.galinha,-3);
    }
    else if (movimento == 's'){
        int linhas = (jogo.qtd_pistas * 3) - 1;
        if (jogo.galinha.y + 3 <= linhas)
        {
            jogo.galinha=moveGalinha(jogo.galinha,3);
        }
    }
    return obtemYGalinha(jogo.galinha);
}
//imprime na tela
void imprimeMatriz(int l, int c, char matriz[l][c])
{
    int i, j;
    printf("|");
    for (i = 0; i < c; i++)
    {
        printf("-");
    }
    printf("|");
    printf("\n");

    for (i = 0; i < l; i++)
    {
        printf("|");
        for (j = 0; j < c; j++){
            printf("%c", matriz[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("|");
    for (i = 0; i < c; i++){
        printf("-");
    }
    printf("|");
    printf("\n");
}
//imprime em um arquivo file
void imprimeMatrizInicializacao(int l, int c, char matriz[l][c],FILE *pInicialização){
    
    int i, j;
    fprintf(pInicialização,"|");
    for (i = 0; i < c; i++)
    {
        fprintf(pInicialização,"-");
    }
    fprintf(pInicialização,"|");
    fprintf(pInicialização,"\n");

    for (i = 0; i < l; i++)
    {
        fprintf(pInicialização,"|");
        for (j = 0; j < c; j++){
            fprintf(pInicialização,"%c", matriz[i][j]);
        }
        fprintf(pInicialização,"|");
        fprintf(pInicialização,"\n");
    }
    fprintf(pInicialização,"|");
    for (i = 0; i < c; i++){
        fprintf(pInicialização,"-");
    }
    fprintf(pInicialização,"|");
    fprintf(pInicialização,"\n");
}

//FUNÇÃO QUE PODE TER ERRO
void inicializarMatriz(int linhas, int colunas, char matriz[linhas][colunas], tjogo jogo,int x){
    int i, j,p,k;
    for (i = 0; i < linhas; i++){
        if (!((1 + i) % 3)){
            for (j = 0; j < colunas; j++){
                if (!((j + 1) % 3)){
                    matriz[i][j] = ' ';
                }
                else{
                    matriz[i][j] = '-';
                }
            }
        }
        else{
            for (j = 0; j < colunas; j++){
                matriz[i][j] = ' ';
            }
        }
    }
    for (i = 0; i < 2; i++) {        // linhas da galinha
        for (j = 0; j < 3; j++) {    // colunas da galinha
            int posY = jogo.galinha.y +i -1;         // linha da galinha
            int posX = jogo.galinha.x +j - 1;   // centraliza no X

            // Só desenha se estiver dentro dos limites
            if (posY >= 0 && posY < linhas && posX >= 0 && posX < jogo.largura_mapa) {
                matriz[posY][posX] = jogo.desenho_galinha[i][j];
            }
        }
    }
    for ( p = 0; p < jogo.qtd_pistas; p++){
        if(jogo.pistas[p].direcao!='0'){
            int linha_carro=p*3;
            for ( k = 0; k < jogo.pistas[p].num_carros; k++){
                if(x==0){
                    for (i = 0; i < 2; i++) {      
                        for (j = 0; j < 3; j++) {  
                            int posY = linha_carro +i;        
                            int posX = (jogo.pistas[p].posicao_carros[k].x + (j - 1) + jogo.largura_mapa) % jogo.largura_mapa;
                            matriz[posY][posX] = jogo.desenho_carro[i][j];
                        }
                    }
                }else{
                    for ( i = 0; i < 2; i++)
                    {
                        for ( j = 0; j < 3; j++)
                        {
                            int posY = linha_carro +i ;        
                            int posX = jogo.pistas[p].posicao_carros[k].x +j - 1;   
                            if (posY >= 0 && posY < linhas && posX >= 0 && posX < jogo.largura_mapa) {
                                matriz[posY][posX] = jogo.desenho_carro[i][j];
                            }
                        }
                        
                    }
                    
                    
                }
           
            }
            
            
        }
        
    }
    


}
// FUNCAO COM ERRO 
tjogo Lejogo(FILE *pConfig_inicial, FILE *pPersonagens)
{
    tjogo jogo;
    int i, j;
    char inicio;
    fscanf(pConfig_inicial, "%d", &jogo.animacao);
    fscanf(pConfig_inicial, "%d %d", &jogo.largura_mapa, &jogo.qtd_pistas);
    int linhas = (jogo.qtd_pistas * 3) - 1;
    jogo.interacoes = 0;
    jogo.pontuacao=0;
    jogo.n_colisoes=0;    
    /*jogo.pistas[0].direcao = '0';
    jogo.pistas[0].num_carros = 0;
    jogo.pistas[0].velocidade = 0;*/
    fgetc(pConfig_inicial);
    //fscanf(pConfig_inicial, "%*c");
    for (i = 0; i < jogo.qtd_pistas; i++)
    {
        inicio=fgetc(pConfig_inicial);
        /*do
        {
            if (fscanf(pConfig_inicial, "%c", &inicio) != 1)
            {
                // Fim de arquivo inesperado
                inicio = '\0';
                break;
            }
        } while (inicio == '\n' || inicio == '\r' || inicio == ' ' || inicio == '\t');
         */
        if (inicio == 'E' || inicio == 'D')
        {
            jogo.pistas[i].direcao = inicio;
            fscanf(pConfig_inicial, "%d", &jogo.pistas[i].velocidade);
            fscanf(pConfig_inicial, "%d", &jogo.pistas[i].num_carros);
            for (j = 0; j < jogo.pistas[i].num_carros; j++)
            {   int x;
                fscanf(pConfig_inicial, "%d", &x);
                jogo.pistas[i].posicao_carros[j].x=x-1;
 
            }
            fgetc(pConfig_inicial);
        }
        else if (inicio == 'G')
        { int xg;
            fscanf(pConfig_inicial, "%d", &xg);
            fscanf(pConfig_inicial, "%d", &jogo.galinha.vidas);
            jogo.galinha.x=xg-1;
            jogo.galinha.y = linhas - 1;
            jogo.pistas[i].direcao = '0';
            jogo.pistas[i].num_carros = 0;
            jogo.pistas[i].velocidade = 0;

        }
        else
        {
            jogo.pistas[i].direcao = '0';
            jogo.pistas[i].num_carros = 0;
            jogo.pistas[i].velocidade = 0;
            
        }
    }
    fscanf(pPersonagens, "%*[\r\n]");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fscanf(pPersonagens, "%c", &jogo.desenho_galinha[i][j]);
        }
        fscanf(pPersonagens, "%*[\r\n]");
    }
    fscanf(pPersonagens, "%*[\r\n]");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fscanf(pPersonagens, "%c", &jogo.desenho_carro[i][j]);
        }
        fscanf(pPersonagens, "%*[\r\n]");
    }
    inicializarMatriz(linhas, jogo.largura_mapa, jogo.matriz, jogo,0);
    return jogo;
}
//impresoes
void Cabelho(tjogo jogo,FILE *pSaida){
    printf("Pontos: %d | Vidas: %d | Iteracoes: %d\n",jogo.pontuacao,obtemVidasGalinha(jogo.galinha),ObtemInteracoesJogo(jogo));
    fprintf(pSaida,"Pontos: %d | Vidas: %d | Iteracoes: %d\n",jogo.pontuacao,obtemVidasGalinha(jogo.galinha),ObtemInteracoesJogo(jogo));
}
void Inicializacao(tjogo jogo, char *diretorio){
    FILE *pInicialização;
    char caminhoInicializacao[1000];
    sprintf(caminhoInicializacao, "%s/saida/inicializacao.txt", diretorio);
    pInicialização=fopen(caminhoInicializacao,"w");
     if (!pInicialização)
    {
        printf("erro ao criar inicialização em:%s\n", caminhoInicializacao);
        return;
    }
    int linhas = (jogo.qtd_pistas * 3) - 1;
    imprimeMatrizInicializacao(linhas, jogo.largura_mapa, jogo.matriz,pInicialização);
    fprintf(pInicialização,"A posicao central da galinha iniciara em (%d %d).",obtemXGalinha(jogo.galinha)+1,obtemYGalinha(jogo.galinha));
    fclose(pInicialização);
    
}
void Debugar(tjogo jogo)
{
    int i = 0, j = 0, c = 0;

    printf("Animação: %d\n", jogo.animacao);
    printf("Largura mapa: %d\n", jogo.largura_mapa);
    printf("Quantidade pistas: %d\n", jogo.qtd_pistas);

    for (i = 0; i < jogo.qtd_pistas; i++)
    {
        printf("Pista %d - Direção: %c; Velocidade: %d; Num carros: %d; ", i, jogo.pistas[i].direcao, jogo.pistas[i].velocidade, jogo.pistas[i].num_carros);
        for (c = 0; c < jogo.pistas[i].num_carros; c++)
        {
            printf("Carro %d: %d; ", c, jogo.pistas[i].posicao_carros[c].x);
        }
        printf("\n");
    }/*
    printf("\n");
    printf("Interacoes: %d\n", jogo.interacoes);

    printf("Galinha - x: %d;y: %d; Vidas: %d; pista:%d\n\n", jogo.galinha.x, jogo.galinha.y, jogo.galinha.vidas, jogo.galinha.y / 3);
    printf("Galinha:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c", jogo.desenho_galinha[i][j]);
        }
        printf("\n");
    }

    printf("Carro:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c", jogo.desenho_carro[i][j]);
        }
        printf("\n");
    }*/
    //int linhas = (jogo.qtd_pistas * 3) - 1;

    //imprimeMatriz(linhas, jogo.largura_mapa, jogo.matriz);
} 
void imprimeColisao(tcolisao colisao,FILE *pranking){
    fprintf(pranking,"%d,%d,%d\n",colisao.id_pista,colisao.id_carro,colisao.interacao);
}
void ImprimeRanking(tjogo jogo, FILE *pranking){
    int i;
    fprintf(pranking,"id_pista,id_carro,iteracao\n");
    for ( i = 0; i < jogo.n_colisoes; i++){
        imprimeColisao(jogo.colisoes[i],pranking);
    }
}
//imprime o estado atual tanto no arquivo saida quanto na tela
void imprimeEstado(tjogo jogo,FILE *pSaida){
    int linhas = (jogo.qtd_pistas * 3) - 1;
    imprimeMatriz(linhas, jogo.largura_mapa, jogo.matriz);
    imprimeMatrizInicializacao(linhas, jogo.largura_mapa, jogo.matriz,pSaida);
}



int main(int argc, char *argv[])
{
    tjogo jogo;
    FILE *pConfig_inicial;
    FILE *pPersonagens;
    FILE *pSaida;
    FILE *pResumo;
    FILE *pRanking;
    FILE *pEstatistica;
    FILE *pMapaCalor;
    char caminhoConfig[1000];
    char caminhoPerson[1000];
    char caminhoSaida[1000];
    char caminhoResumo[1000];
    char caminhoRanking[1000];
    char caminhoEstatistica[1000]; 
    char caminhoMapaCalor[1000]; 

    
    if (argc <= 1)
    {
        printf("ERRO: Informe o diretorio com os arquivos de configuracao.\n");
        return 1;
    } // if argv >1000 informe um erro;
    sprintf(caminhoConfig, "%s/config_inicial.txt", argv[1]);
    sprintf(caminhoPerson, "%s/personagens.txt", argv[1]);
    sprintf(caminhoSaida, "%s/saida/saida.txt", argv[1]);
    sprintf(caminhoResumo, "%s/saida/resumo.txt", argv[1]);
    sprintf(caminhoRanking, "%s/saida/ranking.txt", argv[1]);
    sprintf(caminhoEstatistica, "%s/saida/estatistica.txt", argv[1]);
    sprintf(caminhoMapaCalor, "%s/saida/heatmap.txt", argv[1]);
    pConfig_inicial = fopen(caminhoConfig, "r");
    if (!pConfig_inicial)
    {
        printf("Não foi possivel achar o arquivo de personagens no caminho:%s\n", caminhoConfig);
        return 1;
    }
    pPersonagens = fopen(caminhoPerson, "r");
    if (!pPersonagens)
    {
        printf("Não foi possivel achar o arquivo de personagens no caminho:%s", caminhoPerson);
        return 1;
    }
    pSaida=fopen(caminhoSaida,"w");
     if (!pSaida){
        printf("erro ao criar arquivo saida em:%s\n", caminhoSaida);
        return 1;
    }
    pResumo=fopen(caminhoResumo,"w");
     if (!pResumo){
        printf("erro ao criar arquivo saida em:%s\n", caminhoResumo);
        return 1;
    }
    pRanking=fopen(caminhoRanking,"w");
     if (!pRanking){
        printf("erro ao criar arquivo saida em:%s\n", caminhoRanking);
        return 1;
    }
    pEstatistica=fopen(caminhoEstatistica,"w");
     if (!pEstatistica){
        printf("erro ao criar arquivo saida em:%s\n", caminhoEstatistica);
        return 1;
    }
    pMapaCalor=fopen(caminhoMapaCalor,"w");
     if (!pMapaCalor){
        printf("erro ao criar arquivo saida em:%s\n", caminhoMapaCalor);
        return 1;
    }

    jogo = Lejogo(pConfig_inicial, pPersonagens);
    //Debugar(jogo);
    Cabelho(jogo,pSaida);
    imprimeEstado(jogo,pSaida);
    Inicializacao(jogo,argv[1]);
    char movimento;
    do{
        do{
            scanf("%c", &movimento);
            if (movimento == '\n')
            continue; 
        } while (movimento != 'w' && movimento != 's' && movimento != ' ');
        jogo = aumentaInteracao(jogo);
        jogo = movimentaCarros(jogo);
        int y = movimentaGalinha(jogo, movimento);
        int x = ObtemXGalinhaJogo(jogo);
        int pista_galinha = y / 3;
        if (colisao(jogo, x, pista_galinha,pResumo,pRanking))
        {
            jogo=AtualizaVetorColisoes(jogo, x, pista_galinha,pResumo,pRanking);
            jogo = DiminuiVida(jogo);
            y = voltaInicio(jogo);
            jogo=AtulizaPontucao(jogo,-ObtemPontuacao(jogo));
        }else{
            if(movimento=='w'){
                jogo=AtulizaPontucao(jogo,1);
            }
        }
        jogo = AtualizaGalinha(jogo, y);
        jogo=atualizaMatriz(jogo);
        if(galinhaAtravesou(jogo)){
            jogo=AtulizaPontucao(jogo,10);
        }
        Cabelho(jogo,pSaida);
        imprimeEstado(jogo,pSaida);

    } while (!vidaGalinhaAcabou(jogo) && !galinhaAtravesou(jogo));
    fprintf(pResumo,"[%d] Fim de jogo",ObtemInteracoesJogo(jogo));
    jogo=OrdenaColisao(jogo);
    ImprimeRanking(jogo,pRanking);
    if (galinhaAtravesou(jogo))
    {
        printf("Parabens! Voce atravessou todas as pistas e venceu!\n");
        fprintf(pSaida,"Parabens! Voce atravessou todas as pistas e venceu!\n");
    }
    else if (vidaGalinhaAcabou(jogo))
    {
        printf("Voce perdeu todas as vidas! Fim de jogo.\n");
        fprintf(pSaida,"Voce perdeu todas as vidas! Fim de jogo.\n");
    }

    fclose(pConfig_inicial);
    fclose(pPersonagens);
    fclose(pSaida);
    fclose(pResumo);
    fclose(pRanking);
    fclose(pEstatistica);
    fclose(pMapaCalor);
    return 0;
}   