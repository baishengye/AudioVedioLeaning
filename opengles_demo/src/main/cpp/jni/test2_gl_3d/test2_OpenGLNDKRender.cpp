//
// Created by baishengye on 2023-11-09.
//

#include <jni.h>
#include "../../util/self/NDKRenderDef.h"

#ifdef __cplusplus
extern "C" {
#endif

float test2_m_angle = 0.0f;

void test2_drawCube() {
    //背面不绘制
    glCullFace(GL_BACK);

    PointFloat7 cubeVert[] = {
            {-0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},

            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},

            {-0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f,  0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f,  0.5f, 0.0,0.0,1.0,1.0},
            {-0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},

            {0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {0.5f,  0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},

            {-0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},

            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0}
    };


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof(PointFloat7),cubeVert);
    glColorPointer(4,GL_FLOAT,sizeof(PointFloat7),&cubeVert[0].r);

    test2_m_angle += 0.01f;

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),test2_m_angle,glm::vec3(0.5f, 0.5f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.4f, 0.5) );
    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLES,0,36);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

#ifdef __cplusplus
}
#endif

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test2_1gl_13d_GL3DRender_openGLDraw(JNIEnv *env,
                                                                       jclass clazz) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    test2_drawCube();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test2_1gl_13d_GL3DRender_openGLInit(JNIEnv *env,
                                                                       jclass clazz) {

    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test2_1gl_13d_GL3DRender_openGLResize(JNIEnv *env,
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