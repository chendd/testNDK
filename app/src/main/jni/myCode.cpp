//
// Created by admin on 2016/3/31.
//
#include "com_example_admin_testndk_Load.h"
#include <string.h>

JNIEXPORT jint JNICALL Java_com_example_admin_testndk_Load_addInt (JNIEnv *, jobject, jint a, jint b) {
    return a + b;
}

JNIEXPORT jdouble JNICALL Java_com_example_admin_testndk_Load_mulDouble (JNIEnv *, jobject, jdouble a, jdouble b) {
    return a - b;
}

JNIEXPORT jintArray JNICALL Java_com_example_admin_testndk_Load_intArray (JNIEnv * env, jobject, jintArray a){
    //输入整数数组，将其每个元素加10后输出
    //输入值为a，输出值为b
    int N = env->GetArrayLength(a);
    jint *pA = env->GetIntArrayElements(a,NULL);
    jintArray b = env->NewIntArray(N);
    jint *pB = env->GetIntArrayElements(b,NULL);
    //env->SetIntArrayRegion(b,0,N,pA);
    for (int i = 0 ; i < N; i++) pB[i] = pA[i] + 10;
    env->ReleaseIntArrayElements(a,pA,NULL);
    env->ReleaseIntArrayElements(b,pB,NULL);
    return b;
}

JNIEXPORT jdoubleArray JNICALL Java_com_example_admin_testndk_Load_doubleArray (JNIEnv * env, jobject, jdoubleArray a){
    int N = env->GetArrayLength(a);
    jdouble *pA = env->GetDoubleArrayElements(a,NULL);
    jdoubleArray b = env->NewDoubleArray(N);
    jdouble *pB = env->GetDoubleArrayElements(b,NULL);
    for (int i = 0 ; i < N; i++) pB[i] = pA[i] * 2;
    env->ReleaseDoubleArrayElements(a,pA,NULL);
    env->ReleaseDoubleArrayElements(b,pB,NULL);
    return b;
}

JNIEXPORT jobjectArray JNICALL Java_com_example_admin_testndk_Load_stringArray (JNIEnv * env, jobject, jobjectArray a){
    //输入字符串数组，颠倒顺序后输出
    //输入值为a，输出值为b
    int N = env->GetArrayLength(a);
    jobjectArray b = env->NewObjectArray(N,env->FindClass("java/lang/String"),env->NewStringUTF(""));
    for (int i = 0; i < N; ++i) {
        jstring ai = (jstring)env->GetObjectArrayElement(a,i);
        env->SetObjectArrayElement(b,N-1-i,ai);
        env->DeleteLocalRef(ai);
    }
    return b;
}

char * JstringToCstr(JNIEnv * env, jstring jstr) { //jstring转换为C++的字符数组指针
    char * pChar = NULL;
    jclass classString = env->FindClass("java/lang/String");
    jstring code = env->NewStringUTF("GB2312");
    jmethodID id = env->GetMethodID(classString, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray arr = (jbyteArray)env->CallObjectMethod(jstr, id, code);
    jsize size = env->GetArrayLength(arr);
    jbyte * bt = env->GetByteArrayElements(arr, JNI_FALSE);
    if(size > 0) {
        pChar = (char*)malloc(size + 1);
        memcpy(pChar, bt, size);
        pChar[size] = 0;
    }
    env->ReleaseByteArrayElements(arr, bt, 0);
    return pChar;
}

JNIEXPORT jstring JNICALL Java_com_example_admin_testndk_Load_addString (JNIEnv * env, jobject, jstring a, jstring b){
    char *pA = JstringToCstr(env,a);
    char *pB = JstringToCstr(env,b);
    return env->NewStringUTF(strcat(pA,pB));
}