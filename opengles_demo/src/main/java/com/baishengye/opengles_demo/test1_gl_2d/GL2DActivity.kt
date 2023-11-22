package com.baishengye.opengles_demo.test1_gl_2d

import android.os.Bundle
import com.baishengye.opengles_demo.BR
import com.baishengye.opengles_demo.R
import com.baishengye.opengles_demo.databinding.ActivityGl2dBinding
import com.xiaoyingbo.lib_architecture.data.response.networkState.NetworkStateCallback
import com.xiaoyingbo.lib_architecture.ui.page.BaseActivity
import com.xiaoyingbo.lib_architecture.ui.page.DataBindingConfig
import com.xiaoyingbo.lib_architecture.ui.viewModel.StateHolder
import kotlin.jvm.internal.Intrinsics


class GL2DActivity : BaseActivity<ActivityGl2dBinding>() {
    private lateinit var mGL2DStates: GL2DStates

    override fun initViewModel() {
        super.initViewModel()
        mGL2DStates = getActivityScopeViewModel(GL2DStates::class.java)
    }

    override fun getDataBindingConfig(): DataBindingConfig {
        return DataBindingConfig(R.layout.activity_gl2d,BR.vm,mGL2DStates)
    }

    override fun getNetworkStateCallback(): NetworkStateCallback {
        return object : NetworkStateCallback{}
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)
        binding.glSurfaceView.setRenderer(GL2DRender())
    }

    class GL2DStates : StateHolder()
}
