cmake_minimum_required(VERSION 3.22.1)

SET(GLM_DIR util/3rdParty/libglm)
SET(STBIMG_DIR util/3rdParty/libstbImage)

INCLUDE_DIRECTORIES(${GLM_DIR}/include)
INCLUDE_DIRECTORIES(${STBIMG_DIR}/include)

add_library(Test1_OpenGLRender SHARED
    # List C/C++ source files with relative paths to this CMakeLists.txt.
        util/self/NDKImage.cpp
        jni/test1_gl_2d/test1_OpenGLNDKRender.cpp)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(Test1_OpenGLRender
    # List libraries link to the target library
    -landroid
    -lGLESv1_CM
    -lGLESv2
    log)

add_library(Test2_OpenGLRender SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        util/self/NDKImage.cpp
        jni/test2_gl_3d/test2_OpenGLNDKRender.cpp)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(Test2_OpenGLRender
        # List libraries link to the target library
        -landroid
        -lGLESv1_CM
        -lGLESv2
        log)

add_library(Test3_OpenGLRender SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        util/self/NDKImage.cpp
        jni/test3_gl_texture/test3_OpenGLNDKRender.cpp)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(Test3_OpenGLRender
        # List libraries link to the target library
        -landroid
        -lGLESv1_CM
        -lGLESv2
        log)

add_library(Test4_OpenGLRender SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        util/self/NDKImage.cpp
        jni/test4_gl_texture_3d/test4_OpenGLNDKRender.cpp)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(Test4_OpenGLRender
        # List libraries link to the target library
        -landroid
        -lGLESv1_CM
        -lGLESv2
        log)

add_library(Test5_OpenGLRender SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        util/self/NDKImage.cpp
        jni/test5_gl_texture_assembly/test5_OpenGLNDKRender.cpp)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(Test5_OpenGLRender
        # List libraries link to the target library
        -landroid
        -lGLESv1_CM
        -lGLESv2
        log)

add_library(Test6_OpenGLRender SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        util/self/NDKImage.cpp
        util/self/NDKTexture.cpp
        jni/test6_gl_oop/test6_NDKRender.cpp
        jni/test6_gl_oop/test6_OpenGLNDKRender.cpp)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(Test6_OpenGLRender
        # List libraries link to the target library
        -landroid
        -lGLESv1_CM
        -lGLESv2
        log)
