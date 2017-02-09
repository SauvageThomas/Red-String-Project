
#include <jni.h>
#include "../../jni/src_Controller_Controller.h"
#include "functions.h"

JNIEXPORT void JNICALL 
Java_src_Controller_Controller_search_1by_1file (JNIEnv *env, jobject obj, jobject config){
	search_by_file();
}

JNIEXPORT void JNICALL
Java_src_Controller_Controller_update_1descriptors (JNIEnv *env, jobject obj, jobject config){
	//update_descriptors(config);
}

JNIEXPORT void JNICALL 
Java_src_Controller_Controller_error_1config_1file (JNIEnv *env, jobject obj){
	error_config_file();                              
}

JNIEXPORT void JNICALL
Java_src_Controller_Controller_search_1by_1keyword (JNIEnv *env, jobject obj, jstring keyword){
	search_by_keyword(keyword);
}

JNIEXPORT void JNICALL 
Java_src_Controller_Controller_modif_1config (JNIEnv *env, jobject obj){
	modif_config();
}

JNIEXPORT void JNICALL
Java_src_Controller_Controller_generate_1all_1descriptors (JNIEnv *env, jobject obj, jobject config){
	//generate_all_descriptors(config);
}

JNIEXPORT void JNICALL 
Java_src_Controller_Controller_reset_1config (JNIEnv *env, jobject obj){
	reset_config();
}

JNIEXPORT jobject JNICALL
Java_src_Controller_Controller_load_1config (JNIEnv *env, jobject obj){
	//return load_config();
}

JNIEXPORT void JNICALL
Java_src_Controller_Controller_change_1password (JNIEnv *env, jobject obj){
	change_password();
}

JNIEXPORT jint JNICALL 
Java_src_Controller_Controller_login (JNIEnv *env, jobject obj){
	return login();
}
