#include <iostream>
#include "graph.h"

using namespace std;

int main(){
    Graph *g = new Graph();
    g->display();
    Node *a = new Node("a");
    Node *b = new Node("b");
    g->addNewNode(a);
    a->addAdjNode(b, 0);
    g->display();
    cout << "teste\n";
    return EXIT_SUCCESS;
}