//
//  main.cpp
//  Q458
//
//  Created by Pumpkin Lee on 2/25/14.
//  Copyright (c) 2014 Pumpkin Lee. All rights reserved.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[])
{
    while (true) {
        char c = cin.get();
        if (c == EOF) break;
        else cin.putback(c);
        
        string content;
        getline(cin, content);
        for (int i=0; i<content.length(); ++i) {
            cout << (char)(content.at(i) - 7);
        }
        cout << endl;
    }
    
    return 0;
}

// 加密的key是一位，而且是不变的
// 根据sample直接算出
// 这么简单的题目竟然还看那么久，取一行要用getline