#ifndef QUEUEBASE_H
#define QUEUEBASE_H

#include <concepts>
#include <functional>

template <typename T>
concept QueueBaseElement = std::default_initializable<T> && std::copyable<T> && std::equality_comparable<T>;

template <typename T>
class QueueBaseT
{
    static_assert(QueueBaseElement<T>);

public:
    virtual ~QueueBaseT() = default;

    // 清空
    virtual void Clear() = 0;
    // 判空
    virtual bool Empty() const = 0;
    // 长度
    virtual int Len() const = 0;
    virtual bool GetHead(T &e) const = 0;
    virtual bool EnQueue(const T &e) = 0;
    virtual bool DeQueue(T &e) = 0;
    // 访问所有元素
    virtual void ForEach(const std::function<void(const T &)> &visit) const = 0;
    virtual void ForEach(const std::function<void(T &)> &visit) = 0;
};

using QueueBase = QueueBaseT<int>;

#endif