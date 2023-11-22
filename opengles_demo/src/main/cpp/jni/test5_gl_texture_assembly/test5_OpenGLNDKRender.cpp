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

float test5_m_angle = 0.0f;

GLuint test5_m_texID[6];

void test5_drawAssemblyTexture() {

    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    PointFloat5 planVertices[] =
            {
                    { -1.0f, -1.0f, 1.0f,    0,  0 },
                    {  -1.0f,1.0f, 1.0f,   0,  1 },
                    {  1.0f,-1.0f, 1.0f,    1,  0 },
                    {  1.0f, 1.0f, 1.0f,    1,  1 },
            };



    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,test5_m_texID[3]);


    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,test5_m_texID[5]);



    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PointFloat5),planVertices);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glTexCoordPointer(2,GL_FLOAT,sizeof(PointFloat5),&planVertices[0].u);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE1);
    glTexCoordPointer(2,GL_FLOAT,sizeof(PointFloat5),&planVertices[0].u);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);


    //test5_m_angle += 0.01f;

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),test5_m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.4f, 0.4f, 0.5) );

    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


/**
 * 只能读取png文件，无法读取jpg*/
GLuint createOpenGLTexture(NDKImage* pImg)
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

GLuint readImageFileAndCreateGLTexture(AAssetManager *assetManager, const char* fileName){
    AAsset *asset = AAssetManager_open (assetManager, fileName, AASSET_MODE_UNKNOWN);
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
    GLuint texID = createOpenGLTexture(glImage);

    delete glImage;

    if (imgBuff){
        free(imgBuff);
        imgBuff = NULL;
    }

    AAsset_close(asset);

    return texID;
}


#ifdef __cplusplus
}
#endif

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test5_1gl_1texture_1assembly_GLTextureAssemblyRender_openGLDraw(JNIEnv *env,
                                                                       jclass clazz) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    test5_drawAssemblyTexture();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test5_1gl_1texture_1assembly_GLTextureAssemblyRender_openGLInit(JNIEnv *env,
                                                                       jclass clazz) {

    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_baishengye_opengles_1demo_test5_1gl_1texture_1assembly_GLTextureAssemblyRender_openGLResize(JNIEnv *env,
                                                                         jclass clazz,
                                                                         jint width,
                                                                         jint height) {
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrthof(-1,1,-1,1,0.1,1000.0);
    glFrustumf(-1,1,-1,1,0.1,1000.0);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_baishengye_opengles_1demo_test5_1gl_1texture_1assembly_GLTextureAssemblyRender_jniReadAssetFile(JNIEnv *env,
                                                                                       jclass clazz,
                                                                                       jobject asset_manager,
                                                                                       jstring file_name) {
    AAssetManager *mAssetManager = AAssetManager_fromJava (env, asset_manager);
    if (NULL == mAssetManager){
        LOGF("assetManager is NULL");
        return -1;
    }

    for(int i=0; i<6; i++){

        char nameBuff[6];
        memset(nameBuff,0,sizeof(nameBuff));
        sprintf(nameBuff,"%d.png",i+1);
        nameBuff[5]='\0';
        LOGD("Image Name:%s",nameBuff);
        test5_m_texID[i] = readImageFileAndCreateGLTexture(mAssetManager,nameBuff);
    }

    return 0;
}