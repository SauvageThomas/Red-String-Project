package src.model.entities;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class QTILSoftware {

	private static QTILSoftware software;
	private Map<String, SearchEngine> engines;

	private QTILSoftware() {
		this.engines = new HashMap<String, SearchEngine>();
		try {
			QTILConfiguration settings = new QTILConfiguration(".config");
			this.engines.put("QTIL", new QTILSearchEngine(settings));
		} catch (IOException e) {
			System.out.println("ERROR : " + e.getMessage());
			System.exit(1);
		}
	}

	public static QTILSoftware getSoftware() {
		if (software == null)
			software = new QTILSoftware();
		return software;
	}

	public Map<String, SearchEngine> getEngines() {
		return this.engines;
	}

	public void searchByKeywords(String keywords) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
	}

	public void searchByShadeOfGray(int gray) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
	}

	public void searchByColor(int red, int green, int blue) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
	}

	public void searchByFile(String filePath) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
	}

	public boolean loginAsAdmin(String password) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		return true;
	}
}
