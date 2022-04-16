#include <iostream>
#include "vf2.h"
#include <set>

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
        target.nodelist[from].insert(to, SUCC);
        target.nodelist[to].insert(from, PREV);
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
            pattern.nodelist[from].insert(to, SUCC);
            pattern.nodelist[to].insert(from, PREV);
        }
        vf2(&target, &pattern, false);
    }
}

void read_data(){
    freopen("data.txt", "r", stdin);
    freopen("result.txt", "w", stdout);
    int caseNum;
    while(cin >> caseNum){
        if(caseNum == -1) break;
        cout << "Case " << caseNum << ":" << endl;
        int n, m;
        cin >> n >> m;
        graph<int,int> target(n), pattern(m);
        for(int i=1;i<=n;i++){
            int num;
            cin >> num;
            while(num--){
                int id;
                cin >> id;
                target.nodelist[i].insert(id, SUCC, 0);
            }
            cin >> num;
            while(num--){
                int id;
                cin >> id;
                target.nodelist[i].insert(id, PREV, 0);
            }
        }
        for(int i=1;i<=m;i++){
            int num;
            cin >> num;
            while(num--){
                int id;
                cin >> id;
                pattern.nodelist[i].insert(id, SUCC, 0);
            }
            cin >> num;
            while(num--){
                int id;
                cin >> id;
                pattern.nodelist[i].insert(id, PREV, 0);
            }
        }
        init();
        vf2(&target, &pattern, false);
    }
}

int main() {
    read_data();
    return 0;
}
