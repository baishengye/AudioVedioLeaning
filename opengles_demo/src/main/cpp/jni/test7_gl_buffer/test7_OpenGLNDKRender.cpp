//
// Created by chenchao on 2021/8/10.
//

#include "../../util/self/NDKRender.h"
#include <jni.h>

NDKRender test7_m_ndkRender;

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test7_1gl_1buffer_GLBufferRender_openGLResize(JNIEnv *env,
                                                                           jclass clazz, jint width,
                                                                           jint height) {
    test7_m_ndkRender.ResizeGL(width,height);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test7_1gl_1buffer_GLBufferRender_openGLInit(JNIEnv *env, jclass clazz,
                                                                         jobject asset_manager) {
    AAssetManager *astManager = AAssetManager_fromJava (env, asset_manager);
    if (NULL != astManager){
        test7_m_ndkRender.SetupAssetManager(astManager);
    }

    test7_m_ndkRender.InitGL();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test7_1gl_1buffer_GLBufferRender_openGLDraw(JNIEnv *env,
                                                                         jclass clazz) {
    test7_m_ndkRender.PaintGL();
}