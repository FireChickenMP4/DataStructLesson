#include <iostream>
#include <cstring>
#include <string>
#include <utility>
#include "SeqList.h"

const int maxn = 250005;
const char start_char = ' ';
const int char_size = 95;
// 32 (space) - 126 ~
// 这里把空格作为伪广义SAM的分隔符

char s1[maxn], s2[maxn], combined[maxn * 2 + 1];
int ans, best = -1;
struct Suffix_Automaton // 只处理小写字母了
{
    int len[maxn << 2], link[maxn << 2];
    int ch[maxn << 2][char_size];
    bool f[maxn << 2][2];
    // f用于标记同时拥有两种标记
    SeqList v[maxn << 2];
    int last, siz; // siz是节点数量，或者说分配的节点标号
    int pos[maxn << 2];
    // 用于记录结束位置
    inline void init()
    {
        link[0] = -1;
        siz = last = 0;
    }
    inline bool check(const int x) { return f[x][0] & f[x][1]; }
    inline void extend(char *str, const int op, const int offset = 0)
    {
        // op用于标记来自哪个串
        int n = std::strlen(str);
        for (int _ = 0; _ < n; ++_)
        {
            // 创建一个新的状态cur，len(cur)=len(last) + 1
            int c = str[_] - start_char, p = last, cur = ++siz;
            len[cur] = len[p] + 1;
            f[cur][op] = 1;
            // 打字符串来源tag
            pos[cur] = offset + _;
            while (p != -1 && !ch[p][c])
            {
                // p=-1是判断是不是p=link(空字符)
                // !ch[p][c]是检测有没有这一条出边
                // 其实说ch存的是指向的节点
                ch[p][c] = cur;
                p = link[p];
            }
            if (p == -1)
                link[cur] = 0;
            // 如果遍历完p还没啥事的话，link(cur) = 0(空字符)
            else
            {
                // 其他情况存在了v->c的出边
                int q = ch[p][c];
                // 取出边的节点q
                if (len[q] == len[p] + 1) // 平凡情况
                    link[cur] = q;
                else
                {
                    // 需要将q拆为[short(q),len(p)+1],(len[p]+1,long(q)]
                    // 两个等价类
                    // 前者是copy，后者是新q
                    int copy = ++siz;
                    len[copy] = len[p] + 1;
                    pos[copy] = pos[q];
                    link[copy] = link[q];
                    for (int i = 0; i < char_size; ++i)
                        ch[copy][i] = ch[q][i];
                    // 保持出边
                    while (p != -1 && ch[p][c] == q)
                    {
                        // 如果没遍历完p，并且说后缀连接遍历的出边v->c指向q
                        // 那么就修改出边关系
                        // 否则只要遇到v没有c的出边，或者v的c出边指向不是q
                        // 那就可以中止遍历了
                        ch[p][c] = copy;
                        p = link[p];
                    }
                    link[q] = link[cur] = copy;
                    // 修改后缀连接关系
                }
            }
            last = cur;
            // 然后修改last=cur开始下一个字符的追加
        }
    }
    inline void dfs(const int x)
    {
        for (int i = 0; i < v[x].Len(); ++i)
        {
            int y = v[x][i];
            dfs(y);
            f[x][0] |= f[y][0], f[x][1] |= f[y][1];
        }
        if (check(x) && len[x] > ans)
        {
            ans = len[x];
            best = x;
        }
    }
} sam;

int main()
{
    // 来写一下实验六
    // 然后数组操作用写的顺序表就可以了
    // SeqList List;
    // List.Push_back(2);
    // List.Push_back(3);
    // PrintList(List);
    // 主要是关于字符串最长字串长度
    // 最优秀的算法是后缀自动机(Suffix Automaton),简称SAM
    // 主要是要学这个算法
    // SAM其实是在有向无环图（DAG）里面从起始节点走到中止节点会产生s的所有后缀
    // 而走的过程中，s'是s的前缀，一个包含s所有后缀的所有前缀，即是其所有子串
    // 而SAM是这类DAG里面节点数最少的，所以是最优的
    // 对于O(n)的字符串s,其时间空间复杂度都是O(n)
    // 相当于在线性空间压缩了s的所有子串信息

    // 这里用一个伪广义SAM，我们把两个字符串拼在一起，用特殊分隔符分开
    // 只需要找到出现两次以及上的最长子串就可以了
    // 但是需要防止这个都在特殊符号左侧
    // 所以要给来自s1和s2的串打上不同的标记
    // 只有一个串的endpos内同时拥有两种标记
    // 它才可以尝试去更新答案
    // 打标记和上传标记的方法和统计子串的方式一样
    // 用树形dp
    // 特殊符号用z后面的字符{
    std::cout << "输入s1:";
    std::cin >> s1;
    std::cout << "输入s2:";
    std::cin >> s2;
    int len1 = static_cast<int>(std::strlen(s1));
    std::strcpy(combined, s1);
    combined[len1] = ' ';
    std::strcpy(combined + len1 + 1, s2);
    char qwq[] = " ";
    sam.init();
    sam.extend(s1, 0, 0);
    sam.extend(qwq, 0, len1);
    sam.extend(s2, 1, len1 + 1);
    for (int i = 1; i <= sam.siz; ++i)
        sam.v[sam.link[i]].Push_back(i);
    sam.dfs(0);
    std::cout << "最长子串长度: " << ans;
    if (best != -1)
    {
        int start = sam.pos[best] - sam.len[best] + 1;
        std::string result(combined + start, sam.len[best]);
        std::cout << "\n最长子串: " << result;
    }
}