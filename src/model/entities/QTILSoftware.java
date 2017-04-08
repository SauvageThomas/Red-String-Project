package src.model.entities;

import java.util.HashMap;
import java.util.Map;

public class QTILSoftware {

	private Map<String, SearchEngine> engines;
	
	public QTILSoftware() {
		this.engines = new HashMap<String, SearchEngine>();
	}
}
