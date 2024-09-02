

# map
- map內部的实现自建一颗==红黑树==，这颗树具有对数据自动排序的功能,在map内部所有的数据都是有序的.
- unordered_map: unordered_map内部实现了一个哈希表（也叫散列表，通过把关键码值映射到Hash表中一个位置来访问记录，查找的时间复杂度可达到O(1)）因此，其元素的排列顺序是无序的。


```cpp
map<string,int>m;//定义m
 
1：使用insert添加元素
m.insert(pair<string,int>("sd",19));
m.insert(make_pair(string("def"), 2));

2:直接使用数组下标
m["sd"]=19;

3:用insert函数插入value_type数据：
map<int,string> my_map;
my_map.insert(map<int,string>::value_type(1,"first"));
my_map.insert(map<int,string>::value_type(2,"second"));
 
map<int,string>::iterator it;           //迭代器遍历
for(it=my_map.begin();it!=my_map.end();it++)
    cout<<it->first<<it->second<<endl;

```



