package com.baishengye.opengles_demo.test7_gl_buffer

import android.os.Bundle
import com.baishengye.opengles_demo.BR
import com.baishengye.opengles_demo.R
import com.baishengye.opengles_demo.databinding.ActivityGlBufferBinding
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder


class GLBufferActivity : BaseActivity<ActivityGlBufferBinding>() {
    private lateinit var mGLBufferStates: GLBufferStates

    override fun initViewModel() {
        super.initViewModel()
        mGLBufferStates = getActivityScopeViewModel(GLBufferStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_gl_buffer, BR.vm,mGLBufferStates)
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback {}
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)
        binding.glSurfaceView.setRenderer(GLBufferRender(this))
    }

    class GLBufferStates : StateHolder()
}
