/*---------------------------------------------------------------------------*
 *  CWrapperMicrophoneListener.cpp                                           *
 *                                                                           *
 *  Copyright 2007, 2008 Nuance Communciations, Inc.                               *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the 'License');          *
 *  you may not use this file except in compliance with the License.         *
 *                                                                           *
 *  You may obtain a copy of the License at                                  *
 *      http://www.apache.org/licenses/LICENSE-2.0                           *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an 'AS IS' BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include <assert.h>
#include "jniapi.h"
#include "CWrapperMicrophoneListener.h"
#include "JNIHelper.h"

using namespace android::speech::recognition;
using namespace android::speech::recognition::jni;


CWrapperMicrophoneListener::CWrapperMicrophoneListener(JavaVM* _jvm, jobject _listener,
    ReturnCode::Type& returnCode):
    jvm(_jvm),
    listener(0)
{
  JNIEnv* env = JNIHelper::getEnv(jvm);
  listener = env->NewGlobalRef(_listener);
  if (!listener)
  {
    returnCode = ReturnCode::OUT_OF_MEMORY;
    return;
  }
  returnCode = ReturnCode::SUCCESS;
}

CWrapperMicrophoneListener::~CWrapperMicrophoneListener()
{
  UAPI_FN_NAME("CWrapperMicrophoneListener::~CWrapperMicrophoneListener");
    
  UAPI_TRACE(fn,"this=%p\n", this);
  
  // Delete global reference to the Java listener
  JNIEnv* env = JNIHelper::getEnv(jvm);
  env->DeleteGlobalRef(listener);
}

void CWrapperMicrophoneListener::invokeMethod(const char* methodName)
{
  UAPI_FN_SCOPE("CWrapperMicrophoneListener::invokeMethod");
  
  UAPI_INFO(fn,"invokeMethod name: %s \n",methodName);

  JNIEnv* env = JNIHelper::getEnv(jvm);
  jclass cls = env->GetObjectClass(listener);
  jmethodID mid = env->GetMethodID(cls, methodName, "()V");
  env->DeleteLocalRef(cls);
  assert(mid != 0);
  env->CallVoidMethod(listener, mid, 0);
  if (env->ExceptionCheck())
  {
    jthrowable exc = env->ExceptionOccurred();
    env->ExceptionClear();
    onError(exc);
    env->DeleteLocalRef(exc);
  }
}

void CWrapperMicrophoneListener::onStarted()
{
  UAPI_FN_SCOPE("CWrapperMicrophoneListener::onStarted");
    
  invokeMethod("onStarted");
}


void CWrapperMicrophoneListener::onStopped()
{
  UAPI_FN_SCOPE("CWrapperMicrophoneListener::onStopped");
    
  invokeMethod("onStopped");
}

void CWrapperMicrophoneListener::onError(ReturnCode::Type returnCode)
{
  UAPI_FN_SCOPE("CWrapperMicrophoneListener::onError");
    
  JNIEnv* env = JNIHelper::getEnv(jvm);
  jclass cls = env->GetObjectClass(listener);
  jmethodID mid = env->GetMethodID(cls, "onError", "(Ljava/lang/Exception;)V");
  env->DeleteLocalRef(cls);
  assert(mid != 0);
  jobject exception = JNIHelper::getJavaException(env, listener, returnCode);
  env->CallVoidMethod(listener, mid, exception);
  if (env->ExceptionCheck())
  {
    jthrowable exc = env->ExceptionOccurred();
    env->ExceptionClear();
    env->DeleteLocalRef(exc);
  }
  env->DeleteLocalRef(exception);
}
void CWrapperMicrophoneListener::onError(jthrowable exception)
{
  UAPI_FN_SCOPE("CWrapperMicrophoneListener::onError thru exception");
    
  JNIEnv* env = JNIHelper::getEnv(jvm);
  jclass listenerClass = env->GetObjectClass(listener);
  jmethodID onError = env->GetMethodID(listenerClass, "onError", "(Ljava/lang/Exception;)V");
  env->DeleteLocalRef(listenerClass);
  assert(onError != 0);
  env->CallVoidMethod(listener, onError, exception);
  if (env->ExceptionCheck())
  {
    jthrowable exc = env->ExceptionOccurred();
    env->ExceptionClear();
    env->DeleteLocalRef(exc);
  }
}
