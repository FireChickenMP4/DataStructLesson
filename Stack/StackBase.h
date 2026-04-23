#ifndef STACKBASE_H
#define STACKBASE_H

#include <concepts>
#include <functional>

template <typename T>
concept StackBaseElement = std::default_initializable<T> && std::copyable<T> && std::equality_comparable<T>;

template <typename T>
class StackBaseT
{
    static_assert(StackBaseElement<T>);

private:
    // 获取第i个元素
    virtual bool GetElem(int i, T &e) const = 0;
    // 查找元素 e,返回索引,未找到返回 -1
    virtual int LocateElem(const T &e) const = 0;
    // 在i索引处插入 e (i从0开始)
    virtual bool Insert(int i, const T &e) = 0;
    // 删除第i个元素,删除值由e返回
    virtual bool Delete(int i, T &e) = 0;

public:
    virtual ~StackBaseT() = default;

    // 清空
    virtual void Clear() = 0;
    // 判空
    virtual bool Empty() const = 0;
    // 长度
    virtual int Len() const = 0;
    // 获取栈顶元素
    virtual bool GetTop(T &e) const = 0;
    // 入栈
    virtual bool Push(const T &e) = 0;
    // 出栈
    virtual bool Pop(T &e) = 0;
    // 访问所有元素
    virtual void ForEach(const std::function<void(const T &)> &visit) const = 0;
    virtual void ForEach(const std::function<void(T &)> &visit) = 0;
};

using StackBase = StackBaseT<int>;

#endif