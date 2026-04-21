#include <iostream>
#include <utility>
#include <vector>
#include "SeqList.h"
#include "LinkedList.h"

template <typename T>
void PrintList(const ListT<T> &list, const std::function<void(const T &)> &printer = [](const T &value)
                                     { std::cout << value << " "; })
{
    list.ForEach(printer);
    std::cout << std::endl;
}

void UnionAB(const List &A, const List &B, List &out)
{
    out.Clear();
    // out = A;
    // 不能这么写，跨类就会出问题
    // 类内确实可以赋值
    // emm，我回头或许可以实现一下相互的转化从而可以跨类赋值？
    // 有必要吗？
    for (int i = 0; i < A.Len(); ++i)
    {
        int e;
        A.GetElem(i, e);
        out.Insert(out.Len(), e);
    }
    for (int i = 0; i < B.Len(); ++i)
    {
        int e;
        B.GetElem(i, e);
        if (out.LocateElem(e) == -1)
        {
            out.Insert(out.Len(), e);
        }
    }
}

void IntersectAB(const List &A, const List &B, List &out)
{
    out.Clear();
    for (int i = 0; i < A.Len(); ++i)
    {
        int e;
        A.GetElem(i, e);
        if (B.LocateElem(e) != -1)
        {
            out.Insert(out.Len(), e);
        }
    }
}

void SymmetricDifferenceAB(const List &A, const List &B, List &out)
{
    out.Clear();
    for (int i = 0; i < A.Len(); ++i)
    {
        int e;
        A.GetElem(i, e);
        if (B.LocateElem(e) == -1)
        {
            out.Insert(out.Len(), e);
        }
    }
    for (int i = 0; i < B.Len(); ++i)
    {
        int e;
        B.GetElem(i, e);
        if (A.LocateElem(e) == -1)
        {
            out.Insert(out.Len(), e);
        }
    }
}

void DifferenceAB(const List &A, const List &B, List &out)
{
    out.Clear();
    for (int i = 0; i < A.Len(); ++i)
    {
        int e;
        A.GetElem(i, e);
        if (B.LocateElem(e) == -1)
        {
            out.Insert(out.Len(), e);
        }
    }
}

void DifferenceBA(const List &A, const List &B, List &out)
{
    DifferenceAB(B, A, out);
}

void DemoCustomPrinter();
void Test();

int main()
{
    // Test();
    SeqList seqA, seqB, seqout;
    LinkedList linkedA, linkedB, linkedout;

    // // push_back
    // {
    //     seqA.Push_back(1);
    //     seqA.Push_back(2);
    //     seqA.Push_back(3);
    //     seqA.Push_back(4);

    //     linkedA.Push_back(1);
    //     linkedA.Push_back(2);
    //     linkedA.Push_back(3);
    //     linkedA.Push_back(4);

    //     seqB.Push_back(2);
    //     seqB.Push_back(3);
    //     seqB.Push_back(5);
    //     seqB.Push_back(6);
    //     seqB.Push_back(7);

    //     linkedB.Push_back(2);
    //     linkedB.Push_back(3);
    //     linkedB.Push_back(5);
    //     linkedB.Push_back(6);
    //     linkedB.Push_back(7);
    // }

    // stdin
    {
        int x, y;
        std::cout << "请输入n和数组A\n";
        std::cin >> x;
        for (int i = 0; i < x; ++i)
        {
            int temp;
            std::cin >> temp;
            seqA.Push_back(temp);
            linkedA.Push_back(temp);
        }
        std::cout << "请输入n和数组B\n";
        std::cin >> y;
        for (int i = 0; i < y; ++i)
        {
            int temp;
            std::cin >> temp;
            seqB.Push_back(temp);
            linkedB.Push_back(temp);
        }
    }

    // A并B
    std::cout << "A并B\n";
    UnionAB(seqA, seqB, seqout);
    PrintList(seqout);
    // A交B
    std::cout << "A交B\n";
    IntersectAB(linkedA, seqB, linkedout);
    PrintList(linkedout);
    // A异或B
    // SymmetricDifferenceAB(seqA, linkedB, seqout);
    // PrintList(seqout);
    // A-B
    std::cout << "A-B\n";
    DifferenceAB(linkedA, linkedB, linkedout);
    PrintList(linkedout);
    // B-A
    std::cout << "B-A\n";
    DifferenceBA(seqA, linkedB, seqout);
    PrintList(seqout);

    return 0;
}

void DemoCustomPrinter()
{
    std::cout << "============Custom Printer Demo===========\n";

    SeqListT<std::pair<int, int>> pairList;
    pairList.Push_back({1, 2});
    pairList.Push_back({3, 4});
    pairList.Push_back({5, 8});

    PrintList<std::pair<int, int>>(pairList, [](const std::pair<int, int> &item)
                                   { std::cout << "(" << item.first << ", " << item.second << ") "; });
}

void Test()
{
    // SeqList Test
    {
        std::cout << "===============SeqList Test===============" << std::endl;
        SeqList seqlist(3);
        std::cout << seqlist.Empty() << std::endl;
        seqlist.Push_back(1);
        std::cout << seqlist.Empty() << std::endl;
        seqlist.Push_back(3);
        seqlist.Push_back(2);
        std::cout << seqlist.Len() << std::endl;
        PrintList(seqlist);
        seqlist.Clear();
        seqlist.Push_back(1);
        seqlist.Push_back(3);
        seqlist.Push_back(3);
        seqlist.Push_back(2);
        PrintList(seqlist);
        std::cout << seqlist.LocateElem(3) << " " << seqlist.LocateElem(9) << std::endl;
        int num1 = -1, num2 = -1;
        std::cout << seqlist.PriorElem(3, num1) << " " << seqlist.PriorElem(9, num2) << std::endl;
        std::cout << num1 << " " << num2 << std::endl;
        std::cout << seqlist.NextElem(3, num1) << " " << seqlist.NextElem(9, num2) << std::endl;
        std::cout << num1 << " " << num2 << std::endl;
        seqlist.Insert(2, 9);
        PrintList(seqlist);
        int num3 = -1;
        seqlist.Delete(3, num3);
        PrintList(seqlist);
        std::cout << num3 << std::endl;
        std::cout << seqlist.Len() << " " << seqlist.Cap() << std::endl;
        // seqlist.Resize(); // 实际上应该private的方法
        // std::cout << seqlist.Len() << " " << seqlist.Cap() << std::endl;
        for (auto num : seqlist)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        // 复制和赋值 拷贝和移动
        SeqList origin(5);
        origin.Push_back(10);
        origin.Push_back(30);
        origin.Push_back(20);
        PrintList(origin);
        origin.Push_back(50);
        SeqList copy1(origin);
        PrintList(origin);
        PrintList(copy1);
        SeqList copy2 = origin;
        origin.Push_back(40);
        PrintList(origin);
        PrintList(copy2);

        SeqList move1(std::move(origin));
        PrintList(origin);
        // 因为被移走origin置空，只会输出空行
        PrintList(move1);
        move1.Push_back(60);
        SeqList move2 = std::move(move1);
        PrintList(move1);
        PrintList(move2);
    }

    // LinkedList Test
    {
        std::cout << "==============LinkedList Test=============" << std::endl;
        LinkedList linkedlist;
        std::cout << linkedlist.Empty() << std::endl;

        int edgeDel = -1;
        std::cout << linkedlist.Delete(0, edgeDel) << std::endl;
        int edgeElem = -1;
        std::cout << linkedlist.GetElem(0, edgeElem) << std::endl;
        std::cout << linkedlist.Insert(-1, 100) << std::endl;

        linkedlist.Insert(0, 1);
        linkedlist.Insert(1, 3);
        linkedlist.Insert(2, 2);
        std::cout << linkedlist.Empty() << std::endl;
        std::cout << linkedlist.Len() << std::endl;
        PrintList(linkedlist);

        std::cout << linkedlist.LocateElem(3) << " " << linkedlist.LocateElem(9) << std::endl;

        int pre = -1, nxt = -1;
        std::cout << linkedlist.PriorElem(3, pre) << " " << linkedlist.PriorElem(9, pre) << std::endl;
        std::cout << pre << std::endl;
        std::cout << linkedlist.NextElem(3, nxt) << " " << linkedlist.NextElem(9, nxt) << std::endl;
        std::cout << nxt << std::endl;

        linkedlist.Insert(2, 9);
        PrintList(linkedlist);

        int del = -1;
        linkedlist.Delete(3, del);
        PrintList(linkedlist);
        std::cout << del << std::endl;

        int elem = -1;
        std::cout << linkedlist.GetElem(2, elem) << " " << elem << std::endl;
        std::cout << linkedlist.GetElem(10, elem) << std::endl;

        linkedlist.Push_back(7);
        linkedlist.Push_back(8);
        PrintList(linkedlist);
        std::cout << linkedlist.Insert(100, 10) << std::endl;
        PrintList(linkedlist);
        std::cout << linkedlist.Delete(100, edgeDel) << std::endl;

        int edgePre = -1, edgeNext = -1;
        std::cout << linkedlist.PriorElem(1, edgePre) << std::endl;
        std::cout << linkedlist.NextElem(10, edgeNext) << std::endl;

        linkedlist.Clear();
        std::cout << linkedlist.Empty() << " " << linkedlist.Len() << std::endl;

        // 复制和赋值 拷贝和移动
        LinkedList origin;
        origin.Push_back(10);
        origin.Push_back(30);
        origin.Push_back(20);
        PrintList(origin);
        origin.Push_back(50);
        LinkedList copy1(origin);
        PrintList(origin);
        PrintList(copy1);
        LinkedList copy2 = origin;
        origin.Push_back(40);
        PrintList(origin);
        PrintList(copy2);

        LinkedList move1(std::move(origin));
        PrintList(origin);
        // 因为被移走origin置空，只会输出空行
        PrintList(move1);
        move1.Push_back(60);
        LinkedList move2 = std::move(move1);
        PrintList(move1);
        PrintList(move2);
    }

    // 对于集合A和集合B，用基本操作求A并B，A交B，A异或B，以及A-B，B-A
    // 我们默认认为A和B是集合，也就是自身无重复元素
    // ABTest
    {
        std::cout << "================ABSet Test================" << std::endl;
        SeqList seq1, seq2, out1;
        LinkedList link1, link2, out2;
        // 1,5,7,3,8
        // 10,0,-1,2,5,8
        seq1.Push_back(1);
        seq1.Push_back(5);
        seq1.Push_back(7);
        seq1.Push_back(3);
        seq1.Push_back(8);
        link1.Push_back(1);
        link1.Push_back(5);
        link1.Push_back(7);
        link1.Push_back(3);
        link1.Push_back(8);
        seq2.Push_back(10);
        seq2.Push_back(0);
        seq2.Push_back(-1);
        seq2.Push_back(2);
        seq2.Push_back(5);
        seq2.Push_back(8);
        link2.Push_back(10);
        link2.Push_back(0);
        link2.Push_back(-1);
        link2.Push_back(2);
        link2.Push_back(5);
        link2.Push_back(8);
        UnionAB(seq1, link2, out1);
        UnionAB(link1, seq2, out2);
        // 1,5,7,3,8,10,0,-1,2
        PrintList(out1);
        PrintList(out2);
        IntersectAB(seq1, seq2, out2);
        // 5,8
        PrintList(out2);
        SymmetricDifferenceAB(link1, link2, out1);
        // 1,7,3,10,0,-1,2
        PrintList(out1);
        DifferenceAB(seq1, link2, out2);
        // 1,7,3
        PrintList(out2);
        DifferenceBA(link1, seq2, out1);
        // 10,0,-1,2
        PrintList(out1);
    }

    DemoCustomPrinter();

    std::cout << "=================Test End=================" << std::endl;
}