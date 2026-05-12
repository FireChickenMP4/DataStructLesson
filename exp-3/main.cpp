#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <climits>
#include "SeqList.h"

template <typename T>
void PrintList(const ListT<T> &list, const std::function<void(const T &)> &printer = [](const T &value)
                                     { std::cout << value << " "; })
{
    list.ForEach(printer);
    std::cout << std::endl;
}

template <typename T, typename F1, typename F2>
    requires std::invocable<F1, const T &> && std::invocable<F2>
void ForEachConstFn(const ListT<T> &list, F1 &&fn, F2 &&last)
{
    list.ForEach(std::function<void(const T &)>(std::forward<F1>(fn)));
    std::forward<F2>(last)();
    // 这里干脆也加上完美转发
    // 但是由于虚函数里面无法使用模板
    // 所以要么就是大改架构
    // 要么就是在这里转一次function
    // 其实是绕不开的
}
template <typename T, typename F1>
    requires std::invocable<F1, const T &>
void ForEachConstFn(const ListT<T> &list, F1 &&fn)
{
    list.ForEach(std::function<void(const T &)>(std::forward<F1>(fn)));
}
// 这里重载一个没有last版本
// 其实说可以直接给last上std::function<void()> 然后上个默认值[](){}
// 这样传入无参数的闭包能隐式转换成function
// 也就是有点性能开销
// 我们之所以给fn要上泛型，实际上是因为模板的问题，而不是因为不能隐式转换

template <typename T, typename F1, typename F2>
    requires std::invocable<F1, T &> && std::invocable<F2>
void ForEachMutFn(ListT<T> &list, F1 &&fn, F2 &&last)
{
    // 由于可变，所以也要给ForEach写一个可变的重载
    list.ForEach(std::function<void(T &)>(std::forward<F1>(fn)));
    std::forward<F2>(last)();
}

template <typename T, typename F1>
    requires std::invocable<F1, T &>
void ForEachMutFn(ListT<T> &list, F1 &&fn)
{
    // 由于可变，所以也要给ForEach写一个可变的重载
    list.ForEach(std::function<void(T &)>(std::forward<F1>(fn)));
}

struct Student
{
    std::string ID;
    std::string Name;
    uint32_t Grade;

    Student() = default;
    Student(std::string id, std::string name, uint32_t grade)
        : ID(id), Name(name), Grade(grade) {}
    bool operator==(const Student &other) const = default;

    friend std::ostream &operator<<(std::ostream &os, const Student &s);
    friend std::istream &operator>>(std::istream &is, Student &s);
};

std::ostream &operator<<(std::ostream &os, const Student &s)
{
    os << s.ID << "\t" << s.Name << "\t" << s.Grade;
    return os;
}
std::istream &operator>>(std::istream &is, Student &s)
{
    int64_t temp;
    is >> s.ID >> s.Name >> temp;

    s.Grade = static_cast<uint32_t>(
        std::clamp<int64_t>(temp, 0, UINT32_MAX));

    return is;
}

// template <typename T>
// void SeqListT<T>::Sort(bool (*cmp)(const T &, const T &))
// {
// std::sort(data, data + length, cmp);
// }

template <typename T>
T &SeqListT<T>::operator[](int index)
{
    return data[index];
}
template <typename T>
const T &SeqListT<T>::operator[](int index) const
{
    return data[index];
}
// 会删除数据
template <typename T>
void SeqListT<T>::Resize(size_t n)
{
    // if (n <= length)
    //     return;
    delete[] data;
    capacity = static_cast<int>(n);
    length = static_cast<int>(n);
    data = new T[capacity];
    for (int i = 0; i < length; ++i)
    {
        data[i] = T();
    }
}

template <typename T>
template <typename Key>
void SeqListT<T>::Sort(Key ex)
{
    // 这两个模板要分开，一个类内一个类外
    using KeyType = decltype(ex(std::declval<T>()));
    // using等价typedef
    // decltype(表达式)推测表达式值
    // std::declval<T>()是一个函数模板
    // 声明为 T&& declval() noexcept;
    // 只有声明没有定义
    // 只能在未求值的上下文（如decltype sizeof typeid）中使用
    // 作用是返回T类型的右值引用，用来在不创建真实对象的情况下获得一个T的实例值
    static_assert(std::is_unsigned<KeyType>::value, "Key must be unsigned integer");

    if (length <= 1)
        return;

    const int BITS = sizeof(KeyType) * 8;
    const int RADIX = 256;
    // 按字节分桶
    // std::vector<T> buffer(length);
    // 我们为了将这个buffer也换成我们的顺序表的话
    // 还需要两件事
    // 一个是将其改成可以默认构造初始化每个元素
    // 但是我不是很想改，所以新声明一个重载的Resize了
    // 一个是下标访问operator[]
    // 在SeqList中写声明在这里写实现了
    SeqListT<T> buffer;
    buffer.Resize(length);

    for (int shift = 0; shift < BITS; shift += 8)
    {
        int count[RADIX] = {0};

        // 计算当前字节出现数
        for (int i = 0; i < length; ++i)
        {
            KeyType key = ex(data[i]);
            int byte = (key >> shift) & 0xFF;
            ++count[byte];
        }
        // 计算前缀和，每个桶的起始位置
        for (int i = 1; i < RADIX; ++i)
        {
            count[i] += count[i - 1];
        }
        // 从后向前放置元素，保证稳定性
        for (int i = length - 1; i >= 0; --i)
        {
            KeyType key = ex(data[i]);
            int byte = (key >> shift) & 0xFF;
            int pos = --count[byte];
            buffer[pos] = std::move(data[i]);
        }
        // 交换回原数组
        for (int i = 0; i < length; ++i)
        {
            data[i] = std::move(buffer[i]);
        }
    }
}

int main()
{
    // SeqListT<std::string> list;
    // list.Push_back("qwq");
    // list.Push_back("awa");
    // PrintList(list);
    // SeqListT<Student> Students;
    // Students.Push_back(Student{.ID = "1", .Name = "qwq", .Grade = 123});
    // Students.Push_back(Student{.ID = "2", .Name = "awa", .Grade = 321});
    // PrintList(Students);
    // 这种声明只能适用于聚合类型
    // 原本结构体是聚合类型
    // 而聚合类型必须满足
    // 没有用户声明的构造函数（包括 = default 和 = delete）
    // 没有私有或受保护的非静态数据成员
    // 没有虚函数、虚基类
    // 没有默认成员初始化器（C++20 放宽了部分限制，但构造函数限制仍保留）
    // 因为其有可能会绕过构造函数，导致不满足我们的意图
    // 而且C++聚合初始化早用于函数构造，为了兼容性考虑自然要继承这个限制
    // 当然我不写构造函数也是满足默认构造的
    // 这里只是说一下这种语法使用范围

    // 我们用写的构造函数就行了
    // Student stu;
    // std::cin >> stu;
    // Students.Push_back(Student("001", "qwq", 123));
    // Students.Push_back(Student("002", "awa", 321));
    // Students.Push_back(stu);
    // PrintList(Students, std::function<void(const Student &)>([](const Student &value)
    //                                                          { std::cout << value << "\n"; }));
    // 这里需要再显式转换以下，有点麻烦
    // 而且存在性能开销和推到问题
    // 所以最好把Func也提成模板
    // 当然这个也有问题就是编译后代码膨胀和错误信息复杂
    // 不如写一个ForEachFn函数

    // 用windows.h改一下编码
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    SeqListT<Student> Students;
    // 输入逻辑
    {
        int n = 0;
        std::cout << "请输入学生人数:";
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            Student temp;
            std::printf("请输入第%d个学生学号、姓名和成绩:\n", i + 1);
            std::cin >> temp;
            Students.Push_back(temp);
        }
    }

    // 先用sort快排测试效果
    // std::sort(Students.begin(), Students.end(), [](const Student &a, const Student &b)
    //           { return a.Grade > b.Grade; });
    // 此处并不行，因为迭代器只是实现了基本访问，而不是随机访问
    // sort需要随机访问的迭代器
    // 首先双向移动(++ --)
    // 其次随机访问(+n -n it1-it2)
    // 然后是不只限于!=的比较,== > < <= >=
    // 最后是下标访问
    // 当然可以打包把data取出来操作
    // Students.Sort([](const Student &a, const Student &b)
    //               { return a.Grade > b.Grade; });
    // 测试可以
    Students.Sort([](const Student &s)
                  { return ~s.Grade; });
    // 降序排序可以取反，因为毕竟只是按照取得的参数来进行比较

    // 输出逻辑
    {
        std::cout << "名次\t学号\t姓名\t成绩\n";
        int rank = 1;
        ForEachConstFn(Students, [&rank](const Student &value)
                       { std::cout << rank++ << "\t" << value << "\n"; }, []()
                       { std::cout << std::endl; });
    }

    // 好写完了，一部分我看看有空整合到SeqList和LinkedList里面去
}