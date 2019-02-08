//
// Created by Yakir on 07/06/2017.
//

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

#include <iostream>

template <class Data>
class UnionFind {
//    Data* dataArr;
    int** array;
    int size;
public:
    UnionFind(int n, int* arr);
    ~UnionFind();
    bool areBelongToSameGroup(int n1, int n2);
    int getRoot(int i) const;
    bool isFirstGroupBigger(int g1, int g2);
    int unite(int g1, int g2);
    int getSize(int group);
    void shrinkRoutes(int start, int newFather);
    int find(int x);

    void displayArr() {
        for (int i=0 ; i<size ; i++) {
            for (int j=0 ; j<3 ; j++) {
                std::cout << array[i][j] << " | ";
            }
            std::cout << std::endl << "-----------" <<std::endl;
        }
    }
    /*
     * Error types
     */
    class Failure {};
    class AllocationError {};
    class InvalidInput {};
};


#endif //WET2_UNIONFIND_H
