## 概述

删掉代码中的注释

## 功能

- 删掉代码右侧注释 
    - code // xxx 
    - code /* xxx */
- 删掉代码单独一行注释
    - // xxx
    - /* xxx */
- 不删引号中的注释
    -  " // xxx " 
    -  " /* xxx */ "
## 改进

- [ ] 单独一行注释删除后，空行缩进问题


## 测试
### input.cpp
```cpp
#include <iostream>
using namespace std;
int main()
{
    cout << "test one" << endl; // this is test one note
    cout << "test two" << endl;  /* this is test two note */
    // this is test three note
    /* this is test four note */
    cout << "// this is test five note" << endl;
    cout << "/* this is test six note */" << endl;
    return 0;
}
```

### output.cpp

```cpp
#include <iostream>
using namespace std;
int main()
{
    cout << "test one" << endl; 
    cout << "test two" << endl; 
    
    
    cout << "// this is test five note" << endl;
    cout << "/* this is test six note */" << endl;
    return 0;
}
```
