package com.baishengye.opengles_demo.test6_gl_oop

import android.os.Bundle
import com.baishengye.opengles_demo.BR
import com.baishengye.opengles_demo.R
import com.baishengye.opengles_demo.databinding.ActivityGltOopBinding
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder


class GLOOPActivity : BaseActivity<ActivityGltOopBinding>() {
    private lateinit var mGLOOPStates: GLOOPStates

    override fun initViewModel() {
        super.initViewModel()
        mGLOOPStates = getActivityScopeViewModel(GLOOPStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_glt_oop, BR.vm,mGLOOPStates)
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback {}
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)
        binding.glSurfaceView.setRenderer(GLOOPRender(this))
    }

    class GLOOPStates : StateHolder()
}
