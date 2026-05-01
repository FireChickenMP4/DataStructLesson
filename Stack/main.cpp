#include <iostream>
#include "Stack.h"

template <typename T>
void PrintStack(const StackT<T> &stack, const std::function<void(const T &)> &printer = [](const T &value)
                                        { std::cout << value << " "; })
{
    stack.ForEach(printer);
    std::cout << std::endl;
}

void Test();

int main()
{
    // 写栈
    // emmm我想想啊
    // 栈其实可以直接用SeqList的弱化版模拟
    // 所以我直接在SeqListT<T>上重载就可以了
    Test();

    // 然后专门来写exp-4
}

void Test()
{
    // Stack Test
    {
        std::cout << "================Stack Test================" << std::endl;
        Stack nums;
        auto is_num_empty = [&nums]()
        { std::cout << (nums.Empty() ? "Empty" : "Not Empty") << "\n"; };
        is_num_empty();
        nums.Push(1);
        is_num_empty();
        nums.Push(2);
        nums.Push(3);
        // 栈顶 <- 栈底
        PrintStack(nums);
        std::cout << nums.Len() << " " << nums.Cap() << "\n";
        int e;
        nums.Pop(e);
        std::cout << e << "\n";
        PrintStack(nums);
        nums.GetTop(e);
        std::cout << e << "\n";
        nums.Push(4);
        PrintStack(nums);
        nums.Clear();
        is_num_empty();
        nums.Push(5);
        is_num_empty();
        PrintStack(nums);
        std::cout << nums.Len() << " " << nums.Cap() << "\n";

        // 然后测构造
        std::string s;
        StackT<std::string> s1;
        s1.Push("qwq");
        s1.Push("awa");
        s1.Push("=w=");
        PrintStack(s1);

        StackT<std::string> s2(s1);
        // 拷贝构造
        PrintStack(s2);
        s1.Push("s1");
        PrintStack(s1);
        PrintStack(s2);
        s1.Pop(s);

        StackT<std::string> s3(std::move(s2));
        // 移动构造
        PrintStack(s2);
        PrintStack(s3);

        StackT<std::string> s4;
        s4.Push("s4");
        s4 = s3;
        // 拷贝赋值
        s3.Push("s3");
        PrintStack(s3);
        PrintStack(s4);

        StackT<std::string> s5;
        s5 = std::move(s4);
        PrintStack(s4);
        PrintStack(s5);
    }
    std::cout << "=================Test End=================" << std::endl;
}