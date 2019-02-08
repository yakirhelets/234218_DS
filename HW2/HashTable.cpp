//
// Created by Yakir on 08/06/2017.
//

#include "HashTable.h"
#include <iostream>

static int resizeCount=1;


HashTable::HashTable() {
    arrSize=(SIZE*resizeCount)-1;
    numOfVars=0;
    arr = new Magi*[arrSize];
    isTakenForSearch = new bool[arrSize];
    for (int i=0 ; i<arrSize ; i++) {
        arr[i]=NULL;
        isTakenForSearch[i]=false;
    }
}

HashTable::~HashTable() {
    for (int i=0 ; i<arrSize ; i++) {
        delete arr[i];
    }
    delete[] arr;
    delete[] isTakenForSearch;
}

void HashTable::insert(Magi* magi) {
    int i = magi->getMagiId();
    int index = i%arrSize;
    int r = 1+(i%(arrSize-C));
    while (arr[index] != NULL) {
        if (arr[index]->getMagiId()==i) {
            throw KeyAlreadyExists();
        }
        index=(index+r)%arrSize;
    }
    if (arr[index]!=NULL) {
        throw KeyAlreadyExists();
    }
    arr[index] = magi;
    numOfVars++;
    if (arrSize==numOfVars) {
        this->expand();
    }
}

void HashTable::remove(int id) {
    int i = id;
    int index = i%arrSize;
    int r = 1+(i%(arrSize-C));
    while ((isTakenForSearch[index]) || (arr[index] != NULL && arr[index]->getMagiId()!=id)) {
        index=(index+r)%arrSize;
    }
    if (arr[index]==NULL) {
        throw KeyDoesNotExist();
    } else {
        delete arr[index];
        arr[index]=NULL;
        isTakenForSearch[index]=true;
    }
    if ((arrSize/4)==numOfVars) {
        this->shrink();
    }
}

Magi* HashTable::get(int id) {
    int i = id;
    int index = i%arrSize;
    int r = 1+(i%(arrSize-C));
    while ((isTakenForSearch[index]) || (arr[index] != NULL && arr[index]->getMagiId()!=id)) {
        index=(index+r)%arrSize;
    }
    if (arr[index]==NULL) {
        throw KeyDoesNotExist();
    } else {
        return arr[index];
    }
}

void HashTable::expand() {
    resizeCount*=2;
    int oldSize=arrSize;
    arrSize=(SIZE*resizeCount)-1;
    numOfVars=0;
    Magi** oldArr = arr;
    arr = new Magi*[arrSize];
    bool* oldIsTaken = isTakenForSearch;
    isTakenForSearch = new bool[arrSize];
    for (int i=0 ; i<arrSize ; i++) {
        arr[i]=NULL;
        isTakenForSearch[i]=false;
    }
    for (int i=0 ; i<oldSize ; i++) {
        if (oldArr[i]) {
            insert(oldArr[i]);
        }
    }
    delete oldArr;
    delete oldIsTaken;
}

void HashTable::shrink() {
    resizeCount/=2;
    int oldSize=arrSize;
    arrSize=(SIZE*resizeCount)-1;
    numOfVars=0;
    Magi** oldArr = arr;
    arr = new Magi*[arrSize];
    bool* oldIsTaken = isTakenForSearch;
    isTakenForSearch = new bool[arrSize];
    for (int i=0 ; i<arrSize ; i++) {
        arr[i]=NULL;
        isTakenForSearch[i]=false;
    }
    for (int i=0 ; i<oldSize ; i++) {
        if (oldArr[i]) {
            insert(oldArr[i]);
        }
    }
    delete oldArr;
    delete oldIsTaken;
}