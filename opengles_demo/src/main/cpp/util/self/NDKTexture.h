//
// Created by chenchao on 2021/8/12.
//

#ifndef CCOPENGLES_CCGLTEXTURE_H
#define CCOPENGLES_CCGLTEXTURE_H

#include "NDKRenderDef.h"
#include "NDKAndroidLog.h"
#include "NDKImage.h"

class NDKTexture {

public:
    NDKTexture();
    ~NDKTexture();

    GLuint  GetTextureID();
    GLuint  CreateGLTextureFromFile(AAssetManager *assetManager, const char* fileName);

private:
    GLuint  generateTexture(AAssetManager *assetManager, const char* fileName);
    GLuint  createOpenGLTexture(NDKImage* pImg);

private:
    GLuint m_texID;
};


#endif //CCOPENGLES_CCGLTEXTURE_H
