#include <stdio.h>
#include <jni.h>

#include "include/inlineHook.h"
#include <android/log.h>

#include <sys/types.h>
#include <unistd.h>

#define LOG_TAG "xyz"

#define LOGD(fmt,args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,fmt, ##args)


static unsigned long find_database_of(char* soName)//获取libcocos2dlua.so内存基址
{
  char filename[32];
  char cmdline[256];
  sprintf(filename, "/proc/%d/maps", getpid());
  LOGD("filename = %s", filename);
  FILE *fp = fopen(filename, "r");
  unsigned long revalue = 0;
  if (fp)
  {
    while(fgets(cmdline, 256, fp)) //逐行读取
    {
      if(strstr(cmdline, soName) && strstr(cmdline, "r-xp"))//筛选
      {
        LOGD("cmdline = %s",cmdline);
        char *str = strstr(cmdline,"-");
        if(str)
        {
          *str='\0';
          char num[32];
          sprintf(num, "0x%s", cmdline);
          revalue = strtoul( num, NULL, 0 );
          LOGD("revalue = %lu", revalue);
          return revalue;
        }
      }
      memset(cmdline,0,256); //清零
    }
    fclose(fp);
  }
  return 0L;
}



unsigned long func = NULL;

int (*old_calc)(void* env,void* jobject) = NULL;


int new_CalcFunc(void* env,void* jobject)
{ 
  int ret = old_calc(env,jobject);
  LOGD("修改前的ret = %d", ret);
  return 777;
}


int hookCalcFunc()
{
  LOGD("func = %x", func);
    if (registerInlineHook((uint32_t) func, (uint32_t) new_CalcFunc, (uint32_t **) &old_calc) != ELE7EN_OK) {
        return -1;
    }
    if (inlineHook((uint32_t) func) != ELE7EN_OK) {
        return -1;
    }
    LOGD("hookCalcFunc-------");
    return 0;
}

int unHookCalcFunc()
{
    if (inlineUnHook((uint32_t) func) != ELE7EN_OK) {
        return -1;
    }
    return 0;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM*vm, void* reserved){

    LOGD("enter JNI_OnLoad");

	unsigned long base = find_database_of("libnative-lib.so");
    LOGD("base = %x ",base);

    if (base > 0L) {
        func = base + 0x590 + 1;
		void* func1 = (void*)(base + 0x590 + 1);
        LOGD("FUNC = %x", func);
		hookCalcFunc();
    }	

  return JNI_VERSION_1_6;
}

