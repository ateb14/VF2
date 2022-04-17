#include <iostream>

using namespace std;

template<class T>
struct RET{
    T val;
    bool isTrue;
};

//#define ADJACENCY_LIST
#ifdef ADJACENCY_LIST

template<class T1, class T2>
class nodeAndEdge;
template<class T1, class T2>
class graph;

template<class T1, class T2>
class node{
public:
    int idx;
    T1 nodeVal;
    nodeAndEdge<T1, T2> *succList, *prevList;

    node(T1 nodeVal_= 0):nodeVal(nodeVal_),succList(nullptr),prevList(nullptr){}
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
};

template<class T1, class T2>
class nodeAndEdge{
public:
   unsigned nodeIdx;
    T2 edgeVal;
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
            }
        }
    }
    ~graph(){
        delete [] nodelist;
    }
    void insert(int from, int to,T2 edgeVal=0){
        auto *newOne = new nodeAndEdge<T1,T2>;
        /* SUCC */
        newOne->nodeIdx = to;
        newOne->edgeVal = edgeVal;
        newOne->next = nodelist[from].succList;
        nodelist[from].succList = newOne;
        /* PREV */
        newOne = new nodeAndEdge<T1, T2>;
        newOne->nodeIdx = from;
        newOne->edgeVal = edgeVal;
        newOne->next = nodelist[to].prevList;
        nodelist[to].prevList = newOne;
    }
    void showAll(){
        for(int i=1;i<=nodeNum;i++){
            cout << i << endl;
            nodeAndEdge<T1, T2> *p = nodelist[i].succList;
            cout << "succ: ";
            while(p){
                cout << p->nodeIdx << " ";
                p =  p->next;
            }
            cout << endl;
            p = nodelist[i].prevList;
            cout << "prev: ";
            while(p){
                cout << p->nodeIdx << " ";
                p = p->next;
            }
            cout << endl;
        }
    }
    RET<T2> checkSucc(int targetIdx, int checkIdx){
        nodeAndEdge<T1,T2> *p = nodelist[targetIdx].succList;
        while(p){
            if(checkIdx == p->nodeIdx){
                return {p->edgeVal, true};
            }
            p = p->next;
        }
        return {0, false};
    }
    RET<T2> checkPrev(int targetIdx, int checkIdx){
        nodeAndEdge<T1,T2> *p = nodelist[targetIdx].prevList;
        while(p){
            if(checkIdx == p->nodeIdx){
                return {p->edgeVal, true};
            }
            p = p->next;
        }
        return {0, false};
    }
};

#endif

#define ORTHOGONAL_LIST
#ifdef ORTHOGONAL_LIST

template <class T1, class T2>
class vertex;
template <class T1, class T2>
class edge;

template <class T1, class T2>
class node{
public:
    edge<T1, T2> *prevList, *succList;
    T1 nodeVal;
};

template<class T1, class T2>
class edge{
public:
    int fromVex, toVex;
    T2 edgeVal;
    edge<T1, T2> *fromLink, *toLink;
    edge(int from, int to, T2 val):fromVex(from), toVex(to),edgeVal(val){}
};

template<class T1, class T2>
class graph{
public:
    int nodeNum;
    node<T1, T2> *nodelist;
    graph(int nodeNum_=0):nodeNum(nodeNum_){
        if(nodeNum == 0){
            nodelist = nullptr;
        }
        else{
            nodelist = new node<T1, T2>[nodeNum_+1];
        }
    }
    void deleteEdge(edge<T1, T2> *p){
        if(!p) return;
        if(p->toLink)
            deleteEdge(p->toLink);
        delete p;
    };
    ~graph(){
        if(nodeNum == 0) return;
        for(int i=1;i<=nodeNum;i++){
            deleteEdge(nodelist[i].succList);
        }
        delete [] nodelist;
    }
    void insert(int from, int to, T2 edgeVal=0){
        auto *newEdge = new edge<T1,T2>(from, to, edgeVal);
        newEdge->toLink = nodelist[from].succList;
        newEdge->fromLink = nodelist[to].prevList;
        nodelist[from].succList = newEdge;
        nodelist[to].prevList = newEdge;
    }
    RET<T2> checkSucc(int targetIdx, int checkIdx){
        edge<T1,T2> *p = nodelist[targetIdx].succList;
        while(p){
            if(checkIdx == p->toVex){
                return {p->edgeVal, true};
            }
            p = p->toLink;
        }
        return {0, false};
    }
    RET<T2> checkPrev(int targetIdx, int checkIdx){
        edge<T1,T2> *p = nodelist[targetIdx].prevList;
        while(p){
            if(checkIdx == p->fromVex){
                return {p->edgeVal, true};
            }
            p = p->fromLink;
        }
        return {0, false};
    }
};

#endif