package com.baishengye.opengles_demo.test4_gl_texture_3d

import android.os.Bundle
import com.baishengye.opengles_demo.BR
import com.baishengye.opengles_demo.R
import com.baishengye.opengles_demo.databinding.ActivityGltexture3dBinding
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder

class GLTexture3DActivity : BaseActivity<ActivityGltexture3dBinding>() {

    private lateinit var mGLTexture3DStates: GLTexture3DStates

    override fun initViewModel() {
        super.initViewModel()
        mGLTexture3DStates = getActivityScopeViewModel(GLTexture3DStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_gltexture3d, BR.vm,mGLTexture3DStates)
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback {}
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)
        binding.glSurfaceView.setRenderer(GLTexture3DRender(this))
    }

    class GLTexture3DStates : StateHolder()
}
