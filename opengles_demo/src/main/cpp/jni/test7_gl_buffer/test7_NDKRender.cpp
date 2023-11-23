//
// Created by chenchao on 2021/8/12.
//

#include "../../util/self/NDKRender.h"
#include "../../util/self/NDKTexture.h"

NDKRender::NDKRender():m_pAssetManager(NULL)
{
    m_pVBO = new NDKBuffer(NDKBuffer::VertexBuffer,NDKBuffer::StaticDraw);
    m_pEBO = new NDKBuffer(NDKBuffer::IndexBuffer,NDKBuffer::StaticDraw);
}

NDKRender::~NDKRender()
{
    glDeleteTextures(6,m_texID);

    SafePtrDelete(m_pVBO);
    SafePtrDelete(m_pEBO);
}

void NDKRender::InitGL()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    if(m_pAssetManager != NULL){
        loadTextureResources(m_pAssetManager);
    }


    const PointFloat5 cubeVertexs[]  = {
            {  -1.0,-1.0, 1.0 ,  0.0, 0.0 },
            {  -1.0, 1.0, 1.0 ,  0.0, 1.0 },
            {  1.0, -1.0,  1.0 , 1.0, 0.0 },
            {   1.0, 1.0, 1.0 ,  1.0, 1.0 },

            {   1.0,-1.0, -1.0,   0,  0  },
            {   1.0, 1.0, -1.0,   0,  1  },
            {   -1.0,-1.0, -1.0,   1,  0 },
            {   -1.0, 1.0, -1.0,   1,  1 },


            {   -1.0, -1.0, -1.0,  0,  0 },
            {   -1.0, 1.0, -1.0,   0,  1 },
            {   -1.0, -1.0,  1.0,  1,  0 },
            {   -1.0, 1.0, 1.0,    1,  1 },

            {   1.0,-1.0,  1.0,    0,  0 },
            {   1.0, 1.0,  1.0,    0,  1 },
            {   1.0, -1.0,  -1.0,  1,  0 },
            {   1.0, 1.0, -1.0,    1,  1 },

            {   -1.0, 1.0,  1.0,   0,  0 },
            {   -1.0, 1.0,  -1.0,  0,  1 },
            {   1.0, 1.0, 1.0,     1,  0 },
            {   1.0, 1.0, -1.0,    1,  1 },

            {   -1.0, -1.0, -1.0,  0,  0 },
            {   -1.0, -1.0, 1.0,   0,  1 },
            {   1.0, -1.0, -1.0,   1,  0 },
            {   1.0, -1.0, 1.0,    1,  1 }
    };

    const short cubeIndexs[]= {
            0, 1, 2,  2, 1, 3,
            4, 5, 6,  6, 5, 7,
            8, 9, 10, 10, 9,11,
            12,13,14, 14,13,15,
            16,17,18, 18,17,19,
            20,21,22, 22,21,23,
    };


    m_pVBO->Bind();
    m_pVBO->SetBufferData(cubeVertexs,sizeof(cubeVertexs));
    m_pVBO->Release();

    m_pEBO->Bind();
    m_pEBO->SetBufferData(cubeIndexs,sizeof(cubeIndexs));
    m_pEBO->Release();


}

void NDKRender::PaintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glCullFace(GL_BACK);
    glFrontFace(GL_CW);


    m_pVBO->Bind();


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float* addrVertex = (float*)0;
    float* uvAddress = (float*)12;

    glVertexPointer(3,GL_FLOAT,sizeof(PointFloat5),addrVertex);
    glTexCoordPointer(2,GL_FLOAT,sizeof(PointFloat5),uvAddress);


    m_angle += 0.01f;

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.1));
    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.3f, 0.2f, 0.3) );

    cubeMat = cubeScaleMat * cubeTransMat  * cubeRotMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    m_pEBO->Bind();


    for(int i=0; i< 6; i++)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_texID[i]);

        const short* indices =(const short *) (i*6*sizeof(short));
        glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, indices);

        glBindTexture(GL_TEXTURE_2D,0);

    }


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    m_pVBO->Release();
    m_pEBO->Release();
}

void NDKRender::ResizeGL(int width, int height)
{
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrthof(-1,1,-1,1,0.1,1000.0);
    glFrustumf(-1,1,-1,1,0.1,1000.0);
}

void NDKRender::SetupAssetManager(AAssetManager *pManager)
{
    if(pManager == NULL){
        return;
    }
    m_pAssetManager = pManager;
}

void NDKRender::loadTextureResources(AAssetManager *pManager)
{
    for(int i=0; i<6; i++){

        char nameBuff[6];
        memset(nameBuff,0,sizeof(nameBuff));
        sprintf(nameBuff,"%d.png",i+1);
        nameBuff[5]='\0';
        LOGD("Image Name:%s",nameBuff);
        NDKTexture glTexture;
        m_texID[i] = glTexture.CreateGLTextureFromFile(pManager,nameBuff);
    }
}

void NDKRender::loadShaderResources(AAssetManager *pManager)
{
}
