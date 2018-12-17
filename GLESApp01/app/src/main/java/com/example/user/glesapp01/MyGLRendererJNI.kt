package com.example.user.glesapp01

import android.opengl.GLES31
import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRendererJNI : GLSurfaceView.Renderer {
    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        created()
    }
    override fun onDrawFrame(gl: GL10) {
        draw()
    }
    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        changed(width, height)
    }

    external fun created()
    external fun draw()
    external fun changed(width: Int, height: Int)

}
