


<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [std::enable_if](#stdenable_if)
  - [定义](#定义)
      - [enable_if_t是一个别名](#enable_if_t是一个别名)
  - [作为返回值类型](#作为返回值类型)
    - [利用auto关键字，可以写为如下形式：](#利用auto关键字可以写为如下形式)

<!-- /code_chunk_output -->


# std::enable_if 
顾名思义，满足条件时类型有效。广泛的应用在 C++ 的模板元编程中。
## 定义
```cpp
template <bool _Test, class _Ty = void>
struct enable_if {};

template <class _Ty>
struct enable_if<true, _Ty> { 
    using type = _Ty;
};
```
由此可知，只有当第一个模板参数_Test为 true 时，type 才有定义（type即第二个模板参数_Ty）；否则使用 type 会产生编译错误，且默认模板参数可以让你不必指定类型
#### enable_if_t是一个别名  

template <bool _Test, class _Ty = void>
using enable_if_t = typename enable_if<_Test, _Ty>::type;

---

### 作为模板参数
```cpp
template<typename T>
struct Check1
{
    //如果T的类型是int，则定义函数 int read(void* = nullptr)
	template<typename U = T>
	U read(typename std::enable_if_t<std::is_same_v<U, int> >* = nullptr) {
		return 42;
	}
    
    //如果T的类型是double，则定义函数 double read(void* = nullptr)
	template<typename U = T>
	U read(typename std::enable_if_t<std::is_same_v<U, double> >* = nullptr) {
		return 3.14;
	}
};

// 作为模板参数
template<typename T>
struct Check2
{
    //如果T的类型是int，则定义函数 int read()
	template<typename U = T, typename std::enable_if_t<std::is_same_v<U, int>, int> = 0>
	U read() {
		return 42;
	}
    
    //如果T的类型是double，则定义函数 double read()
	template<typename U = T, typename std::enable_if_t<std::is_same_v<U, double>, int> = 0>
	U read() {
		return 3.14;
	}
};
```

## 作为返回值类型
```cpp
template<typename T>
struct Check3
{
    //如果T的类型是int，则定义函数 int read()
	template<typename U = T>
	typename std::enable_if_t<std::is_same_v<U, int>, U> read() {
		return 42;
	}

    //如果T的类型是double，则定义函数 double read()
	template<typename U = T>
	typename std::enable_if_t<std::is_same_v<U, double>, U> read() {
		return 3.14;
	}
};
```

### 利用auto关键字，可以写为如下形式：
```cpp
// int goo<true>(int x)
template<bool B>
auto goo(int x) -> std::enable_if_t<B, int>
{
	return 1;
}

// int goo<false>(int x)
template<bool B>
auto goo(int x) -> std::enable_if_t<!B, int>
{
	return 2;
}
```
