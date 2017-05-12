package model.entities;

import java.util.ArrayList;
import java.util.List;

public class QTILKernel {

	// Singleton
	private static QTILKernel instance;

	// génère le descripteur de fichier textes + l'index de mots clés (Noyau C)
	private native int update_text_descriptors(int force);
	// génère le descripteur de fichier images + l'index de couleurs (Noyau C)
	private native int update_image_descriptors(int force);
	// génère le descripteur de fichier sons (Noyau C)
	private native int update_sound_descriptors(int force);
	// recherche les résultats d'une recherche par fichiers (textes, images ou sons) (Noyau C)
	private native String[] search_by_file(String path);

	private QTILKernel() {
		// charge la librairie libqtil.so
		System.loadLibrary("qtil");
	}

	// Retourne l'instance
	public static QTILKernel getInstance(){
		if (instance == null)
			instance = new QTILKernel();
		return instance;
	}

	// WRAPPER d'appel natif
	public List<String> searchByFile(String path){
		List<String> results = new ArrayList<>();
		String[] res = (String[]) search_by_file(path);

		for (String str : res){
			results.add(str.replace("\n", ""));
		}

		return results;
	}

	// WRAPPER d'appel natif
	public int updateTextDescriptors(int force){
		return update_text_descriptors(force);
	}

	// WRAPPER d'appel natif
	public int updateImageDescriptors(int force){
		return update_image_descriptors(force);
	}

	// WRAPPER d'appel natif
	public int updateSoundDescriptors(int force){
		return update_sound_descriptors(force);
	}
}
