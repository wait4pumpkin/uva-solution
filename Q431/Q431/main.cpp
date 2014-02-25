//
//  main.cpp
//  Q431
//
//  Created by Pumpkin Lee on 2/24/14.
//  Copyright (c) 2014 Pumpkin Lee. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Evidence {
    int score;
    int time;
    string description;
};

int main(int argc, const char * argv[])
{
    int nCases;
    cin >> nCases;
    cin.get();
    
    string content;
    getline(cin, content);
    
    vector<vector<Evidence>> cases(nCases);
    vector<int> limits;
    for (int idxCase=0; idxCase<nCases; ++idxCase) {
        int limit;
        cin >> limit;
        cin.get();
        limits.push_back(limit);
        
        while (true) {
            getline(cin, content);
            if (content.size() <= 0) break;
            
            int score, time;
            string description;
            stringstream ss(content);
            ss >> score >> time >> description;
            cases[idxCase].push_back(Evidence { score, time, description });
        }
    }
    
    for (int idxCase=0; idxCase<nCases; ++idxCase) {
        cout << "Score  Time  Description" << endl;
        cout << "-----  ----  -----------" << endl;
        
        vector<Evidence> &theCase = cases[idxCase];
        vector<int> memo(limits[idxCase] + 1, 0);
        for (int i=0; i<theCase.size(); ++i) {
            for (int j=limits[idxCase]; j >= theCase[i].time; --j) {
                memo[j] = std::max(memo[j], memo[j - theCase[i].time] + theCase[i].score);
                if (j == limits[idxCase]) cout << i << endl;
            }
        }
        cout << memo[limits[idxCase]] << endl;
        
        cout << endl;
    }
    
    return 0;
}

