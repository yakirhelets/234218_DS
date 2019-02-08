//
// Created by Yakir on 09/06/2017.
//

#include "Magi.h"
#include "HashTable.h"
int main() {
    HashTable* table = new HashTable();

    Magi* m1 = new Magi(1,2);
    Magi* m2 = new Magi(2,4);
    Magi* m3 = new Magi(50,6);
    Magi* m4 = new Magi(4,8);
    Magi* m5 = new Magi(5,10);
    Magi* m6 = new Magi(60,12);
    Magi* m7 = new Magi(7,14);
    Magi* m8 = new Magi(283,16);
    Magi* m9 = new Magi(9,18);

    table->insert(m1);
//    table->insert(m1);
    table->insert(m2);
    table->insert(m3);
    table->insert(m4);
    table->insert(m5);
    table->insert(m6);
    table->insert(m7);
    table->insert(m8);
    table->insert(m9);
    table->get(m1->getMagiId());
    table->get(m2->getMagiId());
    table->get(m3->getMagiId());
    table->get(m4->getMagiId());
    table->get(m5->getMagiId());
    table->get(m6->getMagiId());
    table->get(m7->getMagiId());
    table->get(m8->getMagiId());
    table->get(m9->getMagiId());
    table->remove(m1->getMagiId());
    table->remove(1);
    return 0;
}