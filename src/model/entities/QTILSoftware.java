package src.model.entities;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class QTILSoftware {

	private Map<String, SearchEngine> engines;
	
	public QTILSoftware() {
		this.engines = new HashMap<String, SearchEngine>();
		try {
			QTILConfiguration settings = new QTILConfiguration(".config");
			this.engines.put("QTIL", new QTILSearchEngine(settings));
		} catch (IOException e) {
			System.out.println("ERROR : " + e.getMessage());
			System.exit(1);
		}
		
		
	}
}
