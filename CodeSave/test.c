#include<stdio.h>
union u{
        int i;
        double d;//这个union有8字节大小
};
main(){
        union u uu;
        uu.i = 10;
        printf("%d\n",uu.i);
 
        char * c;
        c = (char *)&uu;//把union的首地址赋值、强转成char类型
        c[0] = 'a';
        c[1] = 'b';
        c[2] = 'c';
        c[3] = '\0';
        c[4] = 'd';
        c[5] = 'e';
//最多能到c[7]
        printf("%s\n",c);//利用结束符'\0'打印字符串"abc"
        printf("%c %c %c %c %c %c\n",c[0],c[1],c[2],c[3],c[4],c[5]);
}