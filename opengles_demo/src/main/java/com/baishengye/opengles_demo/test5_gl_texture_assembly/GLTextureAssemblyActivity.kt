package com.baishengye.opengles_demo.test5_gl_texture_assembly

import android.os.Bundle
import com.baishengye.opengles_demo.BR
import com.baishengye.opengles_demo.R
import com.baishengye.opengles_demo.databinding.ActivityGltextureAssemblyBinding
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder

class GLTextureAssemblyActivity : BaseActivity<ActivityGltextureAssemblyBinding>() {
    private lateinit var  mGLTextureSAssemblyStates: GLTexture3DAssemblyStates

    override fun initViewModel() {
        super.initViewModel()
        mGLTextureSAssemblyStates = getActivityScopeViewModel(GLTexture3DAssemblyStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_gltexture_assembly, BR.vm,mGLTextureSAssemblyStates)
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback {}
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)
        binding.glSurfaceView.setRenderer(GLTextureAssemblyRender(this))
    }

    class GLTexture3DAssemblyStates : StateHolder()
}
