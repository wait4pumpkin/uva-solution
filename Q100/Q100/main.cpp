//
//  main.cpp
//  Q100
//
//  Created by Pumpkin Lee on 2/24/14.
//  Copyright (c) 2014 Pumpkin Lee. All rights reserved.
//

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <algorithm>

using namespace std;

int cycle(int num);

int main(int argc, const char * argv[])
{
    int table[1000000];
    memset(table, 0, sizeof(table));
    
    while (true) {
        int a, b;
        if (scanf("%d %d", &a, &b) == EOF) break;
        
        int max = INT32_MIN;
        int i = std::min(a, b);
        int end = std::max(a, b);
        for (; i<=end; ++i) {
            if (table[i] <= 0) {
                table[i] = cycle(i);
            }
            if (table[i] > max) max = table[i];
        }
        printf("%d %d %d\n", a, b, max);
    }
    
    return 0;
}

int cycle(int num) {
    int result = 1;
    while (num != 1) {
        if (num % 2 == 0) {
            num /= 2;
        } else {
            num = 3 * num + 1;
        }
        ++result;
    }
    return result;
}

// 第一次做，输入终止要通过EOF判断
// 简单题目，按题目流程图做即可，记录一下之前的结果避免重复计算
// 题目有提示最终输出的数字要与输入顺序一致，暗示了输入的两个数大小关系不确定，唯一的坑
