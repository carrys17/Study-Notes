
从intent.startService分析Service的启动过程    

    intent.startService(intent);
  			  ↓
    mBase.startService// mBase的类型是ContextImpl，当activity被创建时会通过attach方法将一个ContextImpl对象关联起来，这个ContextImpl就是mBase
   			  ↓
    mBase.startServiceCommon
  			  ↓
    ActivityManagerNative.getDefault().startService   //ActivityManagerNative.getDefault()实际上就是一个AMS
		      ↓
    mServices.startServiceLocked;   // mServices的类型是ActiveServices，它是一个辅助AMS进行Service管理的类，包括 Service的启动、绑定和停止等
		      ↓
    mServices.startServiceInnerLocked;
		      ↓
    mServices.bringUpServiceLocked;
		      ↓
    mServices.realStartServiceLocked(...){
       // 创建Service对象并调用onCreate 
    app.thread.scheduleCreateService(r, r.serviceInfo,   //  app.thread 就是ApplicationThread
    mAm.compatibilityInfoForPackageLocked(r.serviceInfo.applicationInfo),  
       app.repProcState);   
    ...
    //  调用Service的其他方法，比如onStartCommand
    sendServiceArgsLocked;   
    
    }
 		      ↓
    ApplicationThread.scheduleCreateService( ...){
     sendMessage(H.CREATE_SERVICE, s);
    }
		      ↓
    H.handleMessage(){  // H的定义在ActivityThread中
    case CREATE_SERVICE:
    handleCreateService;
    case ...
    }
		      ↓
    ActivityThread.handleCreateService
    
handleCreateService的方法源码如下：
	
    private void handleCreateService(CreateServiceData data) {
    // If we are getting ready to gc after going to the background, well
    // we are back active so skip it.
    unscheduleGcIdler();
    
    LoadedApk packageInfo = getPackageInfoNoCheck(
    data.info.applicationInfo, data.compatInfo);
    Service service = null;
    try {
    java.lang.ClassLoader cl = packageInfo.getClassLoader();1
    service = (Service) cl.loadClass(data.info.name).newInstance();
    } catch (Exception e) {
    if (!mInstrumentation.onException(service, e)) {
    throw new RuntimeException(
    "Unable to instantiate service " + data.info.name
    + ": " + e.toString(), e);
    }
    }
    
    try {
    if (localLOGV) Slog.v(TAG, "Creating service " + data.info.name);
    
    ContextImpl context = ContextImpl.createAppContext(this, packageInfo);2
    context.setOuterContext(service);
    
    Application app = packageInfo.makeApplication(false, mInstrumentation);   3
    service.attach(context, this, data.info.name, data.token, app,
    ActivityManagerNative.getDefault());
    service.onCreate();4
    mServices.put(data.token, service);
    try {
    ActivityManagerNative.getDefault().serviceDoneExecuting(
    data.token, SERVICE_DONE_EXECUTING_ANON, 0, 0);
    } catch (RemoteException e) {
    throw e.rethrowFromSystemServer();
    }
    } catch (Exception e) {
    if (!mInstrumentation.onException(service, e)) {
    throw new RuntimeException(
    "Unable to create service " + data.info.name
    + ": " + e.toString(), e);
    }
    }
    }
    
ActivityThread的handleCreateService方法主要完成如下几件事：

1、通过类加载器创建Service的实例

2、创建Application对象并调用其onCreate，当然Application的创建只有一次

3、创建ContextImpl对象并通过Service的attach方法建立二者之间的关系

4、调用Service的onCreate方法并将Service对象储存到ActivityThread的一个列表中final ArrayMap<IBinder, Service> mServices = new ArrayMap<>();


由于Service的onCreate方法执行了，这也意味着Service已经启动了。除此之外，ActivityThread中还会通过handleServiceArgs方法调用Service的onStartCommand方法


    private void handleServiceArgs(ServiceArgsData data) {
    Service s = mServices.get(data.token);
    if (s != null) {
        try {
            if (data.args != null) {
                data.args.setExtrasClassLoader(s.getClassLoader());
                data.args.prepareToEnterProcess();
            }
            int res;
            if (!data.taskRemoved) {
                res = s.onStartCommand(data.args, data.flags, data.startId);
            } else {
                s.onTaskRemoved(data.args);
                res = Service.START_TASK_REMOVED_COMPLETE;
            }

            QueuedWork.waitToFinish();

            try {
                ActivityManagerNative.getDefault().serviceDoneExecuting(
                        data.token, SERVICE_DONE_EXECUTING_START, data.startId, res);
            } catch (RemoteException e) {
                throw e.rethrowFromSystemServer();
            }
            ensureJitEnabled();
        } catch (Exception e) {
            if (!mInstrumentation.onException(s, e)) {
                throw new RuntimeException(
                        "Unable to start service " + s
                        + " with " + data.args + ": " + e.toString(), e);
            }
        }
    }
	}


