//
// Created by 汪逸阳 on 2022/3/30.
//

// 十字链表
#include <iostream>
#include <unordered_set>

using namespace std;

template<class T1, class T2>
class nodeAndEdge;
template<class T1, class T2>
class graph;
enum edgeType{
    PREV = 0,
    SUCC
};

template<class T1, class T2>
class node{
public:
    int idx;
    T1 nodeVal;
    nodeAndEdge<T1, T2> *succList, *prevList;
    graph<T1, T2> *parentGraph;

    node(T1 nodeVal_= NULL):nodeVal(nodeVal_),succList(nullptr),prevList(nullptr){}
    void deleteList(nodeAndEdge<T1, T2> *p){
        if(!p) return;
        if(p->next)
            deleteList(p->next);
        delete p;
    };
    ~node(){
        deleteList(succList);
        deleteList(prevList);
    }
    bool checkSucc(int checkIdx){
        nodeAndEdge<T1,T2> *p = succList;
        while(p){
            if(checkIdx == p->curNode->idx){
                return true;
            }
            p = p->next;
        }
        return false;
    }
    bool checkPrev(int checkIdx){
        nodeAndEdge<T1,T2> *p = prevList;
        while(p){
            if(checkIdx == p->curNode->idx){
                return true;
            }
            p = p->next;
        }
        return false;
    }
    void insert(int newIdx, edgeType type, T2 edgeVal=NULL){
        nodeAndEdge<T1, T2> *newOne = new nodeAndEdge<T1,T2>;
        newOne->curNode = &parentGraph->nodelist[newIdx];
        newOne->type = type;
        newOne->edgeVal = edgeVal;
        if(type == SUCC){
            newOne->next = succList;
            succList = newOne;
        }
        else if(type == PREV){
            newOne->next = prevList;
            prevList = newOne;
        }
    }
};

template<class T1, class T2>
class nodeAndEdge{
public:
    node<T1, T2> *curNode;
    T2 edgeVal;
    edgeType type;
    nodeAndEdge *next;
};

template<class T1, class T2>
class graph{
public:
    int nodeNum;
    node<T1, T2> *nodelist;
    graph(int nodeNum_=0):nodeNum(nodeNum_){
        if(nodeNum_ == 0){
            nodelist = nullptr;
        }
        else{
            nodelist = new node<T1, T2>[nodeNum_+1];
            for(int i=1;i<=nodeNum_;i++){
                nodelist[i].idx = i;
                nodelist[i].parentGraph = this;
            }
        }
    }
    ~graph(){
        if(nodelist){
            delete [] nodelist;
        }
    }
    void showAll(){
        for(int i=1;i<=nodeNum;i++){
            cout << i << endl;
            nodeAndEdge<T1, T2> *p = nodelist[i].succList;
            cout << "succ: ";
            while(p){
                cout << p->curNode->idx << " ";
                p =  p->next;
            }
            cout << endl;
            p = nodelist[i].prevList;
            cout << "prev: ";
            while(p){
                cout << p->curNode->idx << " ";
                p = p->next;
            }
            cout << endl;
        }
    }
};