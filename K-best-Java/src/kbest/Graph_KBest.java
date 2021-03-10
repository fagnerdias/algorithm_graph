package kbest;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import org.jgrapht.Graph;
import org.jgrapht.alg.connectivity.ConnectivityInspector;
import org.jgrapht.alg.interfaces.SpanningTreeAlgorithm.SpanningTree;
import org.jgrapht.alg.spanning.PrimMinimumSpanningTree;
import org.jgrapht.graph.SimpleWeightedGraph;

public class Graph_KBest {
	
	int obrigatoria = -1;
	
	static int total = 5;
	
	static LinkedList<EdgeParticao> particao = new LinkedList<EdgeParticao>();
	static ArrayList<LinkedList<EdgeParticao>> list = new ArrayList<LinkedList<EdgeParticao>>();
	
	static HashMap<Integer, LinkedList<EdgeParticao>> c = 
			new HashMap<Integer, LinkedList<EdgeParticao>>();
	
	static HashMap<Integer, SpanningTree<EdgeParticao>> s = 
			new HashMap<Integer, SpanningTree<EdgeParticao>>();
	    	
	static ArrayList<SpanningTree<EdgeParticao>> saida = 
			new ArrayList<SpanningTree<EdgeParticao>>();
	
	
    public static void main(String[] args)
    {
    	Graph<String, EdgeParticao> directedGraph = 
    			new SimpleWeightedGraph<String, EdgeParticao>(EdgeParticao.class);    	  	   
    	    	    
    	
    	
    	directedGraph.addVertex("1");
    	directedGraph.addVertex("2");
    	directedGraph.addVertex("3");
    	directedGraph.addVertex("4");
    	directedGraph.addVertex("5");
    	    	
    	directedGraph.addEdge("1", "2");
    	directedGraph.setEdgeWeight("1", "2", 20);
    	directedGraph.addEdge("1", "3");
    	directedGraph.setEdgeWeight("1", "3", 22);
    	directedGraph.addEdge("1", "4");
    	directedGraph.setEdgeWeight("1", "4", 15);
    	directedGraph.addEdge("1", "5");
    	directedGraph.setEdgeWeight("1", "5", 28);
    	directedGraph.addEdge("2", "5");
    	directedGraph.setEdgeWeight("2", "5", 26);
    	directedGraph.addEdge("2", "3");
    	directedGraph.setEdgeWeight("2", "3", 13);
    	directedGraph.addEdge("2", "4");
    	directedGraph.setEdgeWeight("2", "4", 19);
    	directedGraph.addEdge("3", "4");
    	directedGraph.setEdgeWeight("3", "4", 11);
    	directedGraph.addEdge("3", "5");
    	directedGraph.setEdgeWeight("3", "5", 30);
    	directedGraph.addEdge("4", "5");
    	directedGraph.setEdgeWeight("4", "5", 12);
    	
    	particao.addAll(directedGraph.edgeSet());
    	    	
    	list.add(particao);
    	PrimMinimumSpanningTree<String, EdgeParticao> minimal = new PrimMinimumSpanningTree<>(directedGraph);    	
    	
    	System.out.println("peso da AGM: " + minimal.getSpanningTree().getWeight());
    	c.put((int)minimal.getSpanningTree().getWeight(), particao);
    	s.put((int)minimal.getSpanningTree().getWeight(), minimal.getSpanningTree());
    	
    	while(!list.isEmpty() ) {    		
    		LinkedList<EdgeParticao> part = new LinkedList<EdgeParticao>();    		
    		List<Integer> custo = new ArrayList<Integer>( c.keySet());
    		if (custo.isEmpty()) {
				break;
			}
    		Collections.sort(custo);
    		part = c.get(custo.get(0));    		    		
    		saida.add(s.get(custo.get(0)));
    		list.remove(part);
    		c.remove(custo.get(0));
    		s.remove(custo.get(0));    		
    		makeParticao(part);
    	}
    	List<Integer> custo = new ArrayList<Integer>( c.keySet());
		Collections.sort(custo);
    	for (SpanningTree<EdgeParticao> agm : saida) {
    		System.out.println("Peso - " + agm.getWeight());
    		System.out.println("AGM - " + agm.toString());
			
		}
    	
    }
    
    public static void makeParticao(LinkedList<EdgeParticao> p){
    	LinkedList<EdgeParticao> p1 = new LinkedList<EdgeParticao>();    	
    	LinkedList<EdgeParticao> p2 = new LinkedList<EdgeParticao>();
    	Iterator<EdgeParticao> it = p.iterator();
    	  while (it.hasNext()) {
    		  EdgeParticao s = it.next();    		  
    		  p1.add((EdgeParticao) s.clone());
    		  p2.add((EdgeParticao) s.clone());
    	  }

    	for (int i=0; i < p.size(); i++) {    		
			if (p.get(i).isObrigatorio() == false && p.get(i).isProibida() == false) {
				p1.get(i).setProibida(true);											
				p2.get(i).setObrigatorio(true);
				
		        PrimMinimumSpanningTree<String, EdgeParticao> min = new PrimMinimumSpanningTree<>(MSTGraph(p1));
		        min.getSpanningTree().getWeight();
		        LinkedList<EdgeParticao> t = new LinkedList<EdgeParticao>();
		        for (EdgeParticao edgeParticao : min.getSpanningTree().getEdges()) {
					t.add(edgeParticao);
				}

		        ConnectivityInspector<String, EdgeParticao> conn = new ConnectivityInspector<>(MSTGraph(t));		        
		        if (conn.isConnected()) {
					list.add(p1);
					s.put((int) min.getSpanningTree().getWeight(), min.getSpanningTree());
			        c.put((int) min.getSpanningTree().getWeight(), p1);					
				}		        		        
		        p1.get(i).setProibida(false);
		        p1.get(i).setObrigatorio(true);
			}
		}
    	    	
    }
    
    public static SimpleWeightedGraph<String, EdgeParticao> MSTGraph(LinkedList<EdgeParticao> p1){
    	Graph<String, EdgeParticao> g = 
    			new SimpleWeightedGraph<String, EdgeParticao>(EdgeParticao.class);
        for (EdgeParticao edgeParticao : p1) {
        	String[] source = edgeParticao.toString().replace("(", "").replace(")", "").trim().split(":");
        	g.addVertex(source[0].trim());
        	g.addVertex(source[1].trim());
        	if (!edgeParticao.isProibida()) {        		
	        	g.addVertex(source[0].trim());
	        	g.addVertex(source[1].trim());
	        	g.addEdge(source[0].trim(), source[1].trim());
	        	g.setEdgeWeight(source[0].trim(), source[1].trim(), edgeParticao.getWeight2());
			}		        	
		}
        return (SimpleWeightedGraph<String, EdgeParticao>) g;
    }
	
}
