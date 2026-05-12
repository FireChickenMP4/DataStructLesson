#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include "QueueBase.h"
#include <iostream>
#include <utility>
#include <cassert>

template <typename T>
class CircleQueueT : public QueueBaseT<T>
{
    static_assert(QueueBaseElement<T>);

private:
    T *data;
    int capacity;
    int length;

    std::size_t front_;
    std::size_t rear_;

    void Resize();
    void Swap(CircleQueueT &other) noexcept;

public:
    explicit CircleQueueT(int cap = 10);
    ~CircleQueueT();

    CircleQueueT(const CircleQueueT &);
    CircleQueueT(CircleQueueT &&) noexcept;
    CircleQueueT &operator=(const CircleQueueT &);
    CircleQueueT &operator=(CircleQueueT &&) noexcept;

    void Clear() override;
    bool Empty() const override;
    int Len() const override;
    void ForEach(const std::function<void(const T &)> &visit) const override;
    void ForEach(const std::function<void(T &)> &visit) override;
    int Cap() const;
    bool GetHead(T &e) const override;
    bool EnQueue(const T &e) override;
    bool DeQueue(T &e) override;

    class Iterator
    {
    private:
        friend class CircleQueueT;

        CircleQueueT<T> *queue_;
        std::size_t index_;
        std::size_t remain_;

        Iterator(CircleQueueT<T> *q, std::size_t index, std::size_t remain) : queue_(q), index_(index), remain_(remain) {}

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        Iterator() : queue_(nullptr), index_(0), remain_(0)
        {
        }

        reference operator*() const
        {
            assert(queue_ && remain_ > 0);
            return queue_->data[index_];
        }
        pointer operator->() const
        {
            assert(queue_ && remain_ > 0);
            return &queue_->data[index_];
        }
        Iterator &operator++()
        {
            if (remain_ > 0)
            {
                index_ = (index_ + 1) % queue_->Cap();
                --remain_;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator &other) const { return remain_ == other.remain_ && queue_ == other.queue_; }
        bool operator!=(const Iterator &other) const { return !(*this == other); }
    };

    Iterator begin() { return Iterator(this, front_, static_cast<std::size_t>(this->Len())); }
    Iterator end() { return Iterator(this, rear_, 0); }

    class ConstIterator
    {
    private:
        friend class CircleQueueT;

        const CircleQueueT<T> *queue_;
        std::size_t index_;
        std::size_t remain_;

        ConstIterator(const CircleQueueT<T> *q, std::size_t index, std::size_t remain) : queue_(q), index_(index), remain_(remain) {}

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T *;
        using reference = const T &;

        ConstIterator() : queue_(nullptr), index_(0), remain_(0) {}

        reference operator*() const
        {
            assert(queue_ && remain_ > 0);
            return queue_->data[index_];
        }
        pointer operator->() const
        {
            assert(queue_ && remain_ > 0);
            return &queue_->data[index_];
        }
        ConstIterator &operator++()
        {
            if (remain_ > 0)
            {
                index_ = (index_ + 1) % queue_->Cap();
                --remain_;
            }
            return *this;
        }
        ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const ConstIterator &other) const { return remain_ == other.remain_ && queue_ == other.queue_; }
        bool operator!=(const ConstIterator &other) const { return !(*this == other); }
    };

    ConstIterator begin() const { return ConstIterator(this, front_, static_cast<std::size_t>(this->Len())); }
    ConstIterator end() const { return ConstIterator(this, rear_, 0); }
};

using CircleQueue = CircleQueueT<int>;

template <typename T>
CircleQueueT<T>::CircleQueueT(int cap) : data(nullptr), capacity(cap > 0 ? cap : 10), length(0), front_(0), rear_(0)
{
    data = new T[static_cast<size_t>(capacity)];
}

template <typename T>
CircleQueueT<T>::~CircleQueueT()
{
    delete[] data;
}

template <typename T>
CircleQueueT<T>::CircleQueueT(const CircleQueueT &other) : capacity(other.capacity), length(other.length)
{
    data = new T[static_cast<size_t>(capacity)];
    for (int i = 0; i < length; ++i)
    {
        data[i] = other.data[(other.front_ + i) % other.capacity];
    }
    front_ = 0;
    rear_ = static_cast<std::size_t>(length);
}

template <typename T>
CircleQueueT<T>::CircleQueueT(CircleQueueT &&other) noexcept : data(other.data), capacity(other.capacity), length(other.length), front_(other.front_), rear_(other.rear_)
{
    other.data = nullptr;
    other.capacity = 0;
    other.length = 0;
    other.front_ = 0;
    other.rear_ = 0;
}

template <typename T>
CircleQueueT<T> &CircleQueueT<T>::operator=(const CircleQueueT &other)
{
    if (this != &other)
    {
        CircleQueueT temp(other);
        Swap(temp);
    }
    return *this;
}

template <typename T>
void CircleQueueT<T>::Swap(CircleQueueT &other) noexcept
{
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(length, other.length);
    std::swap(front_, other.front_);
    std::swap(rear_, other.rear_);
}

template <typename T>
CircleQueueT<T> &CircleQueueT<T>::operator=(CircleQueueT &&other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        capacity = other.capacity;
        length = other.length;
        front_ = other.front_;
        rear_ = other.rear_;
        other.data = nullptr;
        other.capacity = 0;
        other.length = 0;
        other.front_ = 0;
        other.rear_ = 0;
    }
    return *this;
}

template <typename T>
void CircleQueueT<T>::Clear()
{
    // 置空时保持不变式 front_ == rear_，避免 Clear 后迭代器指向残留元素
    length = 0;
    front_ = rear_;
}

template <typename T>
bool CircleQueueT<T>::Empty() const
{
    return length == 0;
}

template <typename T>
int CircleQueueT<T>::Len() const
{
    return length;
}

template <typename T>
int CircleQueueT<T>::Cap() const
{
    return capacity;
}

template <typename T>
void CircleQueueT<T>::Resize()
{
    int newCap = (capacity == 0) ? 1 : capacity * 2;
    int oldCap = (capacity <= 0) ? 1 : capacity;
    T *newData = new T[static_cast<size_t>(newCap)];
    for (int i = 0; i < length; ++i)
    {
        newData[i] = std::move(data[(front_ + i) % oldCap]);
    }
    delete[] data;
    data = newData;
    capacity = newCap;
    front_ = 0;
    rear_ = static_cast<std::size_t>(length);
}

template <typename T>
void CircleQueueT<T>::ForEach(const std::function<void(T &)> &visit)
{
    for (auto it = begin(); it != end(); ++it)
    {
        visit(*it);
    }
}

template <typename T>
void CircleQueueT<T>::ForEach(const std::function<void(const T &)> &visit) const
{
    for (auto it = begin(); it != end(); ++it)
    {
        visit(*it);
    }
}

template <typename T>
bool CircleQueueT<T>::GetHead(T &e) const
{
    if (length == 0)
        return false;
    e = data[front_];
    return true;
}

template <typename T>
bool CircleQueueT<T>::EnQueue(const T &e)
{
    if (length == capacity)
    {
        Resize();
    }
    data[rear_] = e;
    rear_ = (rear_ + 1) % capacity;
    ++length;
    return true;
}

template <typename T>
bool CircleQueueT<T>::DeQueue(T &e)
{
    if (Empty())
    {
        return false;
    }
    e = data[front_];
    front_ = (front_ + 1) % capacity;
    length--;
    return true;
}

#endif
