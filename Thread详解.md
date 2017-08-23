Java中实现多线程的几种方式：继承Thread和实现Runnable接口，区别在于一个是继承类，一个是实现接口，所以优缺点都从这点出发分析得到

##Thread有四种状态：新建，就绪，运行，阻塞 ##

新建状态：用new语句创建的线程对象处于新建状态，此时它和java对象一样，仅仅在堆中分配了内存

就绪状态：当Thread调用start方法时，线程处于就绪状态。处于这个状态的线程位于可运行池中，等待获得CPU的使用权

运行状态：处于运行状态的线程占用CPU，执行程序的代码

阻塞状态：当线程处于阻塞状态时，java虚拟机不会给线程分配CPU，直到线程重新进入就绪状态，它才有机会转到运行状态


## 阻塞状态的三种情况 ##

1、位于对象等待池中的阻塞状态：当线程运行时，如果执行了某个对象的wait方法，java虚拟机就会把线程放入到这个对象的等待池中

2、位于对象锁中的阻塞状态：线程访问到某个对象的同步锁时，如果该对象的同步锁已经被别的对象所访问，此时JVM就会把线程放到这个对象的锁池中

3、其他的阻塞状态：线程调用了sleep（）方法，或者调用了其他线程的join方法（等待线程执行完毕），或者发出I/O请求时，就会进入这个状态

## sJava 提供了大量方法来支持阻塞，下面让我们逐一分析 ##

1. sleep() 方法：sleep() 允许 指定以毫秒为单位的一段时间作为参数，它使得线程在指定的时间内进入阻塞状态，不能得到CPU 时间，指定的时间一过，线程重新进入可执行状态。
典型地，sleep() 被用在等待某个资源就绪的情形：测试发现条件不满足后，让线程阻塞一段时间后重新测试，直到条件满足为止。
2. suspend() 和 resume() 方法：两个方法配套使用，suspend()使得线程进入阻塞状态，并且不会自动恢复，必须其对应的resume() 被调用，才能使得线程重新进入可执行状态。典型地，suspend() 和 resume() 被用在等待另一个线程产生的结果的情形：测试发现结果还没有产生后，让线程阻塞，另一个线程产生了结果后，调用 resume() 使其恢复。
3. yield() 方法：yield() 使得线程放弃当前分得的 CPU 时间，但是不使线程阻塞，即线程仍处于可执行（也就是上面的就绪）状态，随时可能再次分得 CPU 时间。调用 yield() 的效果等价于调度程序认为该线程已执行了足够的时间从而转到另一个线程。
4. wait() 和 notify() 方法：两个方法配套使用，wait() 使得线程进入阻塞状态，它有两种形式，一种允许 指定以毫秒为单位的一段时间作为参数，另一种没有参数，前者当对应的 notify() 被调用或者超出指定时间时线程重新进入可执行状态，后者则必须对应的 notify() 被调用。

初看起来它们与 suspend() 和 resume() 方法对没有什么分别，但是事实上它们是截然不同的。区别的核心在于，前面叙述的所有方法，阻塞时都不会释放占用的锁（如果占用了的话），而这一对方法则相反。

上述的核心区别导致了一系列的细节上的区别。

首先，前面叙述的所有方法都隶属于 Thread 类，但是这一对却直接隶属于 Object 类，也就是说，所有对象都拥有这一对方法。初看起来这十分不可思议，但是实际上却是很自然的，因为这一对方法阻塞时要释放占用的锁，而锁是任何对象都具有的，调用任意对象的 wait() 方法导致线程阻塞，并且该对象上的锁被释放。而调用 任意对象的notify()方法则导致因调用该对象的 wait() 方法而阻塞的线程中随机选择的一个解除阻塞（但要等到获得锁后才真正可执行）。

其次，前面叙述的所有方法都可在任何位置调用，但是这一对方法却必须在 synchronized 方法或块中调用，理由也很简单，只有在synchronized 方法或块中当前线程才占有锁，才有锁可以释放。同样的道理，调用这一对方法的对象上的锁必须为当前线程所拥有，这样才有锁可以释放。因此，这一对方法调用必须放置在这样的 synchronized 方法或块中，该方法或块的上锁对象就是调用这一对方法的对象。若不满足这一条件，则程序虽然仍能编译，但在运行时会出现IllegalMonitorStateException 异常。

wait() 和 notify() 方法的上述特性决定了它们经常和synchronized 方法或块一起使用，将它们和操作系统的进程间通信机制作一个比较就会发现它们的相似性：synchronized方法或块提供了类似于操作系统原语的功能，它们的执行不会受到多线程机制的干扰，而这一对方法则相当于 block 和wakeup 原语（这一对方法均声明为 synchronized）。它们的结合使得我们可以实现操作系统上一系列精妙的进程间通信的算法（如信号量算法），并用于解决各种复杂的线程间通信问题。

关于 wait() 和 notify() 方法最后再说明两点：

第一：调用 notify() 方法导致解除阻塞的线程是从因调用该对象的 wait() 方法而阻塞的线程中随机选取的，我们无法预料哪一个线程将会被选择，所以编程时要特别小心，避免因这种不确定性而产生问题。

第二：除了 notify()，还有一个方法 notifyAll() 也可起到类似作用，唯一的区别在于，调用 notifyAll() 方法将把因调用该对象的 wait() 方法而阻塞的所有线程一次性全部解除阻塞。当然，只有获得锁的那一个线程才能进入可执行状态。

谈到阻塞，就不能不谈一谈死锁，略一分析就能发现，suspend() 方法和不指定超时期限的 wait() 方法的调用都可能产生死锁。遗憾的是，Java 并不在语言级别上支持死锁的避免，我们在编程中必须小心地避免死锁。

## 终止线程的三种方法 ##

1、使用退出标志，使线程正常退出，也就是run方法完成后线程终止。（使用共享变量（shared variable）发出信号，让线程自己退出）最简单的就是使用一个布尔类型的变量来判断。
public volatile boolean exit = false;   
     public void run() { 
          while (!exit){  
              //do something  
         }  
}   
2、使用Thread的interrupt()方法中断线程

3、使用Thread的stop()方法来强制终止线程（这个方法已经被废弃了，因为和suspend，resume方法一样会造成不可预料的结果）

可以看下这篇文章

Java中为什么反对使用Thread.stop, Thread.suspend, Thread.resume and Runtime.runFinalizersOnExit?

[http://blog.csdn.net/loongshawn/article/details/53034176](http://http://blog.csdn.net/loongshawn/article/details/53034176 "java中为什么反对使用Thread.stop, Thread.suspen, Thread.resume and Runtime.runFinalizersOnExit?")
## sleep()方法和yield()方法的区别 ##

sleep()：让当前正在执行的线程休眠，有一种用法可以代替yield()方法，就是sleep（0）

yield()： 暂停当前正在执行的线程对象，并执行其他线程，也就是让出CPU的使用

sleep()和yeild()的区别如下：

1、sleep（）方法会给其他线程运行的机会，而不考虑线程的优先级，因此会给较低线程一个运行的机会，而yield方法不会考虑较低优先级的线程，只考虑给相同优先级或者更高优先级的线程一个机会

2、当线程sleep(long mills)方法后，将转到阻塞状态，参数mills指定睡眠时间。当线程执行yield方法后，将转到就绪状态

3、线程执行了sleep()后抛出一个InterruptedException异常，而yeild方法没有抛出任何异常信息

4、sleep比yield具有更好的移植性

## sleep()方法和wait()方法的区别 ##

sleep()方法和wait()方法都是停止当前线程。sleep方法是Thread类的方法，执行该方法会让线程暂停执行指定的时间，将执行机会给其他的线程，但是不会释放对象锁。

wait()方法必须在同步锁中执行，而且它是Object类的方法，执行时会释放对象锁，进入到等待此对象的等待锁定池，只有针对此对象发出notify（或者notifyAll）才会进入对象锁定池准备获取对象锁进入运行状态。

## Synchronized和Lock的异同 ##

主要相同点：Lock能完成synchronized所实现的所有功能

主要不同点：synchronized持有锁资源。Lock有比synchronized更精确的线程语义和更好的性能。synchronized会自动释放锁，而Lock一定要求程序员手工释放，并且必须在finally从句中释放。Lock还有更加强大的功能，例如，它的tryLock()方法可以非阻塞方式去拿锁。

	public void run() {  
       // TODO Auto-generated method stub  
       int count = 10;  
       while( count > 0 ) {  
             try {  
                  lock.lock();  
                  count --;  
                  System. out.print( "B");  
             } finally {  
                  lock.unlock(); //主动释放锁  
                  try {  
                      Thread. sleep(91L);  
                  } catch (InterruptedException e) {  
                      // TODO Auto-generated catch block  
                      e.printStackTrace();  
                  }  
             }  
 	 }  


当竞争不是很激烈时，synchronized使用的是轻量级锁或者偏向锁，这两种锁都能减少轮询或者阻塞的发生，与之相比Lock要将未获得锁的线程放入等待队列阻塞，带来上下文切换的开销，此时synchronized的效率更高些。

当竞争激烈时，synchronized升级为重量级锁，由于synchronized的出对速度相比Lock要慢，所以Lock的效率会更高些。

一般对于数据结构设计或者框架的设计都倾向使用Lock而非synchronized
