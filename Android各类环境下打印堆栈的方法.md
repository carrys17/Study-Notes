在开发中，有时很需要通过打印来判断函数的调用过程。下面列出几种比较常用到的打印堆栈的方法。

## 一、Andorid c++（native层）：



### 方式一：（通过unwind来实现）



	#include <unwind.h>
	#include <dlfcn.h>
	#include <iomanip>
	#include <sstream>
	
	namespace {
	
	
		struct BacktraceState
		{
			void** current;
			void** end;
		};
		
		
		static _Unwind_Reason_Code unwindCallback(struct _Unwind_Context* context, void* arg)
		{
			BacktraceState* state = static_cast<BacktraceState*>(arg);
			uintptr_t pc = _Unwind_GetIP(context);
			if (pc) {
				if (state->current == state->end) {
					return _URC_END_OF_STACK;
				} else {
					*state->current++ = reinterpret_cast<void*>(pc);
				}
			}
			return _URC_NO_REASON;
		}
	}
	
	
	size_t captureBacktrace(void** buffer, size_t max)
	{
		BacktraceState state = {buffer, buffer + max};
		_Unwind_Backtrace(unwindCallback, &state);
		return state.current - buffer;
	}
	
	
	void dumpBacktrace(std::ostream& os, void** buffer, size_t count)
	{
		for (size_t idx = 0; idx < count; ++idx) {
			const void* addr = buffer[idx];
			const char* symbol = "";
			Dl_info info;
			if (dladdr(addr, &info) && info.dli_sname) {
				symbol = info.dli_sname;
			}
			os << "  #" << std::setw(2) << idx << ": " << addr << "  " << symbol << "\n";
		}
	}
	
	
	void backtraceToLogcat()
	{
		const size_t max = 30; // 调用的层数
		void* buffer[max];
		std::ostringstream oss;
		
		
		dumpBacktrace(oss, buffer, captureBacktrace(buffer, max));
		
		
		__android_log_print(ANDROID_LOG_INFO, "INJECT", "%s", oss.str().c_str());
	}




在需要查看的地方调用 `backtraceToLogcat()  ` 即可。



它的log如下：

      # 0: 0x9b4524af  
      # 1: 0x9b4530ad  
      # 2: 0x95e1d2fa  
      # 3: 0x9548be48  
      # 4: 0x954f5ca4  
      # 5: 0x953db5ba  
      # 6: 0x96ec8641  
      # 7: 0x96ed9b3c  il2cpp_runtime_invoke （有导出符号的函数）
      # 8: 0x9c5679ef  
      # 9: 0x9c557875  
      #10: 0x9c54f557  
      #11: 0x9c54f77a  




这种方式的好处是不会使程序卡死，不好的地方在于输出的log不够详细，然后打印出来的地址是绝对的，要分析时需要结合/proc/pid/maps 中的基址去定位到函数。


### 方式二：

直接在JNI_OnLoad方法中通过JavaVM 去获取到JNIEnv 变量并保存 ，然后再需要的地方调用`mEnv->FindClass(NULL)`  去打印堆栈信息 



这种方法的好处是简单，而且它的log信息比较详细，除了地址之外，还有所在so的信息。然后它打印出来的地址是相对的，可以直接在ida按G键跳转到对应的地方。不好的地方在于，会使程序异常退出。



*native: #01 pc 005366fe  /system/lib/libart.so(_ZNK3art6Thread4DumpERNSt3__113basic_ostreamIcNS1_11char_traitsIcEEEE+286)

native: #02 pc 003980af  /system/lib/libart.so (_ZN3art9JavaVMExt8JniAbortEPKcS2_+1247)

native: #03 pc 003997e9  /system/lib/libart.so (_ZN3art9JavaVMExt9JniAbortFEPKcS2_z+115)

native: #04 pc 003df47a  /system/lib/libart.so (_ZN3art3JNI9FindClassEP7_JNIEnvPKc+2266)

native: #05 pc 0004c0bd  /data/data/[packagename]/lib/x86/libtest.so (???)

native: #06 pc 00cc12f9  /data/app/[packagename]/lib/x86/libil2cpp.so (???)

native: #07 pc 0032fe47  /data/app/[packagename]/lib/x86/libil2cpp.so (???)

native: #08 pc 00399ca3  /data/app/[packagename]/lib/x86/libil2cpp.so (???)

native: #09 pc 0027f5b9  /data/app/[packagename]/lib/x86/libil2cpp.so (???)

native: #10 pc 01d6c640  /data/app/[packagename]/lib/x86/libil2cpp.so (???)

native: #11 pc 01d7db3b  /data/app/[packagename]/lib/x86/libil2cpp.so(il2cpp_runtime_invoke+56)

native: #12 pc 000b19ee  /data/app/[packagename]/lib/x86/libunity.so (???)

native: #13 pc 000a1874  /data/app/[packagename]/lib/x86/libunity.so (???)

native: #14 pc 00099556  /data/app/[packagename]/lib/x86/libunity.so (???)

native: #15 pc 00099779  /data/app/[packagename]/lib/x86/libunity.so (???)

native: #16 pc 00097e7f  /data/app/[packagename]/lib/x86/libunity.so (???)*



####  注： 网上提到的一种方法如下：




    #include <utils/CallBack.h>
    android::CallBack stack;
    stack.update()
    stack.log("log_tag");



这个方法已经不适用了，因为include的时候会报找不到库文件。




# lua中

直接通过调用 `debug.traceback()` 即可



# Java 中 



通过try  catch 捕获一个抛出的异常即可


	try{
		throw new Exception("抛出异常看堆栈"); 
	}catch (Exception e){
		Log.i(TAG, "catch异常: ",e); 
	} 


