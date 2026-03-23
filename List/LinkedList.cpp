#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
    head = new Node();
    length = 0;
}

LinkedList::~LinkedList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

LinkedList::LinkedList(LinkedList &&other) noexcept : head(other.head), length(other.length)
{
    other.head = nullptr;
    other.length = 0;
}

LinkedList &LinkedList::operator=(LinkedList &&other) noexcept
{
    if (this != &other)
    {
        Node *cur = head;
        while (cur != nullptr)
        {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }

        head = other.head;
        length = other.length;

        other.head = nullptr;
        other.length = 0;
    }
    return *this;
}

void LinkedList::Clear()
{
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

bool LinkedList::Empty() const
{
    return length == 0;
}

int LinkedList::Len() const
{
    return length;
}
// i为index
bool LinkedList::GetElem(int i, int &e) const
{
    if (i < 0 || i >= length)
        return false;
    Node *current = head->next;
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

int LinkedList::LocateElem(int e) const
{
    Node *current = head->next;
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

bool LinkedList::PriorElem(int cur_e, int &pre_e) const
{
    Node *current = head->next;
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
            else
            {
                pre_e = temp->data;
                return true;
            }
        }
        temp = current;
        current = current->next;
        ++pos;
    }
    return false;
}

bool LinkedList::NextElem(int cur_e, int &next_e) const
{
    Node *current = head->next;
    int pos = 0;
    while (current != nullptr)
    {
        if (current->data == cur_e)
        {
            if (pos == length - 1)
            {
                return false;
            }
            else
            {
                next_e = current->next->data;
                return true;
            }
        }
        current = current->next;
        ++pos;
    }
    return false;
}

bool LinkedList::Insert(int i, int e)
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
bool LinkedList::Delete(int i, int &e)
{
    if (i < 0 || length == 0 || i >= length)
        return false;
    Node *prev = head;
    for (int j = 0; j < i; ++j)
    {
        prev = prev->next;
    }
    // prev是i-1处的节点
    // 特殊情况是末尾，删除length-1处的节点
    // 因为其本身后面没有节点
    // 其他节点情况一致
    // 最后一个节点的next指向的是nullptr,所以不用特殊处理

    // 执行删除
    Node *to_del = prev->next;
    e = to_del->data;
    prev->next = to_del->next;
    delete to_del;

    --length;
    return true;
}

void LinkedList::Traverse() const
{
    for (auto num : *this)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

bool LinkedList::Push_back(int e)
{
    return Insert(length, e);
}