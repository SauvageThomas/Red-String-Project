package model.entities;

import java.util.ArrayList;
import java.util.List;

public class QTILKernel {

	private static QTILKernel instance;

	private native int update_text_descriptors(int force);
	private native int update_image_descriptors(int force);
	private native int update_sound_descriptors(int force);
	private native char[][] search_by_file(String path);
	private native String[] search_by_keyword(String[] keywords);

	private QTILKernel() {
		try{
			System.loadLibrary("qtil");
		}
		catch(UnsatisfiedLinkError e){
			NativeUtil.
		}
	}

	public static QTILKernel getInstance(){
		if (instance == null)
			instance = new QTILKernel();
		return instance;
	}

	public List<String> searchByFile(String path){
		List<String> results = new ArrayList<>();
		char[][] res = search_by_file(path);
		System.out.println(res.toString());
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

	public String[] searchByKeyword(String[] keywords){
		return search_by_keyword(keywords);
	}
}
