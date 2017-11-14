初始化和清理正是涉及安全的两个问题。

1、用构造器确保初始化

如果你的类没有构造器，编译器会自动帮我们创建一个

构造器的重载，参数个数或者顺序或者类型的不同

在构造器中调用构造器，一定在句首使用，而且不能调用两次，另外禁止在非构造方法中调用构造器

2、基本数据类型的重载

 char → int   自动，扩展转换
 
 double  →  （char）x 窄化转换


3、根据方法的返回值来区分重载方法是行不通的。

4、this关键字

通常写this的时候，都是指“这个对象”或者“当前对象”。

5、static方法就是没有this的方法；static方法内部不能调用非静态方法；static 可以直接被类调用。


清理：
1、对象可能不被垃圾回收
2、垃圾回收并不等于“构析”（c++销毁对象时必须用到这个函数）
3、垃圾回收只与内存有关

finalize（）方法：  一旦垃圾回收器准备好释放对象占用的存储空间，将首先调用其finalize( )方法，并且在下一次垃圾回收动作发生时，才会真正回收对象占用的内存。

无论对象是如何创建的，垃圾回收都会负责释放对象占据的所有内存。

这将对finalize（）的需求限制到一种特殊情况，即通过某种创建对象方式以外的方式为对象分配了存储空间。

如果JVM并未面临内存耗尽的情形，它是不会浪费时间去执行垃圾回收以恢复内存的。

	class Book{
	    boolean isCheckOut = false;
	    Book(boolean isCheckOut){
	        this.isCheckOut= isCheckOut;
	    }
	    
	    void checkIn(){
	        this.isCheckOut= false;   
	    }
	
	    protected void finalize(){
	        if(isCheckOut){
	            Syso("出错，必须先签入（checkIn）");
	            // 也可以用下面的方式
	            super.finalize();
	        }
	    }
	
	    public statci void main(String[] args){
	        Book book = new Book(true);
	        book.checkIn();
	        
	        new Book(true);
	        
	        System.gc();
	        
	    }
	}  


这个程序会输出  出错，必须先签入（checkIn）

因为每次回收前调用到finalize（）方法，而在这个方法中会判断是否为false（已被签入，也就是该CheckIn（）方法有没有被调用），所以这是finalize的一种使用方式，用于验证终结条件。

2、垃圾回收器

gc调用时，会  回收空间  和 使堆中的对象紧凑排列。

3、成员初始化

局部变量必须初始化时赋值，下面这种就是会报错的。

	int i；
	i++；

如果是类成员变量就可以这样做，它们会有默认值。但是局部变量就不行

java可以在成员变量定义时为其赋值，c++不行

4、在类的内部，成员变量的初始化总是比成员方法先调用。

5、静态数据初始化
无论创建多少个对象，静态数据都只占用一份存储区域（静态成员变量只有在第一个对象创建的时候被初始化，此后不会再次被创建）
static 关键字不能用于局部变量，只能作用于域


![](https://i.imgur.com/z23GBsN.png)

6、enum枚举

![](https://i.imgur.com/VWC8UJQ.png)

在创建枚举时，编译器会自动添加一些有用的特性。例如

toString（） 用于显示某个enum实例的名字

ordinal( )用于表示某个特定enum常量的声明顺序

static values( ) 用于按照enum常量的声明顺序，产生有这些常量值构成的数组

![](https://i.imgur.com/DgT8SlB.png)

enum还有一个非常实用的特性，即它可以在switch语句内使用。
