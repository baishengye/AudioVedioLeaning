#include <jni.h>
#include "../../util/self/NDKRenderDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * 绘制四边形*/
void test1_drawQuadrangle() {
    glFrontFace(GL_CW);//表示将正面朝向设置为逆时针方向。这通常用于在绘制三角形时，使其按照逆时针的顺序进行面部着色
    PointFloat7 vertexQuadrangle[] = {
            {-0.5, 0.1, -0.1, 1.0, 0.0, 0.0, 1.0},
            {-0.5, 0.9, -0.1, 0.0, 1.0, 0.0, 1.0},
            {0.5,  0.1, -0.1, 0.0, 0.0, 1.0, 1.0},
            {0.5,  0.9, -0.1, 1.0, 0.0, 1.0, 1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(PointFloat7), &vertexQuadrangle[0].x);
    glColorPointer(4, GL_FLOAT, sizeof(PointFloat7), &vertexQuadrangle[0].r);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

/**
 * 绘制三角形*/
void test1_drawTriangle() {
    glFrontFace(GL_CW);
    PointFloat7 vertexTriangle[] = {
            {-0.5, -0.1, -0.1, 1.0, 0.0, 0.0, 1.0},
            {-0.5, -0.9, -0.1, 0.0, 1.0, 0.0, 1.0},
            {0.5,  -0.1, -0.1, 0.0, 0.0, 1.0, 1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(PointFloat7), &vertexTriangle[0].x);
    glColorPointer(4, GL_FLOAT, sizeof(PointFloat7), &vertexTriangle[0].r);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

#ifdef __cplusplus
}
#endif

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test1_1gl_12d_GL2DRender_openGLDraw(JNIEnv *env,
                                                                                      jclass clazz) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    test1_drawQuadrangle();
    test1_drawTriangle();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test1_1gl_12d_GL2DRender_openGLInit(JNIEnv *env,
                                                                                      jclass clazz) {
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test1_1gl_12d_GL2DRender_openGLResize(JNIEnv *env,
                                                                                        jclass clazz,
                                                                                        jint width,
                                                                                        jint height) {
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(-1,1,-1,1,0.1,1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}