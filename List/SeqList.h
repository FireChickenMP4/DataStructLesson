#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include <iostream>
#include <utility>

template <typename T>
class SeqListT : public ListT<T>
{
    static_assert(ListElement<T>);

private:
    T *data;
    int capacity;
    int length;
    void Resize();
    void Swap(SeqListT &other) noexcept;

public:
    explicit SeqListT(int cap = 10);
    ~SeqListT();

    SeqListT(const SeqListT &);
    SeqListT(SeqListT &&) noexcept;
    SeqListT &operator=(const SeqListT &);
    SeqListT &operator=(SeqListT &&) noexcept;

    void Clear() override;
    bool Empty() const override;
    int Len() const override;
    bool GetElem(int i, T &e) const override;
    int LocateElem(const T &e) const override;
    bool PriorElem(const T &cur_e, T &pre_e) const override;
    bool NextElem(const T &cur_e, T &next_e) const override;
    bool Insert(int i, const T &e) override;
    bool Delete(int i, T &e) override;
    void ForEach(const std::function<void(const T &)> &visit) const override;
    int Cap() const;
    bool Push_back(const T &e);

    class Iterator
    {
    private:
        T *ptr;

    public:
        Iterator(T *p = nullptr) : ptr(p) {}

        T &operator*() const { return *ptr; }
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

        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }

    class ConstIterator
    {
    private:
        const T *ptr;

    public:
        ConstIterator(const T *p = nullptr) : ptr(p) {}

        const T &operator*() const { return *ptr; }
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

        bool operator!=(const ConstIterator &other) const { return ptr != other.ptr; }
    };

    ConstIterator begin() const { return ConstIterator(data); }
    ConstIterator end() const { return ConstIterator(data + length); }
};

using SeqList = SeqListT<int>;

template <typename T>
SeqListT<T>::SeqListT(int cap) : data(nullptr), capacity(cap > 0 ? cap : 10), length(0)
{
    data = new T[static_cast<size_t>(capacity)];
}

template <typename T>
SeqListT<T>::~SeqListT()
{
    delete[] data;
}

template <typename T>
SeqListT<T>::SeqListT(const SeqListT &other) : capacity(other.capacity), length(other.length)
{
    data = new T[static_cast<size_t>(capacity)];
    for (int i = 0; i < length; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
SeqListT<T>::SeqListT(SeqListT &&other) noexcept : data(other.data), capacity(other.capacity), length(other.length)
{
    other.data = nullptr;
    other.capacity = 0;
    other.length = 0;
}

template <typename T>
SeqListT<T> &SeqListT<T>::operator=(const SeqListT &other)
{
    if (this != &other)
    {
        SeqListT temp(other);
        Swap(temp);
    }
    return *this;
}

template <typename T>
void SeqListT<T>::Swap(SeqListT &other) noexcept
{
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(length, other.length);
}

template <typename T>
SeqListT<T> &SeqListT<T>::operator=(SeqListT &&other) noexcept
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
void SeqListT<T>::Clear()
{
    length = 0;
}

template <typename T>
bool SeqListT<T>::Empty() const
{
    return length == 0;
}

template <typename T>
int SeqListT<T>::Len() const
{
    return length;
}

template <typename T>
int SeqListT<T>::Cap() const
{
    return capacity;
}

template <typename T>
void SeqListT<T>::Resize()
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
bool SeqListT<T>::GetElem(int i, T &e) const
{
    if (i < 0 || i >= length)
        return false;
    e = data[i];
    return true;
}

template <typename T>
int SeqListT<T>::LocateElem(const T &e) const
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

template <typename T>
bool SeqListT<T>::PriorElem(const T &cur_e, T &pre_e) const
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
            pre_e = data[i - 1];
            return true;
        }
    }
    return false;
}

template <typename T>
bool SeqListT<T>::NextElem(const T &cur_e, T &next_e) const
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
            next_e = data[i + 1];
            return true;
        }
    }
    return false;
}

template <typename T>
bool SeqListT<T>::Insert(int i, const T &e)
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
bool SeqListT<T>::Delete(int i, T &e)
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
void SeqListT<T>::ForEach(const std::function<void(const T &)> &visit) const
{
    for (auto it = begin(); it != end(); ++it)
    {
        visit(*it);
    }
}

template <typename T>
bool SeqListT<T>::Push_back(const T &e)
{
    return Insert(length, e);
}

#endif
