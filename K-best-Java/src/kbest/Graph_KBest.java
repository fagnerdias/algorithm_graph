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
    	int id =0;
    	while(!list.isEmpty() && total > 0) {    		
    		LinkedList<EdgeParticao> part = new LinkedList<EdgeParticao>();
    		
    		List<Integer> custo = new ArrayList<Integer>( c.keySet());
    		Collections.sort(custo);
    		part = c.get(custo.get(id));    		    		
    		saida.add(s.get(custo.get(id)));
    		list.remove(part);
    		id++;
    		total--;
    		makeParticao(part,s.get(custo.get(id-1)).getEdges());
    	}
    	List<Integer> custo = new ArrayList<Integer>( c.keySet());
		Collections.sort(custo);
//    	for (int peso : custo) {
//    		System.out.println("Peso - " + peso);
//    		PrimMinimumSpanningTree<String, EdgeParticao> min = new PrimMinimumSpanningTree<>(MSTGraph(c.get(peso)));
//    		System.out.println("AGM - " + min.getSpanningTree().toString());
//			
//		}
    	for (SpanningTree<EdgeParticao> agm : saida) {
    		System.out.println("Peso - " + agm.getWeight());
    		System.out.println("AGM - " + agm.toString());
			
		}
    	
    }
    
    public static void makeParticao(LinkedList<EdgeParticao> p, Set<EdgeParticao> agm){
    	LinkedList<EdgeParticao> p1 = new LinkedList<EdgeParticao>();    	
    	LinkedList<EdgeParticao> p2 = new LinkedList<EdgeParticao>();
    	Iterator<EdgeParticao> it = agm.iterator();
    	  while (it.hasNext()) {
    		  EdgeParticao s = it.next();    		  
    		  p1.add((EdgeParticao) s.clone());
    		  p2.add((EdgeParticao) s.clone());
    	  }
    	EdgeParticao[] part = new EdgeParticao[agm.size()];  
    	agm.toArray(part);
    	for (int i=0; i < part.length; i++) {    		
			if (part[i].isObrigatorio() == false && part[i].isProibida() == false) {
				p1.get(i).setObrigatorio(true);
				p1.get(i).setProibida(false);
				
				p2.get(i).setObrigatorio(false);
				p2.get(i).setProibida(true);
				String[] total = p.toString().replace("[", "").replace("]", "").split(", ");
				String[] mst = agm.toString().replace("[", "").replace("]", "").split(", ");
				boolean add = false;
				for (int j = 0; j < total.length; j++) {
					for (int j2 = 0; j2 < mst.length; j2++) {
						add = true;
						if(total[j].equals(mst[j2])) {
							add = false;
							break;
						}
					}
					if (add) {
						p1.add(p.get(j));
						p2.add(p.get(j));
					}
				}										        
		        
		        PrimMinimumSpanningTree<String, EdgeParticao> min = new PrimMinimumSpanningTree<>(MSTGraph(p1));
		        min.getSpanningTree().getWeight();
		        ConnectivityInspector<String, EdgeParticao> conn = new ConnectivityInspector<>(MSTGraph(p1));
		        
		        if (conn.isConnected()) {
					list.add(p1);
					s.put((int) min.getSpanningTree().getWeight(), min.getSpanningTree());
			        c.put((int) min.getSpanningTree().getWeight(), p1);
					
				}
		        		        
		        LinkedList<EdgeParticao> aux = new LinkedList<>();
		        Iterator<EdgeParticao> it2 = p2.iterator();
		    	  while (it2.hasNext()) {
		    		  EdgeParticao s = it2.next();		    		  
		    		  aux.add((EdgeParticao) s.clone());
		    	  }

		        p1 = aux;
			}
		}
    	    	
    }
    
    public static SimpleWeightedGraph<String, EdgeParticao> MSTGraph(LinkedList<EdgeParticao> p1){
    	Graph<String, EdgeParticao> g = 
    			new SimpleWeightedGraph<String, EdgeParticao>(EdgeParticao.class);
        for (EdgeParticao edgeParticao : p1) {
        	if (!edgeParticao.isProibida()) {
        		String[] source = edgeParticao.toString().replace("(", "").replace(")", "").trim().split(":");
	        	g.addVertex(source[0].trim());
	        	g.addVertex(source[1].trim());
	        	g.addEdge(source[0].trim(), source[1].trim());
	        	g.setEdgeWeight(source[0].trim(), source[1].trim(), edgeParticao.getWeight2());
			}		        	
		}
        return (SimpleWeightedGraph<String, EdgeParticao>) g;
    }
	
}
