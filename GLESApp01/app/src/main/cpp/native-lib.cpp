#include <jni.h>
#include <string>
#include "NativeRenderer.h"

static NativeRenderer* render = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_com_example_user_glesapp01_MyGLRendererJNI_created(
        JNIEnv *env, jobject /* this */) {
    if (render) {
        delete render;
        render = nullptr;
    }
    render = new NativeRenderer();
    return;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_user_glesapp01_MyGLRendererJNI_draw(
        JNIEnv *env, jobject /* this */) {
    render->draw();
    return;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_user_glesapp01_MyGLRendererJNI_changed(
        JNIEnv *env, jobject /* this */, jint width, jint height) {
    render->changed(width, height);
    return;
}
