#include <iostream>
#include "SeqList.h"
#include "LinkedList.h"

void UnionAB(const List &A, const List &B, List &out)
{
    // 思路：
    // 1) 先清空 out。
    // 2) 遍历 A，把不在 out 里的元素插入 out。
    // 3) 再遍历 B，把不在 out 里的元素插入 out。
    // 4) 判重可用 LocateElem，插入可用 Insert(out.Len(), e)。
    // TODO: 在这里实现 A并B 逻辑
}

void IntersectAB(const List &A, const List &B, List &out)
{
    // 思路：
    // 1) 先清空 out。
    // 2) 遍历 A，若元素也在 B 中出现，则考虑加入 out。
    // 3) 为避免重复加入，可先检查该元素是否已在 out 中。
    // 4) 成员检测可用 LocateElem。
    // TODO: 在这里实现 A交B 逻辑
}

void SymmetricDifferenceAB(const List &A, const List &B, List &out)
{
    // 思路：
    // 1) 对每个 A 中元素：若不在 B 中，则加入 out。
    // 2) 对每个 B 中元素：若不在 A 中，则加入 out。
    // 3) 也可先分别求 A-B 与 B-A，再合并。
    // 4) 注意 out 内部去重。
    // TODO: 在这里实现 A异或B 逻辑
}

void DifferenceAB(const List &A, const List &B, List &out)
{
    // 思路：
    // 1) 先清空 out。
    // 2) 遍历 A，把“不在 B 中”的元素加入 out。
    // 3) 这就是 A-B。
    // TODO: 在这里实现 A-B 逻辑
}

void DifferenceBA(const List &A, const List &B, List &out)
{
    // 思路：
    // 1) 先清空 out。
    // 2) 遍历 B，把“不在 A 中”的元素加入 out。
    // 3) 这就是 B-A。
    // TODO: 在这里实现 B-A 逻辑
}

int main()
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
        seqlist.Traverse();
        seqlist.Clear();
        seqlist.Push_back(1);
        seqlist.Push_back(3);
        seqlist.Push_back(3);
        seqlist.Push_back(2);
        seqlist.Traverse();
        std::cout << seqlist.LocateElem(3) << " " << seqlist.LocateElem(9) << std::endl;
        int num1 = -1, num2 = -1;
        std::cout << seqlist.PriorElem(3, num1) << " " << seqlist.PriorElem(9, num2) << std::endl;
        std::cout << num1 << " " << num2 << std::endl;
        std::cout << seqlist.NextElem(3, num1) << " " << seqlist.NextElem(9, num2) << std::endl;
        std::cout << num1 << " " << num2 << std::endl;
        seqlist.Insert(2, 9);
        seqlist.Traverse();
        int num3 = -1;
        seqlist.Delete(3, num3);
        seqlist.Traverse();
        std::cout << num3 << std::endl;
        std::cout << seqlist.Len() << " " << seqlist.Cap() << std::endl;
        // seqlist.Resize(); // 实际上应该private的方法
        // std::cout << seqlist.Len() << " " << seqlist.Cap() << std::endl;
        for (auto num : seqlist)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        // 复制和赋值
        SeqList origin(5);
        origin.Push_back(10);
        origin.Push_back(30);
        origin.Push_back(20);
        origin.Traverse();

        SeqList copy(std::move(origin));
    }

    // LinkedList Test
    {
        std::cout << "==============LinkedList Test==============" << std::endl;
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
        linkedlist.Traverse();

        std::cout << linkedlist.LocateElem(3) << " " << linkedlist.LocateElem(9) << std::endl;

        int pre = -1, nxt = -1;
        std::cout << linkedlist.PriorElem(3, pre) << " " << linkedlist.PriorElem(9, pre) << std::endl;
        std::cout << pre << std::endl;
        std::cout << linkedlist.NextElem(3, nxt) << " " << linkedlist.NextElem(9, nxt) << std::endl;
        std::cout << nxt << std::endl;

        linkedlist.Insert(2, 9);
        linkedlist.Traverse();

        int del = -1;
        linkedlist.Delete(3, del);
        linkedlist.Traverse();
        std::cout << del << std::endl;

        int elem = -1;
        std::cout << linkedlist.GetElem(2, elem) << " " << elem << std::endl;
        std::cout << linkedlist.GetElem(10, elem) << std::endl;

        linkedlist.Push_back(7);
        linkedlist.Push_back(8);
        linkedlist.Traverse();
        std::cout << linkedlist.Insert(100, 10) << std::endl;
        linkedlist.Traverse();
        std::cout << linkedlist.Delete(100, edgeDel) << std::endl;

        int edgePre = -1, edgeNext = -1;
        std::cout << linkedlist.PriorElem(1, edgePre) << std::endl;
        std::cout << linkedlist.NextElem(10, edgeNext) << std::endl;

        linkedlist.Clear();
        std::cout << linkedlist.Empty() << " " << linkedlist.Len() << std::endl;
    }
    std::cout << "==================Test End==================" << std::endl;

    // 对于集合A和集合B，用基本操作求A并B，A交B，A异或B，以及A-B，B-A

    return 0;
}