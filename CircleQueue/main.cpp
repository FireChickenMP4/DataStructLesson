#include <iostream>
#include "CircleQueue.h"

template <typename T>
void PrintCircleQueue(const CircleQueueT<T> &cq, const std::function<void(const T &)> &printer = [](const T &value)
                                                 { std::cout << value << " "; })
{
    cq.ForEach(printer);
    std::cout << std::endl;
}

void Test();

int main()
{
    // 先做一些说明
    // 我想想，队列也是一种特殊的线性表
    // 所以依旧是在Seqlist基础上改
    // 然后就是普通队列不是很舒服，所以底层用循环队列实现
    // 所以会有两个头文件QueueBase.h和CircleQueue.h
    // 然后主要是要改一下调用Insert和Delete以及GetElem的逻辑
    // 其实就是通过front和rear算出来对应索引就可以了
    // 当然emm
    // 迭代器的输出，或者说ForEach
    // 要改动一下迭代器的逻辑

    // 并非
    // 感觉循环队列和线性表差别过大，没法直接复用现有的Insert，需要重写，那干脆就直接重写得了
    Test();

    return 0;
}

void Test()
{
    // CircleQueue Test
    {
        std::cout << "=============CircleQueue Test=============" << std::endl;
        CircleQueue nums;
        auto is_num_empty = [&nums]()
        { std::cout << (nums.Empty() ? "Empty" : "Not Empty") << "\n"; };
        is_num_empty();
        nums.EnQueue(1);
        is_num_empty();
        nums.EnQueue(2);
        nums.EnQueue(3);
        // 队首 <- 队尾
        PrintCircleQueue(nums);
        std::cout << nums.Len() << " " << nums.Cap() << "\n";
        int e;
        nums.DeQueue(e);
        std::cout << e << "\n";
        PrintCircleQueue(nums);
        nums.GetHead(e);
        std::cout << e << "\n";
        nums.EnQueue(4);
        PrintCircleQueue(nums);
        nums.Clear();
        is_num_empty();
        nums.EnQueue(5);
        is_num_empty();
        PrintCircleQueue(nums);
        std::cout << nums.Len() << " " << nums.Cap() << "\n";

        CircleQueue resize_test;
        for (int i = 0; i < 20; ++i)
        {
            resize_test.EnQueue(i);
        }
        PrintCircleQueue(resize_test);
        std::cout << resize_test.Len() << " " << resize_test.Cap() << "\n";

        CircleQueue circle_test;
        for (int i = 0; i < 8; ++i)
        {
            circle_test.EnQueue(i);
        }
        for (int i = 0; i < 5; ++i)
        {
            int temp;
            circle_test.DeQueue(temp);
        }
        for (int i = 0; i < 6; ++i)
        {
            circle_test.EnQueue(i);
        }
        PrintCircleQueue(circle_test);
        std::cout << circle_test.Len() << " " << circle_test.Cap() << "\n";

        // 然后测构造
        std::string s;
        CircleQueueT<std::string> s1;
        s1.EnQueue("qwq");
        s1.EnQueue("awa");
        s1.EnQueue("=w=");
        PrintCircleQueue(s1);

        CircleQueueT<std::string> s2(s1);
        // 拷贝构造
        PrintCircleQueue(s2);
        s1.EnQueue("s1");
        PrintCircleQueue(s1);
        PrintCircleQueue(s2);
        s1.DeQueue(s);

        CircleQueueT<std::string> s3(std::move(s2));
        // 移动构造
        PrintCircleQueue(s2);
        PrintCircleQueue(s3);

        CircleQueueT<std::string> s4;
        s4.EnQueue("s4");
        s4 = s3;
        // 拷贝赋值
        s3.EnQueue("s3");
        PrintCircleQueue(s3);
        PrintCircleQueue(s4);

        CircleQueueT<std::string> s5;
        s5 = std::move(s4);
        PrintCircleQueue(s4);
        PrintCircleQueue(s5);
    }
    std::cout << "=================Test End=================" << std::endl;
}