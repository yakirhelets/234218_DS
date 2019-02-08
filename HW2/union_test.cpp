//
// Created by Yakir on 08/06/2017.
//

#include "UnionFind.h"
#include <iostream>

int main() {
    int n=7;
    int arr[n]= {1,10,20,30,40,50,60};

    //makeSetTest
    UnionFind uni = UnionFind(n, arr);
    uni.displayArr();
    std::cout << "************" << std::endl;
    //unionTest
    uni.unite(1,5);
    uni.displayArr();
    std::cout << "************" << std::endl;
    uni.unite(6,3);
    uni.displayArr();
    std::cout << "************" << std::endl;
    uni.unite(5,6);
    uni.displayArr();
    std::cout << "************" << std::endl;
    //findTest

    return 0;
}
