#ifndef LIST_H
#define LIST_H

class List
{
public:
    virtual ~List() = default;

    // 清空
    virtual void Clear() = 0;
    // 判空
    virtual bool Empty() const = 0;
    // 长度
    virtual int Len() const = 0;
    // 获取第i个元素
    virtual bool GetElem(int i, int &e) const = 0;
    // 查找元素 e,返回索引,未找到返回 -1
    virtual int LocateElem(int e) const = 0;
    // 前驱
    virtual bool PriorElem(int cur_e, int &pre_e) const = 0;
    // 后驱
    virtual bool NextElem(int cur_e, int &next_e) const = 0;
    // 在i索引处插入 e (i从0开始)
    virtual bool Insert(int i, int e) = 0;
    // 删除第i个元素,删除值由e返回
    virtual bool Delete(int i, int &e) = 0;
    // 遍历输出所有元素
    virtual void Traverse() const = 0;
};

#endif