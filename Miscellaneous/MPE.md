

# MPE使用

## 空格
- &nbsp
不换行空格，全称是 No-Break Space，它是最常见和我们使用最多的空格，大多数的人可能只接触了 ，它是按下space键产生的空格。在HTML中，如果你用空格键产生此空格，空格是不会累加的（只算1个）。要使用html实体表示才可累加，该空格占据宽度受字体影响明显而强烈。
- &ensp
半角空格，全称是 En Space，en是字体排印学的计量单位，为em宽度的一半。根据定义，它等同于字体度的一半（如16px字体中就是8px）。名义上是小写字母n的宽度。此空格传承空格家族一贯的特性：透明的，此空格有个相当稳健的特性，就是其占据的宽度正好是1/2个中文宽度，而且基本上不受字体影响。
- &emsp
全角空格，全称是 Em Space，em是字体排印学的计量单位，相当于当前指定的点数。例如，1 em在16px的字体中就是16px。此空格也传承空格家族一贯的特性：透明的，此空格也有个相当稳健的特性，就是其占据的宽度正好是1个中文宽度，而且基本上不受字体影响。



## 上标
30^th^

## 下标
H~2~O

## 脚注
Content [^1]
[^1]: Hi! This is a footnote

## 缩略
*[HTML]: Hyper Text Markup Language
*[W3C]: World Wide Web Consortium
The HTML specification
is maintained by the W3C.

## Admonitions插件
!!! success This is the admonition title
    This is the admonition body
==**note abstract info tip success question warning failure danger bug example quote**==