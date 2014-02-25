//
//  main.cpp
//  Q102
//
//  Created by Pumpkin Lee on 2/25/14.
//  Copyright (c) 2014 Pumpkin Lee. All rights reserved.
//

#include <iostream>
#include <cstdint>

using namespace std;

int main(int argc, const char * argv[])
{
    int lookup[6][3] = { { 0, 5, 7 }, { 0, 4, 8 }, { 2, 3, 7 },
                         { 2, 4, 6 }, { 1, 3, 8 }, { 1, 5, 6 } };
    const char *str[6] = { "BCG", "BGC", "CBG", "CGB", "GBC", "GCB" };
    while (true) {
        int nums[9];
        if (scanf("%d %d %d %d %d %d %d %d %d",
                  &nums[0], &nums[1], &nums[2], &nums[3], &nums[4],
                  &nums[5], &nums[6], &nums[7], &nums[8]) == EOF) break;
        
        int max = INT32_MIN;
        int result = -1;
        for (int i=0; i<6; ++i) {
            int sum = 0;
            int *table = lookup[i];
            for (int k=0; k<3; ++k) {
                sum += nums[table[k]];
            }
            if (sum > max) {
                max = sum;
                result = i;
            }
        }
        
        int total = 0;
        for (int i=0; i<9; ++i) {
            total += nums[i];
        }
        printf("%s %d\n", str[result], total - max);
    }
    
    return 0;
}

// 根据题目意思，转换一下，就是求每个bin不移动的bottle数最多，做一个table求和选最大即可
