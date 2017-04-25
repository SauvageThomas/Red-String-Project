package model.entities;

import java.util.ArrayList;
import java.util.List;

public class QTILKernel {

	private static QTILKernel instance;

	private native int update_text_descriptors(int force);
	private native int update_image_descriptors(int force);
	private native int update_sound_descriptors(int force);
	private native String[] search_by_file(String path);

	private QTILKernel() {
		System.loadLibrary("qtil");
	}

	public static QTILKernel getInstance(){
		if (instance == null)
			instance = new QTILKernel();
		return instance;
	}

	public List<String> searchByFile(String path){
		List<String> results = new ArrayList<>();
		String[] res = (String[]) search_by_file(path);

		for (String str : res){
			results.add(str.replace("\n", ""));
		}

		return results;
	}

	public int updateTextDescriptors(int force){
		return update_text_descriptors(force);
	}

	public int updateImageDescriptors(int force){
		return update_image_descriptors(force);
	}

	public int updateSoundDescriptors(int force){
		return update_sound_descriptors(force);
	}
}
