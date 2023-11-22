package com.baishengye.opengles_demo.test1_gl_2d

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import kotlin.jvm.internal.Intrinsics

class GL2DRender : GLSurfaceView.Renderer {
    companion object{
        init {
            System.loadLibrary("Test1_OpenGLRender")
        }

        @JvmStatic
        private external fun openGLDraw()

        @JvmStatic
        private external fun openGLInit()

        @JvmStatic
        private external fun openGLResize(width: Int, height: Int)
    }


    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        openGLInit()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        openGLResize(width, height)
    }

    override fun onDrawFrame(gl: GL10) {
        openGLDraw()
    }
}
