# Linear List

## 1. Sequential List

顺序表使用连续内存存储元素。

### Operations

- Initialize
- Destroy
- Insert
- Delete
- Search
- Get element
- Traverse

### Complexity

| Operation | Complexity |
|---|---|
| Access | O(1) |
| Search | O(n) |
| Insert | O(n) |
| Delete | O(n) |

## 2. Linked List
# 顺序表（Sequential List）学习笔记

## 1. 本节学习目标

通过 C 语言手动实现一个动态申请内存的顺序表，掌握：

* 顺序表的基本结构
* 动态内存申请与释放
* `struct` 结构体
* 指针与结构体指针
* 数组下标与逻辑位置的转换
* 尾插
* 遍历
* 指定位置插入
* 指定位置删除
* 按值查找
* 按位置查找
* 时间复杂度分析
* `const` 的基本使用
* 通过指针参数返回结果

---

# 2. 什么是线性表

线性表是一种具有线性关系的数据结构。

例如：

text
88 → 46 → 45 → 67

在线性表中，除了第一个元素和最后一个元素以外，每个元素都有：

* 一个直接前驱
* 一个直接后继

常见的线性表实现有两种：

```text
线性表
├── 顺序表
└── 链表
```

其中：

### 顺序表

使用一块连续的内存空间保存元素：

```text
data
 ↓
+----+----+----+----+----+
| 88 | 46 | 45 | 67 |    |
+----+----+----+----+----+
  0    1    2    3
```

特点：

* 内存连续
* 可以通过下标快速访问
* 查询指定位置非常快
* 中间插入和删除需要移动元素

### 链表

链表的节点通常分散在内存中，通过指针连接：

```text
[data|next] → [data|next] → [data|next] → NULL
```

因此：

> 本程序实现的是顺序表，而不是链表。

---

# 3. 顺序表的数据结构设计

程序首先定义：

```c
#define MAXSIZE 100

typedef int ElementType;
```

其中：

```c
MAXSIZE
```

表示顺序表最大容量为：

```text
100
```

而：

```c
typedef int ElementType;
```

相当于：

```c
ElementType == int
```

这样做的优点是以后如果想把顺序表中的数据类型改成：

```c
double
```

或者其他类型，只需要修改：

```c
typedef double ElementType;
```

不需要修改整个程序。

---

# 4. SeqList 结构体

顺序表定义如下：

```c
typedef struct
{
    ElementType *data;
    int length;
} SeqList;
```

结构体内部有两个成员：

| 成员       | 类型              | 作用              |
| -------- | --------------- | --------------- |
| `data`   | `ElementType *` | 指向真正存放元素的连续内存   |
| `length` | `int`           | 当前顺序表中实际存在的元素数量 |

例如顺序表：

```text
88 46 45 67
```

此时：

```c
L->length == 4
```

但实际上我们申请了：

```text
100
```

个 `ElementType` 的空间。

因此要区分两个概念：

```text
容量 capacity = 100
当前长度 length = 4
```

---

# 5. 顺序表在内存中的结构

初始化之后：

```text
SeqList
┌──────────────┐
│ data ────────────────┐
│ length = 0  │        │
└──────────────┘        │
                        ↓
                Heap 堆内存
                ┌────┬────┬────┬────┬───────┐
                │    │    │    │    │ ...   │
                └────┴────┴────┴────┴───────┘
                  0    1    2    3       99
```

这里进行了 **两次动态内存申请**。

第一次：

```c
SeqList *L = malloc(sizeof(SeqList));
```

申请：

```text
SeqList 结构体
```

第二次：

```c
L->data = malloc(sizeof(ElementType) * MAXSIZE);
```

申请：

```text
100 个 ElementType
```

因此销毁时也必须对应执行两次 `free()`。

---

# 6. 初始化顺序表

函数：

```c
SeqList *SeqListInit(void)
```

作用：

> 创建一个新的顺序表，并返回指向该顺序表的指针。

首先：

```c
SeqList *L = malloc(sizeof(SeqList));
```

申请一个 `SeqList` 结构体。

如果申请失败：

```c
if (L == NULL)
```

返回：

```c
NULL
```

然后继续为数据区域申请空间：

```c
L->data = malloc(sizeof(ElementType) * MAXSIZE);
```

可以写成更常见的形式：

```c
L->data = malloc(sizeof *L->data * MAXSIZE);
```

结构体本身也可以：

```c
SeqList *L = malloc(sizeof *L);
```

这种写法的优点是：

> 即使以后修改变量类型，也不需要同步修改 `sizeof()` 中的类型名称。

最后：

```c
L->length = 0;
```

说明：

```text
当前顺序表为空
```

---

# 7. 为什么第二次 malloc 失败后要 free(L)

代码：

```c
if (L->data == NULL)
{
    printf("data内存申请失败\n");
    free(L);
    return NULL;
}
```

原因是：

```c
SeqList *L = malloc(...)
```

已经成功申请过一次内存。

如果：

```c
L->data = malloc(...)
```

第二次失败，而直接：

```c
return NULL;
```

那么第一块内存就永远找不到了。

这属于：

```text
Memory Leak
内存泄漏
```

所以必须：

```c
free(L);
```

然后才能返回。

---

# 8. 销毁顺序表

函数：

```c
void SeqListDestroy(SeqList *L)
```

代码逻辑：

```c
if (L != NULL)
{
    free(L->data);
    free(L);
}
```

释放顺序必须理解：

```text
L
│
└── data → 数据空间
```

应该先：

```c
free(L->data);
```

再：

```c
free(L);
```

因为如果先：

```c
free(L);
```

那么之后：

```c
L->data
```

已经属于访问失效内存。

因此这里采用：

```text
先释放内部资源
↓
再释放结构体本身
```

这是处理动态结构体时非常重要的原则。

---

# 9. 尾插 appendElem

函数：

```c
int appendElem(SeqList *L, ElementType e)
```

作用：

> 在顺序表最后添加一个元素。

例如：

```text
原来：

88 46 45 67

插入：

12

结果：

88 46 45 67 12
```

核心代码：

```c
L->data[L->length] = e;
L->length++;
```

假设：

```c
length = 4;
```

当前有效下标：

```text
0 1 2 3
```

那么新元素应该放在：

```text
下标 4
```

正好就是：

```c
data[length]
```

因此：

```c
L->data[L->length] = e;
```

然后：

```c
L->length++;
```

更新逻辑长度。

---

# 10. 为什么尾插是 O(1)

尾插不需要移动其他元素。

只执行：

```c
data[length] = e;
length++;
```

操作次数不会随着元素数量增加而增加。

因此：

```text
时间复杂度：O(1)
```

需要注意：

> 这是因为本实现一开始已经分配了固定大小 `MAXSIZE` 的数组，而且不会自动扩容。

---

# 11. 遍历顺序表

函数：

```c
void listElem(const SeqList *L)
```

遍历：

```c
for (int i = 0; i < L->length; i++)
{
    printf("%d\t", L->data[i]);
}
```

如果：

```text
length = n
```

需要访问：

```text
n 个元素
```

所以：

```text
时间复杂度：O(n)
```

---

# 12. 为什么这里使用 const

函数参数：

```c
const SeqList *L
```

表示：

> 这个函数只允许读取顺序表，不应该修改顺序表。

例如：

```c
listElem()
findElem()
getElem()
```

本质上都是查询操作。

因此使用：

```c
const SeqList *L
```

比：
