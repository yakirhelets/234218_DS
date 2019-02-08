//
// Created by Yakir on 06/06/2017.
//

#ifndef WET2SPRING17_GENERICUNIONFIND_H
#define WET2SPRING17_GENERICUNIONFIND_H

#include <iostream>
#define NONE -1
#define GROUP_SIZE 0
#define FATHERS_INDEX 1

template <class Data>
class UnionFind {
    Data* dataArr;
    int** array; //2xN matrix
    int size;
public:
    UnionFind(int n, Data* dataArr) {
        /* row i - group i
         *
         * col 0 - group size
         * col 1 - father's index
         */
        size = n;
        array = new int*[n];
        this->dataArr = dataArr;
        for(int i = 0; i < size; ++i) {
            array[i] = new int[2];
        }
        for (int i=0 ; i<size ; ++i) {
            array[i][GROUP_SIZE] = 1;
            array[i][FATHERS_INDEX] = NONE;
        }
    }

    ~UnionFind() {
        for(int i = 0; i < size; ++i) {
            delete[] array[i];
        }
        delete[] array;
        for(int i = 0; i < size; ++i) {
            delete dataArr[i];
        }
        delete[] dataArr;
    }

    bool areBelongToSameGroup(int n1, int n2) {
        if (n1<0 || n2<0 || n1>=size || n2>=size) {
            throw InvalidInput();
        }
        return ( find(n1)==find(n2) );
    }

    bool isFirstGroupBigger(int g1, int g2) {
        if (g1<0 || g1>=size || g2<0 || g2>=size) {
            throw Failure();
        }
        return ( array[getRoot(g1)][GROUP_SIZE]>=array[getRoot(g2)][GROUP_SIZE] );
    }

    Data& unite(int g1, int g2) {
        if (g1<0 || g1>=size || g2<0 || g2>=size) {
            throw InvalidInput();
        }
        if (size<=1 || (g1==g2) || areBelongToSameGroup(g1,g2) || (getRoot(g1)==NONE && getRoot(g2)==NONE) ) {
            throw Failure();
        }
        int newGroupSize=(array[find(g1)][GROUP_SIZE])+(array[find(g2)][GROUP_SIZE]);
        array[find(g1)][GROUP_SIZE]=newGroupSize;
        array[find(g2)][GROUP_SIZE]=newGroupSize;
        if( isFirstGroupBigger(g1, g2)) {
            array[find(g2)][FATHERS_INDEX]=find(g1);
            return dataArr[find(g1)];
        } else {
            array[find(g1)][FATHERS_INDEX]=find(g2);
            return dataArr[find(g2)];
        }
    }

    int getSize(int group) {
        int root = find(group);
        return array[root][GROUP_SIZE];
    }
    void shrinkRoutes(int start, int newFather) {
        if (start<0 || start>=size || newFather<0 || newFather>=size) {
            throw Failure();
        }
        int curr = start;
        int next;
        while (curr!=newFather) {
            next = array[curr][FATHERS_INDEX];
            array[curr][FATHERS_INDEX]=newFather;
            curr = next;
        }
    }

    int getRoot(int i) const {
        int father = i;
        int cur = 0;
        do {
        	cur = father;
        	father=array[cur][FATHERS_INDEX];
        } while(father != NONE);
        return cur;
    }

    int find(int i) {
        if (i<0 || i>=size) {
            throw InvalidInput();
        }
        int curr = i;
        int last = getRoot(curr);
        shrinkRoutes(i, last);
        return last;
    }

    Data& dataFind(int i) {
        return dataArr[find(i)];
    }

    /*
     * Error types
     */
    class Failure {};
    class InvalidInput {};
};

#endif //WET2SPRING17_GENERICUNIONFIND_H
