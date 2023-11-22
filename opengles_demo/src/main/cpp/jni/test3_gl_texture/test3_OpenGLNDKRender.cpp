//
// Created by baishengye on 2023-11-09.
//
#include <jni.h>

#include "../../util/self/NDKAndroidLog.h"
#include "../../util/self/NDKRenderDef.h"
#include "../../util/self/NDKImage.h"

#ifdef __cplusplus
extern "C" {
#endif

float test3_m_angle = 0.0f;

GLuint test3_m_texID;

void test3_drawTexture() {
    //背面不绘制
    glCullFace(GL_BACK);

    PointFloat5 planVertices[] =
            {
                    { -1.0f, -1.0f, 1.0f,    0,  1 },
                    {  -1.0f,1.0f, 1.0f,   1,  1 },
                    {  1.0f,-1.0f, 1.0f,    0,  0 },
                    {  1.0f, 1.0f, 1.0f,    1,  0 },
            };

    glBindTexture(GL_TEXTURE_2D,test3_m_texID);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof(PointFloat5),planVertices);
    glTexCoordPointer(2,GL_FLOAT,sizeof(PointFloat5),&planVertices[0].u);

    test3_m_angle += 0.005f;

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),test3_m_angle,glm::vec3(0.0f, 0.0f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.7f, 0.7f, 0.5) );

    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

/**
 * 只能读取png文件，无法读取jpg*/
GLuint test3_createOpenGLTexture(NDKImage* pImg)
{
    if(pImg == NULL){
        return -1;
    }

    GLuint textureID;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);//产生纹理索引
    glBindTexture(GL_TEXTURE_2D,textureID);//绑定纹理索引，之后的操作都针对当前纹理索引

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//指当纹理图象被使用到一个大于它的形状上时
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//指当纹理图象被使用到一个小于或等于它的形状上时
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImg->GetWidth(),pImg->GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,pImg->GetData());//指定参数，生成纹理

    return textureID;
}

#ifdef __cplusplus
}
#endif

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test3_1gl_1texture_GLTextureRender_openGLDraw(JNIEnv *env,
                                                                       jclass clazz) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    test3_drawTexture();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test3_1gl_1texture_GLTextureRender_openGLInit(JNIEnv *env,
                                                                       jclass clazz) {

    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test3_1gl_1texture_GLTextureRender_openGLResize(JNIEnv *env,
                                                                         jclass clazz,
                                                                         jint width,
                                                                         jint height) {
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(-1,1,-1,1,0.1,1000.0);
    //glFrustumf(-1,1,-1,1,0.1,1000.0);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_baishengye_opengles_1demo_test3_1gl_1texture_GLTextureRender_jniReadAssetFile(JNIEnv *env,
                                                                                       jclass clazz,
                                                                                       jobject asset_manager,
                                                                                       jstring file_name) {
    AAssetManager *mAssetManager = AAssetManager_fromJava (env, asset_manager);
    if (NULL == mAssetManager){
        LOGF("assetManager is NULL");
        return -1;
    }
    const char *fileName = env->GetStringUTFChars(file_name, 0);
    if (NULL == fileName){
        LOGF("fileName is NULL");
        return -1;
    }
    LOGD ("FileName is %s", fileName);
    AAsset *asset = AAssetManager_open (mAssetManager, fileName, AASSET_MODE_UNKNOWN);
    if (NULL == asset){
        LOGF("asset is NULL");
        return -1;
    }
    off_t bufferSize = AAsset_getLength(asset);
    LOGD("buffer size is %ld", bufferSize);

    unsigned char *imgBuff = (unsigned char *)malloc(bufferSize + 1);
    if (NULL == imgBuff){
        LOGF("imgBuff alloc failed");
        return -1;
    }
    memset(imgBuff, 0, bufferSize + 1);
    int readLen = AAsset_read(asset, imgBuff, bufferSize);
    LOGD("Picture read: %d", readLen);

    NDKImage* glImage = new NDKImage();
    glImage->ReadFromBuffer(imgBuff,readLen);
    test3_m_texID = test3_createOpenGLTexture(glImage);
    LOGD("test3_m_texID : %d", test3_m_texID);

    delete glImage;

    if (imgBuff){
        free(imgBuff);
        imgBuff = NULL;
    }

    AAsset_close(asset);
    env->ReleaseStringUTFChars(file_name, fileName);

    return 0;
}