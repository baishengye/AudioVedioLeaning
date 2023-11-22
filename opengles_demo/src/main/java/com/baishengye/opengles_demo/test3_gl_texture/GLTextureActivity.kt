package com.baishengye.opengles_demo.test3_gl_texture

import android.os.Bundle
import com.baishengye.opengles_demo.BR
import com.baishengye.opengles_demo.R
import com.baishengye.opengles_demo.databinding.ActivityGltextureBinding
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder


class GLTextureActivity : BaseActivity<ActivityGltextureBinding>() {
    private lateinit var mGLTextureStates: GLTextureStates

    override fun initViewModel() {
        super.initViewModel()
        mGLTextureStates = getActivityScopeViewModel(GLTextureStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_gltexture, BR.vm,mGLTextureStates)
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback {}
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)
        binding.glSurfaceView.setRenderer(GLTextureRender(this))
    }

    class GLTextureStates : StateHolder()
}
