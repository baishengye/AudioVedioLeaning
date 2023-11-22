//
// Created by chenchao on 2021/8/12.
//

#include "../../util/self/NDKRender.h"
#include "../../util/self/NDKTexture.h"

NDKRender::NDKRender(): m_pAssetManager(nullptr)
{

}

NDKRender::~NDKRender()
{
    glDeleteTextures(6,m_texID);
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
}

void NDKRender::PaintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    PointFloat5 planVertices[] =
            {
                    { -1.0f, -1.0f, 1.0f,    0,  0 },
                    {  -1.0f,1.0f, 1.0f,   0,  1 },
                    {  1.0f,-1.0f, 1.0f,    1,  0 },
                    {  1.0f, 1.0f, 1.0f,    1,  1 },
            };

    PointFloat5  cubeVertexs[] = {
            { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f},
            { 0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
            { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
            {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

            {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
    };




    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof(PointFloat5),cubeVertexs);
    glTexCoordPointer(2,GL_FLOAT,sizeof(PointFloat5),&cubeVertexs[0].u);

    m_angle += 0.01f;

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.4f, 0.4f, 0.5) );

    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    //glDrawArrays(GL_TRIANGLES,0,36);
    for(int i=0; i< 6; i++)
    {
        glBindTexture(GL_TEXTURE_2D,m_texID[i]);
        glDrawArrays(GL_TRIANGLES,i*6,6);

    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
