package com.baishengye.opengles_demo.test3_gl_texture

import android.content.Context
import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import kotlin.jvm.internal.Intrinsics

class GLTextureRender(context: Context) : GLSurfaceView.Renderer {
    private val appContext: Context

    init {
        appContext = context.applicationContext
    }

    companion object{
        init {
            System.loadLibrary("Test3_OpenGLRender")
        }
        @JvmStatic
        private external fun jniReadAssetFile(assetManager: AssetManager, fileName: String): Int
        @JvmStatic
        private external fun openGLDraw()
        @JvmStatic
        private external fun openGLInit()
        @JvmStatic
        private external fun openGLResize(width: Int, height: Int)
    }

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        openGLInit()
        jniReadAssetFile(appContext.assets, "wuzhizhuansheng.png")
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        openGLResize(width, height)
    }

    override fun onDrawFrame(gl: GL10) {
        openGLDraw()
    }
}
