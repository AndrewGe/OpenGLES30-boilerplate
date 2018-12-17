package com.example.user.glesapp01

import android.content.Context
import android.opengl.GLSurfaceView

class MyGLSurfaceView(context: Context) : GLSurfaceView(context) {

    private val mRenderer: GLSurfaceView.Renderer

    init {

        // Create an OpenGL ES 3.X context
        setEGLContextClientVersion(3)

        mRenderer = MyGLRendererJNI()

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(mRenderer)
    }
}

