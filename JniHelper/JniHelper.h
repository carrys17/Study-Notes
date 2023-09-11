//
// Created by dell on 2023/8/30.
//

#ifndef WALLFACER_JNIHELPER_H
#define WALLFACER_JNIHELPER_H


#include <jni.h>
#include <list>

/***
 * 参考项目地址 https://github.com/w296488320/JnitraceForCpp
 * 优化：
 * 1、堆栈判断是哪个so
 * 2、避免死循环和一些闪退问题
 */
namespace wallfacer{
    namespace JniHelper{


        extern jmethodID g_method_id_Class_getName;
        extern jmethodID g_method_id_Object_toString;
        // 黑名单
        extern std::list<std::string> gForbidSoList;
        // 白名单
        extern std::list<std::string> gFilterSoList;
        extern bool gIsForbidMode;

        // 开始监控jni的调用
        void startTraceJniFunc(JNIEnv *env,bool isForbidMode, const std::list<std::string> &forbid_list, const std::list<std::string> &filter_list);
        // 停止监控jni的调用
        void stopTraceJniFunc();

        // 是否打印log, gIsForbidMode
        // gIsForbidMode模式，只过滤黑名单，白名单填了也没用（即除了黑名单so的调用，其他的都打印）
        // 非gIsForbidMode模式，只过滤白名单，黑名单填了也没用（即只打印白名单so的调用）
        bool isLog();

        // 获取jobject信息, 是否指定classInfo, 大部分情况为nullptr, 只有在遍历va_list需要传入
        const char* getJObjectInfo(JNIEnv *env, jobject obj, const char* classInfo);
        // 获取jclass信息
        const char* getJObjectClassInfo(JNIEnv *env, jobject objClass);
        // 通过toString获取jobject 信息
        const char *getJObjectToString(JNIEnv *env, jobject obj);
        // 获取方法的argsInfo, 会返回对应的方法名和参数值
        const char* getArgsInfo(JNIEnv *env, jobject obj, jmethodID jmethodId,va_list args, bool isStatic);

        jstring char2jstring(JNIEnv *env, const char *pat);

        std::string jstring2str(JNIEnv *env, jstring jstr);

        bool jboolean2bool(jboolean value);

        std::list<std::string> jlist2clist(JNIEnv *env, jobject jlist);

    }
}
#endif //WALLFACER_JNIHELPER_H
