/*----------------------------------------------------------[]
Programa: Gerador.c

Programador: Claudia Nasu/Edson Norberto Caceres Data: 23/08/2002

Dialogo: Este programa gera grafos eulerianos aleatoriamente 
[]	*/
// Declaracao das bibliotecas utilizadas 
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

#define MAX 1024 // Numero maximo de arestas do grafo 
int mat_adj[MAX][MAX];
// Matriz de adjacencias do grafo

// Funcao principal
int main( int argc, char *argv[] )
{
    FILE *ArqS;
    int i, j, dif, somal, somac, aux, flag, nvertices, narestas;

// Passo 1. Verifique se houve erro nos argumentos 
    if (argc != 3)
    {
        printf("Gerador <numero de vertices> <nome do arquivo>"); 
        exit(0);
    }
    nvertices = atoi(argv[1]);

// Passo 2. Inicialize a semente do srand 
    srand ((unsigned)time(0));
// Passo 3. Gere a matriz de adjacencias do grafo 
    for( i = 0; i < nvertices; i++ )
        for( j = 0; j < nvertices; j++ ) { 
            if( i == j )
                mat_adj[i][j] = -1; // grafo nao possui lacos 
            else if( mat_adj[i][j] != -1 ) {
// Inclui uma aresta no grafo com probabilidade de 20 
                aux = rand()%4;
            if( aux == 1 ) // inclui aresta entre i e j 
                mat_adj[i][j] = 1;
            else // nao inclui aresta entre i e j 
                mat_adj[i][j] = 0;
            } // fim else-if
        } // fim for j
// Passo 4. Verifique se o grafo gerado eh euleriano 
        flag = 1;
        while( flag ) { 
            flag = 0;
            for( i = 0; i < nvertices; i++ ) { 
                somal = 0;
                somac = 0;
                for( j = 0; j < nvertices; j++ ) { 
                    if( mat_adj[i][j] > 0 )
                        somal += mat_adj[i][j]; if( mat_adj[j][i] > 0 )
                    somac += mat_adj[j][i];
                } // fim for
                if( somal < somac ) {
// quantas arestas faltam na linha 
                    dif = somac - somal;
// Procura nas colunas posteriores
// procura um coluna naquela linha para modificar 
                    for( j = i; dif > 0 && j < nvertices; j++ ) {
                        if( mat_adj[i][j] == 0 ) {
                            mat_adj[i][j] = 1; dif--;
                        } // fim if
                    } // fim for
// Nao havia colunas posteriores em 0 suficiente

                    if( dif > 0 ) {
// Procura nas colunas anteriores
// procura um coluna naquela linha para modificar 
                        for( j = 0; dif > 0 && j < i; j++ ) { 
                            if( mat_adj[i][j] == 0 ) {
                                mat_adj[i][j] = 1; dif--;
                                flag = 1;
                            } // fim if
                        } // fim for
                    } // fim if
// Nao havia colunas ant/post suficientes 
                    if( dif > 0 ) {
// Elimina arestas nas colunas
                        for( j = 0; dif > 0 && j < nvertices; j++ ) { 
                            if( mat_adj[j][i] == 1 ) {
                                mat_adj[j][i] = 0; dif--;
                                if( j < i ) 
                                    flag = 1;
                            } // fim if
                        } // fim for
                    } // fim if
                } // fim if
                else if( somac < somal ){ 
                    dif = somal - somac;
// Procura nas linhas posteriores
// procura um linha naquela coluna para modificar 
                    for( j = i; dif > 0 && j < nvertices; j++ ) {
                        if( mat_adj[j][i] == 0 ) {
                            mat_adj[j][i] = 1; dif--;
                        } // fim if
                    } // fim for
// Nao havia linhas posteriores suficientes 
                    if( dif > 0 ) {
// Procura nas linhas anteriores
// procura um linha naquela coluna para modificar 
                        for( j = 0; dif > 0 && j < i; j++ ) {
                            if( mat_adj[j][i] == 0 ) {
                                mat_adj[j][i] = 1; dif--;
                                flag = 1;
                            } // fim if
                        } // fim for
                    } // fim if
// Nao havia linhas ant/post suficiente 
                    if( dif > 0 ) {
// Elimina arestas na linha
                        for( j = 0; dif > 0 && j < nvertices; j++ ) { 
                            if( mat_adj[i][j] == 1 ) {
                                mat_adj[i][j] = 0; dif--;
                                if( j < i ) 
                                    flag = 1;
                            } // fim if
                        } // fim for
                    }// fim if
                } // fim if-else
            } // fim for i
        } // fim while
// Passo 5. Calcule o numero de arestas do grafo 
        narestas = 0;
        for( i = 0; i < nvertices; i++ ) 
            for( j = 0; j < nvertices; j++ )
// Se existe uma aresta entre os vertices i e j 
                if( mat_adj[i][j] == 1 )
                    narestas++;
// Passo 6. Armazene as arestas do grafo gerado em arquivo 
        ArqS = fopen(argv[2], "w");
// Passo 6.1. Ordene pelo vertice destino - Edge 
        fprintf(ArqS, "%d \n", nvertices); 
        fprintf(ArqS, "%d \n", narestas);
        for( i = 0; i < nvertices; i++ ) 
            for( j = 0; j < nvertices; j++ )
                if( mat_adj[j][i] == 1 ) 
                    fprintf(ArqS, "%d	%d\n", j, i);
// Passo 6.2. Ordene pelo vertice origem - Sucessor 
        for( i = 0; i < nvertices; i++ )
        for( j = 0; j < nvertices; j++ ) 
            if( mat_adj[i][j] == 1 )
                fprintf(ArqS, "%d	%d\n", i, j);
// Passo 6.3. Fecha o arquivo 
        fclose(ArqS);
}
