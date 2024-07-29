











```cpp
// math.h文件的内容 

//意思是如果使用该头文件math.h的文件定义了__cplusplus，
//则下面代码到#endif都是有效的,在这里是 extern "C" { 有效
#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus

int add (int x,int y);//加法
int sub(int x,int y);//减法
int mult(int x,int y);//乘法
int div(int x,int y); //除法

//意思是如果使用该头文件math.h的文件定义了__cplusplus，
//则下面代码到#endif都是有效的,在这里是 } 有效
#ifdef __cplusplus
}
#endif  //__cplusplus

```