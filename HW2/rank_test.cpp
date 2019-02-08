//
// Created by Yakir on 09/06/2017.
//

#include "RankTree.h"
#include "Magi.h"

int main() {
    RankTree* tree = new RankTree;
    Magi* m1 = new Magi(1,2);
    Magi* m2 = new Magi(2,4);
    Magi* m3 = new Magi(3,6);
    Magi* m4 = new Magi(4,8);
    Magi* m5 = new Magi(5,10);
    Magi* m6 = new Magi(6,12);
    Magi* m7 = new Magi(7,14);
    Magi* m8 = new Magi(8,16);
    Magi* m9 = new Magi(9,18);

    std::cout << m1->getSeniority() << std::endl;
    std::cout << m8->getSeniority() << std::endl;
    std::cout << m7->getSeniority() << std::endl;

    std::cout << "tree is:" << std::endl;
    tree->print(tree->getRoot());

    tree->insert(m1,m1->getMagiLevel());

    std::cout << "tree is:" << std::endl;
    tree->print(tree->getRoot());

    tree->remove(m1->getMagiLevel());

    std::cout << "tree is:" << std::endl;
    tree->print(tree->getRoot());

    tree->insert(m1,m1->getMagiLevel());
    tree->insert(m2,m2->getMagiLevel());
    tree->insert(m3,m3->getMagiLevel());
    tree->insert(m4,m4->getMagiLevel());
    tree->insert(m5,m5->getMagiLevel());
    tree->insert(m9,m9->getMagiLevel());
    tree->insert(m8,m8->getMagiLevel());
    tree->insert(m6,m6->getMagiLevel());
    tree->insert(m7,m7->getMagiLevel());

    std::cout << "tree is:" << std::endl;
    tree->print(tree->getRoot());

    tree->remove(m4->getMagiLevel());
    tree->remove(m7->getMagiLevel());
    tree->remove(m3->getMagiLevel());
    tree->remove(m1->getMagiLevel());
    tree->insert(m3,m3->getMagiLevel());
    tree->insert(m1,m1->getMagiLevel());
    tree->insert(m4,m4->getMagiLevel());


    std::cout << "tree is:" << std::endl;
    tree->print(tree->getRoot());
    return 0;
}