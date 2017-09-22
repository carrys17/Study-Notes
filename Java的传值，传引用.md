#Java的传值，传引用

先来一个简单的？！！
    
    List<List<String>> fatherList = new LinkedList<>();
    List<String> childList = new ArrayList<>();
    childList.add("before");
    fatherList.add(childList);
    childList.add("after");
    System.out.println("father ------> "+ fatherList.toString());
    
上面这个程序输出的结果为： 

father ------> [[before, after]]

可以看到这里的child是整个传进来，而且是随着它的改变father也会跟着改变。所以这是传引用（也即是child的所指向的地址）。 


--------------------------

下面看这个例子
    
    String ss1 = "hello";
    String ss2 = "byebye";
    System.out.println(ss1 + "----" +ss2); // hello—--byebye
    change(ss1,ss2);
    System.out.println(ss1 + "----" +ss2); // hello---byebye
    
    
    StringBuffer sb1 = new StringBuffer("hello");
    StringBuffer sb2 = new StringBuffer("byebye");
    System.out.println(sb1 + "----" + sb2); // hello----byebye
    change(sb1,sb2);
    System.out.println(sb1 + "----" + sb2); // hello----byebyebyebye
    
    public static void change(String ss1,String ss2){
    ss1 = ss2;
    ss2 = ss1 + ss2;
    }
    
    public static void change(StringBuffer sb1, StringBuffer sb2){
    sb1 = sb2;
    sb2 = sb2.append(sb1);
    }


这个例子先思考着，解释在后面

-------------------------
![](https://i.imgur.com/36KfZdI.png)
![](https://i.imgur.com/P33ZA5d.png)
![](https://i.imgur.com/ZfymYKc.png)
![](https://i.imgur.com/ZCouJ5o.png)
![](https://i.imgur.com/uDPjnDJ.png)
![](https://i.imgur.com/FjaJJGX.png)

-----------------
最后再看一个例子

![](https://i.imgur.com/41saXzG.png)
![](https://i.imgur.com/GekkZjT.png)
![](https://i.imgur.com/0I7NnG1.png)

输出为

![](https://i.imgur.com/wqtoPub.png)

这里的关键就是change方法里面的第一句，new一个新的对象出来了，去掉的话就可以输出18了
