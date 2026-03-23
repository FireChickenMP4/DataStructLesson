#include "SeqList.h"
#include <iostream>
#include <cstring>

SeqList::SeqList(int cap) : data(nullptr), capacity(cap > 0 ? cap : 10), length(0)
{
    data = new int[capacity];
}

SeqList::~SeqList()
{
    delete[] data;
}

SeqList::SeqList(SeqList &&other) noexcept : data(other.data), capacity(other.capacity), length(other.length)
{
    other.data = nullptr;
    other.capacity = 0;
    other.length = 0;
}

SeqList &SeqList::operator=(SeqList &&other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        capacity = other.capacity;
        length = other.length;
        other.data = nullptr;
        other.capacity = 0;
        other.length = 0;
    }
    return *this;
}

void SeqList::Clear()
{
    length = 0;
    // 跟磁盘一样，反正这块地是你的
    // 你到时候写的时候覆盖了就好
    // 链表要除了头节点都释放掉
}

bool SeqList::Empty() const
{
    return length == 0;
}

int SeqList::Len() const
{
    return length;
}
int SeqList::Cap() const
{
    return capacity;
}
// 一般都是在length==capacity的时候再加就会要扩容
void SeqList::Resize()
{
    int newCap = (capacity == 0) ? 1 : capacity * 2;
    int *newData = new int[newCap];
    memmove(newData, data, length * sizeof(int));
    delete[] data;
    data = newData;
    capacity = newCap;
}
// i为index
bool SeqList::GetElem(int i, int &e) const
{
    if (i < 0 || i >= length)
        return false;
    else
    {
        e = data[i];
        return true;
    }
}

int SeqList::LocateElem(int e) const
{
    int i = 0;
    for (auto it = begin(); it != end(); ++it, ++i)
    {
        if (*it == e)
        {
            return i;
        }
    }
    return -1;
}

bool SeqList::PriorElem(int cur_e, int &pre_e) const
{
    int i = 0;
    for (auto it = begin(); it != end(); ++it, ++i)
    {
        if (*it == cur_e)
        {
            if (i == 0)
            {
                return false;
            }
            else
            {
                pre_e = data[i - 1];
                return true;
            }
        }
    }
    return false;
}

bool SeqList::NextElem(int cur_e, int &next_e) const
{
    int i = 0;
    for (auto it = begin(); it != end(); ++it, ++i)
    {
        if (*it == cur_e)
        {
            if (i == length - 1)
            {
                return false;
            }
            else
            {
                next_e = data[i + 1];
                return true;
            }
        }
    }
    return false;
}

bool SeqList::Insert(int i, int e)
{
    if (i < 0)
        return false;
    if (i > length)
        i = length;
    if (length == capacity)
    {
        // 考虑扩容
        Resize();
    }
    // for (int j = length; j >= i; --j)
    // {
    //     data[j] = data[j - 1];
    // } // 往后移动
    // 用标准库的memmove更快一些，能处理重叠
    // memmove(void *str1,const void *str2, size_t n)
    // 很明显，str2复制到str1
    if (i < length)
    {
        memmove(data + i + 1, data + i, (length - i) * sizeof(int));
    }
    data[i] = e;
    ++length;
    return true;
}

bool SeqList::Delete(int i, int &e)
{
    if (i < 0 || i >= length || length == 0)
        return false;
    e = data[i];
    memmove(data + i, data + i + 1, (length - i - 1) * sizeof(int));
    --length;
    return true;
}

void SeqList::Traverse() const
{
    for (auto it = begin(); it != end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

bool SeqList::Push_back(int e)
{
    return Insert(length, e);
}