#include <iostream>
#include "Stack.h"
#include "SeqList.h"

template <typename T>
void PrintList(const SeqListT<T> &list, const std::function<void(const T &)> &printer = [](const T &value)
                                        { std::cout << value << " "; })
{
    list.ForEach(printer);
    std::cout << std::endl;
}

template <typename T>
void PrintStack(const StackT<T> &stack, const std::function<void(const T &)> &printer = [](const T &value)
                                        { std::cout << value << " "; })
{
    stack.ForEach(printer);
    std::cout << std::endl;
}

void Test();

struct bag
{
    SeqList hasTakeIndex;
    int weight; // 累计重量
    int next;   // 下一个从哪个开始

    bag() = default;
    bag(SeqList list, int weight, int next) : hasTakeIndex(list), weight(weight), next(next) {}
};

void Solution(const SeqList &w, int T);

int main()
{
    // 写栈
    // emmm我想想啊
    // 栈其实可以直接用SeqList的弱化版模拟
    // 所以我直接在SeqListT<T>上重载就可以了
    // Test();

    int T, n; // T背包总体积
    SeqList w;
    // in
    {
        std::cout << "请输入物品个数:";
        std::cin >> n;
        std::cout << "请输入物品重量:\n";
        for (int i = 0; i < n; ++i)
        {
            int t;
            std::cin >> t;
            w.Push_back(t);
        }

        std::cout << "请输入背包总重:";
        std::cin >> T;
    }
    Solution(w, T);
    // 输出在Soultion中集成
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
void Solution(const SeqList &w, int T)
{
    // 不妨想想函数递归是如何的
    // 先是一个已经取了什么包 然后就是剩余数量
    // 假设取了 1 3 4
    // 那为了不重复，直接取5及之后的即可，因为1 3 4肯定是之前取上的
    // 分两个，一个取一个不取
    // 递归条件就是如果超出不是解
    // 如果等于就是解
    // 如果小于就继续尝试递归
    StackT<bag> s;
    s.Push(bag(SeqList(), 0, 0));
    while (!s.Empty()) // 不空就继续循环
    {
        bag state;
        s.Pop(state);
        // 这里Pop出状态，然后检查状态
        if (state.weight > T)
        {
            // 这里不是解
            // 继续循环
            continue;
        }
        if (state.weight == T)
        {
            // 解输出
            std::cout << "找到一组解(第i个物品):";
            PrintList(state.hasTakeIndex, std::function<void(const int &)>([](const int &value)
                                                                           { std::cout << value + 1 << " "; }));
            continue;
            // 继续循环
        }
        // 其他情况就是要继续递归加包了
        // 一个是加包一个是不加
        if (state.next < w.Len())
        {
            bag take = state;
            bag notTake = state;
            take.hasTakeIndex.Push_back(take.next);
            take.weight += w[take.next];
            ++take.next;
            ++notTake.next;
            s.Push(take);
            s.Push(notTake);
        }
    }
}