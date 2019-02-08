//
// Created by Yakir on 07/06/2017.
//

#include "UnionFind.h"
#define NONE -1
#define GROUP_SIZE 0
#define FATHERS_INDEX 1

//template <class Data>
UnionFind::UnionFind(int n, int* arr) {
    /* row i - group i
     *
     * col 0 - group size
     * col 1 - father's index
     */
    size = n;
    array = new int*[n];
    for(int i = 0; i < size; ++i) {
        array[i] = new int[2];
    }
    for (int i=0 ; i<size ; ++i) {
        array[i][GROUP_SIZE] = 1;
        array[i][FATHERS_INDEX] = NONE;
//        dataArr[i] = Data(i);
    }
}

UnionFind::~UnionFind() {
    for(int i = 0; i < size; ++i) {
        delete[] array[i];
    }
    delete[] array;

}

bool UnionFind::areBelongToSameGroup(int n1, int n2) {
    if (n1<0 || n2<0 || n1>=size || n2>=size) {
        throw InvalidInput();
    }
    return ( find(n1)==find(n2) );
}

bool UnionFind::isFirstGroupBigger(int g1, int g2) {
    if (g1<0 || g1>=size || g2<0 || g2>=size) {
        throw Failure();
    }
    return ( array[getRoot(g1)][GROUP_SIZE]>=array[getRoot(g2)][GROUP_SIZE] );
}

int UnionFind::unite(int g1, int g2) {
    if (g1<0 || g1>=size || g2<0 || g2>=size) {
        throw InvalidInput();
    }
    if (size<=1 || (g1==g2) || (getRoot(g1)==getRoot(g2) && getRoot(g1)!=NONE && getRoot(g2)!=NONE) ) {
        throw Failure();
    }
    if (array[getRoot(g1)][MAGIS_COUNT]>0 || array[getRoot(g2)][MAGIS_COUNT]>0) {
        throw Failure();
    }
    int newNumberOfCreatures=(array[find(g1)][GROUP_SIZE])+(array[find(g2)][GROUP_SIZE]);
    int newRiskLevel=(array[find(g1)][RISK_LEVEL])+(array[find(g2)][RISK_LEVEL]);
    array[find(g1)][GROUP_SIZE]=newNumberOfCreatures;
    array[find(g1)][RISK_LEVEL]=newRiskLevel;
    array[find(g2)][GROUP_SIZE]=newNumberOfCreatures;
    array[find(g2)][RISK_LEVEL]=newRiskLevel;
    if( isFirstGroupBigger(g1, g2)) {
        array[find(g2)][FATHERS_INDEX]=find(g1);
//        displayArr();
        return g1;
    } else {
        array[find(g1)][FATHERS_INDEX]=find(g2);
//        displayArr();
        return g2;
    }
}
int UnionFind::getRiskLevel(int group) {
    return array[group][RISK_LEVEL];
}

int UnionFind::getSize(int group) {
    int root = find(group);
    return array[root][GROUP_SIZE];
}

int UnionFind::getMagisCount(int group) {
    return array[group][MAGIS_COUNT];
}

void UnionFind::setMagisCount(int group, int count) {
    array[group][MAGIS_COUNT]=count;
}

void UnionFind::shrinkRoutes(int start, int newFather) {
    if (start<0 || start>=size || newFather<0 || newFather>=size) {
        throw Failure();
    }
    int curr = start;
    int next;
    while (curr!=newFather) {
        next = array[curr][FATHERS_INDEX];
        array[curr][FATHERS_INDEX]=newFather;
        array[curr][MAGIS_COUNT]=array[newFather][MAGIS_COUNT];
        array[curr][RISK_LEVEL]=array[newFather][RISK_LEVEL];
        curr = next;
    }
}

int UnionFind::getRoot(int i) const {
    if (array[i][FATHERS_INDEX]==NONE) {
        return i;
    }
    int father=array[i][FATHERS_INDEX];
    while (array[father][FATHERS_INDEX]!=NONE) {
        father=array[father][FATHERS_INDEX];
    }
    return father;
}

int UnionFind::find(int i) {
    if (i<0 || i>=size) {
        throw InvalidInput();
    }
    int curr = i;
    int last = getRoot(curr);
    shrinkRoutes(i, last);
    return last;
}