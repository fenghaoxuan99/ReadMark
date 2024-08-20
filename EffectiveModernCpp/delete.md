

template<typename T>
void processPointer(T* ptr);
在指针的世界里有两种特殊情况。一是void*指针，因为没办法对它们进行解引用，或者加加减减等。另一种指针是char*，因为它们通常代表C风格的字符串，而不是正常意义下指向单个字符的指针。这两种情况要特殊处理，在processPointer模板里面，我们假设正确的函数应该拒绝这些类型。也即是说，processPointer不能被void*和char*调用。

要想确保这个很容易，使用delete标注模板实例：


template<>
void processPointer<void>(void*) = delete;

template<>
void processPointer<char>(char*) = delete;