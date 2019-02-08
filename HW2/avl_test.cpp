//
// Created by Yakir on 06/01/2017.
//

#include "RankTree.h.h"

int main() {
    RankTree<int,int>* tree = new RankTree<int,int>;
    //test1
    std::cout << "TEST 1" << std::endl;
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->insert(20,20);
    tree->insert(4,4);
    tree->insert(15,15);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(15);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(20);
    tree->remove(4);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());

    //test2
    std::cout << "TEST 2" << std::endl;
    tree->insert(20,20);
    tree->insert(4,4);
    tree->insert(26,26);
    tree->insert(3,3);
    tree->insert(9,9);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->insert(15,15);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(20);
    tree->remove(15);
    tree->remove(26);
    tree->remove(4);
    tree->remove(9);
    tree->remove(3);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());

    //test3
    std::cout << "TEST 3" << std::endl;
    tree->insert(20,20);
    tree->insert(4,4);
    tree->insert(26,26);
    tree->insert(3,3);
    tree->insert(9,9);
    tree->insert(21,21);
    tree->insert(30,30);
    tree->insert(2,2);
    tree->insert(7,7);
    tree->insert(11,11);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->insert(15,15);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(20);
    tree->remove(4);
    tree->remove(26);
    tree->remove(3);
    tree->remove(7);
    tree->remove(11);
    tree->remove(21);
    tree->remove(30);
    tree->remove(9);
    tree->remove(15);
    tree->remove(2);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());

    //test4
    std::cout << "TEST 4" << std::endl;
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->insert(20,20);
    tree->insert(4,4);
    tree->insert(8,8);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(8);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(20);
    tree->remove(4);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());

    //test5
    std::cout << "TEST 5" << std::endl;
    tree->insert(20,20);
    tree->insert(4,4);
    tree->insert(26,26);
    tree->insert(3,3);
    tree->insert(9,9);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->insert(8,8);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(20);
    tree->remove(26);
    tree->remove(3);
    tree->remove(8);
    tree->remove(4);
    tree->remove(9);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());

    //test6
    std::cout << "TEST 6" << std::endl;
    tree->insert(20,20);
    tree->insert(4,4);
    tree->insert(26,26);
    tree->insert(3,3);
    tree->insert(9,9);
    tree->insert(21,21);
    tree->insert(30,30);
    tree->insert(2,2);
    tree->insert(7,7);
    tree->insert(11,11);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->insert(8,8);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(11);
    tree->remove(20);
    tree->remove(21);
    tree->remove(30);
    tree->remove(3);
    tree->remove(4);
    tree->remove(2);
    tree->remove(26);
    tree->remove(7);
    tree->remove(9);
    tree->remove(8);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());

    //test7
    std::cout << "TEST 7" << std::endl;
    tree->insert(2,2);
    tree->insert(1,1);
    tree->insert(4,4);
    tree->insert(3,3);
    tree->insert(5,5);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(1);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(2);
    tree->remove(3);
    tree->remove(4);
    tree->remove(5);

    //test8
    std::cout << "TEST 8" << std::endl;
    tree->insert(6,6);
    tree->insert(2,2);
    tree->insert(9,9);
    tree->insert(1,1);
    tree->insert(4,4);
    tree->insert(8,8);
    tree->insert(12,12);
    tree->insert(3,3);
    tree->insert(5,5);
    tree->insert(7,7);
    tree->insert(10,10);
    tree->insert(13,13);
    tree->insert(15,15);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(1);
    tree->remove(2);
    tree->remove(3);
    tree->remove(4);
    tree->remove(5);
    tree->remove(6);
    tree->remove(7);
    tree->remove(8);
    tree->remove(9);
    tree->remove(10);
    tree->remove(12);
    tree->remove(13);
    tree->remove(15);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());

    //test9
    std::cout << "TEST 9" << std::endl;
    tree->insert(5,5);
    tree->insert(2,2);
    tree->insert(8,8);
    tree->insert(1,1);
    tree->insert(3,3);
    tree->insert(7,7);
    tree->insert(10,10);
    tree->insert(4,4);
    tree->insert(6,6);
    tree->insert(9,9);
    tree->insert(12,12);
    tree->insert(13,13);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    tree->remove(1);
    tree->remove(2);
    tree->remove(3);
    tree->remove(4);
    tree->remove(5);
    tree->remove(6);
    tree->remove(7);
    tree->remove(8);
    tree->remove(9);
    tree->remove(10);
    tree->remove(12);
    tree->remove(13);
    std::cout << "current tree:" << std::endl;
    tree->print(tree->getRoot());
    return 0;
}