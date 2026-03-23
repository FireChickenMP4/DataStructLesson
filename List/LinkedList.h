#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "List.h"

class LinkedList : public List
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int val = 0, Node *nxt = nullptr) : data(val), next(nxt) {}
    };
    Node *head;
    int length;

public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList &) = delete;
    LinkedList(LinkedList &&) noexcept;
    LinkedList &operator=(const LinkedList &) = delete;
    LinkedList &operator=(LinkedList &&) noexcept;

    void Clear() override;
    bool Empty() const override;
    int Len() const override;
    bool GetElem(int i, int &e) const override;
    int LocateElem(int e) const override;
    bool PriorElem(int cur_e, int &pre_e) const override;
    bool NextElem(int cur_e, int &next_e) const override;
    bool Insert(int i, int e) override;
    bool Delete(int i, int &e) override;
    void Traverse() const override;
    bool Push_back(int e);

    class Iterator
    {
        //* ++ !=
    private:
        Node *ptr;

    public:
        Iterator(Node *p = nullptr) : ptr(p) {}

        int &operator*() const { return ptr->data; }
        Iterator &operator++() // 这是前置递增
        {
            ptr = ptr->next;
            return *this;
        }
        Iterator operator++(int) // 这是后置递增
        {
            Iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
        }

        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(head->next); }
    Iterator end() { return Iterator(nullptr); }

    class ConstIterator
    {
        //* ++ !=
    private:
        const Node *ptr;

    public:
        ConstIterator(const Node *p = nullptr) : ptr(p) {}

        const int &operator*() const { return ptr->data; }
        ConstIterator &operator++() // 这是前置递增
        {
            ptr = ptr->next;
            return *this;
        }
        ConstIterator operator++(int) // 这是后置递增
        {
            ConstIterator tmp = *this;
            ptr = ptr->next;
            return tmp;
        }

        bool operator!=(const ConstIterator &other) const { return ptr != other.ptr; }
    };

    ConstIterator begin() const { return ConstIterator(head->next); }
    ConstIterator end() const { return ConstIterator(nullptr); }
};

#endif