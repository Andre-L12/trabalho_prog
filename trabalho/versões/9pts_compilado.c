#include <stdio.h>
//strucs
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
    tcarro posicao_carros[10];

} tpista;
typedef struct 
{
    int id_pista;
    int id_carro;
    int interacao;
    int x;
    int y;
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
    char desenho_carro[4][2][3];
    int interacoes;
    int n_colisoes;
    int n_movimentoS;
    int n_movimentosW;
    tcolisao colisoes[20];
    int heatmap[35][100];

} tjogo;

//funções colisao
tcolisao Lecolisao(int p,int c,int i,int x,int y){
    tcolisao colisao;
    colisao.id_pista=p;
    colisao.id_carro=c;
    colisao.interacao=i;
    colisao.x=x;
    colisao.y=y;
    return colisao;
}
void AdicionaColisao(tcolisao colisao, tcolisao *colisoes,int n){
    colisoes[n]=colisao;
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
tgalinha atualizaMaxima(tgalinha galinha,int y){
    if(y<galinha.altura_maxima){
        galinha.altura_maxima=y;
    }
    return galinha;
}
tgalinha atualizaMaxMinColisao(tgalinha galinha,int y){
    if(y > galinha.min_atropelamento){
        galinha.min_atropelamento=y;
    }if(y<galinha.maximo_atropelamento){
        galinha.maximo_atropelamento=y;
    }
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

//função jogo colisao
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
tjogo AltualziaMaximaJogo(tjogo jogo, int y){
    jogo.galinha=atualizaMaxima(jogo.galinha,y);
    return jogo;
}
tjogo AtualizaMaxMinColisaoJogo(tjogo jogo,int y){
    jogo.galinha=atualizaMaxMinColisao(jogo.galinha,y);
    return jogo;
}
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
tjogo aumentaMovimentoS(tjogo jogo){
    jogo.n_movimentoS++;
    return jogo;
}
tjogo aumentaMovimentoW(tjogo jogo){
    jogo.n_movimentosW++;
    return jogo;
}
tjogo aumentaInteracao(tjogo jogo,char movimento)
{
    jogo.interacoes++;
    
    if(movimento=='s'){
        jogo=aumentaMovimentoS(jogo);
    }else if(movimento=='w'){
        jogo=aumentaMovimentoW(jogo);
    }
    jogo = movimentaCarros(jogo);
    return jogo;
}

//atualiza o estado atual da matriz
void inicializarMatriz(int linhas, int colunas, char matriz[linhas][colunas], tjogo jogo,int x);
tjogo Lejogo(char *diretorio){
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
    }
    pPersonagens = fopen(caminhoPerson, "r");
    if (!pPersonagens)
    {
        printf("Não foi possivel achar o arquivo de personagens no caminho:%s", caminhoPerson);
    }
    int i, j,p;
    char inicio;

    fscanf(pConfig_inicial, "%d", &jogo.animacao);
    fscanf(pConfig_inicial, "%d %d", &jogo.largura_mapa, &jogo.qtd_pistas);

    int linhas = (jogo.qtd_pistas * 3) - 1;
    jogo.interacoes = 0;
    jogo.pontuacao=0;
    jogo.n_colisoes=0;  
    jogo.n_movimentoS=0;
    jogo.n_movimentosW=0;

    fgetc(pConfig_inicial);
    //pega pistas
    for (i = 0; i < jogo.qtd_pistas; i++){
        inicio=fgetc(pConfig_inicial);
        if (inicio == 'E' || inicio == 'D'){
            jogo.pistas[i].direcao = inicio;
            fscanf(pConfig_inicial, "%d", &jogo.pistas[i].velocidade);
            fscanf(pConfig_inicial, "%d", &jogo.pistas[i].num_carros);
            for (j = 0; j < jogo.pistas[i].num_carros; j++){  
                int x;
                fscanf(pConfig_inicial, "%d", &x);
                jogo.pistas[i].posicao_carros[j].x=x-1; // guarda posição do carro correta
            }
            fgetc(pConfig_inicial);//pega último barra n pista
        }
        else if (inicio == 'G'){ 
            int xg;
            fscanf(pConfig_inicial, "%d", &xg);
            fscanf(pConfig_inicial, "%d", &jogo.galinha.vidas);
            jogo.galinha.x=xg-1;//guarda posição correta galinha;
            jogo.galinha.y = linhas - 1;
            jogo.galinha.altura_maxima=linhas-1;
            jogo.galinha.maximo_atropelamento=linhas-1;
            jogo.galinha.min_atropelamento=0;
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
    for (i = 0; i < 2; i++){
        for (j = 0; j < 3; j++){
            fscanf(pPersonagens, "%c", &jogo.desenho_galinha[i][j]);
        }
        fscanf(pPersonagens, "%*[\r\n]");
    }for ( p= 0; p< 4; p++)
    {
        fscanf(pPersonagens, "%*[\r\n]");
        for (i = 0; i < 2; i++){
            for (j = 0; j < 3; j++){
                fscanf(pPersonagens, "%c", &jogo.desenho_carro[p][i][j]);
            }
            fscanf(pPersonagens, "%*[\r\n]");
        }
    }
    inicializarMatriz(linhas, jogo.largura_mapa, jogo.matriz, jogo,0);
    fclose(pConfig_inicial);
    fclose(pPersonagens);
    return jogo;
}
tjogo atualizaMatriz(tjogo jogo){
    int linhas = (jogo.qtd_pistas * 3) - 1;
    inicializarMatriz(linhas, jogo.largura_mapa, jogo.matriz, jogo,jogo.animacao);
    return jogo;   
}

//previsao movimento galinha. 
int voltaInicio(tjogo jogo)
{
    int posicao_inicial = (jogo.qtd_pistas * 3) - 2;
    return posicao_inicial;
}
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

//verifica colisao
int colisao(tjogo jogo, int x, int pista_galinha)
{
    int i, j, c = 0;
    for (i = 0; i < jogo.qtd_pistas; i++){
        if (i == pista_galinha){
            for (j = 0; j < obtemNumCarrosPista(jogo.pistas[i]); j++){ 
                int pCarro=obtemXCarroPista(jogo.pistas[i],j);
                if (pCarro == x||pCarro+2 == x||pCarro-2 == x ||pCarro-1 == x||pCarro+1 == x){
                    c = 1;
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
tjogo AtualizaVetorColisoes(tjogo jogo, int x, int pista_galinha,int animacao){
    int i, j, c = 0,col,l;
    for (i = 0; i < jogo.qtd_pistas; i++){
        if (i == pista_galinha){
            for (j = 0; j < obtemNumCarrosPista(jogo.pistas[i]); j++){ 
                int pCarro=obtemXCarroPista(jogo.pistas[i],j);
                if (pCarro == x||pCarro+2 == x||pCarro-2 == x ||pCarro-1 == x||pCarro+1 == x){
                    tcolisao colisao=Lecolisao(pista_galinha+1,j+1,jogo.interacoes,x+1,(pista_galinha*3)+1);
                    AdicionaColisao(colisao,jogo.colisoes,jogo.n_colisoes);
                    if(animacao && (jogo.pistas[i].velocidade>1)){
                        jogo.pistas[i].velocidade--;
                    }
                    jogo.n_colisoes++;
                    l = pista_galinha * 3;
                    for (int col = 0; col < jogo.largura_mapa; col++) {
                        jogo.heatmap[l][col] = -1;
                        jogo.heatmap[l+1][col] = -1;
                    }
                    return jogo;
                }
            }
        }
    }
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
    for (i = 0; i < c; i++){
        fprintf(pInicialização,"-");
    }
    fprintf(pInicialização,"|");
    fprintf(pInicialização,"\n");

    for (i = 0; i < l; i++){
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

//preenche a matriz com carros e galinha
void inicilizarHeatmap(tjogo jogo){
    int linhas = (jogo.qtd_pistas * 3) - 1,i,j;
    for ( i = 0; i < linhas; i++){
        for ( j = 0; j < jogo.largura_mapa; j++){
            jogo.heatmap[i][j]=0;
        }
    }
}
tjogo incrementaHeatmapGalinha(tjogo jogo){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++){
            int y = jogo.galinha.y + i - 1;
            int x = jogo.galinha.x + j - 1;
            if (y >= 0 && y < (jogo.qtd_pistas*3)-1 && x >= 0 && x < jogo.largura_mapa){
                if (jogo.heatmap[y][x] != -1 && jogo.heatmap[y][x] < 99){
                    jogo.heatmap[y][x]++;
                }
            }
        }
    }
    return jogo;
}
void inicializarMatriz(int linhas, int colunas, char matriz[linhas][colunas], tjogo jogo,int x){
    int i, j,p,k,m;
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
                            matriz[posY][posX] = jogo.desenho_carro[0][i][j];
                        }
                    }
                }else{
                    m=jogo.interacoes%4;
                    for (i = 0; i < 2; i++) {      
                        for (j = 0; j < 3; j++) {  
                            int posY = linha_carro +i;        
                            int posX = (jogo.pistas[p].posicao_carros[k].x + (j - 1) + jogo.largura_mapa) % jogo.largura_mapa;
                            matriz[posY][posX] = jogo.desenho_carro[m][i][j];
                        }
                    }
                    
                }
           
            }
            
            
        }
        
    }
    


}

//Impresoes 
void Cabecalho(tjogo jogo){
    printf("Pontos: %d | Vidas: %d | Iteracoes: %d\n",jogo.pontuacao,obtemVidasGalinha(jogo.galinha),ObtemInteracoesJogo(jogo));   
}
//imprime o estado atual tanto no arquivo saida quanto na tela
void imprimeEstado(tjogo jogo){
    int linhas = (jogo.qtd_pistas * 3) - 1;
    Cabecalho(jogo);
    imprimeMatriz(linhas, jogo.largura_mapa, jogo.matriz);
}
void imprimeColisao(tcolisao colisao,FILE *pranking){
    fprintf(pranking,"%d,%d,%d\n",colisao.id_pista,colisao.id_carro,colisao.interacao);
}

//arquivos
void ImprimeInicializacao(tjogo jogo, char *diretorio){
    FILE *pInicialização;
    char caminhoInicializacao[1000];
    sprintf(caminhoInicializacao, "%s/saida/inicializacao.txt", diretorio);
    pInicialização=fopen(caminhoInicializacao,"w");
     if (!pInicialização){
        printf("erro ao criar inicialização em:%s\n", caminhoInicializacao);
        return;
    }
    
    int linhas = (jogo.qtd_pistas * 3) - 1;
    imprimeMatrizInicializacao(linhas, jogo.largura_mapa, jogo.matriz,pInicialização);
    fprintf(pInicialização,"A posicao central da galinha iniciara em (%d %d).",obtemXGalinha(jogo.galinha)+1,obtemYGalinha(jogo.galinha));
    fclose(pInicialização);
}
void ImprimeResumo(tjogo jogo, char *diretorio){
    FILE *pResumo;
    int i;
    char caminhoResumo[1000];
    sprintf(caminhoResumo, "%s/saida/resumo.txt", diretorio);
    pResumo=fopen(caminhoResumo,"w");
     if (!pResumo){
        printf("erro ao criar arquivo saida em:%s\n", caminhoResumo);
        return;
    }
    for ( i = 0; i < jogo.n_colisoes; i++)
    {
        fprintf(pResumo,"[%d] Na pista %d o carro %d atropelou a galinha na posicao (%d,%d).\n",jogo.colisoes[i].interacao,jogo.colisoes[i].id_pista,jogo.colisoes[i].id_carro,jogo.colisoes[i].x,jogo.colisoes[i].y);
    }
    fprintf(pResumo,"[%d] Fim de jogo",ObtemInteracoesJogo(jogo));
    fclose(pResumo);
    

}
void ImprimeRanking(tjogo jogo, char *diretorio){
    jogo=OrdenaColisao(jogo);
    FILE *pRanking;
    char caminhoRanking[1000];
    sprintf(caminhoRanking, "%s/saida/ranking.txt", diretorio);
    pRanking=fopen(caminhoRanking,"w");
     if (!pRanking){
        printf("erro ao criar arquivo saida em:%s\n", caminhoRanking);
        return;
    }
    int i;
    
    fprintf(pRanking,"id_pista,id_carro,iteracao\n");
    for ( i = 0; i < jogo.n_colisoes; i++){
        imprimeColisao(jogo.colisoes[i],pRanking);
    }
    fclose(pRanking);
}
void ImprimeEstatistica(tjogo jogo, char *diretorio){
    FILE *pEstatistica; 
    char caminhoEstatistica[1000];
    sprintf(caminhoEstatistica, "%s/saida/estatistica.txt", diretorio);
    pEstatistica=fopen(caminhoEstatistica,"w");
     if (!pEstatistica){
        printf("erro ao criar arquivo saida em:%s\n", caminhoEstatistica);
        return;
    }
    int linhas=(jogo.qtd_pistas*3);
    int maxAltura=linhas-jogo.galinha.altura_maxima;
    int maxAtro=linhas-jogo.galinha.maximo_atropelamento;
    int minAtro=linhas-jogo.galinha.min_atropelamento;
    fprintf(pEstatistica,"Numero total de movimentos: %d\n",jogo.n_movimentosW+jogo.n_movimentoS);
    fprintf(pEstatistica,"Altura maxima que a galinha chegou: %d\n",maxAltura);
    if (jogo.n_colisoes == 0) {
    fprintf(pEstatistica,"Altura maxima que a galinha foi atropelada: 0\n");
    fprintf(pEstatistica,"Altura minima que a galinha foi atropelada: 0\n");
    } else {
    int maxAtro = linhas - jogo.galinha.maximo_atropelamento;
    int minAtro = linhas - jogo.galinha.min_atropelamento;
    fprintf(pEstatistica,"Altura maxima que a galinha foi atropelada: %d\n", maxAtro);
    fprintf(pEstatistica,"Altura minima que a galinha foi atropelada: %d\n", minAtro);
    }
    fprintf(pEstatistica,"Numero de movimentos na direcao oposta: %d\n",jogo.n_movimentoS);
    fclose(pEstatistica);
}
void ImprimeHeatmap(tjogo jogo, char *diretorio){
    FILE *pMapaCalor;
    char caminhoMapaCalor[1000]; 
    sprintf(caminhoMapaCalor, "%s/saida/heatmap.txt", diretorio);
    pMapaCalor=fopen(caminhoMapaCalor,"w");
    if (!pMapaCalor){
        printf("erro ao criar arquivo saida em:%s\n", caminhoMapaCalor);
        return;
    } 
    int l = (jogo.qtd_pistas * 3) - 1;  // o mesmo 'linhas' usado no resto
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < jogo.largura_mapa; j++) {
            if (jogo.heatmap[i][j] == -1)
                fprintf(pMapaCalor, " * ");
            else
                fprintf(pMapaCalor, "%2d ", jogo.heatmap[i][j]);
        }
        fprintf(pMapaCalor, "\n");
    }
    fclose(pMapaCalor);
}

int main(int argc, char *argv[])
{
    tjogo jogo;
    if (argc <= 1){
        printf("ERRO: Informe o diretorio com os arquivos de configuracao.\n");
        return 1;
    }
    
    jogo = Lejogo(argv[1]);
    imprimeEstado(jogo);
    ImprimeInicializacao(jogo,argv[1]);
    char movimento;
    do{
        do{
            scanf("%c", &movimento);
            if (movimento == '\n')
            continue; 
        } while (movimento != 'w' && movimento != 's' && movimento != ' ');
        //aumenta interacao - movimenta carros - conta movimentos w s
        jogo = aumentaInteracao(jogo,movimento);
        jogo= incrementaHeatmapGalinha(jogo);
        int y = movimentaGalinha(jogo, movimento);
        int x = ObtemXGalinhaJogo(jogo);
        int pista_galinha = y / 3;
        if (colisao(jogo, x, pista_galinha))
        {   jogo=AtualizaVetorColisoes(jogo, x, pista_galinha,jogo.animacao);
            jogo=AtualizaMaxMinColisaoJogo(jogo,y);
            jogo = DiminuiVida(jogo);
            y = voltaInicio(jogo);
            jogo=AtulizaPontucao(jogo,-ObtemPontuacao(jogo));
        }else{
            if(movimento=='w'){
                jogo=AtulizaPontucao(jogo,1);
                jogo=AltualziaMaximaJogo(jogo,y);
            }
        }
        jogo = AtualizaGalinha(jogo, y);
        jogo=atualizaMatriz(jogo);
        if(galinhaAtravesou(jogo)){
            jogo=AtulizaPontucao(jogo,10);
        }
        imprimeEstado(jogo);

    } while (!vidaGalinhaAcabou(jogo) && !galinhaAtravesou(jogo));
    
    jogo= incrementaHeatmapGalinha(jogo);
    if (galinhaAtravesou(jogo)){
        printf("Parabens! Voce atravessou todas as pistas e venceu!\n");
    }
    else if (vidaGalinhaAcabou(jogo)){
        printf("Voce perdeu todas as vidas! Fim de jogo.\n");
    }
    ImprimeResumo(jogo,argv[1]);
    ImprimeRanking(jogo,argv[1]);
    ImprimeEstatistica(jogo,argv[1]);
    ImprimeHeatmap(jogo,argv[1]);
    return 0;
}   