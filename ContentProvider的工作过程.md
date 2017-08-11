#ContentProvider的工作过程

首先看下这张图片，很好的画出了ContentProvider的启动过程

![](http://i.imgur.com/6WIhtUI.png)

图片的左下角，可以看到ContentProvider的onCreate要先于Application的onCreate，这在四大组件中是一个少有的现象。

访问ContentProvider需要通过ContentResolver，而ContentResolver是一个抽象类。getContentResolver最终得到的是ApplicationContentResolver，ApplicationContentResolver继承了ContentResolver并实现其中的抽象方法。

第一次访问ContentProvider时，会触发ContentProvider的创建，通过ContentProvider四个方法中的任意一个都可以触发ContentProvider的启动过程，这里选择query分析

ContentProvider的query方法中，首先会获取IContentProvider对象，最终会调用acquireProvider来获取ContentProvider。

	ContentProvider.query
			↓
	IContentProvider.acquireProvider
			↓
	
	public final IContentProvider acquireProvider(
            Context c, String auth, int userId, boolean stable) {
        final IContentProvider provider = acquireExistingProvider(c, auth, userId, stable);
        if (provider != null) {
			// 检测是否存在目标ContentProvider
            return provider;
        }

     	...
        IActivityManager.ContentProviderHolder holder = null;
        try {
            holder = ActivityManagerNative.getDefault().getContentProvider(
                    getApplicationThread(), auth, userId, stable);
        } catch (RemoteException ex) {
            throw ex.rethrowFromSystemServer();
        }
        if (holder == null) {
            Slog.e(TAG, "Failed to find provider info for " + auth);
            return null;
        }

        // Install provider will increment the reference count for us, and break
        // any ties in the race.
        holder = installProvider(c, holder, holder.info,
                true /*noisy*/, holder.noReleaseNeeded, stable);
        return holder.provider;
    }
	
如果目前ContentProvider没有启动，就发送一个进程间的请求给AMS让其启动目标ContentProvider，最后再通过installProvider方法来修改引用计数

AMS启动ContentProvider是通过AMS的startProcessLocked方法来完成的，其内部是通过Process的start来完成一个新进程的启动，新进程的启动后其入口为ActivityThread的main方法

	 public static void main(String[] args) {
        Trace.traceBegin(Trace.TRACE_TAG_ACTIVITY_MANAGER, "ActivityThreadMain");
        SamplingProfilerIntegration.start();

        // CloseGuard defaults to true and can be quite spammy.  We
        // disable it here, but selectively enable it later (via
        // StrictMode) on debug builds, but using DropBox, not logs.
        CloseGuard.setEnabled(false);

        Environment.initForCurrentUser();

        // Set the reporter for event logging in libcore
        EventLogger.setReporter(new EventLoggingReporter());

        // Make sure TrustedCertificateStore looks in the right place for CA certificates
        final File configDir = Environment.getUserConfigDirectory(UserHandle.myUserId());
        TrustedCertificateStore.setDefaultUserDirectory(configDir);

        Process.setArgV0("<pre-initialized>");

        Looper.prepareMainLooper();

        ActivityThread thread = new ActivityThread();
        thread.attach(false);

        if (sMainThreadHandler == null) {
            sMainThreadHandler = thread.getHandler();
        }

        if (false) {
            Looper.myLooper().setMessageLogging(new
                    LogPrinter(Log.DEBUG, "ActivityThread"));
        }

        // End of event ActivityThreadMain.
        Trace.traceEnd(Trace.TRACE_TAG_ACTIVITY_MANAGER);
        Looper.loop();

        throw new RuntimeException("Main thread loop unexpectedly exited");
    }

ActivityThread的main方法是一个静态方法，在它内部首先创建ActivityThread的实例并调用attach，接着就开始进行消息循环了。

	ActivityThread.attach
			↓
	AMS.attachApplication
			↓	
	AMS.attachApplicationLocked
			↓
	ApplicationThread.bindApplication
			↓
	ActivityThread.handleBindApplication
			
ActivityThread.handleBindApplication方法则完成Application的创建已经ContentProvider的创建，分为如下几个步骤：

1、创建ContextImpl和Instrumentation

2、创建Application

3、启动当前进程的ContentProvider并调用onCreate方法

4、调用Application的onCreate方法


经过上面4个步骤，ContentProvider已经成功启动，并且其所在进程的Application要已经启动，其他应用就可以通过AMS来访问换个ContentProvider了。需要注意的是，这里的ContentProvider并不是原始的ContentProvider，而是ContentProvider的Binder对象IContentProvider，具体实现是ContentProvider.Transport。ContentProvider.Transport的query方法返回的是ContentProvider.this.query，执行结果后并通过Binder返回给调用者，至此，这个调用过程就完成了。



	
	
		
