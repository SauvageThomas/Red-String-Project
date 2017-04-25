/*
 ============================================================================
 Name        : image_color_finder.java
 Author      : Pierre
 Description : Find image thanks to a color
 ============================================================================
 */

package model.entities.qtil;

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

	public static int errorMargin = 20;
	public static String nameFile = "../assets/engines/QTIL/descriptors/image_index";

	public static List<String> searchImageColor(int red, int green, int blue) {
		//Configuration config = Configuration.INSTANCE;
		//String path = config.getDescriptorPath();
		File file = new File(nameFile);
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
				boolean test = (redTmp >= red - errorMargin && redTmp <= red + errorMargin  );
				if(test)
					test = (greenTmp >= green - errorMargin && greenTmp <= green + errorMargin  );
				if(test)
					test = (blueTmp >= blue - errorMargin && blueTmp <= blue + errorMargin  );
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

	public static List<String> searchByShadeOfGrey(int color) {
		/*Configuration config = Configuration.INSTANCE;
		String path = config.getDescriptorPath();*/
		File file = new File(nameFile);
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
				boolean test = (colorTmp >= color - errorMargin && colorTmp <= color + errorMargin  );
				if(test){
					nameFile = nameFile.substring(0, nameFile.length()-3);
					nameFile = nameFile +"jpg";
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
