package kbest;

import org.jgrapht.graph.DefaultWeightedEdge;

public class EdgeParticao extends DefaultWeightedEdge{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	boolean obrigatorio;
	boolean proibida;
	
	
		

	public boolean isObrigatorio() {
		return obrigatorio;
	}

	public void setObrigatorio(boolean obrigatorio) {
		this.obrigatorio = obrigatorio;
	}

	public boolean isProibida() {
		return proibida;
	}

	public void setProibida(boolean proibida) {
		this.proibida = proibida;
	}
	
	public double getWeight2() {
		return this.getWeight();
	}
	
	public Object getSource2() {
		return this.getSource();
	}
	
	public Object getTarget2() {
		return this.getTarget();
	}
	
}
