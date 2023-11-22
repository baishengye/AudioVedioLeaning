package com.baishengye.opengles_demo.test2_gl_3d

import android.os.Bundle
import com.baishengye.opengles_demo.BR
import com.baishengye.opengles_demo.R
import com.baishengye.opengles_demo.databinding.ActivityGl3dBinding
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder

class GL3DActivity : BaseActivity<ActivityGl3dBinding>() {
    private lateinit var mGL3DStates: GL3DStates

    override fun initViewModel() {
        super.initViewModel()
        mGL3DStates = getActivityScopeViewModel(GL3DStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_gl3d, BR.vm,mGL3DStates)
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback {}
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)
        binding.glSurfaceView.setRenderer(GL3DRender())
    }

    class GL3DStates : StateHolder()
}
