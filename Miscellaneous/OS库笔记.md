
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [OS库的使用](#os库的使用)
    - [os.walk使用](#oswalk使用)
    - [os.access()使用](#osaccess使用)
      - [下面的值可以作为access()的模式参数传递来测试以下内容:](#下面的值可以作为access的模式参数传递来测试以下内容)
      - [返回:](#返回)
  - [os.chflags()使用](#oschflags使用)
      - [参数：](#参数)
  - [os.chmod()](#oschmod)
      - [参数:](#参数-1)
      - [Mode:](#mode)
  - [os.chroot()](#oschroot)
  - [os.getlogin()使用](#osgetlogin使用)
  - [os.getenv()使用](#osgetenv使用)
  - [os.getpid()](#osgetpid)
  - [os.strerror()](#osstrerror)
  - [os.path.splitext()](#ospathsplitext)
  - [os.umask()](#osumask)
    - [查看当前的umask值：](#查看当前的umask值)
  - [os.linesep()](#oslinesep)
  - [os.pathsep()](#ospathsep)
  - [os.path.lexists()](#ospathlexists)
  - [os.cpu_count](#oscpu_count)
  - [os.system()](#ossystem)
    - [注意事项：](#注意事项)
  - [subprocess](#subprocess)
      - [参数说明：](#参数说明)
      - [为什么使用 PIPE？](#为什么使用-pipe)
      - [主要区别：](#主要区别)

<!-- /code_chunk_output -->



# OS库的使用
 1. os.getcwd() 获取当前工作目录，即当前python脚本工作的目录路径
 2. os.chdir("dirname")   改变当前脚本工作目录；相当于shell下cd
 3. os.curdir  返回当前目录: ('.')
 4. os.pardir  获取当前目录的父目录字符串名：('..')
 5. os.makedirs('dirname1/dirname2')可生成多层递归目录
 6. os.removedirs('dirname1')       若目录为空，则删除，并递归到上一级目录，如若也为空，则删除，依此类推
 7. os.mkdir('dirname')             生成单级目录；相当于shell中mkdir dirname
 8. os.rmdir('dirname')             删除单级空目录，若目录不为空则无法删除，报错；相当于shell中rmdir dirname
 9. os.listdir('dirname')           列出指定目录下的所有文件和子目录，包括隐藏文件，并以列表方式打印
10. os.remove()                     删除一个文件
11. os.rename("oldname","newname")  重命名文件/目录
12. os.stat('path/filename')        获取文件/目录信息
13. os.sep        输出操作系统特定的路径分隔符，win下为"\\",Linux下为"/"
14. os.linesep    输出当前平台使用的行终止符，win下为"\t\n",Linux下为"\n"
15. os.pathsep    输出用于分割文件路径的字符串
16. os.name       输出字符串指示当前使用平台。win->'nt'; Linux->'posix'
17. os.system("bash command")  运行shell命令，直接显示
18. os.environ    获取系统环境变量
19. os.path.abspath(path)   返回path规范化的绝对路径
20. os.path.split(path)     将path分割成目录和文件名二元组返回
21. os.path.dirname(path)   返回path的目录。其实就是os.path.split(path)的第一个元素
22. os.path.basename(path)  返回path最后的文件名。如何path以／或\结尾，那么就会返回空值。即os.path.split(path)的第二个元素
23. os.path.exists(path)    如果path存在，返回True；如果path不存在，返回False
24. os.path.isabs(path)     如果path是绝对路径，返回True
25. os.path.isfile(path)    如果path是一个存在的文件，返回True。否则返回False
26. os.path.isdir(path)     如果path是一个存在的目录，则返回True。否则返回False
27. os.path.join(path1[, path2[, ...]])  将多个路径组合后返回，第一个绝对路径之前的参数将被忽略
28. os.path.getatime(path)  返回path所指向的文件或者目录的最后存取时间
29. os.path.getmtime(path)  返回path所指向的文件或者目录的最后修改时间



### os.walk使用
OS.walk()通过自顶向下或自底向上遍历目录树生成文件名。对于根在目录top的树中的每个目录(包括top本身)，它会生成一个3元组(dirpath, dirnames, filename)。
os.walk 的返回值是一个生成器(generator),也就是说我们需要用循环不断的遍历它（不可以直接print），来获得所有的内容。

每次遍历的对象都是返回的是一个三元元组(root,dirs,files)

root  所指的是当前正在遍历的这个文件夹的本身的地址
dirs  是一个 list ，内容是该文件夹中所有的目录的名字(不包括子目录)
files 同样是 list , 内容是该文件夹中所有的文件(不包括子目录)
```python
# Driver function
import os
if __name__ == "__main__":
    for (root,dirs,files) in os.walk(r'C:\Users\hp\Desktop\apimemos', topdown=True):
        print (root)
        print (dirs)
        print (files)

C:\Users\hp\Desktop\apimemos
[]
['apidemos.com.txt', 'target.txt'] 
```

### os.access()使用

Python中的 os.access()方法使用真实的uid/gid来**测试对path的访问权限**。大多数操作使用有效的uid/gid，因此，可以在suid/sgid环境中使用此例程来测试调用用户是否具有指定的路径访问权。
使用格式：os.access(path, mode) 

#### 下面的值可以作为access()的模式参数传递来测试以下内容:
- os.F_OK:测试路径是否存在。
- os.R_OK:测试路径的可读性。
- os.W_OK:测试路径可写性。
- os.X_OK:检查路径是否可以执行。
#### 返回:
如果允许访问返回True，否则返回False。  
```python
import os
import sys
 
# Checking access with os.F_OK
path1 = os.access("gfg.txt", os.F_OK)
print("Exists the path:", path1)
 
# Checking access with os.R_OK
path2 = os.access("gfg.txt", os.R_OK)
print("Access to read the file:", path2)
 
# Checking access with os.W_OK
path3 = os.access("gfg.txt", os.W_OK)
print("Access to write the file:", path3)
 
# Checking access with os.X_OK
path4 = os.access("gfg.txt", os.X_OK)
print("Check if path can be executed:", path4)
```

## os.chflags()使用
**格式：os.chflag(path, flags)**
#### 参数：
path:待修改目录的完整路径。
flag:采用下列标志值的组合(按位OR)-
os.UF_NODUMP -不要转储文件。
os.UF_IMMUTABLE -文件不能被修改(只读)。
os.UF_APPEND -文件只能被追加到。
os.UF_OPAQUE -目录是不透明的，通过联合堆栈查看。
os.UF_NOUNLINK -文件不能被重命名或删除。
os.UF_COMPRESSED -文件被压缩保存
os.UF_HIDDEN -文件不应该显示在GUI中
os.SF_ARCHIVED -文件可能被存档。(可设置为超级用户)
os.SF_IMMUTABLE -文件不能被修改。(可设置为超级用户)
os.SF_APPEND -文件只能被追加到。(可设置为超级用户)
os.SF_NOUNLINK -文件不能重命名或删除。(可设置为超级用户)
os.SF_SNAPSHOT -文件是一个快照文件。(可设置为超级用户)
返回:不返回任何值

## os.chmod()
Python中的os.chmod()方法用于更改文件或目录的权限。  
**格式：os.chmod(path, mode)**
#### 参数:
Path -文件或目录路径的路径名称
#### Mode:
stat.S_ISUID:设置执行时的用户ID
stat.S_ISGID:在执行时设置组ID
stat.S_ENFMT:执行记录锁定
stat.S_ISVTX:执行后保存文本图像
stat.S_IREAD:由所有者阅读。
stat.S_IWRITE:由所有者写入。
stat.S_IEXEC:由所有者执行。
stat.S_IRWXU:由所有者进行读、写和执行
stat.S_IRUSR:由所有者阅读
stat.S_IWUSR:所有者写入。
stat.S_IXUSR:由所有者执行。
stat.S_IRWXG:按组读、写和执行
stat.S_IRGRP:按组读
stat.S_IWGRP:按组写
stat.S_IXGRP:按组执行
stat.S_IRWXO:由其他人读取、写入和执行。
stat.S_IROTH:其他人读
stat.S_IWOTH:别人写
stat.S_IXOTH:被其他人执行

## os.chroot()  
Python中的os.chroot()方法用于将当前进程的根目录更改为path。  
```python
import os, sys
os.chroot("/Geeks/gfg")
print ("root path successfully changed.")


# Function to Change root directory of the process.
def change_root_directory(path):
    try:
        os.chdir(path)
        os.chroot(path)
    except Exception as exc:
        error = DaemonOSEnvironmentError("Unable to change root directory ({exc})".format(exc = exc))
        raise error
# main function
change_root_directory("/Geeks/gfg")

```

## os.getlogin()使用
Python中的os.getlogin()方法用于获取在进程的控制终端上登录的用户的名称。

语法:os.getlogin()

参数:不需要

返回类型:该方法返回一个字符串，表示在进程的控制终端上登录的用户的名称。

```python
import os
user = os.getlogin()
print(user) 
```

## os.getenv()使用
Python中的os.getenv()方法返回环境变量键的值(如果它存在，则返回默认值)。
**语法:os.getenv(key, default = None)**

参数:
key:表示环境变量名的字符串
Default(可选):字符串，表示key不存在时的默认值。如果省略，默认设置为“None”。
返回类型:该方法返回一个字符串，表示环境变量key的值。如果key不存在，则返回默认参数的值。

```python
import os
key = 'HOME'
value = os.getenv(key)
print("Value of 'HOME' environment variable :", value) 
key = 'JAVA_HOME'
value = os.getenv(key)
print("Value of 'JAVA_HOME' environment variable :", value) 
```

## os.getpid()
Python中的os.getpid()方法用于获取当前进程的进程ID。
语法:os.getpid()
参数:不需要
返回类型:该方法返回一个整数值，表示当前进程的进程ID。这个方法的返回类型是’ int ‘类。
```python
import os
pid = os.getpid()
print(pid) 
```

## os.strerror()
os模块中的所有函数在文件名和路径无效或不可访问，或其他具有正确类型但操作系统不接受的参数时都会引发OSError。
**Python中的os.strerror()方法用于获取与错误代码对应的错误消息。**
语法:os.strerror(code)
参数:
code:表示错误码的整数值
返回类型:该方法返回一个字符串，表示与指定错误码对应的错误消息。
```python
import os
code = 1
error = os.strerror(code)
print("Error message corresponding to error code % d:" % code, error)

code = 5
error = os.strerror(code)
print("Error message corresponding to error code % d:" % code, error)
```

## os.path.splitext()
Python中的os.path.splitext()方法用于分割路径，返回路径名和文件扩展名的元组。在这里，ext代表扩展，并具有指定路径的扩展部分，而root是除ext部分以外的所有内容。
**如果指定的路径没有任何扩展名，则Ext为空。如果指定的路径有前导句号(‘ . ‘)，它将被忽略。**
**语法:os.path.splitext(path)**
参数:
path:表示文件系统路径的类路径对象。类路径对象是表示路径的str或bytes对象。
返回类型:该方法返回一个元组，表示指定路径名的根和ext部分。
```python
import os
path = '/home/User/Desktop/file.txt'
root_ext = os.path.splitext(path)

print("root part of '% s':" % path, root_ext[0])
print("ext part of '% s':"  % path, root_ext[1], "\n")
  
输出：
root part of '/home/User/Desktop/file.txt': /home/User/Desktop/file
ext part of  '/home/User/Desktop/file.txt': .txt 
```

## os.umask()
Python中的os.umask()方法用于设置当前数值umask值并获取以前的umask值。

**Umask代表用户文件创建模式掩码。用于确定新创建的文件或目录的文件权限。**

语法:os.umask(mask)
参数:
mask:整数，表示有效的umask值。
返回类型:这个方法设置当前的umask值，并返回一个代表前一个umask值的整数值。

默认情况下的umask值是022，此时建立的文件默认权限是644(6-0,6-2,6-2)，
建立的目录的默认 权限是755(7-0,7-2,7-2)，它是为了控制默认权限，不要使默认的文件和目录具有全权而设的


**umask　024则以后建立的文件和目录的默认权限就为642,753了**
Linux 中umask的工作方式与chmod命令类似，它也用于定义文件或目录的权限。它们之间的区别在于chmod用于改变已有文件或目录的权限，而**umask用于定义新建文件或目录的默认权限**。  

每次新建一个文件时，文件的默认权限是由umask的值决定的。当我们输入umask命令时，它会输出一个4为的八进制数值，如0002。如果umask值的某位被设置，**在新建文件或目录时将禁用对应的权限。**
os.umask() 只影响当前进程及其子进程的文件和目录创建权限。
**改变umask会影响所有随后创建的文件和目录，因此在改变umask之前应该谨慎考虑。**
改变umask的值应该在程序的早期阶段完成，以确保所有文件和目录都使用新的掩码。
```py
import os
mask = 0o777
umask = os.umask(mask) 
print("Current umask:", mask)
print("Previous umask:", umask) 
```
### 查看当前的umask值：
```py
import os
current_umask = os.umask(0)
print("Current umask:", current_umask)
```

## os.linesep()
描述：当前平台用于分隔（或终止）行的字符串。它可以是单个字符，如 POSIX 上是 '\n'，也可以是多个字符，如 Windows 上是 '\r\n'。在写入以文本模式（默认模式）打开的文件时，请不要使用 os.linesep 作为行终止符，请在所有平台上都使用一个 '\n' 代替。
## os.pathsep()
描述：操作系统通常用于分隔搜索路径（如 PATH）中不同部分的字符，如 POSIX 上是 ':'，Windows 上是 ';'。在 os.path 中也可用。
语法：os.pathsep
## os.path.lexists()
描述：路径存在则返回True，路径损坏也返回True， 不存在，返回 False。

## os.cpu_count
描述：返回当前系统的CPU核心数

## os.system()
在一个子终端运行系统命令，而不能获取命令执行后的返回信息。
os.system(cmd)的返回值。如果执行成功，那么会返回0，表示命令执行成功。否则，则是执行错误。
### 注意事项：
1. 安全性：由于 os.system() 会执行传入的任何命令，如果命令字符串包含用户输入，可能会受到注入攻击。
2. 环境依赖：执行的命令依赖于系统的 shell 环境，不同操作系统或不同用户配置可能有不同的行为。
3. 错误处理：返回的退出状态码可以用来判断命令是否成功执行，但通常需要额外的错误处理逻辑。

