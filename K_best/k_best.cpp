/*
	Implementação do algoritmo de Kruskal
	Para detectar ciclos iremos utilizar o algoritmo Union-Find que detecta
	ciclos em grafos NÃO direcionados.
*/

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset
#include "conn.h"
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
	vector<Grafo> list;
	int pesoMST;
	int pos;
public:

	int getQntVertice(){
		return V;
	}

	void setPos(int p ){ this->pos = p;}
	int getPos(){return this->pos;}

	bool operator < (const Grafo& g) const
	{
		return (pesoMST < g.pesoMST);
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

	// função que busca o subconjunto de um elemento "i"
	int buscar(int subset[], int i)
	{
		if(subset[i] == -1)
			return i;
		return buscar(subset, subset[i]);
	}

	// função para unir dois subconjuntos em um único subconjunto
	void unir(int subset[], int v1, int v2)
	{
		int v1_set = buscar(subset, v1);
		int v2_set = buscar(subset, v2);
		subset[v1_set] = v2_set;
	}

	// função que roda o algoritmo de Kruskal
	void kruskal()
	{
		vector<Aresta> arvore;
		int total = 0;
		int size_arestas = arestas.size();

		// ordena as arestas pelo menor peso
		sort(arestas.begin(), arestas.end());

		// aloca memória para criar "V" subconjuntos
		int * subset = new int[V];

		// inicializa todos os subconjuntos como conjuntos de um único elemento
		memset(subset, -1, sizeof(int) * V);

		for(int i = 0; i < size_arestas; i++)
		{
			int v1 = buscar(subset, arestas[i].obterVertice1());
			int v2 = buscar(subset, arestas[i].obterVertice2());

			if(v1 != v2 && arestas[i].getInclido() != 0)
			{
				// se forem diferentes é porque NÃO forma ciclo, insere no vetor
				arvore.push_back(arestas[i]);
				unir(subset, v1, v2); // faz a união
				total += arestas[i].obterPeso();
			}
		}
    
		//int size_arvore = arvore.size();

		// mostra as arestas selecionadas com seus respectivos pesos
		/*for(int i = 0; i < size_arvore; i++)
		{
			char v1 = 'A' + arvore[i].obterVertice1();
			char v2 = 'A' + arvore[i].obterVertice2();
			cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
		}*/
		//this->pesoMST = total;		
        
        
		this->pesoMST = total;
        
	}

    void particao(Grafo P){        
        Grafo P1(P.V);
		P1.arestas = P.arestas;
        Grafo P2(P.V);
		P2.arestas = P.arestas;
        for(int i = 0; i < P.arestas.size(); i++){
            if (P.arestas[i].getInclido() != 1 && P.arestas[i].getInclido() != 0)
            {
                P1.arestas[i].setIncluido(0);
                P2.arestas[i].setIncluido(1);
                P1.kruskal();
                //if(P1.arestas.size() == V-1){
				if(Is_Connected(P1.arestas[i].obterVertice1())){
					P1.setPos(P.getPos()+1);
                    this->list.push_back(P1);
                }
                P1 = P2;
            }
            
        }
        
    }

	Grafo getMinMST(vector<Grafo> list){
		Grafo result = list.front();
		for(Grafo g : list){
			if (g.pesoMST <= result.pesoMST)
			{
				result = g;
			}			
		}
		return result;
	}
	int getPos(vector<Grafo> list, Grafo g){
		int pos = 0;
		for(Grafo e : list){
			if(e.pesoMST == g.pesoMST){
				return pos;
			}
			pos++;
		}
	}

    void k_best(){        
        vector<Grafo> output;
		this->setPos(0);
		this->kruskal();
        list.push_back(*this);	        
        while( this->list.empty() != true){
            Grafo ps = getMinMST(this->list);	
			ps.kruskal();
            output.push_back(ps);
            //list.pop_back();
			//printList();
			//cout << ps.pesoMST << " pos: " << ps.pos << " \n";
			this->list.erase(this->list.begin()+ ps.getPos());
            particao(ps);
        }        
        for (int i = 0 ;  i < output.size() ; i++)
        {
            cout << "Grafo[" << i << "] - peso:" << output[i].pesoMST << "\n";
            //output[i].display();
        }
        
    }

	void printList(){
		cout << "[ ";
		for(int i = 0; i < list.size(); i++){
			cout << list[i].pesoMST << ", ";
		}
		cout << " ]\n";
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
			v1 = rand() % V;
			v2 = rand() % V;
			p = rand() % max;
			if (v1 != v2)
			{
				r.adicionarAresta(v1,v2,p);	
			}					
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


};

int main(int argc, char *argv[])
{
	Grafo g(20); // grafo
	g.makeRandGrafo(30,50,10);
	return 0;
}