<h1>存储器区块错误</h1>
（英语：Segmentation fault，经常被缩写为segfault），又译为存储器段错误，也称访问权限冲突（access violation），是一种程序错误。

它会出现在当程序企图访问CPU无法定址的存储器区块时。当错误发生时，硬件会通知操作系统产生了存储器访问权限冲突的状况。操作系统通常会产生核心转储（core dump）以方便程序员进行调试。通常该错误是由于调用一个地址，而该地址为空（NULL）所造成的，例如链表中调用一个未分配地址的空链表单元的元素。数组访问越界也可能产生这个错误。
<h3>网友总结的Linux开发中可能遇到Segmentation fault的情况</h3>

<p  >

1 使用非法的内存地址（指针），包括使用未经初始化及已经释放的指针、不存在的地址、受系统保护的地址，只读的地址等，这一类也是最常见和最好解决的段错误问题，使用GDB print一下即可知道原因。

2 内存读/写越界。包括数组访问越界，或在使用一些写内存的函数时，长度指定不正确或者这些函数本身不能指定长度，典型的函数有strcpy(strncpy)，sprintf(snprint)等等。

3 对于C++对象，应该通过相应类的接口来去内存进行操作，禁止通过其返回的指针对内存进行写操作，典型的如string类的c_str()接口，如果你强制往其返回的指针进行写操作肯定会段错误的，因为其返回的地址是只读的。

4 函数不要返回其中局部对象的引用或地址，当函数返回时，函数栈弹出，局部对象的地址将失效，改写或读这些地址都会造成未知的后果。

5 避免在栈中定义过大的数组，否则可能导致进程的栈空间不足，此时也会出现段错误，同样的，在创建进程/线程时如果不知道此线程/进程最大需要多少栈空间时最好不要在代码中指定栈大小，应该使用系统默认的，这样问题比较好查，ulimit一下即可知道。这类问题也是为什么我的程序在其他平台跑得好好的，为什么一移植到这个平台就段错误了。

6 操作系统的相关限制，如：进程可以分配的最大内存，进程可以打开的最大文件描述符个数等，在Linux下这些需要通过ulimit、setrlimit、sysctl等来解除相关的限制，这类段错误问题在系统移植中也经常发现，以前我们移植Linux的程序到VxWorks下时经常遇到（VxWorks要改内核配置来解决）。

7 多线程的程序，涉及到多个线程同时操作一块内存时必须进行互斥，否则内存中的内容将不可预料。

8 在多线程环境下使用非线程安全的函数调用，例如 strerror 函数等。

9 在有信号的环境中，使用不可重入函数调用，而这些函数内部会读或写某片内存区，当信号中断时，内存写操作将被打断，而下次进入时将无法避免地出错。

10 跨进程传递某个地址，传递的都是经过映射的虚拟地址，对另外一个进程是不通用的。

11 某些有特殊要求的系统调用，例如epool_wait，正常情况下使用close关闭一个套接字后，epool会不再返回这个socket上的事件，但是如果你使用dup或dup2操作，将导致epool无法进行移除操作，此时再进行读写操作肯定是段错误的。

</p>


<style>
  h1
  {
    color:red;
    text-decoration:underline;
  }

/* p {
	font-family:"Times New Roman";
	font-size:20px;
    color:red;
} */

</style>