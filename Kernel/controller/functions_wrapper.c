
#include <jni.h>
#include "model_entities_QTILKernel.h"
#include "functions.h"

JNIEXPORT jint JNICALL Java_model_entities_QTILKernel_update_1text_1descriptors (JNIEnv *env, jobject obj, jint force){
	return update_text_descriptor(force);
}

JNIEXPORT jint JNICALL Java_model_entities_QTILKernel_update_1image_1descriptors (JNIEnv *env, jobject obj, jint force){
	return update_image_descriptor(force);
}

JNIEXPORT jint JNICALL Java_model_entities_QTILKernel_update_1sound_1descriptors (JNIEnv *env, jobject obj, jint force){
	return update_sound_descriptor(force);
}


JNIEXPORT jobjectArray JNICALL Java_model_entities_QTILKernel_search_1by_1file (JNIEnv *env, jobject obj, jstring filepath){
	const char* path = (*env)->GetStringUTFChars(env, filepath, 0);
	char** res = search_data(path);

	int count = (atoi(res[0])) > 0 ? atoi(res[0]) + 1 : 1;
	jstring str;
	jobjectArray result = 0;
	result = (*env)->NewObjectArray(env, count, (*env)->FindClass(env, "java/lang/String"), 0);

	for(int i = 0; i < count; i++){
		str = (*env)->NewStringUTF(env, res[i]);
		(*env)->SetObjectArrayElement(env, result, i, str);
	}
	(*env)->ReleaseStringUTFChars(env, filepath, path);
	return result;
}
