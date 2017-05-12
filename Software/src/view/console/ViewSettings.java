package view.console;

import controller.ControllerSoftware;
import model.entities.Settings;

public class ViewSettings extends View{

	private ControllerSoftware controllerSoftware;
	
	public ViewSettings(ControllerSoftware controllerSoftware) {
		this.controllerSoftware = controllerSoftware;
	}
	
	@Override
	public void showView() {
		// parcours chaque type de parametre (Globaux + 1 par moteur de recherche)
		for(Settings settings : this.controllerSoftware.getAllSettings()){
			System.out.println("\n--------------------------------------------------");
			System.out.println(settings.getName() + " settings :");
			// Pour chaque type de parametre, on affiche tous les champs
			for (String settingName : settings.getSettings().keySet()){
				System.out.println("  -> " + settingName + " = " + settings.getSettings().get(settingName).getValue());
			}
		}
		System.out.println("\n\n");
	}

}
