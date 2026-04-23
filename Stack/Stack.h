#ifndef STACK_H
#define STACK_H

#include "StackBase.h"
#include <iostream>
#include <utility>
#include <iterator>

template <typename T>
class StackT : public StackBaseT<T>
{
    static_assert(StackBaseElement<T>);

private:
    T *data;
    int capacity;
    int length;
    void Resize();
    void Swap(StackT &other) noexcept;
    bool GetElem(int i, T &e) const override;
    int LocateElem(const T &e) const override;
    bool Insert(int i, const T &e) override;
    bool Delete(int i, T &e) override;

public:
    explicit StackT(int cap = 10);
    ~StackT();

    StackT(const StackT &);
    StackT(StackT &&) noexcept;
    StackT &operator=(const StackT &);
    StackT &operator=(StackT &&) noexcept;

    void Clear() override;
    bool Empty() const override;
    int Len() const override;
    void ForEach(const std::function<void(const T &)> &visit) const override;
    void ForEach(const std::function<void(T &)> &visit) override;
    int Cap() const;
    bool GetTop(T &e) const override;
    bool Push(const T &e) override;
    bool Pop(T &e) override;

    class Iterator
    {
    private:
        T *ptr;

    public:
        Iterator(T *p = nullptr) : ptr(p) {}
        // 由于是栈
        // 所以++等效--
        // 下面有关begin和end的逻辑也修改了
        // 但注意data-1这种写法很危险，不能进行任何有效的解引用操作
        // emm
        // 好像其实有更好的方法
        // 就是实现反向遍历
        // 所以不改了直接反向遍历了
        // 然后修改ForEach
        // 但是这样需要加一些参数来让其有迭代器特征(traits)
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;
        // 以及需要==和->
        // 虽然不是严格，但是最好写一下

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }
        Iterator &operator++()
        {
            ++ptr;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        Iterator &operator--()
        {
            --ptr;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --ptr;
            return tmp;
        }

        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
        bool operator==(const Iterator &other) const { return ptr == other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }

    using ReverseIterator = std::reverse_iterator<Iterator>;
    ReverseIterator rbegin() { return ReverseIterator(end()); }
    ReverseIterator rend() { return ReverseIterator(begin()); }

    class ConstIterator
    {
    private:
        const T *ptr;

    public:
        ConstIterator(const T *p = nullptr) : ptr(p) {}

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T *;
        using reference = const T &;

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }
        ConstIterator &operator++()
        {
            ++ptr;
            return *this;
        }
        ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            ++ptr;
            return tmp;
        }
        ConstIterator &operator--()
        {
            --ptr;
            return *this;
        }
        ConstIterator operator--(int)
        {
            ConstIterator tmp = *this;
            --ptr;
            return tmp;
        }

        bool operator!=(const ConstIterator &other) const { return ptr != other.ptr; }
        bool operator==(const ConstIterator &other) const { return ptr == other.ptr; }
    };

    ConstIterator begin() const { return ConstIterator(data); }
    ConstIterator end() const { return ConstIterator(data + length); }

    using ReverseConstIterator = std::reverse_iterator<ConstIterator>;
    ReverseConstIterator rbegin() const { return ReverseConstIterator(end()); }
    ReverseConstIterator rend() const { return ReverseConstIterator(begin()); }
};

using Stack = StackT<int>;

template <typename T>
StackT<T>::StackT(int cap) : data(nullptr), capacity(cap > 0 ? cap : 10), length(0)
{
    data = new T[static_cast<size_t>(capacity)];
}

template <typename T>
StackT<T>::~StackT()
{
    delete[] data;
}

template <typename T>
StackT<T>::StackT(const StackT &other) : capacity(other.capacity), length(other.length)
{
    data = new T[static_cast<size_t>(capacity)];
    for (int i = 0; i < length; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
StackT<T>::StackT(StackT &&other) noexcept : data(other.data), capacity(other.capacity), length(other.length)
{
    other.data = nullptr;
    other.capacity = 0;
    other.length = 0;
}

template <typename T>
StackT<T> &StackT<T>::operator=(const StackT &other)
{
    if (this != &other)
    {
        StackT temp(other);
        Swap(temp);
    }
    return *this;
}

template <typename T>
void StackT<T>::Swap(StackT &other) noexcept
{
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(length, other.length);
}

template <typename T>
StackT<T> &StackT<T>::operator=(StackT &&other) noexcept
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

template <typename T>
void StackT<T>::Clear()
{
    length = 0;
}

template <typename T>
bool StackT<T>::Empty() const
{
    return length == 0;
}

template <typename T>
int StackT<T>::Len() const
{
    return length;
}

template <typename T>
int StackT<T>::Cap() const
{
    return capacity;
}

template <typename T>
void StackT<T>::Resize()
{
    int newCap = (capacity == 0) ? 1 : capacity * 2;
    T *newData = new T[static_cast<size_t>(newCap)];
    for (int i = 0; i < length; ++i)
    {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    capacity = newCap;
}

template <typename T>
bool StackT<T>::GetElem(int i, T &e) const
{
    if (i < 0 || i >= length)
        return false;
    e = data[i];
    return true;
}

template <typename T>
int StackT<T>::LocateElem(const T &e) const
{
    int i = 0;
    for (auto it = begin(); it != end(); ++it, ++i)
    {
        if (*it == e)
        {
            return i;
        }
    }
    // 其实还是不推荐用迭代器实现
    // 容易出乱子就是了
    return -1;
}

template <typename T>
bool StackT<T>::Insert(int i, const T &e)
{
    if (i < 0)
        return false;
    if (i > length)
        i = length;
    if (length == capacity)
    {
        Resize();
    }
    if (i < length)
    {
        for (int j = length; j > i; --j)
        {
            data[j] = std::move(data[j - 1]);
        }
    }
    data[i] = e;
    ++length;
    return true;
}

template <typename T>
bool StackT<T>::Delete(int i, T &e)
{
    if (i < 0 || i >= length || length == 0)
        return false;
    e = data[i];
    for (int j = i; j < length - 1; ++j)
    {
        data[j] = std::move(data[j + 1]);
    }
    --length;
    return true;
}

template <typename T>
void StackT<T>::ForEach(const std::function<void(T &)> &visit)
{
    for (auto it = rbegin(); it != rend(); ++it)
    {
        visit(*it);
    }
}

template <typename T>
void StackT<T>::ForEach(const std::function<void(const T &)> &visit) const
{
    for (auto it = rbegin(); it != rend(); ++it)
    {
        visit(*it);
    }
}

template <typename T>
bool StackT<T>::Push(const T &e)
{
    return Insert(length, e);
}

template <typename T>
bool StackT<T>::Pop(T &e)
{
    return Delete(length - 1, e);
}

template <typename T>
bool StackT<T>::GetTop(T &e) const
{
    return GetElem(length - 1, e);
}

#endif
