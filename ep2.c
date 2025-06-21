/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2025                          **/
/**   Prof. Luciano Digiampietri                                    **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   <Kevin Rodrigues Nunes>                   <        >          **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define INFINITO 999999

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias */
typedef struct {
    int numVertices;
    int numArestas;
    bool** matriz;
} Grafo;


/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123(){
    // Funcao usada pelo sistema de correcao automatica (nao mexer)
}



/* Estrutura para representar elementos de uma lista ligada de vertices */
typedef struct aux{
  int vertice;
  struct aux* prox;
} ElementoLista, *PONT;


/* Estrutura para representar elementos de uma lista ligada com arestas
   (pares de vertices)*/
typedef struct aux2{
  int origem;
  int destino;
  struct aux2* prox;
} ArestaLista, * PONT2;


/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencia (preenchida com ARESTAS_INVALIDAS),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool**) malloc(sizeof(bool*)*vertices);
  for (x=0; x<vertices; x++){
    g->matriz[x] = (bool*) malloc(sizeof(bool)*vertices);
    for (y=0; y<vertices; y++){
      g->matriz[x][y] = false;
    }
  }
  return true;
}


/* Funcao que libera a memoria da matriz de adjacencias do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  for (x=0; x<g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia.
*/
bool insereAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  if (g->matriz[v1][v2] == false){
      g->matriz[v1][v2] = true;
      g->numArestas++;
  }
  return true;
}


/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->numArestas--;
  return true;
}


/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  int x, y, a, total;
  if (numVertices < 1 || numArestas >= numVertices*numVertices/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);

  a = 0;
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (g->matriz[x][y] == false){
      g->matriz[x][y] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}



/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencias.
*/
void exibeGrafo(Grafo* g){
  if(!g) return;
  int x, y;
  printf("\nImprimindo grafo (v=%i; a=%i)\n   ", g->numVertices, g->numArestas);
  for (x=0;x<g->numVertices;x++) printf(" %3i",x);
  printf("\n");
  for (x=0;x<g->numVertices;x++){
    printf("%3i",x);
    for (y=0;y<g->numVertices;y++)
      printf(" %3i",g->matriz[x][y]);
    printf("\n");
  }
  printf("\n");
}


/* Funcao que calcula a distancia e o predecedor considerando todos os pares
   vertices (distancia de todos para todos), com base no algoritmo de
   Floyd-Warshall.
*/
void calculaDistanciaFloydWarshall(Grafo* g, int** dist, int** pred){
  int i, j, k, n;
  n = g->numVertices;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      if(g->matriz[i][j] != false){
        dist[i][j] = g->matriz[i][j];
        pred[i][j] = i;
      }else{
        dist[i][j] = INFINITO;
        pred[i][j] = -1;
      }
  for(i=0;i<n;i++) {
    dist[i][i] = 0;
    pred[i][i] = i;
  }

  for(k=0;k<n;k++)
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(dist[i][j] > dist[i][k] + dist[k][j]){
          dist[i][j] = dist[i][k] + dist[k][j];
          pred[i][j] = pred[k][j];
        }
}


/* Funcao que exibe uma matriz de distancias.
   Caso a distancia seja INFINITO, imprime '-'.
*/
void exibeMatrizDistancias(int** matriz, int n){
  printf("Exibindo matriz de distancias.\n");
  int x, y;
  for (x=0; x<n; x++) printf("\t%3i", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%i", x);
    for (y=0; y<n; y++){
      if (matriz[x][y] == INFINITO) printf("\t-");
      else printf("\t%3i",matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}


/* Funcao que exibe uma matriz de predecessores.
   Caso a distancia seja INFINITO, imprime '-'.
*/
void exibeMatrizPredecessores(int** matriz, int n){
  printf("Exibindo matriz de predecessores.\n");
  int x, y;
  for (x=0; x<n; x++) printf("\t%3i", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%i", x);
    for (y=0; y<n; y++){
      printf("\t%3i",matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}


/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(double* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf("  v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%4.3f\t",arranjo[x]);
  }
  printf("\n\n");
}




/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep2/ep2.pdf        */


//As duas funções a seguir calculam, respectivamente, grau de entrada e de saída dos vértices de um grafo.
//Serão utilizadas em "centralidadeDeGrau" e "centralidadePageRank"

int grauDeEntrada(Grafo* g, int v){
  int x;
  int grau = 0;

  //laço que verifica existência de arestas entre cada vertice e o vértice v
  for(x=0; x<g->numVertices; x++){
    if(g->matriz[x][v] && x!=v){
      grau++;
    }
  }

  return grau;
}

int grauDeSaida(Grafo* g, int v){
  int y;
  int grau = 0;

  //laço que verifica todas as arestas existentes do vertice v
  for(y=0; y<g->numVertices; y++){
    if(g->matriz[v][y] && v!=y){
      grau ++;
    }
  }

  return grau;
}

/* Funcao que calcula a Centralidade de Grau de todos os vertices.*/
void centralidadeDeGrau(Grafo* g, double* valores) {
  int x,y; 
  
  //laço que para cada vertice do grafo, calcula a centralidade de grau com base no seu grau de entrada
  for (x=0; x<g->numVertices; x++) {
    valores[x] = grauDeEntrada(g, x) / (double)(g->numVertices - 1);
  }
}


/* Funcao que calcula a Centralidade de Proximidade de todos os vertices. */
void centralidadeDeProximidade(Grafo* g, double* valores) {
  int x,y;


  //alocação das matrizes que serão passadas no calculaDistanciaFloydWarshall
  int** dist = (int**) malloc(sizeof(int*)*g->numVertices);
  for (x=0; x<g->numVertices; x++){
    dist[x] = (int*) malloc(sizeof(int)*g->numVertices);
  }
  int** pred = (int**) malloc(sizeof(int*)*g->numVertices);
  for (x=0; x<g->numVertices; x++){
    pred[x] = (int*) malloc(sizeof(int)*g->numVertices);
  }

  calculaDistanciaFloydWarshall(g, dist, pred); 

  //laço que armazena em valores[x] a soma das distâncias de x para todo vertice y do grafo.
  for(x=0; x<g->numVertices; x++){
    valores[x] = 0;
    for(y=0; y<g->numVertices; y++){
        valores[x] = valores[x] + dist[x][y];
    }
  }

  //laço que aplica o divisor na soma das distâncias para efetivamente obter o grau de proximidade de cada vertice
  for(x=0; x<g->numVertices; x++){
    valores[x] = (g->numVertices-1)/valores[x];
  }

  //laço que libera as matrizes dist e pred
  for(x=0; x<g->numVertices; x++){
    free(dist[x]);
    free(pred[x]);
  }
  free(dist);
  free(pred);
}


/* Funcao que calcula a Centralidade de Intermediacao de todos os vertices. */
void centralidadeDeIntermediacao(Grafo* g, double* valores) {
  int x, y;

  //inicializa vetor valores com 0
  for(x=0; x<g->numVertices; x++){
    valores[x] = 0.0;
  }

  //criação das matrizes a serem incluídas no Floyd-Warshall
  int** dist = (int**) malloc(sizeof(int*)*g->numVertices);
  for (x=0; x<g->numVertices; x++){
    dist[x] = (int*) malloc(sizeof(int)*g->numVertices);
  }
  int** pred = (int**) malloc(sizeof(int*)*g->numVertices);
  for (x=0; x<g->numVertices; x++){
    pred[x] = (int*) malloc(sizeof(int)*g->numVertices);
  }


  calculaDistanciaFloydWarshall(g, dist, pred);
  
  int atual;

  //laços "x" e "y" tem como função percorrer toda a matriz de predecessores, isto é, caminhar por todos os caminhos minimos
  for(x=0; x<g->numVertices; x++){
    for(y=0; y<g->numVertices; y++){
      
      atual = pred[x][y]; //iniciando o caminho de x a y
      
      if(x!=y && dist[x][y] != INFINITO){ //se o caminho não for um auto-laço ou não existir, entra na condição
        
        while(atual != x && atual != -1){ //enquanto o atual for diferente da origem (x) e não ser um caminho invalido...
          
          valores[atual] = valores[atual] + 1.0; //o vertice atual esta presente em mais um caminho minimo 
          atual = pred[x][atual]; //atual passa a ser o proximo vertice do caminho de x a y

        }

      }
    }
  }  

  //laço que aplica o divisor para efetivamente obter o grau de intermediacao de cada vertice
  for(x=0; x<g->numVertices; x++){
    valores[x] = valores[x]/((g->numVertices-1)*(g->numVertices-2));
  }

  //libera a memoria das metrizes dist e pred
  for(x=0; x<g->numVertices; x++){
    free(dist[x]);
    free(pred[x]);
  }
  free(dist);
  free(pred);
}

/* Funcao que calcula a Centralidade Page Rank de todos os vertices. */
void centralidadePageRank(Grafo* g, double* valores, int iteracoes) {
  int x, y, z, i;
  const double d = 0.85;
  double* valoresTemp = (double*) malloc(sizeof(double)*g->numVertices); //esse vetor sera usado para armazenar o pageRank real de cada iteracao

  //inicalizando Valores
  for(x=0; x<g->numVertices; x++){
    valores[x] = 1/(double)g->numVertices;
  }

  double somatoria;

  for(i=0; i<iteracoes; i++){ //laço que roda o numero de iteracoes pre-estabelecido
    for(x=0; x<g->numVertices; x++){ //laco que calcula o page rank do vertice x na iteracao i
      
      somatoria = 0.0;
      
      for(y = 0; y<g->numVertices; y++){ //para todos os demais vertices
        
        if(g->matriz[y][x] && y!=x){ //se y apontar para x (e y nao for x)
          
          somatoria = somatoria + valores[y]/(double)grauDeSaida(g, y); //calcula a somatoria 
        
        }
      }
      valoresTemp[x] = (1-d)/(double)g->numVertices + d * somatoria; //atribui pageRank atual no vetor valores temporario
    }
    
    //adiciona os novos pageRank no vetor Valores
    for(x=0; x<g->numVertices; x++){
      valores[x] = valoresTemp[x];
    }

  }

  free(valoresTemp);
}


/* FIM DAS FUNCOES QUE DEVEM SER COMPLETADAS */


/* Funcao que invoca e exibe os valores de cada uma das funcoes que voces
   devem implementar neste EP.
*/
void testaFuncoes(Grafo* g, int n){

  double* valoresReais = (double*)malloc(sizeof(double)*n);

  printf("Centralidade de Grau:\n");
  centralidadeDeGrau(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Proximidade:\n");
  centralidadeDeProximidade(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Intermediacao:\n");
  centralidadeDeIntermediacao(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 0 iteracoes\n");
  centralidadePageRank(g, valoresReais, 0);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 1 iteracao\n");
  centralidadePageRank(g, valoresReais, 1);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 10 iteracoes\n");
  centralidadePageRank(g, valoresReais, 10);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 100 iteracoes\n");
  centralidadePageRank(g, valoresReais, 100);
  exibeArranjoReais(valoresReais, n);

  free(valoresReais);
}


/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;
  double* valoresReais = (double*)malloc(sizeof(double)*n);

  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1,0,1);
  insereAresta(&g1,1,2);
  insereAresta(&g1,2,3);
  insereAresta(&g1,3,4);
  insereAresta(&g1,4,0);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);


  printf("\n\nSEGUNDO EXEMPLO [auto-lacos]\n");
  insereAresta(&g1,0,0);
  insereAresta(&g1,2,2);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);


  printf("\n\nTERCEIRO EXEMPLO\n");
  Grafo g2;
  inicializaGrafo(&g2, n);
  insereAresta(&g2,0,2);
  insereAresta(&g2,1,2);
  insereAresta(&g2,3,2);
  insereAresta(&g2,4,2);
  insereAresta(&g2,2,0);
  insereAresta(&g2,2,1);
  insereAresta(&g2,2,3);
  insereAresta(&g2,2,4);

  exibeGrafo(&g2);

  testaFuncoes(&g2, n);


  printf("\n\nQUARTO EXEMPLO (grafo aleatorio)\n\n");
  n = 10;
  int arestas = 40;

  Grafo* g3 = criaGrafoAleatorio(n,arestas);

  exibeGrafo(g3);

  testaFuncoes(g3, n);

  printf("Resolucao das funcoes de centralidade por Kevin Rodrigues\n\n"); 

  return 0;
}
