//
// Created by Yakir on 08/06/2017.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#define SIZE 6
#define C 3

class HashTable {
    int arrSize;
    int numOfVars;
    Magi** arr;
    bool* isTakenForSearch;
public:
    HashTable();
    ~HashTable();
    void insert(Magi* magi);
    void remove(int id);
    Magi* get(int id);
    void expand();
    void shrink();

    class KeyAlreadyExists {};
    class KeyDoesNotExist {};
};


#endif //WET2_HASHTABLE_H
