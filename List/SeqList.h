#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"

class SeqList : public List
{
private:
    int *data;
    int capacity;
    int length;
    void Resize();
    // noexcept是承诺不抛出异常

public:
    SeqList(int cap = 10);
    ~SeqList();

    SeqList(const SeqList &) = delete;
    SeqList(SeqList &&) noexcept;
    SeqList &operator=(const SeqList &) = delete;
    SeqList &operator=(SeqList &&) noexcept;

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
    int Cap() const;
    bool Push_back(int e);

    class Iterator
    {
        //* ++ !=
    private:
        int *ptr;

    public:
        Iterator(int *p = nullptr) : ptr(p) {}

        int &operator*() const { return *ptr; }
        Iterator &operator++() // 这是前置递增
        {
            ++ptr;
            return *this;
        }
        Iterator operator++(int) // 这是后置递增
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
        //* ++ !=
    private:
        const int *ptr;

    public:
        ConstIterator(const int *p = nullptr) : ptr(p) {}

        const int &operator*() const { return *ptr; }
        ConstIterator &operator++() // 这是前置递增
        {
            ++ptr;
            return *this;
        }
        ConstIterator operator++(int) // 这是后置递增
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

#endif