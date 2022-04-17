#include "graph.h"
#include <cstring>
#define MAXNUM 9001
#define ISEMPTY_2(arr1, arr2) !(arr1[0]-arr2[0])
#define IST(arr1, arr2, idx) (arr1[idx])&&(!arr2[idx])
#define ISHERE(arr, idx) !!arr[idx]

using namespace std;

// vector[0]用来记录vector[1~MAXNUM-1]中的非零元素个数
int core_1[MAXNUM]={0}, core_2[MAXNUM]={0}, in_1[MAXNUM]={0}, in_2[MAXNUM]={0}, out_1[MAXNUM]={0}, out_2[MAXNUM]={0};
int patternNum, targetNum, matchNum;
bool attributeMode = false;

template<class T1, class T2>
bool syn(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m);
template<class T1, class T2>
bool sema(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m);
template<class T1, class T2>
bool feasibility(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m);
template<class T1, class T2>
void pushStatus(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m, int depth);
template<class T1, class T2>
void traceback(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m, int depth);

void output();


void init(){
    matchNum = 0;
    memset(core_1, 0, sizeof(int)*MAXNUM);
    memset(core_2, 0, sizeof(int)*MAXNUM);
    memset(in_1, 0, sizeof(int)*MAXNUM);
    memset(in_2, 0, sizeof(int)*MAXNUM);
    memset(out_1, 0, sizeof(int)*MAXNUM);
    memset(out_2, 0, sizeof(int)*MAXNUM);
}

template<class T1, class T2>
void vf2(graph<T1,T2> *target, graph<T1,T2> *pattern, bool attribute){
    attributeMode = attribute;
    patternNum = pattern->nodeNum;
    targetNum = target->nodeNum;
    match(target, pattern, 1);
    cout << "Total number of matched subgraph(s): " << matchNum << endl;
}

template<class T1, class T2>
void match(graph<T1, T2>* target, graph<T1, T2>* pattern, int depth){
    if(patternNum == core_2[0]) {
        matchNum++;
        output();
        return;
    }
    int new_n, new_m;
    // calculate p(s)
    if(!(ISEMPTY_2(out_1, core_1) || ISEMPTY_2(out_2, core_2))){
        for(int i=1;i<=patternNum;i++) {
            if(IST(out_2, core_2, i)){
                new_m = i;
                break;
            }
        }
        for(int i=1;i<=targetNum;i++){
            if(IST(out_1, core_1, i)){
                new_n = i;
                if(feasibility(target, pattern, new_n, new_m)){
                    pushStatus(target, pattern, new_n, new_m, depth);
                    match(target, pattern, depth+1);
                    traceback(target, pattern, new_n, new_m, depth);
                }
            }
        }
    }
    if(!(ISEMPTY_2(in_1, core_1) || ISEMPTY_2(in_2, core_2))){
        for(int i=1;i<=patternNum;i++){
            if(IST(in_2, core_2, i)){
                new_m = i;
                break;
            }
        }
        for(int i=1;i<=targetNum;i++){
            if(IST(in_1, core_1, i)){
                new_n = i;
                if(feasibility(target, pattern, new_n, new_m)){
                    pushStatus(target, pattern, new_n, new_m, depth);
                    match(target, pattern, depth+1);
                    traceback(target, pattern, new_n, new_m, depth);
                }
            }
        }
    }
    if(ISEMPTY_2(in_1, core_1) && ISEMPTY_2(in_2, core_2) && ISEMPTY_2(out_1, core_1) && ISEMPTY_2(out_2, core_2)){
        for(int i=1;i<=patternNum;i++){
            if(!ISHERE(core_2, i)){
                new_m = i;
                break;
            }
        }
        for(int i=1;i<=targetNum;i++){
            if(!ISHERE(core_1, i)){
                new_n = i;
                if(feasibility(target, pattern, new_n, new_m)){
                    pushStatus(target, pattern, new_n, new_m, depth);
                    match(target, pattern, depth+1);
                    traceback(target, pattern, new_n, new_m, depth);
                }
            }
        }
    }
}

// 将新增加的点对(n,m)所引入的前驱、后继以及n、m点加入SSR中。
template<class T1, class T2>
void pushStatus(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m, int depth){
    core_1[0]++;
    core_2[0]++;
    core_1[n] = m;
    core_2[m] = n;
    if(!ISHERE(in_1, n)){
        in_1[0]++;
        in_1[n] = depth;
    }
    if(!ISHERE(out_1, n)){
        out_1[0]++;
        out_1[n] = depth;
    }
    if(!ISHERE(in_2, m)){
        in_2[0]++;
        in_2[m] = depth;
    }
    if(!ISHERE(out_2, m)){
        out_2[0]++;
        out_2[m] = depth;
    }
    // 检查n引入的前驱与后继
    node<T1, T2> *pNode = &target->nodelist[n];
    edge<T1, T2> *plist = pNode->prevList;
    while(plist){
        int curIdx = plist->fromVex;
        if(!ISHERE(in_1, curIdx)){
            in_1[0] ++;
            in_1[curIdx] = depth;
        }
        plist = plist->fromLink;
    }
    plist = pNode->succList;
    while(plist){
        int curIdx = plist->toVex;
        if(!ISHERE(out_1, curIdx)){
            out_1[0]++;
            out_1[curIdx] = depth;
        }
        plist = plist->toLink;
    }
    // 检查m引入的前驱与后继
    pNode = &pattern->nodelist[m];
    plist = pNode->prevList;
    while(plist){
        int curIdx = plist->fromVex;
        if(!ISHERE(in_2, curIdx)){
            in_2[0]++;
            in_2[curIdx] = depth;
        }
        plist = plist->fromLink;
    }
    plist = pNode->succList;
    while(plist){
        int curIdx = plist->toVex;
        if(!ISHERE(out_2, curIdx)){
            out_2[0]++;
            out_2[curIdx] = depth;
        }
        plist = plist->toLink;
    }
}

template<class T1, class T2>
void traceback(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m, int depth){
    core_1[0]--;
    core_2[0]--;
    core_1[n] = 0;
    core_2[m] = 0;
    if(in_1[n] == depth){
        in_1[n] = 0;
        in_1[0]--;
    }
    if(out_1[n] == depth){
        out_1[n] = 0;
        out_1[0]--;
    }
    if(in_2[m] == depth){
        in_2[m] = 0;
        in_2[0]--;
    }
    if(out_2[m] == depth){
        out_2[m] = 0;
        out_2[0]--;
    }
    node<T1, T2> *pNode = &target->nodelist[n];
    edge<T1, T2> *plist = pNode->prevList;
    while(plist){
        int curIdx = plist->fromVex;
        if(in_1[curIdx] == depth){
            in_1[curIdx] = 0;
            in_1[0]--;
        }
        plist = plist->fromLink;
    }
    plist = pNode->succList;
    while(plist){
        int curIdx = plist->toVex;
        if(out_1[curIdx] == depth){
            out_1[curIdx] = 0;
            out_1[0]--;
        }
        plist = plist->toLink;
    }

    pNode = &pattern->nodelist[m];
    plist = pNode->prevList;
    while(plist){
        int curIdx = plist->fromVex;
        if(in_2[curIdx] == depth){
            in_2[curIdx] = 0;
            in_2[0]--;
        }
        plist = plist->fromLink;
    }
    plist = pNode->succList;
    while(plist){
        int curIdx = plist->toVex;
        if(out_2[curIdx] == depth){
            out_2[curIdx] = 0;
            out_2[0]--;
        }
        plist = plist->toLink;
    }
}

template<class T1, class T2>
bool feasibility(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m){
    return syn(target, pattern, n, m) && sema(target, pattern, n, m);
}

template<class T1, class T2>
bool syn(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m){
    int succ_in_1 =0, succ_in_2=0, pred_in_1=0, pred_in_2=0;
    int succ_out_1=0, succ_out_2=0, pred_out_1=0, pred_out_2=0;
    int succ_other_1=0, succ_other_2=0, pred_other_1=0, pred_other_2=0;
    //R_{pred} test
    edge<T1, T2> *p = target->nodelist[n].prevList;
    while(p){
        int curIdx = p->fromVex;
        if(ISHERE(core_1, curIdx)){
            int mm = core_1[curIdx];
            if(!pattern->checkPrev(m, mm).isTrue){
                return false;
            }
        }
        if(IST(in_1, core_1, curIdx)) pred_in_1++;
        if(IST(out_1, core_1, curIdx)) pred_out_1++;
        if(!ISHERE(in_1, curIdx) && !ISHERE(out_1, curIdx)) pred_other_1++;
        p = p->fromLink;
    }
    p = pattern->nodelist[m].prevList;
    while(p){
        int curIdx = p->fromVex;
        if(ISHERE(core_2, curIdx)){
            int nn = core_2[curIdx];
            if(!target->checkPrev(n, nn).isTrue){
                return false;
            }
        }
        if(IST(in_2, core_2, curIdx)) pred_in_2++;
        if(IST(out_2, core_2, curIdx)) pred_out_2++;
        if(!ISHERE(in_2, curIdx) && !ISHERE(out_2, curIdx)) pred_other_2++;
        p = p->fromLink;
    }
    //R_{succ} test
    p = target->nodelist[n].succList;
    while(p){
        int curIdx = p->toVex;
        if(ISHERE(core_1, curIdx)){
            int mm = core_1[curIdx];
            if(!pattern->checkSucc(m,mm).isTrue){
                return false;
            }
        }
        if(IST(in_1, core_1, curIdx)) succ_in_1++;
        if(IST(out_1, core_1, curIdx)) succ_out_1++;
        if(!ISHERE(in_1, curIdx) && !ISHERE(out_1, curIdx)) succ_other_1++;
        p = p->toLink;
    }
    p = pattern->nodelist[m].succList;
    while(p){
        int curIdx = p->toVex;
        if(ISHERE(core_2, curIdx)){
            int nn = core_2[curIdx];
            if(!target->checkSucc(n,nn).isTrue){
                return false;
            }
        }
        if(IST(in_2, core_2, curIdx)) succ_in_2++;
        if(IST(out_2, core_2, curIdx)) succ_out_2++;
        if(!ISHERE(in_2, curIdx) && !ISHERE(out_2, curIdx)) succ_other_2++;
        p = p->toLink;
    }
    // R_{in} test
    if(pred_in_1 < pred_in_2 || succ_in_1 < succ_in_2){
        return false;
    }
    // R_{out} test
    if(pred_out_1 < pred_out_2 || succ_out_1 < succ_out_2){
        return false;
    }
    // R_{new} test
    if(succ_other_1 < succ_other_2 || pred_other_1 < pred_other_2){
        return false;
    }
    return true;
}

/*
 *  Attributes matching
 */

template <class T>
bool equal(T first, T second){
    return first == second;
}

template<class T>
bool compare(T first, T second, bool (*cmp)(T, T)){
    return cmp(first, second);
}


template<class T1, class T2>
bool sema(graph<T1, T2>* target, graph<T1, T2>* pattern, int n, int m){
    if(!attributeMode){
        return true;
    }
    /* matching nodeVal */
    if(!compare(target->nodelist[n].nodeVal, pattern->nodelist[m].nodeVal, equal)){
        return false;
    }
    /* matching edgeVal */
    for(int mm=1;mm<=patternNum;mm++){
        if(ISHERE(core_2, mm)){
            RET<T2> succRetM = pattern->checkSucc(m, mm);
            if(succRetM.isTrue){
                RET<T2> succRetN = target->checkSucc(n, core_2[mm]);
                if(!succRetN.isTrue){
                    cerr << "This is impossible!" << endl;
                    return false;
                }
                if(!compare(succRetN.val, succRetM.val, equal)){
                    return false;
                }
            }
            RET<T2> prevRetM = pattern->checkPrev(m, mm);
            if(prevRetM.isTrue){
                RET<T2> prevRetN = target->checkPrev(n, core_2[mm]);
                if(!prevRetN.isTrue){
                    cerr << "This is impossible!" << endl;
                    return false;
                }
                if(!compare(prevRetN.val, prevRetM.val, equal)){
                    return false;
                }
            }
        }
    }
    return true;
}


void output(){
    cout << "match " << matchNum << ":target -- pattern" << endl;
    for(int i=1;i<=patternNum;i++){
        cout << core_2[i] << " <--> " << i << endl;
    }
}