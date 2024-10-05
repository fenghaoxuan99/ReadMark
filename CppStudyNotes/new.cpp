#include <iostream>

using namespace std;


//展开函数
template<class ...Args>
void ShowList(Args... args)
{
  auto func = [](int val) {cout << val << " "; };
	int arr[] = {(func(args),0)...  }; //列表初始化
	//打印参数包中的各个参数
	

}
 
int main()
{
  ShowList();
	ShowList(1);
	ShowList(1, 2);
	ShowList(1, 2, 3);
	return 0;
}