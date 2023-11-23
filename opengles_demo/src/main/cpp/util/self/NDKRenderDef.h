//
// Created by baishengye on 2023-11-07.
//

#ifndef AUDIOVEDIOLEANING_NDKRENDERDEF_H
#define AUDIOVEDIOLEANING_NDKRENDERDEF_H

#include <string>

#include <GLES/gl.h>
#include <GLES2/gl2.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <assert.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

#include "NDKAndroidLog.h"

/**
 * 释放指针*/
template<typename T>
void SafePtrDelete(T* ptr)
{
    delete ptr;
    ptr = NULL;
}

class GlobalDefine
{
    inline static void PrintGLError()
    {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            LOGD("glError: %u",err);
        }
    }

};

#ifdef __cplusplus
extern "C" {
#endif


struct  PointFloat7{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float a;
};

struct  PointFloat5{
    float x;
    float y;
    float z;
    float u;
    float v;
};

struct  PointFloat4{
    float r;
    float g;
    float b;
    float a;
};

struct  PointFloat3{
    float x;
    float y;
    float z;
};

#ifdef __cplusplus
}
#endif

#endif //AUDIOVEDIOLEANING_NDKRENDERDEF_H
