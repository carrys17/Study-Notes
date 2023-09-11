//
// Created by dell on 2023/8/30.
//

#include "log.h"
#include "JniHelper.h"
#include "../../substrate/SubstrateHook.h"
#include "utils.h"
#include <cstring>
#include <cstdio>
#include <sstream>
#include "encrypt/encrypt_include.h"
#include <regex>
#include <string>


#define HOOK_JNI_FUNC(env, func) \
     MSHookFunction(    \
      (void*)(env)->functions->func,\
      (void*)func##_hook,\
      (void**)&func##_f )         \


#define HOOK_FUNC_DEF(func, ret ,...) \
    ret (*func##_f)(__VA_ARGS__); \
    ret func##_hook(__VA_ARGS__)


namespace wallfacer{
    namespace JniHelper{

// ----------------------------- CallxxxMethod start -------------------------------------
        // jobject     (*CallObjectMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallObjectMethodV, jobject, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallObjectMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallObjectMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallObjectMethodV method, jobjInfo info = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallObjectMethodV method, argsInfo = %s", argsInfo);
            jobject ret = CallObjectMethodV_f(env, jobj, jmethodId, args);
            // 频繁调用时，打印ret的值会闪退
//            const char* retInfo = getJObjectInfo(env,ret, nullptr);
//            WLOGD("enter CallObjectMethodV method, ret = %s", retInfo);
            return ret;
        }

        // jboolean    (*CallBooleanMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallBooleanMethodV, jboolean, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallBooleanMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallBooleanMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallBooleanMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallBooleanMethodV method, argsInfo = %s", argsInfo);
            jboolean ret = CallBooleanMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallBooleanMethodV method, ret = %d", ret);
            return ret;
        }

        // jbyte       (*CallByteMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallByteMethodV, jbyte, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallByteMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallByteMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallByteMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallByteMethodV method, argsInfo = %s", argsInfo);
            jbyte ret = CallByteMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallByteMethodV method, ret = %hhd", ret);
            return ret;
        }

        // jchar       (*CallCharMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallCharMethodV, jchar, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallCharMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallCharMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallCharMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallCharMethodV method, argsInfo = %s", argsInfo);
            jchar ret = CallCharMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallCharMethodV method, ret = %c", ret);
            return ret;
        }

        // jshort      (*CallShortMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallShortMethodV, jshort, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallShortMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallShortMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallShortMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallShortMethodV method, argsInfo = %s", argsInfo);
            jshort ret = CallShortMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallShortMethodV method, ret = %d", ret);
            return ret;
        }

        // jint        (*CallIntMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallIntMethodV, jint, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallIntMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallIntMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallIntMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallIntMethodV method, argsInfo = %s", argsInfo);
            jint ret = CallIntMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallIntMethodV method, ret = %d", ret);
            return ret;
        }

        // jlong       (*CallLongMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallLongMethodV, jlong, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallLongMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallLongMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallLongMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallLongMethodV method, argsInfo = %s", argsInfo);
            jlong ret = CallLongMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallLongMethodV method, ret = %ld", ret);
            return ret;
        }

        // jfloat      (*CallFloatMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallFloatMethodV, jfloat, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallFloatMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallFloatMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallFloatMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallFloatMethodV method, argsInfo = %s", argsInfo);
            jfloat ret = CallFloatMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallFloatMethodV method, ret = %f", ret);
            return ret;
        }

        // jdouble     (*CallDoubleMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallDoubleMethodV, jdouble, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallDoubleMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallDoubleMethodV method");
            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
            WLOGD("enter CallDoubleMethodV method, jobjInfo = %s",jobjInfo);
            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
            WLOGD("enter CallDoubleMethodV method, argsInfo = %s", argsInfo);
            jdouble ret = CallDoubleMethodV_f(env, jobj, jmethodId, args);
            WLOGD("enter CallDoubleMethodV method, ret = %f", ret);
            return ret;
        }

        // void        (*CallVoidMethodV)(JNIEnv*, jobject, jmethodID, va_list);
        HOOK_FUNC_DEF(CallVoidMethodV, void, JNIEnv* env, jobject jobj, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallVoidMethodV_f(env, jobj, jmethodId, args);
            }
            WLOGD("enter CallVoidMethodV method");
            // 不用调用getJObjectInfo和getArgsInfo，里边的getObjectClass有时会无限调用到CallVoidMethodV
            // 单独开启hook这个函数时，由于频繁调用private void android.view.DisplayEventReceiver.dispatchVsync这种方法，也是会导致闪退
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter CallVoidMethodV method, jobjInfo = %s",jobjInfo);
//            const char* argsInfo = getArgsInfo(env,jobj,jmethodId,args, false);
//            WLOGD("enter CallVoidMethodV method, argsInfo = %s", argsInfo);
            return CallVoidMethodV_f(env, jobj, jmethodId, args);
        }
// ----------------------------- CallxxxMethod end -------------------------------------


// ----------------------------- CallStaticxxxMethod start -------------------------------------
        // jobject     (*CallStaticObjectMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticObjectMethodV, jobject, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticObjectMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticObjectMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticObjectMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticObjectMethodV method ,argsInfo = %s",argsInfo);
            return CallStaticObjectMethodV_f(env, jclass, jmethodId, args);
        }

        // jboolean    (*CallStaticBooleanMethodV)(JNIEnv*, jclass, jmethodID, va_list)
        HOOK_FUNC_DEF(CallStaticBooleanMethodV, jboolean, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticBooleanMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticBooleanMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticBooleanMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticBooleanMethodV method ,argsInfo = %s",argsInfo);
            jboolean ret = CallStaticBooleanMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticBooleanMethodV method ,ret = %d",ret);
            return ret;
        }

        // jbyte       (*CallStaticByteMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticByteMethodV, jbyte, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticByteMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticByteMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticByteMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticByteMethodV method ,argsInfo = %s",argsInfo);
            jbyte ret = CallStaticByteMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticByteMethodV method ,ret = %d",ret);
            return ret;
        }

        // jchar       (*CallStaticCharMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticCharMethodV, jchar, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticCharMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticCharMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticCharMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticCharMethodV method ,argsInfo = %s",argsInfo);
            jchar ret = CallStaticCharMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticCharMethodV method ,ret = %d",ret);
            return ret;
        }

        // jshort      (*CallStaticShortMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticShortMethodV, jshort, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticShortMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticShortMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticShortMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticShortMethodV method ,argsInfo = %s",argsInfo);
            jshort ret = CallStaticShortMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticShortMethodV method ,ret = %d",ret);
            return ret;
        }

        // jint        (*CallStaticIntMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticIntMethodV, jint, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticIntMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticIntMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticIntMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticIntMethodV method ,argsInfo = %s",argsInfo);
            jint ret = CallStaticIntMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticIntMethodV method ,ret = %d",ret);
            return ret;
        }

        // jlong       (*CallStaticLongMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticLongMethodV, jlong, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticLongMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticLongMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticLongMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticLongMethodV method ,argsInfo = %s",argsInfo);
            jlong ret = CallStaticLongMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticLongMethodV method ,ret = %ld",ret);
            return ret;
        }

        // jfloat      (*CallStaticFloatMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticFloatMethodV, jfloat, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticFloatMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticFloatMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticFloatMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticFloatMethodV method ,argsInfo = %s",argsInfo);
            jfloat ret = CallStaticFloatMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticFloatMethodV method ,ret = %f",ret);
            return ret;
        }

        // jdouble     (*CallStaticDoubleMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticDoubleMethodV, jdouble, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticDoubleMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticDoubleMethodV method");
            const char* jclassInfo = getJObjectClassInfo(env, jclass);
            WLOGD("enter CallStaticDoubleMethodV method ,jclassInfo = %s",jclassInfo);
            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
            WLOGD("enter CallStaticDoubleMethodV method ,argsInfo = %s",argsInfo);
            jdouble ret = CallStaticDoubleMethodV_f(env, jclass, jmethodId, args);
            WLOGD("enter CallStaticDoubleMethodV method ,ret = %f",ret);
            return ret;
        }

        // void        (*CallStaticVoidMethodV)(JNIEnv*, jclass, jmethodID, va_list);
        HOOK_FUNC_DEF(CallStaticVoidMethodV, void, JNIEnv* env, jclass jclass, jmethodID jmethodId, va_list args){
            if(!isLog()){
                return CallStaticVoidMethodV_f(env, jclass, jmethodId, args);
            }
            WLOGD("enter CallStaticVoidMethodV method");
            //类似于CallVoidMethodV的原因
//            const char* jclassInfo = getJObjectClassInfo(env, jclass);
//            WLOGD("enter CallStaticVoidMethodV method ,jclassInfo = %s",jclassInfo);
//            const char* argsInfo = getArgsInfo(env,jclass,jmethodId,args,true);
//            WLOGD("enter CallStaticVoidMethodV method ,argsInfo = %s",argsInfo);
            return CallStaticVoidMethodV_f(env, jclass, jmethodId, args);
        }
// ----------------------------- CallStaticxxxMethod end -------------------------------------


// ----------------------------- GetxxxField start -------------------------------------
        // jobject     (*GetObjectField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetObjectField, jobject, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetObjectField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetObjectField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetObjectField method, jobjInfo = %s",jobjInfo);
            jobject ret = GetObjectField_f(env, jobj, jfieldId);
            const char* retInfo = getJObjectInfo(env, ret, nullptr);
            WLOGD("enter GetObjectField method, ret = %s",retInfo);
            return ret;
        }

        // jboolean    (*GetBooleanField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetBooleanField, jboolean, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetBooleanField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetBooleanField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetBooleanField method, jobjInfo = %s",jobjInfo);
            jboolean ret = GetBooleanField_f(env, jobj, jfieldId);
            WLOGD("enter GetBooleanField method, ret = %d",ret);
            return ret;
        }

        // jbyte       (*GetByteField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetByteField, jbyte, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetByteField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetByteField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetByteField method, jobjInfo = %s",jobjInfo);
            jbyte ret = GetByteField_f(env, jobj, jfieldId);
            WLOGD("enter GetByteField method, ret = %d",ret);
            return ret;
        }

        // jchar       (*GetCharField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetCharField, jchar, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetCharField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetCharField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetCharField method, jobjInfo = %s",jobjInfo);
            jchar ret = GetCharField_f(env, jobj, jfieldId);
            WLOGD("enter GetCharField method, ret = %d",ret);
            return ret;
        }

        // jshort      (*GetShortField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetShortField, jshort, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetShortField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetShortField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetShortField method, jobjInfo = %s",jobjInfo);
            jshort ret = GetShortField_f(env, jobj, jfieldId);
            WLOGD("enter GetShortField method, ret = %d",ret);
            return ret;
        }

        // jint        (*GetIntField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetIntField, jint, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetIntField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetIntField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetIntField method, jobjInfo = %s",jobjInfo);
            jint ret = GetIntField_f(env, jobj, jfieldId);
            WLOGD("enter GetIntField method, ret = %d",ret);
            return ret;
        }

        // jlong       (*GetLongField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetLongField, jlong, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetLongField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetLongField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetLongField method, jobjInfo = %s",jobjInfo);
            jlong ret = GetLongField_f(env, jobj, jfieldId);
            WLOGD("enter GetLongField method, ret = %ld",ret);
            return ret;
        }

        // jfloat      (*GetFloatField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetFloatField, jfloat, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetFloatField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetFloatField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetFloatField method, jobjInfo = %s",jobjInfo);
            jfloat ret = GetFloatField_f(env, jobj, jfieldId);
            WLOGD("enter GetFloatField method, ret = %f",ret);
            return ret;
        }

        // jdouble     (*GetDoubleField)(JNIEnv*, jobject, jfieldID);
        HOOK_FUNC_DEF(GetDoubleField, jdouble, JNIEnv* env, jobject jobj, jfieldID jfieldId){
            if(!isLog()){
                return GetDoubleField_f(env, jobj, jfieldId);
            }
            WLOGD("enter GetDoubleField method");
//            const char* jobjInfo = getJObjectInfo(env,jobj, nullptr);
//            WLOGD("enter GetDoubleField method, jobjInfo = %s",jobjInfo);
            jdouble ret = GetDoubleField_f(env, jobj, jfieldId);
            WLOGD("enter GetDoubleField method, ret = %f",ret);
            return ret;
        }
// ----------------------------- GetxxxField end -------------------------------------



// ----------------------------- GetStaticxxxField start -------------------------------------
        // jobject     (*GetStaticObjectField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticObjectField, jobject, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticObjectField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticObjectField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticObjectField method, jclzInfo = %s",jclzInfo);
            jobject ret = GetStaticObjectField_f(env, jclz, jfieldId);
            const char* retInfo = getJObjectInfo(env, ret, nullptr);
            WLOGD("enter GetStaticObjectField method, ret = %s",retInfo);
            return ret;
        }

        // jboolean    (*GetStaticBooleanField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticBooleanField, jboolean, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticBooleanField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticBooleanField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticBooleanField method, jclzInfo = %s",jclzInfo);
            jboolean ret = GetStaticBooleanField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticObjectField method, ret = %d",ret);
            return ret;
        }

        // jbyte       (*GetStaticByteField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticByteField, jbyte, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticByteField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticByteField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticByteField method, jclzInfo = %s",jclzInfo);
            jbyte ret = GetStaticByteField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticByteField method, ret = %d",ret);
            return ret;
        }

        // jchar       (*GetStaticCharField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticCharField, jchar, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticCharField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticCharField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticCharField method, jclzInfo = %s",jclzInfo);
            jchar ret = GetStaticCharField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticCharField method, ret = %d",ret);
            return ret;
        }

        // jshort      (*GetStaticShortField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticShortField, jshort, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticShortField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticShortField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticShortField method, jclzInfo = %s",jclzInfo);
            jshort ret = GetStaticShortField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticShortField method, ret = %d",ret);
            return ret;
        }

        // jint        (*GetStaticIntField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticIntField, jint, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticIntField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticIntField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticIntField method, jclzInfo = %s",jclzInfo);
            jint ret = GetStaticIntField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticIntField method, ret = %d",ret);
            return ret;
        }

        // jlong       (*GetStaticLongField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticLongField, jlong, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticLongField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticLongField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticLongField method, jclzInfo = %s",jclzInfo);
            jlong ret = GetStaticLongField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticLongField method, ret = %ld",ret);
            return ret;
        }

        // jfloat      (*GetStaticFloatField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticFloatField, jfloat, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticFloatField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticFloatField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticFloatField method, jclzInfo = %s",jclzInfo);
            jfloat ret = GetStaticFloatField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticFloatField method, ret = %f",ret);
            return ret;
        }

        // jdouble     (*GetStaticDoubleField)(JNIEnv*, jclass, jfieldID);
        HOOK_FUNC_DEF(GetStaticDoubleField, jdouble, JNIEnv* env, jclass jclz, jfieldID jfieldId){
            if(!isLog()){
                return GetStaticDoubleField_f(env, jclz, jfieldId);
            }
            WLOGD("enter GetStaticDoubleField method");
            const char* jclzInfo = getJObjectClassInfo(env,jclz);
            WLOGD("enter GetStaticDoubleField method, jclzInfo = %s",jclzInfo);
            jdouble ret = GetStaticDoubleField_f(env, jclz, jfieldId);
            WLOGD("enter GetStaticDoubleField method, ret = %f",ret);
            return ret;
        }
// ----------------------------- GetStaticxxxField end -------------------------------------


// ----------------------------- 字符串相关 start -------------------------------------
        // jstring     (*NewStringUTF)(JNIEnv*, const char*);
        HOOK_FUNC_DEF(NewStringUTF, jstring, JNIEnv* env, const char* str){
            if(!isLog()){
                return NewStringUTF_f(env, str);
            }
            WLOGD("enter NewStringUTF method, str = %s",str);
            return NewStringUTF_f(env, str);
        }

        // const char* (*GetStringUTFChars)(JNIEnv*, jstring, jboolean*);
        HOOK_FUNC_DEF(GetStringUTFChars, const char*, JNIEnv* env, jstring jstr, jboolean* isCopy){
            if(!isLog()){
                return GetStringUTFChars_f(env, jstr, isCopy);
            }
            WLOGD("enter GetStringUTFChars method");
            const char* ret = GetStringUTFChars_f(env, jstr, isCopy);
            WLOGD("enter GetStringUTFChars method, ret = %s",ret);
            return ret;
        }
// ----------------------------- 字符串相关 end -------------------------------------


// ----------------------------- findClass RegisterNatives Id相关 start -------------------------------------
        // jclass      (*FindClass)(JNIEnv*, const char*);
        HOOK_FUNC_DEF(FindClass, jclass, JNIEnv* env, const char* name){
            if(!isLog()){
                return FindClass_f(env, name);
            }
            WLOGD("enter FindClass method, name = %s",name);
            return FindClass_f(env, name);
        }

        // jint        (*RegisterNatives)(JNIEnv*, jclass, const JNINativeMethod*,jint);
        HOOK_FUNC_DEF(RegisterNatives, jint, JNIEnv* env, jclass jclz, const JNINativeMethod* methods, jint method_count){
            if(!isLog()){
                return RegisterNatives_f(env, jclz, methods, method_count);
            }
            WLOGD("enter RegisterNatives method");
            const char* clzInfo = getJObjectClassInfo(env, jclz);
            WLOGD("enter RegisterNatives method, clz = %s",clzInfo);
            for (int i = 0; i <method_count; ++i) {
                const char* name = methods[i].name;
                const char* sig = methods[i].signature;
                const void* fnPtr = methods[i].fnPtr;
                WLOGD("enter RegisterNatives method, name = %s, sig = %s, fnPtr = %p",name, sig, fnPtr);
            }
            return RegisterNatives_f(env, jclz, methods, method_count);
        }

        // jfieldID    (*GetFieldID)(JNIEnv*, jclass, const char*, const char*);
        HOOK_FUNC_DEF(GetFieldID, jfieldID, JNIEnv* env, jclass jclz, const char* name, const char* signature){
            if(!isLog()){
                return GetFieldID_f(env, jclz, name, signature);
            }
            WLOGD("enter GetFieldID method");
            const char* clzInfo = getJObjectClassInfo(env, jclz);
            WLOGD("enter GetFieldID method, clzInfo = %s, name = %s, signature = %s", clzInfo, name, signature);
            return GetFieldID_f(env, jclz, name, signature);
        }

        // jfieldID    (*GetStaticFieldID)(JNIEnv*, jclass, const char*,  const char*);
        HOOK_FUNC_DEF(GetStaticFieldID, jfieldID, JNIEnv* env, jclass jclz, const char* name, const char* signature){
            if(!isLog()){
                return GetStaticFieldID_f(env, jclz, name, signature);
            }
            WLOGD("enter GetStaticFieldID method");
            const char* clzInfo = getJObjectClassInfo(env, jclz);
            WLOGD("enter GetStaticFieldID method, clzInfo = %s, name = %s, signature = %s", clzInfo, name, signature);
            return GetStaticFieldID_f(env, jclz, name, signature);
        }

        // jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
        HOOK_FUNC_DEF(GetMethodID, jmethodID, JNIEnv* env, jclass jclz, const char* name, const char* signature){
            if(!isLog()){
                return GetMethodID_f(env, jclz, name, signature);
            }
            WLOGD("enter GetStaticFieldID method");
            const char* clzInfo = getJObjectClassInfo(env, jclz);
            WLOGD("enter GetStaticFieldID method, clzInfo = %s, name = %s, signature = %s", clzInfo, name, signature);
            return GetMethodID_f(env, jclz, name, signature);
        }

        // jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass, const char*, const char*);
        HOOK_FUNC_DEF(GetStaticMethodID, jmethodID, JNIEnv* env, jclass jclz, const char* name, const char* signature){
            if(!isLog()){
                return GetStaticMethodID_f(env, jclz, name, signature);
            }
            WLOGD("enter GetStaticMethodID method");
            const char* clzInfo = getJObjectClassInfo(env, jclz);
            WLOGD("enter GetStaticMethodID method, clzInfo = %s, name = %s, signature = %s", clzInfo, name, signature);
            return GetStaticMethodID_f(env, jclz, name, signature);
        }
// ----------------------------- findClass RegisterNatives Id相关 end -------------------------------------



// ----------------------------- 避免解析数据时陷入死循环或者打印干扰信息 start ----------------------------
        jobject CallObjectMethod_SAFE(JNIEnv *env, jobject jobj, jmethodID jmethodId,...){
//            WLOGD("enter CallObjectMethod_SAFE method, CallObjectMethodV_f = %p",CallObjectMethodV_f);
            if (CallObjectMethodV_f){
                va_list args;
                jobject result;
                va_start(args,jmethodId);
                result = CallObjectMethodV_f(env, jobj,jmethodId,args);
                va_end(args);
                return result;
            }else{
                return env->CallObjectMethod(jobj,jmethodId);
            }
        }

        jobject CallStaticObjectMethod_SAFE(JNIEnv *env, jclass clazz, jmethodID methodID, ...) {
//            WLOGD("enter CallStaticObjectMethod_SAFE method, CallStaticObjectMethodV_f = %p",CallStaticObjectMethodV_f);
            if (CallStaticObjectMethodV_f) {
                va_list args;
                va_start(args, methodID);
                jobject ret = CallStaticObjectMethodV_f(env, clazz, methodID, args);
                va_end(args);
                return ret;
            } else {
                return env->CallStaticObjectMethod(clazz, methodID);
            }
        }

        // jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
         jint CallIntMethod_SAFE(JNIEnv *env, jobject obj, jmethodID methodID, ...) {
//            WLOGD("enter CallIntMethod_SAFE method, CallIntMethodV_f = %p",CallIntMethodV_f);
            if (CallIntMethodV_f) {
                va_list args;
                va_start(args, methodID);
                jint ret = CallIntMethodV_f(env, obj, methodID, args);
                va_end(args);
                return ret;
            } else {
                return env->CallIntMethod(obj, methodID);
            }
        }

        // const char* GetStringUTFChars(JNIEnv*, jstring, jboolean*);
        const char* GetStringUTFChars_SAFE(JNIEnv* env, jstring jstr, jboolean* isCopy){
            if (GetStringUTFChars_f){
                return GetStringUTFChars_f(env,jstr,isCopy);
            }else{
                return env->GetStringUTFChars(jstr,isCopy);
            }
        }

        // jclass FindClass(const char* name)
        jclass FindClass_SAFE(JNIEnv* env, const char* name){
            if (FindClass_f){
                return FindClass_f(env, name);
            }else{
                return env->FindClass(name);
            }
        }

        // jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
        jmethodID GetMethodID_SAFE(JNIEnv* env, jclass jclz, const char* name, const char* signature){
            if (GetMethodID_f){
                return GetMethodID_f(env, jclz, name, signature);
            }else{
                return env->GetMethodID(jclz, name, signature);
            }
        }

        // jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass, const char*, const char*);
        jmethodID GetStaticMethodID_SAFE(JNIEnv* env, jclass jclz, const char* name, const char* signature){
            if (GetStaticMethodID_f){
                return GetStaticMethodID_f(env, jclz, name, signature);
            }else{
                return env->GetStaticMethodID(jclz, name, signature);
            }
        }
// ----------------------------- 避免解析数据时陷入死循环或者打印干扰信息 end ----------------------------



        // 是否打印log, gIsForbidMode
        // gIsForbidMode模式，只过滤黑名单，白名单填了也没用（即除了黑名单so的调用，其他的都打印）
        // 非gIsForbidMode模式，只过滤白名单，黑名单填了也没用（即只打印白名单so的调用）
        bool isLog(){
            Dl_info info;
            // 这里要__builtin_return_address(1)，表示堆栈的第二层，__builtin_return_address(0)拿到的恒为当前的so
            dladdr((void *) __builtin_return_address(1), &info);
            const char*fname = info.dli_fname;
//            WLOGD("fname = %s",fname);

            // is not app file
            if (strstr(fname, ENCRYPT("/data/")) == nullptr) {
//                WLOGD("is not app file");
                return false;
            }
            if (gIsForbidMode){
                for (const std::string &forbid: gForbidSoList) {
                    if (strstr(fname, forbid.c_str()) != nullptr) {
                        return false;
                    }
                }
//                WLOGD("gIsHookAll = true, fname = %s",fname);
                return true;
            }else{
                for (const std::string &filter: gFilterSoList) {
                    if (strstr(fname, filter.c_str()) != nullptr) {
                        return true;
                    }
                }
                return false;
            }
        }


        // 获取方法的argsInfo, 会返回对应的方法名和参数值
        const char* getArgsInfo(JNIEnv *env, jobject obj, jmethodID jmethodId,va_list args, bool isStatic){
            if (obj == nullptr){
                return nullptr;
            }
            if (jmethodId == nullptr) {
                return nullptr;
            }

            jclass objclass1 = env->GetObjectClass(obj);

            //获取被调用的方法信息
            jobject invokeMethod = env->ToReflectedMethod(objclass1, jmethodId, isStatic);

            std::ostringstream oss;
            //打印被调用方法信息,只需要调用他的toString
            const char* invokeMethodInfo = getJObjectInfo(env, invokeMethod, nullptr);
            oss << "\ninvokeMethod : " << invokeMethodInfo << "\n";

            jclass invokejclass = env->GetObjectClass(invokeMethod);

            jmethodID parCountId = GetMethodID_SAFE(env, invokejclass, ENCRYPT("getParameterCount"), ENCRYPT("()I"));

            jint size = CallIntMethod_SAFE(env,invokeMethod, parCountId);

            if (size == 0) {
                //长度等于0直接return,不打印参数信息
                return oss.str().c_str();
            }

            jmethodID method_id_getTypes = GetMethodID_SAFE(env,
                    invokejclass,
                    ENCRYPT("getParameterTypes"),
                    ENCRYPT("()[Ljava/lang/Class;"));

            auto objectArray = (jobjectArray) (CallObjectMethod_SAFE(env,invokeMethod,
                                                                     method_id_getTypes));
            for (int i = 0; i < size; i++) {
                auto argobj = env->GetObjectArrayElement(objectArray, i);
                if (argobj == nullptr) {
                    continue;
                }
                char argsInfo[20];
                sprintf(argsInfo, ENCRYPT("args %d"), i);
                //具体每个类型的class
                const char *classInfo = getJObjectClassInfo(env, argobj);
                jobject arg = va_arg(args, jobject);
                const char* argInfo = getJObjectInfo(env,arg, classInfo);
                if (argInfo != nullptr) {
                    oss << argsInfo << " : " << argInfo << "\n";
                } else {
                    oss << argsInfo << " : null\n";
                }
            }
            //end
            va_end(args);
            return oss.str().c_str();

        }


        // 直接通过toString获取jobject 信息
        const char *getJObjectToString(JNIEnv *env, jobject obj) {
            if(!g_method_id_Object_toString){
                g_method_id_Object_toString =
                        GetMethodID_SAFE(env,FindClass_SAFE(env,ENCRYPT("java/lang/Object")), ENCRYPT("toString"),
                                         ENCRYPT("()Ljava/lang/String;"));
            }
            jobject jobj = CallObjectMethod_SAFE(env, obj, g_method_id_Object_toString);
            return GetStringUTFChars_SAFE(env,(jstring) (jobj), nullptr);
        }


        // 获取jclass信息
        const char *getJObjectClassInfo(JNIEnv *env, jobject objClass) {
            if (objClass == nullptr) {
                return nullptr;
            }
//            这里改为全局获取，首次初始化获取即可，不需要每次都去获取，因为发现FindClass有时会调用到CallObjectMethod导致死循环
//            jclass clazz = env->FindClass("java/lang/Class");
//            jmethodID method_id_getName = env->GetMethodID(clazz, ENCRYPT("getName"), ENCRYPT("()Ljava/lang/String;"));
            if(!g_method_id_Class_getName){
                g_method_id_Class_getName =
                        GetMethodID_SAFE(env,FindClass_SAFE(env,ENCRYPT("java/lang/Class")), ENCRYPT("getName"),
                                         ENCRYPT("()Ljava/lang/String;"));
            }
            jstring getClassName_ret = (jstring) (CallObjectMethod_SAFE(env,objClass, g_method_id_Class_getName));
            const char *getClass = GetStringUTFChars_SAFE(env,getClassName_ret, nullptr);
            //free
            env->ReleaseStringUTFChars(getClassName_ret, getClass);
            env->DeleteLocalRef(getClassName_ret);
            return getClass;
        }


        /**
         * 获取jobject信息
         * @param env
         * @param obj
         * @param classInfo 是否指定classInfo, 大部分情况为nullptr, 只有在遍历va_list需要传入
         * @return
         */
        const char* getJObjectInfo(JNIEnv *env, jobject obj, const char* classInfo) {
            if (obj == nullptr) {
                return nullptr;
            }
            if (classInfo == nullptr) {
                jobject objClass = env->GetObjectClass(obj);
                classInfo = getJObjectClassInfo(env,objClass);
            }
            if (classInfo == nullptr) {
                return nullptr;
            }
            const char *objStr = nullptr;
            //需要先排除基础类型
            if (strcmp(classInfo, ENCRYPT("boolean")) == 0 ||
                strcmp(classInfo, ENCRYPT("java.lang.Boolean")) == 0) {
                jclass clazz = FindClass_SAFE(env,ENCRYPT("java/lang/Boolean"));
                jmethodID id = GetStaticMethodID_SAFE(env, clazz, ENCRYPT("toString"), ENCRYPT("(Z)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env, jStr, nullptr);
            } else if (strcmp(classInfo, ENCRYPT("byte")) == 0 ||
                       strcmp(classInfo, ENCRYPT("java.lang.Byte")) == 0) {
                jclass clazz = FindClass_SAFE(env,ENCRYPT("java/lang/Byte"));
                jmethodID id = GetStaticMethodID_SAFE(env, clazz, ENCRYPT("toString"), ENCRYPT("(B)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env,jStr, nullptr);
            } else if (strcmp(classInfo, ENCRYPT("char")) == 0 ||
                       strcmp(classInfo, ENCRYPT("java.lang.Character")) == 0) {
                jclass clazz =FindClass_SAFE(env,ENCRYPT("java/lang/Character"));
                jmethodID id = GetStaticMethodID_SAFE(env, clazz, ENCRYPT("toString"), ENCRYPT("(C)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env, jStr, nullptr);
            } else if (strcmp(classInfo, ENCRYPT("short")) == 0 ||
                       strcmp(classInfo, ENCRYPT("java.lang.Short")) == 0) {
                jclass clazz = FindClass_SAFE(env,ENCRYPT("java/lang/Short"));
                jmethodID id = GetStaticMethodID_SAFE(env, clazz, ENCRYPT("toString"), ENCRYPT("(S)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env, jStr, nullptr);
            } else if (strcmp(classInfo, ENCRYPT("int")) == 0 ||
                       strcmp(classInfo, ENCRYPT("java.lang.Integer")) == 0) {
                jclass clazz = FindClass_SAFE(env,ENCRYPT("java/lang/Integer"));
                jmethodID id = GetStaticMethodID_SAFE(env, clazz, ENCRYPT("toString"), ENCRYPT("(I)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env,jStr, nullptr);
            } else if (strcmp(classInfo, ENCRYPT("float")) == 0 ||
                       strcmp(classInfo, ENCRYPT("java.lang.Float")) == 0) {
                jclass clazz = FindClass_SAFE(env,ENCRYPT("java/lang/Float"));
                jmethodID id = env->GetStaticMethodID(clazz, ENCRYPT("toString"), ENCRYPT("(F)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env, jStr, nullptr);
            } else if (strcmp(classInfo, ENCRYPT("double")) == 0 ||
                       strcmp(classInfo, ENCRYPT("java.lang.Double")) == 0) {
                jclass clazz = FindClass_SAFE(env,ENCRYPT("java/lang/Double"));
                jmethodID id = GetStaticMethodID_SAFE(env, clazz, ENCRYPT("toString"), ENCRYPT("(D)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env, jStr, nullptr);
            } else if (strcmp(classInfo, ENCRYPT("long")) == 0 ||
                       strcmp(classInfo, ENCRYPT("java.lang.Long")) == 0) {
                jclass clazz = FindClass_SAFE(env,ENCRYPT("java/lang/Long"));
                jmethodID id = GetStaticMethodID_SAFE(env, clazz, ENCRYPT("toString"), ENCRYPT("(J)Ljava/lang/String;"));
                auto jStr = (jstring)CallStaticObjectMethod_SAFE(env, clazz, id, obj);
                objStr = GetStringUTFChars_SAFE(env, jStr, nullptr);
            }else if (strstr(classInfo, ENCRYPT("["))) {
                //数组类型需要特殊处理,非数组直接打印
                auto arg = (jobjectArray) obj;
                //数组类型参数
                jstring argJstr;
                //byte数组 特殊处理
                if (strcmp(classInfo, ENCRYPT("[B")) == 0) {
                    jsize length = env->GetArrayLength(arg);
                    jbyte* elements = env->GetByteArrayElements((jbyteArray)arg, nullptr);\
                    std::string output = "";
                    if (length>0){
                        // 构建输出字符串
                        output = "[";
                        for (int i = 0; i < length; i++) {
                            if (i > 0) {
                                output += ", ";
                            }
                            output += std::to_string(elements[i]);
                        }
                        output += "]";
                    }
                    objStr = output.c_str();
                } else {
                    //其他的则调用Arrays.toString 处理
                    jclass ArrayClazz = FindClass_SAFE(env,ENCRYPT("java/util/Arrays"));

                    //这个需要用object类型
                    jmethodID methodid =
                            GetStaticMethodID_SAFE(env, ArrayClazz,
                                                   ENCRYPT("toString"),
                                                   ENCRYPT("([Ljava/lang/Object;)Ljava/lang/String;"));
                    argJstr = (jstring) (CallStaticObjectMethod_SAFE(env,ArrayClazz, methodid, arg));
                    if (argJstr != nullptr) {
                        //上面的逻辑主要是为了处理argJstr的赋值
                        objStr = GetStringUTFChars_SAFE(env,argJstr, nullptr);
                    }
                }
            }else {
                //其他任何类型直接toString
                objStr = getJObjectToString(env, obj);
            }
            if (env->ExceptionCheck()) {
                env->ExceptionClear();
            }
            std::string ret;
            if (objStr!= nullptr){
                ret.append("classInfo : ").append(classInfo).append(", info : ").append(objStr);
            } else{
                ret.append("classInfo : ").append(classInfo).append(", info : ").append("null");
            }
            return ret.c_str();
        }

        void startHook(JNIEnv *env){
            WLOGD("enter startHook method");

            HOOK_JNI_FUNC(env, CallObjectMethodV);
            HOOK_JNI_FUNC(env, CallBooleanMethodV);
            HOOK_JNI_FUNC(env, CallByteMethodV);
            HOOK_JNI_FUNC(env, CallCharMethodV);
            HOOK_JNI_FUNC(env, CallShortMethodV);
            HOOK_JNI_FUNC(env, CallIntMethodV);
            HOOK_JNI_FUNC(env, CallLongMethodV);
            HOOK_JNI_FUNC(env, CallFloatMethodV);
            HOOK_JNI_FUNC(env, CallDoubleMethodV);
            HOOK_JNI_FUNC(env, CallVoidMethodV);

            HOOK_JNI_FUNC(env, CallStaticObjectMethodV);
            HOOK_JNI_FUNC(env, CallStaticBooleanMethodV);
            HOOK_JNI_FUNC(env, CallStaticByteMethodV);
            HOOK_JNI_FUNC(env, CallStaticCharMethodV);
            HOOK_JNI_FUNC(env, CallStaticShortMethodV);
            HOOK_JNI_FUNC(env, CallStaticIntMethodV);
            HOOK_JNI_FUNC(env, CallStaticLongMethodV);
            HOOK_JNI_FUNC(env, CallStaticFloatMethodV);
            HOOK_JNI_FUNC(env, CallStaticDoubleMethodV);
            HOOK_JNI_FUNC(env, CallStaticVoidMethodV);

            HOOK_JNI_FUNC(env, GetObjectField);
            HOOK_JNI_FUNC(env, GetBooleanField);
            HOOK_JNI_FUNC(env, GetByteField);
            HOOK_JNI_FUNC(env, GetCharField);
            HOOK_JNI_FUNC(env, GetShortField);
            HOOK_JNI_FUNC(env, GetIntField);
            HOOK_JNI_FUNC(env, GetLongField);
            HOOK_JNI_FUNC(env, GetFloatField);
            HOOK_JNI_FUNC(env, GetDoubleField);

            HOOK_JNI_FUNC(env, GetStaticObjectField);
            HOOK_JNI_FUNC(env, GetStaticBooleanField);
            HOOK_JNI_FUNC(env, GetStaticByteField);
            HOOK_JNI_FUNC(env, GetStaticCharField);
            HOOK_JNI_FUNC(env, GetStaticShortField);
            HOOK_JNI_FUNC(env, GetStaticIntField);
            HOOK_JNI_FUNC(env, GetStaticLongField);
            HOOK_JNI_FUNC(env, GetStaticFloatField);
            HOOK_JNI_FUNC(env, GetStaticDoubleField);

            HOOK_JNI_FUNC(env, NewStringUTF);
            HOOK_JNI_FUNC(env, GetStringUTFChars);

            HOOK_JNI_FUNC(env, FindClass);
            HOOK_JNI_FUNC(env, RegisterNatives);
            HOOK_JNI_FUNC(env, GetFieldID);
            HOOK_JNI_FUNC(env, GetStaticFieldID);
            HOOK_JNI_FUNC(env, GetMethodID);
            HOOK_JNI_FUNC(env, GetStaticMethodID);

            WLOGD("hook success!");
        }

        void init(JNIEnv *env, bool isForbidMode, const std::list<std::string> &forbid_list, const std::list<std::string> &filter_list){
            WLOGD("enter init method");
            g_method_id_Class_getName =
                    env->GetMethodID(env->FindClass(ENCRYPT("java/lang/Class")), ENCRYPT("getName"),
                                                 ENCRYPT("()Ljava/lang/String;"));
            g_method_id_Object_toString =
                    env->GetMethodID(env->FindClass(ENCRYPT("java/lang/Object")), ENCRYPT("toString"),
                                     ENCRYPT("()Ljava/lang/String;"));

            gForbidSoList = std::list<std::string>(forbid_list);
            gFilterSoList = std::list<std::string>(filter_list);
            gIsForbidMode = isForbidMode;
            WLOGD("init success!");
        }

        void startTraceJniFunc(JNIEnv *env, bool isForbidMode,const std::list<std::string> &forbid_list, const std::list<std::string> &filter_list){
            WLOGD("start trace");
            init(env, isForbidMode, forbid_list, filter_list);
            startHook(env);
        }

        void stopTraceJniFunc(){
            gIsForbidMode = false;
            gForbidSoList.clear();
            gFilterSoList.clear();
        }

        jmethodID g_method_id_Class_getName;
        jmethodID g_method_id_Object_toString;

        std::list<std::string> gForbidSoList;
        std::list<std::string> gFilterSoList;
        bool gIsForbidMode;


        jstring char2jstring(JNIEnv *env, const char *pat){
            //定义java String类 strClass
            jclass strClass = (env)->FindClass(ENCRYPT("java/lang/String"));
            //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
            jmethodID ctorID = (env)->GetMethodID(strClass, ENCRYPT("<init>"), ENCRYPT("([BLjava/lang/String;)V"));
            //建立byte数组
            jbyteArray bytes = (env)->NewByteArray(strlen(pat));
            //将char* 转换为byte数组
            (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
            // 设置String, 保存语言类型,用于byte数组转换至String时的参数
            jstring encoding = (env)->NewStringUTF(ENCRYPT("GB2312"));
            //将byte数组转换为java String,并输出
            return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
        }

        std::string jstring2str(JNIEnv *env, jstring jstr){
            char *rtn = nullptr;
            jclass clsstring = env->FindClass(ENCRYPT("java/lang/String"));
            jstring strencode = env->NewStringUTF(ENCRYPT("GB2312"));
            jmethodID mid = env->GetMethodID(clsstring, ENCRYPT("getBytes"), ENCRYPT("(Ljava/lang/String;)[B"));
            auto barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
            jsize alen = env->GetArrayLength(barr);
            jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
            if (alen > 0) {
                rtn = (char *) malloc(alen + 1);
                memcpy(rtn, ba, alen);
                rtn[alen] = 0;
            }
            env->ReleaseByteArrayElements(barr, ba, 0);
            std::string stemp(rtn);
            free(rtn);
            return stemp;
        }

        bool jboolean2bool(jboolean value){
            return value == JNI_TRUE;
        }

        std::list<std::string> jlist2clist(JNIEnv *env, jobject jlist){
            std::list<std::string> clist;
            jclass listClazz = env->FindClass(ENCRYPT("java/util/ArrayList"));
            jmethodID sizeMid = env->GetMethodID(listClazz, ENCRYPT("size"), ENCRYPT("()I"));
            jint size = env->CallIntMethod(jlist, sizeMid);
            jmethodID list_get = env->GetMethodID(listClazz, ENCRYPT("get"), ENCRYPT("(I)Ljava/lang/Object;"));
            for (int i = 0; i < size; i++) {
                jobject item = env->CallObjectMethod(jlist, list_get, i);
                //末尾添加
                clist.push_back(jstring2str(env, (jstring) item));
            }
            return clist;
        }

    }
}