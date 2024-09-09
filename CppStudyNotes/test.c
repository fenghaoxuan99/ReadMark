// Demo_3
#include <assert.h>

int main(){
    assert(+0. == -0.);      // 断言成功
    assert(1.0/+0. == 1.0/-0.); // 断言失败
    return 0;
}