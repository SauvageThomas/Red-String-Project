/*
 ============================================================================
 Name        : image_color_finder.java
 Author      : Pierre
 Description : Find image thanks to a color
 ============================================================================
 */

package model.entities;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ImageColorFinder {

	private String imageIndexPath;//Renseigne l'adresse à laquelle l'index image va être généré

	/*Constructeur qui permet d'initialiser l'adresse de l'index image*/
	public ImageColorFinder(String imageIndexPath) {
		this.imageIndexPath = imageIndexPath;
	}

	/*Renvoie une liste de String, chaque String correspond au nom d'un fichier image en RGB qui est résultat de la recherche
		La recherche est basée sur une valeur de rouge, une de verte, une de bleue et une marge d'erreur
		Tous les résultats trouvés auront une valeur de rouge comprise entre le paramètre rouge - la marge et le paramètre rouge + la marge
		De même pour chaque couleur
	*/
	public List<String> searchImageColor(int red, int green, int blue, int margin) {
		File file = new File(this.imageIndexPath);
		Map<String, Integer> resultTmp = new HashMap<String, Integer>();
		int rank;
		try {
			InputStream ips=new FileInputStream(file); 
			InputStreamReader ipsr=new InputStreamReader(ips);
			BufferedReader br=new BufferedReader(ipsr);
			String nameFile;
			String value;
			while ((nameFile=br.readLine())!=null){
				rank=0;
				value = br.readLine();
				br.readLine();
				if ( value.length() <= 4)
					continue;
				nameFile = nameFile.substring(1);
				String[] values = value.split(" ");
				int redTmp = Integer.valueOf(values[0]);
				int greenTmp = Integer.valueOf(values[1]);
				int blueTmp = Integer.valueOf(values[2]);
				boolean test = (redTmp >= red - margin && redTmp <= red + margin  );
				if(test)
					test = (greenTmp >= green - margin && greenTmp <= green + margin  );
				if(test)
					test = (blueTmp >= blue - margin && blueTmp <= blue + margin  );
				if(test){
					nameFile = nameFile.substring(0, nameFile.length()-3);
					nameFile = nameFile +"jpg";
					rank=Math.abs(redTmp-red) + Math.abs(greenTmp-green) + Math.abs(blueTmp-blue);
					resultTmp.put(nameFile, rank);
				}

			}
			br.close(); 
		} catch (IOException e) {
			e.printStackTrace();
		};
		return hashMapToArrayList(resultTmp);
	}
	/* Même principe que la méthode du dessus mais pour les images en nuances de gris 
		Les paramètres d'entré sont le niveau de gris et la marge d'erreur
	*/
	public List<String> searchByShadeOfGrey(int color, int margin) {
		File file = new File(this.imageIndexPath);
		Map<String, Integer> resultTmp = new HashMap<String, Integer>();
		int rank;
		try {
			InputStream ips=new FileInputStream(file); 
			InputStreamReader ipsr=new InputStreamReader(ips);
			BufferedReader br=new BufferedReader(ipsr);
			String nameFile;
			String value;
			while ((nameFile=br.readLine())!=null){
				value = br.readLine();
				br.readLine();
				if ( value.length() >= 4)
					continue;

				nameFile = nameFile.substring(1);
				value = value.trim();
				int colorTmp = Integer.valueOf(value);
				boolean test = (colorTmp >= color - margin && colorTmp <= color + margin  );
				if(test){
					nameFile = nameFile.substring(0, nameFile.length()-3);
					nameFile = nameFile +"bmp";
					rank=Math.abs(colorTmp-color);
					resultTmp.put(nameFile, rank);
				}
			}
			br.close(); 
		} catch (IOException e) {
			e.printStackTrace();
		};
		return hashMapToArrayList(resultTmp);
	}
	

	/*Cette méthode convertit une Map (paramètre d'entrée) en une liste triée (ArrayList en sortie)
		Le fait que la liste soit triée en sortie permet au moteur d'afficher les résultats par ordre de pertinance
	*/
	private static  ArrayList<String> hashMapToArrayList(Map<String, Integer> map){
		ArrayList<String> result = new ArrayList<String>();
		int min;
		String tmp = "";
		while(map.size()!=0){
			for(String str : map.keySet()){
				min=map.get(str);
				tmp = str;
				for(String str2 : map.keySet()){
					if(min > map.get(str2)){
						min=map.get(str2);
						tmp =str2;
					}
				}
			}
			map.remove(tmp);
			result.add(tmp);
		}
		return result;
	}

}
