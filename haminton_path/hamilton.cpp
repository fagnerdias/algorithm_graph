/*
	Implementação do algoritmo de Kruskal
	Para detectar ciclos iremos utilizar o algoritmo Union-Find que detecta
	ciclos em grafos NÃO direcionados.
*/

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset
#include "../K_best/conn.h"
//#include "sort.h"
using namespace std;

class Aresta
{
	int vertice1, vertice2, peso;
    int incluido; // 1 - incluido; 0 - excluido; 2 - Op;

public:
	

	Aresta(int v1, int v2, int peso)
	{
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}

	int obterVertice1()
	{
		return vertice1;
	}

	int obterVertice2()
	{
		return vertice2;
	}


	int obterPeso()
	{
		return peso;
	}

    void setIncluido(int inc){
        this->incluido = inc;
    }
    int getInclido(){return incluido;}

	// sobrescrita do operador "<"
	bool operator < (const Aresta& aresta2) const
	{
		return (peso < aresta2.peso);
	}
};

class Grafo
{
	int V; // número de vértices
	vector<Aresta> arestas; // vetor de arestas		
public:

	int getQntVertice(){
		return V;
	}

	Grafo(int V)
	{
		this->V = V;
	}

	// função que adiciona uma aresta
	void adicionarAresta(int v1, int v2, int peso)
	{
		Aresta aresta(v1, v2, peso);
        aresta.setIncluido(2);
		arestas.push_back(aresta);
	}


    void display(){
        for(Aresta i : this->arestas){
        
		    cout << "(" << i.obterVertice1() << "," << i.obterVertice2() << ") w = " << i.obterPeso() << "\n";
        }
    }

	Grafo makeRandGrafo(int V,int a, int max){
		Grafo r(V);
		for(int i =0 ; i < a; i++){
			int v1,v2,p = 0;
			v1 = rand() % max;
			v2 = rand() % max;
			p = rand() % max;
			r.adicionarAresta(v1,v2,p);
		}
		if (Is_Connected(r.arestas[0].obterVertice1()))
		{
			r.display();
			return r;	
		}
		else{
			makeRandGrafo(V,a,max);
		}
		
	}

    bool contains(vector<Aresta> arestas, Aresta a){
        for(Aresta e: arestas){
            if(e.obterVertice1() == a.obterVertice1() && e.obterVertice2() == a.obterVertice2())
                return true;
        }
        return false;
    }

    bool check_all_permutations(Grafo g, int n){
        vector<int>v;
        for(int i=0; i<n; i++)
            v.push_back(i);
        do{
            bool valid=true;
            for(int i=0; i<v.size()-1; i++){
                if(contains(g.arestas,Aresta(i, i+1, 0)) == false){
                    valid=false;
                    break;
                }     
            }
            if(valid){                
                return true;
            }                
        }while(next_permutation(v.begin(), v.end()));
        return false;
}


};

int main(int argc, char *argv[]){

    Grafo g(10);

    g.adicionarAresta(1, 2,0);
    g.adicionarAresta(1, 3,0);
    g.adicionarAresta(1 ,4 ,0);
    g.adicionarAresta(2, 3,0);
    g.adicionarAresta(2, 4,0);
    g.adicionarAresta(3, 5,0);
    g.adicionarAresta(4, 6,0);
    g.adicionarAresta(5, 6,0);
    g.adicionarAresta(5, 7,0);
    g.adicionarAresta(6, 7,0);
    g.adicionarAresta(7, 8,0);
    g.adicionarAresta(8, 9,0);
    g.adicionarAresta(8 ,10,0);
    g.adicionarAresta(9 ,10,0);
    
    if(g.check_all_permutations(g,10))
        cout << "vdd";
    else
    {
        cout << "false";
    }
    


    return 0;
}