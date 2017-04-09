package src.view.console;

import java.util.Map;

import src.controller.ControllerSoftware;
import src.model.entities.QTILSoftware;
import src.model.entities.SearchEngine;
import src.model.entities.Setting;

public class ViewSettings extends View{

	private ControllerSoftware controllerSoftware;
	
	public ViewSettings(ControllerSoftware controllerSoftware) {
		this.controllerSoftware = controllerSoftware;
	}
	
	@Override
	public void showView() {
		Map<String, SearchEngine> engines = this.controllerSoftware.getEngines();
		for(String engineName : engines.keySet()){
			System.out.println("\n--------------------------------------------------");
			System.out.println(engineName + " settings :");
			Map<String, Setting> settings = engines.get(engineName).getSettings();
			for (String settingName : settings.keySet()){
				System.out.println("  -> " + settingName + " = " + settings.get(settingName).getValue());
			}
		}
		System.out.println("\n\n");
	}

}
