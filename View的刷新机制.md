#在Android中，父View负责刷新、布局显示子View，子View刷新时通知父View来完成。#

子View跟父View建立关系的方式有两种：

1、View加入ViewGroup中

	private void addViewInner(View child, int index, LayoutParams params, boolean preventRequestLayout) {  
	         .....  
	             // tell our children  
	         if (preventRequestLayout) {  
	             child.assignParent(this);  
	         } else {  
	             child.mParent = this;  
	         }  
	        .....  
	}

2、DecorView注册给WindowManagerImpl时，产生一个 ViewRoot作为其父View

	public void setView(View view, WindowManager.LayoutParams attrs, View panelParentView){  
	     .....  
	     view.assignParent(this);  
	     ....  
	}  

AttachInfo是在View第一次attach到Window时，ViewRoot传给自己的子View的。这个AttachInfo最后会顺着布局体系一直传递到最底层的View。

View.dispatchAttachedToWindow

	void dispatchAttachedToWindow(AttachInfo info, int visibility) {
	    mAttachInfo = info;
	   ...
	}

ViewGroup.dispatchAttachedToWindow (ViewGroup继承View)

	@Override
	void dispatchAttachedToWindow(AttachInfo info, int visibility) {
	    mGroupFlags |= FLAG_PREVENT_DISPATCH_ATTACHED_TO_WINDOW;
	    super.dispatchAttachedToWindow(info, visibility);
	    mGroupFlags &= ~FLAG_PREVENT_DISPATCH_ATTACHED_TO_WINDOW;
	
	    final int count = mChildrenCount;
	    final View[] children = mChildren;
	    for (int i = 0; i < count; i++) {
	        final View child = children[i];
	        child.dispatchAttachedToWindow(info,
	                combineVisibility(visibility, child.getVisibility()));
	    }
	    final int transientCount = mTransientIndices == null ? 0 : mTransientIndices.size();
	    for (int i = 0; i < transientCount; ++i) {
	        View view = mTransientViews.get(i);
	        view.dispatchAttachedToWindow(info,
	                combineVisibility(visibility, view.getVisibility()));
	    }
	}

-----------------------------------------------------------------
# 刷新机制#

View.invalidate

	public void invalidate() {
	    invalidate(true);
	}
	
	
	void invalidate(boolean invalidateCache) {
	    invalidateInternal(0, 0, mRight - mLeft, mBottom - mTop, invalidateCache, true);
	}
	
	void invalidateInternal(int l, int t, int r, int b, boolean invalidateCache,
	        boolean fullInvalidate) {
	    if (mGhostView != null) {
	        mGhostView.invalidate(true);
	        return;
	    }
	
	    if (skipInvalidate()) {
	        return;
	    }
	
	    if ((mPrivateFlags & (PFLAG_DRAWN | PFLAG_HAS_BOUNDS)) == (PFLAG_DRAWN | PFLAG_HAS_BOUNDS)
	            || (invalidateCache && (mPrivateFlags & PFLAG_DRAWING_CACHE_VALID) == PFLAG_DRAWING_CACHE_VALID)
	            || (mPrivateFlags & PFLAG_INVALIDATED) != PFLAG_INVALIDATED
	            || (fullInvalidate && isOpaque() != mLastIsOpaque)) {
	        if (fullInvalidate) {
	            mLastIsOpaque = isOpaque();
	            mPrivateFlags &= ~PFLAG_DRAWN;
	        }
	
	        mPrivateFlags |= PFLAG_DIRTY;
	
	        if (invalidateCache) {
	            mPrivateFlags |= PFLAG_INVALIDATED;
	            mPrivateFlags &= ~PFLAG_DRAWING_CACHE_VALID;
	        }
	
	        // Propagate the damage rectangle to the parent view.
	        final AttachInfo ai = mAttachInfo;
	        final ViewParent p = mParent;
	        if (p != null && ai != null && l < r && t < b) {
	            final Rect damage = ai.mTmpInvalRect;
	            damage.set(l, t, r, b);
	            p.invalidateChild(this, damage);
	        }
	
	        // Damage the entire projection receiver, if necessary.
	        if (mBackground != null && mBackground.isProjected()) {
	            final View receiver = getProjectionReceiver();
	            if (receiver != null) {
	                receiver.damageInParent();
	            }
	        }
	
	        // Damage the entire IsolatedZVolume receiving this view's shadow.
	        if (isHardwareAccelerated() && getZ() != 0) {
	            damageShadowReceiver();
	        }
	    }
	}


**子view在invalidate（）中调用viewParent.invalidateChild（）方法。（子view调用 invalidate时，找到自己的父view并将 AttachInfo信息告诉父view刷新自己）这是一个从下向上回溯的过程，每一层的父View都将自己的显示区域与传入的刷新Rect做交集（刷新需要绘制的地方）。这个过程到ViewRoot那里结束，由ViewRoot对这个最终的刷新区域做刷新。**

ViewRoot.invalidateChild    最终会调用到**scheduleTraversals**方法（中间经过invalidateChild --> invalidateChildInParent-->invalidateRectOnScreen-->scheduleTraversals）

	public void invalidateChild(View child, Rect dirty) {  
	    scheduleTraversals();  
	}
	 
最后：

Invalidate()方法不能放在线程中，所以需要把Invalidate()方法放在Handler中。在MyThread中只需要在规定时间内发送一个Message给handler，当Handler接收到消息就调用Invalidate()方法。

postInvalidate()方法就可以放在线程中做处理，就不需要Handler。

而上面的新线程MyThread可以放在OnCreate()中开始，也可以放在OnStart()中开始。

当Invalidate()被调用的时候，View的OnDraw()就会被调用，Invalidate()必须是在UI线程中被调用，如果在新线程中更新视图的就调用postInvalidate()。






