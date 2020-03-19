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
			printList();
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


};

int main(int argc, char *argv[])
{
	Grafo g(50); // grafo
	
	// adiciona as arestas
	/*
	g.adicionarAresta(0, 1, 7);
	g.adicionarAresta(0, 3, 5);
	g.adicionarAresta(1, 2, 8);
	g.adicionarAresta(1, 3, 9);
	g.adicionarAresta(1, 4, 7);
	g.adicionarAresta(2, 4, 5);
	g.adicionarAresta(3, 4, 15);
	g.adicionarAresta(3, 5, 6);
	g.adicionarAresta(4, 5, 8);
	g.adicionarAresta(4, 6, 9);
	g.adicionarAresta(5, 6, 11);
	//g.kruskal(); // roda o algoritmo de Kruskal
    g.k_best();
	
	g.adicionarAresta(0,6, 38);
	g.adicionarAresta(17,14, 39);
	g.adicionarAresta(32,4, 4);
	g.adicionarAresta(25,29, 41);
	g.adicionarAresta(12,38, 19);
	g.adicionarAresta(36,20, 6);
	g.adicionarAresta(44,10, 49);
	g.adicionarAresta(14,15, 14);
	g.adicionarAresta(26,36, 33);
	g.adicionarAresta(39,19, 35);
	g.adicionarAresta(2,21, 43);
	g.adicionarAresta(40,39, 9);
	g.adicionarAresta(31,23, 14);
	g.adicionarAresta(35,48, 45);
	g.adicionarAresta(27,13, 33);
	g.adicionarAresta(48,49, 5);
	g.adicionarAresta(5,43, 18);
	g.adicionarAresta(6,10, 33);
	g.adicionarAresta(23,36, 21);
	g.adicionarAresta(8,27, 40);
	g.adicionarAresta(45,31, 11);
	g.adicionarAresta(40,23, 0);
	g.adicionarAresta(0,4, 25);
	g.adicionarAresta(14,42, 24);
	g.adicionarAresta(9,19, 39);
	g.adicionarAresta(44,19, 38);
	g.adicionarAresta(1,26, 33);
	g.adicionarAresta(19,33, 43);
	g.adicionarAresta(4,6, 31);
	g.adicionarAresta(25,16, 11);
	g.adicionarAresta(17,12, 42);
	g.adicionarAresta(29,2, 18);
	g.adicionarAresta(31,2, 24);
	g.adicionarAresta(7,18, 16);
	g.adicionarAresta(33,27, 37);
	g.adicionarAresta(22,23, 7);
	g.adicionarAresta(12,25, 33);
	g.adicionarAresta(47,46, 18);
	g.adicionarAresta(41,3, 26);
	g.adicionarAresta(24,30, 43);
	g.adicionarAresta(35,48, 5);
	g.adicionarAresta(30,29, 9);
	g.adicionarAresta(48,10, 12);
	g.adicionarAresta(24,19, 30);
	g.adicionarAresta(41,2, 10);
	g.adicionarAresta(30,26, 33);
	g.adicionarAresta(39,40, 8);
	g.adicionarAresta(23,38, 7);
	g.adicionarAresta(43,31, 10);
	g.adicionarAresta(20,5, 40);
	*/
	
	
	
	g.adicionarAresta(1,27, 43);
	g.adicionarAresta(49,41, 20);
	g.adicionarAresta(37,38, 46);
	g.adicionarAresta(7,44, 6);
	g.adicionarAresta(21,26, 13);
	g.adicionarAresta(12,15, 41);
	g.adicionarAresta(44,26, 30);
	g.adicionarAresta(22,32, 42);
	g.adicionarAresta(13,41, 8);
	g.adicionarAresta(24,15, 37);
	g.adicionarAresta(6,16, 15);
	g.adicionarAresta(1,17, 8);
	g.adicionarAresta(21,5, 48);
	g.adicionarAresta(19,12, 43);
	g.adicionarAresta(25,33, 21);
	g.adicionarAresta(40,47, 38);
	g.adicionarAresta(33,42, 14);
	g.adicionarAresta(13,16, 49);
	g.adicionarAresta(7,29, 40);
	g.adicionarAresta(16,3, 5);
	g.adicionarAresta(3,9, 21);
	g.adicionarAresta(20,10, 38);
	g.adicionarAresta(30,34, 45);
	g.adicionarAresta(29,3, 8);
	g.adicionarAresta(22,31, 43);
	g.adicionarAresta(45,23, 43);
	g.adicionarAresta(33,7, 35);
	g.adicionarAresta(49,22, 3);
	g.adicionarAresta(48,30, 32);
	g.adicionarAresta(40,48, 37);
	g.adicionarAresta(45,3, 47);
	g.adicionarAresta(18,26, 9);
	g.adicionarAresta(9,6, 45);
	g.adicionarAresta(4,35, 49);
	g.adicionarAresta(14,9, 32);
	g.adicionarAresta(10,4, 5);
	g.adicionarAresta(3,39, 14);
	g.adicionarAresta(40,41, 37);
	g.adicionarAresta(43,41, 19);
	g.adicionarAresta(27,32, 19);
	g.adicionarAresta(14,29, 22);
	g.adicionarAresta(11,48, 48);
	g.adicionarAresta(23,9, 7);
	g.adicionarAresta(18,13, 42);
	g.adicionarAresta(19,30, 4);
	g.adicionarAresta(1,40, 10);
	g.adicionarAresta(9,45, 0);
	g.adicionarAresta(25,35, 43);
	g.adicionarAresta(12,30, 34);
	g.adicionarAresta(33,7, 16);
	g.adicionarAresta(2,21, 48);
	g.adicionarAresta(27,35, 48);
	g.adicionarAresta(27,10, 7);
	g.adicionarAresta(34,28, 22);
	g.adicionarAresta(29,0, 2);
	g.adicionarAresta(33,3, 44);
	g.adicionarAresta(43,12, 39);
	g.adicionarAresta(45,38, 24);
	g.adicionarAresta(38,2, 4);
	g.adicionarAresta(23,38, 13);
	g.adicionarAresta(41,42, 35);
	g.adicionarAresta(39,21, 22);
	g.adicionarAresta(37,49, 32);
	g.adicionarAresta(44,35, 12);
	g.adicionarAresta(19,16, 12);
	g.adicionarAresta(21,49, 16);
	g.adicionarAresta(16,45, 30);
	g.adicionarAresta(7,42, 20);
	g.adicionarAresta(32,31, 25);
	g.adicionarAresta(38,6, 15);
	g.adicionarAresta(4,49, 7);
	g.adicionarAresta(39,39, 31);
	g.adicionarAresta(11,28, 32);
	g.adicionarAresta(45,25, 17);
	g.adicionarAresta(7,44, 34);
	g.adicionarAresta(22,17, 35);
	g.adicionarAresta(40,35, 32);
	g.adicionarAresta(22,43, 27);
	g.adicionarAresta(43,27, 8);
	g.adicionarAresta(20,17, 16);
	g.adicionarAresta(35,21, 15);
	g.adicionarAresta(44,12, 6);
	g.adicionarAresta(25,25, 37);
	g.adicionarAresta(7,20, 12);
	g.adicionarAresta(27,30, 8);
	g.adicionarAresta(13,2, 25);
	g.adicionarAresta(0,42, 13);
	g.adicionarAresta(35,14, 8);
	g.adicionarAresta(12,9, 35);
	g.adicionarAresta(22,29, 4);
	g.adicionarAresta(40,16, 26);
	g.adicionarAresta(7,13, 38);
	g.adicionarAresta(14,40, 16);
	g.adicionarAresta(3,0, 36);
	g.adicionarAresta(17,27, 16);
	g.adicionarAresta(25,42, 20);
	g.adicionarAresta(2,44, 14);
	g.adicionarAresta(17,29, 29);
	g.adicionarAresta(25,43, 40);
	g.adicionarAresta(12,15, 22);

	g.k_best();
	
	//g.makeRandGrafo(40,60,50);
	return 0;
}