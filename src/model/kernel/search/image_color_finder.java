/*
 ============================================================================
 Name        : image_color_finder.java
 Author      : Pierre
 Description : Find image thanks to a color
 ============================================================================
 */
package src.model.kernel.search;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import com.sun.prism.paint.Color;

public class image_color_finder {
	
	public static int errorMargin = 10;
	public static String nameFile = "index_image";

	public static List<String> search_image_by_color(Color color){
		int red = (int)color.getRed();
		int green = (int)color.getGreen();
		int blue = (int)color.getBlue();
		src.view.tools.Configuration config = src.view.tools.Configuration.INSTANCE;
		String path = config.getDescriptorPath();
		File file = new File(path + nameFile);
		
		if(red == green && green == blue)
			return search_image_black_white(red, file);
		return search_image_color(red, green, blue, file);
	}

	
	private static List<String> search_image_color(int red, int green, int blue, File file) {
		
		List<String> result = new ArrayList<String>();
		try {
			InputStream ips=new FileInputStream(file); 
			InputStreamReader ipsr=new InputStreamReader(ips);
			BufferedReader br=new BufferedReader(ipsr);
			String nameFile;
			String value;
			while ((nameFile=br.readLine())!=null){
				br.readLine();
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
				if(test)
					result.add(nameFile);
			}
			br.close(); 
		} catch (IOException e) {
			e.printStackTrace();
		};
		return result;
	}

	
	private static List<String> search_image_black_white(int color, File file) {
		List<String> result = new ArrayList<String>();
		try {
			InputStream ips=new FileInputStream(file); 
			InputStreamReader ipsr=new InputStreamReader(ips);
			BufferedReader br=new BufferedReader(ipsr);
			String nameFile;
			String value;
			while ((nameFile=br.readLine())!=null){
				br.readLine();
				value = br.readLine();
				br.readLine();
				if ( value.length() >= 4)
					continue;
				
				nameFile = nameFile.substring(1);
				value = value.trim();
				int colorTmp = Integer.valueOf(value);
				boolean test = (colorTmp >= color - errorMargin && colorTmp <= color + errorMargin  );
				if(test)
					result.add(nameFile);
			}
			br.close(); 
		} catch (IOException e) {
			e.printStackTrace();
		};
		return result;
	}

}