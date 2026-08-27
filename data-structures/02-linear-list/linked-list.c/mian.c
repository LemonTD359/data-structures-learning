#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElementType;

typedef struct
{
    ElementType *data;
    int length;
} SeqList;

/* 动态分配内存初始化--链表学习的基础 */
SeqList *SeqListInit(void)
{
    SeqList *L = malloc(sizeof(SeqList));

    if (L == NULL)
    {
        printf("SeqList内存申请失败\n");
        return NULL;
    }

    L->data = malloc(sizeof(ElementType) * MAXSIZE);
    //L->data = malloc(sizeof *L->data * MAXSIZE);
    //SeqList *L = malloc(sizeof *L);

    if (L->data == NULL)
    {
        printf("data内存申请失败\n");
        free(L);
        return NULL;
    }

    L->length = 0;

    return L;
}

void SeqListDestroy(SeqList *L)
{
    if (L != NULL)
    {
        free(L->data);
        free(L);
    }
}

/* 尾插 */
int appendElem(SeqList *L, ElementType e)
{
    if (L->length >= MAXSIZE)
    {
        printf("线性表已经塞满了");
        return 0;
    }
    L->data[L->length] = e;
    L->length ++;
    return 1;
}

/* 遍历 */
void listElem(const SeqList *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("%d\t",L->data[i]);
    }
    printf("\n");
}

/* 指定位置插入 */
int insertElem(SeqList *L, int pos, ElementType e)
{
    if (L->length >= MAXSIZE)
    {
        printf("线性表已经满了\n");
        return 0;
    }

    if (pos < 1 || pos > L->length + 1)
    {
        printf("插入位置不合法\n");
        return 0;
    }

    for (int i = L->length; i >= pos; i--)
    {
        L->data[i] = L->data[i - 1];
    }

    L->data[pos - 1] = e;
    L->length++;

    return 1;
}

/* 删除指定位置元素 */
int deleteElem(SeqList *L, int pos, ElementType *e)
{
    if (L->length == 0)
    {
        printf("线性表为空，无法删除\n");
        return 0;
    }
    /*
    插入：
    1 <= pos <= length + 1

    删除：
    1 <= pos <= length
    */

    if (pos < 1 || pos > L->length)
    {
        printf("删除位置不合法\n");
        return 0;
    }
    
    *e = L->data[pos - 1];


    for (int i = pos; i < L->length; i++)
    {
        L->data[i - 1] = L->data[i];
    }        

    L->length --;
    return 1;

}

/* 按值查找 */
int findElem(const SeqList *L, ElementType e)
{
    if (L->length == 0)
    {
        printf("空列表！");
        return 0;
    }
    
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == e)
        {
            return i + 1;
        }  
    }
    return 0;
}

/* 按位查找---顺序表最大的优势之一：按位置访问非常快 */
int getElem(const SeqList *L, int pos, ElementType *e)
{
    if (pos < 1 || pos > L->length)
    {
        printf("查找位置不合法\n");
        return 0;
    }
    //用一个指针参数把结果带回来
    *e = L->data[pos - 1];

    return 1;
}

int main(void)
{
    //SeqList List;

    //SeqListInit(&List);
    SeqList *List = SeqListInit();
    appendElem(List, 88);
    appendElem(List, 46);
    appendElem(List, 45);
    appendElem(List, 67);

    printf("原始顺序表：\n");
    listElem(List);

    insertElem(List, 2, 34);

    printf("在第2个位置插入34：\n");
    listElem(List);

    appendElem(List, 12);

    printf("尾插12：\n");
    listElem(List);

    ElementType deleted;

    if (deleteElem(List, 4, &deleted))
    {
        printf("删除的元素是：%d\n", deleted);
    }

    printf("删除后：\n");
    listElem(List);

    int pos = findElem(List, 46);

    if (pos != 0)
    {
        printf("46在列表的第%d个位置\n", pos);
    }
    else
    {
        printf("没有找到46\n");
    }

    ElementType value;

    if (getElem(List, 3, &value))
    {
        printf("第3个元素是;%d\n", value);
    }

    SeqListDestroy(List);

    return 0;
}



/*
    | 操作          | 函数               | 时间复杂度 |
    | ------        | ---------------   | ----: |
    | 初始化        |SeqListInit()`      |  O(1) |
    | 尾插          |appendElem()`       |  O(1) |
    | 遍历          |listElem()`         |  O(n) |
    | 指定位置插入   |insertElem()`       |  O(n) |
    | 指定位置删除   |deleteElem()`       |  O(n) |
    | 按值查找       |findElem()`        |  O(n) |
    | 按位查找       |getElem()`         |  O(1) |

*/