//
// Created by chenchao on 2021/8/10.
//

#include "../../util/self/NDKRender.h"

NDKRender test6_m_ndkRender;

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test6_1gl_1oop_GLOOPRender_openGLResize(JNIEnv *env,
                                                                           jclass clazz, jint width,
                                                                           jint height) {
    test6_m_ndkRender.ResizeGL(width,height);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test6_1gl_1oop_GLOOPRender_openGLInit(JNIEnv *env, jclass clazz,
                                                                         jobject asset_manager) {
    AAssetManager *astManager = AAssetManager_fromJava (env, asset_manager);
    if (NULL != astManager){
        test6_m_ndkRender.SetupAssetManager(astManager);
    }

    test6_m_ndkRender.InitGL();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test6_1gl_1oop_GLOOPRender_openGLDraw(JNIEnv *env,
                                                                         jclass clazz) {
    test6_m_ndkRender.PaintGL();
}