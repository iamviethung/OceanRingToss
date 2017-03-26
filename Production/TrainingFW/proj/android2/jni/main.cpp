#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../../../source/stdafx.h"
#include "../../../source/Game.h"
#include "../../../source/SceneManager.h"
#include "../../../source/Platform/PlatformAndroid.h"
#include "../../../source/Platform/InputManager.h"
#include "../../../source/Utils/FPSLimiter.h"


#define JNI_FUNCTION(function) 		 Java_com_android_trainingfws_ ## function

Game* game = NULL;
JNIEnv *env;
jobject obj;
bool temp=false;

void GameInit(int width, int height)
{
	LOGI("INIT GAME # %d - %d", width, height);
	
	//init singleton
	game = new Game();
	new PlatformAndroid();
	game->Init(width, height);
	game->setRunning();
	LOGI("INIT GAME - DONE");
}

void GameRender()
{
	LOGE("GameRender->xx1");
	if (temp){
		game->Replay();
		temp = false;
	}
	game->Update(FPS_LMT->getDeltaTime());
	LOGE("GameRender->xx2");
	/*if (game->is_TurnOff != temp){
		JNI_FUNCTION(GameSurfaceView_setTurnState) (env, obj, game->is_TurnOff);
		temp = game->is_TurnOff;
		LOGE("GameRender->xx3");
	}*/
	LOGE("GameRender->xx4");
	game->Render();
	LOGE("GameRender->xx5");
}

extern "C" {
    JNIEXPORT void JNICALL JNI_FUNCTION(GameRenderer_nativeInit) (JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL JNI_FUNCTION(GameRenderer_nativeRender) (JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL JNI_FUNCTION(GameRenderer_nativeResize) (JNIEnv * env, jobject obj,  jint width, jint height);
	JNIEXPORT void JNICALL JNI_FUNCTION(GameSurfaceView_nativeOnTouch) (JNIEnv * env, jobject obj,  jfloat x, jfloat y, jint action);
	JNIEXPORT void JNICALL JNI_FUNCTION(GameSurfaceView_nativeOnSensorChanged) (JNIEnv * env, jobject obj, jfloat x, jfloat y, jfloat z);
	JNIEXPORT void JNICALL JNI_FUNCTION(GameActivity_nativeOnResume) (JNIEnv * env, jobject obj, jboolean isResume);
};

JNIEXPORT void JNICALL JNI_FUNCTION(GameRenderer_nativeInit) (JNIEnv * env, jobject obj,  jint width, jint height)
{
    GameInit(width, height);
}

JNIEXPORT void JNICALL JNI_FUNCTION(GameRenderer_nativeRender) (JNIEnv * env, jobject obj)
{
    GameRender();
}

JNIEXPORT void JNICALL JNI_FUNCTION(GameRenderer_nativeResize) (JNIEnv * env, jobject obj,  jint width, jint height)
{
	LOGI("Resize # %d - %d", width, height);
	PLATFORM->Resize(width, height);
}

JNIEXPORT void JNICALL JNI_FUNCTION(GameSurfaceView_nativeOnTouch) (JNIEnv * env, jobject obj,  jfloat x, jfloat y, jint action)
{	
	INPUT_MGR->updatePointerEvent((PointerState) action, (short) x, (short) y);
}

JNIEXPORT void JNICALL JNI_FUNCTION(GameSurfaceView_nativeOnSensorChanged) (JNIEnv * env, jobject obj, jfloat x, jfloat y, jfloat z)
{
	INPUT_MGR->updateSensorEvent((short)x, (short)y, (short)z);
}

JNIEXPORT void JNICALL JNI_FUNCTION(GameActivity_nativeOnResume) (JNIEnv * env, jobject obj, jboolean isResume)
{
	temp = isResume;
}
