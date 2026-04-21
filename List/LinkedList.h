#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "List.h"
#include <iostream>
#include <utility>

template <typename T>
class LinkedListT : public ListT<T>
{
    static_assert(ListElement<T>);

private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &val = T{}, Node *nxt = nullptr) : data(val), next(nxt) {}
    };

    Node *head;
    int length;
    void Swap(LinkedListT &other) noexcept;

public:
    LinkedListT();
    ~LinkedListT();

    LinkedListT(const LinkedListT &);
    LinkedListT(LinkedListT &&) noexcept;
    LinkedListT &operator=(const LinkedListT &);
    LinkedListT &operator=(LinkedListT &&) noexcept;

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
    bool Push_back(const T &e);

    class Iterator
    {
    private:
        Node *ptr;

    public:
        Iterator(Node *p = nullptr) : ptr(p) {}

        T &operator*() const { return ptr->data; }
        Iterator &operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
        }

        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(head ? head->next : nullptr); }
    Iterator end() { return Iterator(nullptr); }

    class ConstIterator
    {
    private:
        const Node *ptr;

    public:
        ConstIterator(const Node *p = nullptr) : ptr(p) {}

        const T &operator*() const { return ptr->data; }
        ConstIterator &operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            ptr = ptr->next;
            return tmp;
        }

        bool operator!=(const ConstIterator &other) const { return ptr != other.ptr; }
    };

    ConstIterator begin() const { return ConstIterator(head ? head->next : nullptr); }
    ConstIterator end() const { return ConstIterator(nullptr); }
};

using LinkedList = LinkedListT<int>;

template <typename T>
LinkedListT<T>::LinkedListT()
{
    head = new Node();
    length = 0;
}

template <typename T>
LinkedListT<T>::~LinkedListT()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
LinkedListT<T>::LinkedListT(const LinkedListT &other)
{
    head = new Node();
    length = 0;

    Node *tail = head;
    Node *cur = other.head ? other.head->next : nullptr;
    while (cur != nullptr)
    {
        tail->next = new Node(cur->data);
        tail = tail->next;
        cur = cur->next;
        ++length;
    }
}

template <typename T>
LinkedListT<T>::LinkedListT(LinkedListT &&other) noexcept : head(other.head), length(other.length)
{
    other.head = new Node();
    other.length = 0;
}

template <typename T>
LinkedListT<T> &LinkedListT<T>::operator=(const LinkedListT &other)
{
    if (this != &other)
    {
        LinkedListT temp(other);
        Swap(temp);
    }
    return *this;
}

template <typename T>
void LinkedListT<T>::Swap(LinkedListT &other) noexcept
{
    std::swap(head, other.head);
    std::swap(length, other.length);
}

template <typename T>
LinkedListT<T> &LinkedListT<T>::operator=(LinkedListT &&other) noexcept
{
    if (this != &other)
    {
        Clear();
        delete head;

        head = other.head;
        length = other.length;

        other.head = new Node();
        other.length = 0;
    }
    return *this;
}

template <typename T>
void LinkedListT<T>::Clear()
{
    if (head == nullptr)
    {
        head = new Node();
        length = 0;
        return;
    }

    Node *current = head->next;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head->next = nullptr;
    length = 0;
}

template <typename T>
bool LinkedListT<T>::Empty() const
{
    return length == 0;
}

template <typename T>
int LinkedListT<T>::Len() const
{
    return length;
}

template <typename T>
bool LinkedListT<T>::GetElem(int i, T &e) const
{
    if (i < 0 || i >= length)
        return false;
    Node *current = head ? head->next : nullptr;
    int pos = 0;
    while (current != nullptr && pos < i)
    {
        current = current->next;
        ++pos;
    }
    if (current == nullptr)
        return false;
    e = current->data;
    return true;
}

template <typename T>
int LinkedListT<T>::LocateElem(const T &e) const
{
    Node *current = head ? head->next : nullptr;
    int pos = 0;
    while (current != nullptr)
    {
        if (current->data == e)
        {
            return pos;
        }
        current = current->next;
        ++pos;
    }
    return -1;
}

template <typename T>
bool LinkedListT<T>::PriorElem(const T &cur_e, T &pre_e) const
{
    Node *current = head ? head->next : nullptr;
    Node *temp = head;
    int pos = 0;
    while (current != nullptr)
    {
        if (current->data == cur_e)
        {
            if (pos == 0)
            {
                return false;
            }
            pre_e = temp->data;
            return true;
        }
        temp = current;
        current = current->next;
        ++pos;
    }
    return false;
}

template <typename T>
bool LinkedListT<T>::NextElem(const T &cur_e, T &next_e) const
{
    Node *current = head ? head->next : nullptr;
    int pos = 0;
    while (current != nullptr)
    {
        if (current->data == cur_e)
        {
            if (pos == length - 1)
            {
                return false;
            }
            next_e = current->next->data;
            return true;
        }
        current = current->next;
        ++pos;
    }
    return false;
}

template <typename T>
bool LinkedListT<T>::Insert(int i, const T &e)
{
    if (i < 0)
        return false;
    if (i > length)
        i = length;
    Node *prev = head;
    for (int index = 0; index < i; ++index)
    {
        prev = prev->next;
    }

    Node *temp = new Node(e);
    temp->next = prev->next;
    prev->next = temp;
    ++length;
    return true;
}

template <typename T>
bool LinkedListT<T>::Delete(int i, T &e)
{
    if (i < 0 || length == 0 || i >= length)
        return false;
    Node *prev = head;
    for (int j = 0; j < i; ++j)
    {
        prev = prev->next;
    }

    Node *to_del = prev->next;
    e = to_del->data;
    prev->next = to_del->next;
    delete to_del;

    --length;
    return true;
}

template <typename T>
void LinkedListT<T>::ForEach(const std::function<void(const T &)> &visit) const
{
    for (auto it = begin(); it != end(); ++it)
    {
        visit(*it);
    }
}

template <typename T>
bool LinkedListT<T>::Push_back(const T &e)
{
    return Insert(length, e);
}

#endif
