#include <iostream>
#include "vf2.h"
#include <set>
#include <cstdio>

using namespace std;

void read_wiki_vote(){
    // 无权有向图
    // 出现的点中最大的为8297，最小的为3
    // 实际出现点数7115，边数103689
    // 将数据中未出现的点看作独立点，不影响算法正确性
    freopen("Wiki-Vote.txt", "r", stdin);
    freopen("result.txt", "w", stdout);
    graph<int,int> target(8297);
    int from, to;
    while(cin >> from >> to){
        target.insert(from, to);
    }
    int caseNum;
    cin.clear();
    freopen("wiki_data.txt", "r", stdin);
    while(cin >> caseNum){
        if(caseNum == -1) break;
        int n, m;
        cin >> n >> m;
        graph<int, int> pattern(m);
        while(n--){
            cin >> from >> to;
            pattern.insert(from,to);
        }
        vf2(&target, &pattern, false);
    }
}

void read_arrtribute_data(){
    freopen("attribute.txt", "r", stdin);
    freopen("result.txt", "w", stdout);
    graph<int,int> target(3);
    int from, to, val;
    while(cin >> from >> to >> val){
        if(from == -1) break;
        target.insert(from, to, val);
    }
    graph<int,int> pattern(3);
    while(cin >> from >> to >> val){
        if(from == -1) break;
        pattern.insert(from, to, val);
    }
    vf2(&target, &pattern, true);
}

void read_bitcoin(){
    freopen("soc-sign-bitcoinalpha.csv", "r", stdin);
    freopen("result.txt", "w", stdout);
    graph<int,int> target(7604);
    int from, to, val, tmp;
    while(scanf("%d,%d,%d,%d",&from, &to, &val, &tmp) != EOF){
        target.insert(from, to, val);
    }
    cin.clear();
    freopen("bitcoindata.txt", "r", stdin);
    graph<int,int> pattern(2);
    while(cin >> from >> to >> val){
        if(from == -1) break;
        pattern.insert(from, to, val);
    }
    vf2(&target, &pattern, true);
}

int main() {
    freopen("error.txt", "w", stderr);
    read_bitcoin();
    return 0;
}
