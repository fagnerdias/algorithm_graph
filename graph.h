#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node;

class Edge{
    Node *parent;
    Node *son;
    int weight;

public:
    Edge(Node *_parent, Node *_son, int _weigth){
        parent = _parent;
        son = _son;
        weight = _weigth;
    }

    Node* getSon(){return son;}
    Node* getParent(){return parent;}
    int getWeigth(){return weight;}

};

class Node{ 
    private:   
    string name;
    bool visited;
    vector<Edge> adjNodeList;

    public:
    Node(string _name){
        name = _name;
        visited = false;
    }
    ~Node(){
        adjNodeList.clear();
    }

    string getName(){return name;}
    bool wasVisited(){return visited;}
    void setVisited(bool _visited){visited = _visited;}

// Possible error in this method.
    bool addAdjNode(Node *node, int _weigth){
        Edge *aux = new Edge(this, node, _weigth);
        adjNodeList.push_back(*aux);
    }

    vector<Edge>& getAdlNodeList(){return adjNodeList;}

    void display(){
        for(Edge e : adjNodeList){
            cout << name << "->" << e.getSon()->getName() << endl ;
        }
    }
};



class Graph{
    private:
    vector<Node*> nodeList;
    
    void clearVisited(){
        for(Node *e : nodeList){
            e->setVisited(false);
        }
    }
    public:
    void addNewNode(Node *_node){
        nodeList.push_back(_node);
    }

    Node* findNodeByName(string _name){
        for(Node *e : nodeList){
            if (e->getName() == _name)
                return e;            
        }
        return NULL;
    }

    
    Graph(){

    }

    ~Graph(){
        for(Node *e : nodeList){
            delete e;            
        }
        nodeList.clear();
    }

    void display(){
        for(Node *e : nodeList){
            e->display();
        }
    }
};

#endif