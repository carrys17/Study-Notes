
    bindService
       ↓
    mBase.bindService  // mBase的类型是ContextImpl
       ↓
    mBase.bindServiceCommon{
    	// 1、将ServiceConnection转换为ServiceDispatcher.InnerConnection
    	LoadedApk.getServiceDispatcher
   	   ` // 2、AMS.bindService``
    	ActivityManagerNative.getDefault().bindService
    }
    	↓
    mServices.bindServiceLocked//mServices的类型是ActiveServices
   	  ` ↓`
    mServices.bringUpServiceLocked
        ↓
    mServices.realStartServiceLocked{
       	app.thread.scheduleBindService{
    		sendMessage(H.BIND_SERVICE，s );
    	}
    }
    	↓
    ActivityThread.H.handleBindServie
    
handleBindService方法如下

    private void handleBindService(BindServiceData data) {
    	Service s = mServices.get(data.token); //首先根据Service的token取出Service对象
   	  ` if (DEBUG_SERVICE)`
    		Slog.v(TAG, "handleBindService s=" + s + " rebind=" + data.rebind);
       	if (s != null) {
    		try {
   			 `data.intent.setExtrasClassLoader(s.getClassLoader());`
   			` data.intent.prepareToEnterProcess();`
    		  try {
   			` if (!data.rebind) {`
    			IBinder binder = s.onBind(data.intent);//然后调用Service的onBind方法
    			ActivityManagerNative.getDefault().publishService(   //此时客户端还不知道连接上了Service，所以要调用客户端的ServiceConnection的onServiceConnection方法，这个方法在publishService中实现
    			data.token, data.intent, binder);
    		} else {
    			s.onRebind(data.intent);
    			ActivityManagerNative.getDefault().serviceDoneExecuting(
    			data.token, SERVICE_DONE_EXECUTING_ANON, 0, 0);
    		}
    		ensureJitEnabled();
    	} catch (RemoteException ex) {
       	 	throw ex.rethrowFromSystemServer();
   		`}`
    	} catch (Exception e) {
    	if (!mInstrumentation.onException(s, e)) {
    		throw new RuntimeException(
    		"Unable to bind to service " + s
    		+ " with " + data.intent + ": " + e.toString(), e);
    		}
    		}
    	}
    }

ActivityManagerNative.getDefault()的publishService方法
    
    public void publishService(IBinder token, Intent intent, IBinder service) {
	    // Refuse possible leaked file descriptors
	    if (intent != null && intent.hasFileDescriptors() == true) {
	        throw new IllegalArgumentException("File descriptors passed in Intent");
	    }
	
	    synchronized(this) {
	        if (!(token instanceof ServiceRecord)) {
	            throw new IllegalArgumentException("Invalid service token");
	        }
	        mServices.publishServiceLocked((ServiceRecord)token, intent, service);
	    }
	}

从上面的源码可以看出，publishService方法将调用publishServiceLocked方法，而publishServiceLocked的源码中，只有下面这个是关键 

    c.conn.connected(r.name, service); // c为ConnectionRecord，c.conn就是ServiceDispatcher.InnerConnection，service就是Service的onBind返回的Binder对象

而ServiceDispatcher.InnerConnection的connected方法又调用的是ServiceDispatcher的connected方法

	public void connetced(ComponentName name, IBinder service){
	    if(mActivityThread!=null){
	        mActivityThread.post(new RunConnection(name, service ,0));
	    }else{
	        doConnected(name,service);
	    }
	}

这样一来，RunConnection就进过H的post方法从而运行在主线程中，因此，客户端ServiceConnection中的方法是在主线程中被回调的。

RunConnection的run方法也是简单的调用了ServiceDispatcher的doConnected方法，由于ServiceDispatcher的内部保存了客户端的ServiceConnection对象，因此它可以很方便地调用ServiceConnection对象的onServiceConnection方法。

客户端的onServiceConnection执行后，Service的绑定也就完成了。