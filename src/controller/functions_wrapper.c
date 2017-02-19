
#include <jni.h>
#include "../../jni/src_Controller_Controller.h"
#include "functions.h"

JNIEXPORT jint JNICALL
Java_src_controller_Controller_update_1text_1descriptors (JNIEnv *env, jobject obj, jint force){
	return update_text_descriptor(force);
}

JNIEXPORT jint JNICALL
Java_src_controller_Controller_update_1image_1descriptors (JNIEnv *env, jobject obj, jint force){
	return update_image_descriptor(force);
}


JNIEXPORT jint JNICALL
Java_src_controller_Controller_update_1sound_1descriptors (JNIEnv *env, jobject obj, jint force){
	return update_sound_descriptor(force);
}


JNIEXPORT jobjectArray JNICALL
Java_src_controller_Controller_search_1by_1file (JNIEnv *env, jobject obj, jstring path){
	return search_by_file(path);
}


JNIEXPORT jobjectArray JNICALL
Java_src_controller_Controller_search_1by_1keyword (JNIEnv *env, jobject obj, jobjectArray keywords){
	return search_by_keywords(keywords);
}


JNIEXPORT jint JNICALL
Java_src_controller_Controller_login (JNIEnv *env, jobject obj, jstring password){
	return login(password);
}
