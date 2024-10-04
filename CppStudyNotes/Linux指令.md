
# Linux 指令

ls                  用来显示目标列表
cd [path]           用来切换工作目录
pwd                 以绝对路径的方式显示用户当前工作目录
man [command]       查看Linux中的指令帮助、配置文件帮助和编程帮助等信息
apropos [whatever]  在一些特定的包含系统命令的简短描述的数据库文件里查找关键字
echo [string]       打印一行文本，参数“-e”可激活转义字符
cat [file]          连接文件并打印到标准输出设备上
less [file]         允许用户向前或向后浏览文字档案的内容
mv [file1] [file2]  用来对文件或目录重新命名，或者将文件从一个目录移到另一个目录中
cp [file1] [file2]  用来将一个或多个源文件或者目录复制到指定的目的文件或目录
rm [file]           可以删除一个目录中的一个或多个文件或目录，也可以将某个目录及其下属的所有文件及其子目录均删除掉
ps                  用于报告当前系统的进程状态
top                 实时查看系统的整体运行情况
kill                杀死一个进程
ifconfig            查看或设置网络设备
ping                查看网络上的主机是否工作
netstat             显示网络连接、路由表和网络接口信息
nc(netcat)          建立 TCP 和 UDP 连接并监听
su                  切换当前用户身份到其他用户身份
touch [file]        创建新的空文件
mkdir [dir]         创建目录
chmod               变更文件或目录的权限
chown               变更某个文件或目录的所有者和所属组
nano / vim / emacs  字符终端的文本编辑器
exit                退出 shell


当程序运行的过程中异常终止或崩溃，操作系统会将程序当时的内存、寄存器状态、堆栈指针、内存管理信息等记录下来，保存在一个文件中，这种行为就叫做核心转储（Core Dump）。


会产生核心转储的信号
Signal	Action	Comment
SIGQUIT	Core	Quit from keyboard
SIGILL	Core	Illegal Instruction
SIGABRT	Core	Abort signal from abort
SIGSEGV	Core	Invalid memory reference
SIGTRAP	Core	Trace/breakpoint trap


开启核心转储
输入命令 ulimit -c，输出结果为 0，说明默认是关闭的。
输入命令 ulimit -c unlimited 即可在当前终端开启核心转储功能。
如果想让核心转储功能永久开启，可以修改文件 /etc/security/limits.conf，增加一行：