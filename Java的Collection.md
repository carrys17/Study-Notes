 # Java的Collection


先来看总的一个图

![](https://i.imgur.com/LekW3bW.jpg)

其中加粗的就是常用的几个
-
![](https://i.imgur.com/8WZNnbW.png)

现在看下面的这个程序，其中的注释也写的非常清楚了

![](https://i.imgur.com/3xb6QRR.png)

它的输出为

![](https://i.imgur.com/KR5SJZ5.png)
-
## Set

Set是一种不包含重复的元素的Collection，即随便的两个元素e1和e2都有e1.equals（e2）=false，Set最多有一个null元素。

请重视：必须警惕操纵可变对象（Mutable Object）。若是一个Set中的可变元素改变了自身状况导致Object.equals（Object）=true将导致一些问题。



HashSet 所维护的顺序是没有规则可循的，出于速度原因的考虑，它是用散列

TreeSet 将元素存储在红黑树数据结构中，它的数据是按升序的结果来保存的。（但是不是按照词典的顺序，A，B，a，b）如果想按照词典的顺序（A，a, B , b）可以这样初始化  Set<String> set = new TreeSet<String>(String.CASE_INSENSITIVE_ORDER);

LinkedHashSet 因为速度查询原因也使用了散列，但是看起来它使用了链表来维护元素的插入顺序




## List
List是有序的Collection，应用此接口可以或许正确的把握每个元素插入的地位。用户可以或许应用索引（元素在List中的地位，类似于数组下标）来接见List中的元素，这类似于Java的数组。和Set不同，List容许有雷同的元素。

ArrayList  它善于随机访问元素，但是在List的中间插入和移除元素时较慢

LinkedList  它通过代价较低的在List中间进行的插入和删除操作，提供了优化的顺序访问。
但是在随机访问方面相对较慢，不过它的特性集较ArrayList更大

LinkedList : 它这里有几个方法，需要注意一下

getFirst（）和 element ( ) 完全一样，都是返回列表的头（第一个元素），而不移除它，如果List为空，则抛出NoSuchElementException

peek（）方法与这两个方式只是稍有差异，它在列表为空时返回null



removeFirst（）和 remove（）完全一样，它们移除并返回列表的头，如果列表为空则抛出NoSuchElementException。

poll（）稍有差异，它在列表为空时返回null

addFirst()与add()和addLast()相比，addFirst()将某个元素插入到列表的头部,而add()和addLast()将某个元素插入到列表的尾部

removeLast（）移除并返回列表的最后一个元素




## Vector

Vector很是类似ArrayList，然则Vector是同步的。由Vector创建的Iterator，固然和ArrayList创建的Iterator是同一接口，然则，因为Vector是同步的，当一个Iterator被创建并且正在被应用，另一个线程改变了Vector的状况（例如，添加或删除了一些元素），这时调用Iterator的办法时将抛出ConcurrentModificationException，是以必须捕获该异常。Vector因为应用了synchronized办法（线程安然）所以机能上比ArrayList要差


ArrayList和Vector的性能分析

1、Vector是多线程安全的，而ArrayList不是。在Vector的源码中可以看出，Vector类中的方法很多有synchronized进行修饰，这样就导致Vector的效率低于ArrayList

2、Vector和ArrayList的底层实现都是Object[ ]，但是当空间不足时，两个类的增加方式是不同的。通常情况下，Vector增加原来空间的一倍，ArrayList增加原来空间的一半，因此，在同等条件下，ArrayList扩容量小于Vector，在性能上更高一些。





## Stack
Stack  ，栈，用LinkedList来实现，

其中的push 是把元素放入栈顶

pop返回并移除栈顶元素

peek是返回栈顶元素
##

![](https://i.imgur.com/n4nbKmc.png)

![](https://i.imgur.com/p0VixwO.png)


## Queue


offer() 方法是与Queue相关的方法之一，它在允许的情况下，将一个元素插入到队尾，或者返回false。

peek（）和element（）都将在不移除的情况下返回队头，但是peek（）在队列为空是返回null，而element（）会抛出NoSuchElementException异常

poll（）和remove（）将移除并返回队头，但是poll（）在队列为空时返回null，而remove（）会抛出NoSuchElementException异常


PriorityQueue  优先级队列

可以实现下一个弹出的元素是最需要的元素（具有最高的优先级）

![](https://i.imgur.com/q5knReC.png)

输出结果

![](https://i.imgur.com/NVP6jt9.png)

##

**各种Queue和栈的行为，都是由LinkedList提供**


因为这篇写的只是Java的Collection，所以没有ArrayMap和SparseMap，这两个是Android里面的，用来代替HashMap来实现内存优化的。在另外的文章有详讲
