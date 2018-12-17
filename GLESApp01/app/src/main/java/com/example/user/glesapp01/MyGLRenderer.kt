package com.example.user.glesapp01

import android.opengl.GLES31
import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRenderer : GLSurfaceView.Renderer {
    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        // Set the background frame color
        GLES31.glClearColor(0.2f, 0.3f, 0.4f, 1.0f)
    }
    override fun onDrawFrame(gl: GL10) {
        // Redraw background color
        GLES31.glClear(GLES31.GL_COLOR_BUFFER_BIT)
    }
    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        GLES31.glViewport(0, 0, width, height)
    }
}
