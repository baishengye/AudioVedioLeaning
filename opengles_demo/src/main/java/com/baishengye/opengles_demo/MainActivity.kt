package com.baishengye.opengles_demo

import android.content.Intent
import android.view.View
import com.baishengye.opengles_demo.databinding.ActivityMainBinding
import com.baishengye.opengles_demo.test1_gl_2d.GL2DActivity
import com.baishengye.opengles_demo.test2_gl_3d.GL3DActivity
import com.baishengye.opengles_demo.test3_gl_texture.GLTextureActivity
import com.baishengye.opengles_demo.test4_gl_texture_3d.GLTexture3DActivity
import com.baishengye.opengles_demo.test5_gl_texture_assembly.GLTextureAssemblyActivity
import com.baishengye.opengles_demo.test6_gl_oop.GLOOPActivity
import com.baishengye.opengles_demo.test7_gl_buffer.GLBufferActivity
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder
import kotlin.jvm.internal.Intrinsics


class MainActivity : BaseActivity<ActivityMainBinding>() {

    private lateinit var mMainStates: MainStates

    override fun initViewModel() {
        super.initViewModel()
        mMainStates = getActivityScopeViewModel(MainStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_main,BR.vm,mMainStates)
            .addBindingParam(BR.clickProxy,ClickProxy())
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback{}
    }

    class MainStates:StateHolder(){

    }

    inner class ClickProxy{
        fun toGL2DActivity(view: View) {
            this@MainActivity.startActivity(Intent(this@MainActivity, GL2DActivity::class.java))
        }

        fun toGL3DActivity(view: View) {
            this@MainActivity.startActivity(Intent(this@MainActivity, GL3DActivity::class.java))
        }

        fun toGLTextureActivity(view: View) {
            this@MainActivity.startActivity(Intent(this@MainActivity, GLTextureActivity::class.java))
        }

        fun toGLTexture3DActivity(view: View) {
            this@MainActivity.startActivity(Intent(this@MainActivity, GLTexture3DActivity::class.java))
        }

        fun toGLTextureAssemblyActivity(view: View) {
            this@MainActivity.startActivity(Intent(this@MainActivity, GLTextureAssemblyActivity::class.java))
        }

        fun toGLOOPActivity(view: View) {
            this@MainActivity.startActivity(Intent(this@MainActivity, GLOOPActivity::class.java))
        }

        fun toGLBufferActivity(view: View) {
            this@MainActivity.startActivity(Intent(this@MainActivity, GLBufferActivity::class.java))
        }
    }
}