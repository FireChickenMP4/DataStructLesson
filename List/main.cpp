#include <iostream>
#include "SeqList.h"
#include "LinkedList.h"
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

    return 0;
}