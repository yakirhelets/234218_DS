//
// Created by Yakir on 06/06/2017.
//

#ifndef WET2SPRING17_GENERICHASHTABLE_H
#define WET2SPRING17_GENERICHASHTABLE_H

#include <iostream>
#include "AVL.h"

#define SIZE 6
#define C 3

template <class Data>
class HashTable {
public:
private:
    static int resizeCount;
    int arrSize;
    int numOfVars;
    AVL<Data,int>** arr;
public:
    HashTable() {
        arrSize=SIZE*resizeCount;
        numOfVars=0;
        arr = new AVL*[arrSize];
        for (int i=0 ; i<arrSize ; i++) {
            arr[i]= new AVL<Data,int>();
        }
    }

    ~HashTable() {
        for (int i=0 ; i<arrSize ; i++) {
            delete arr[i];
        }
        delete[] arr;
    }
    void insert(const Data& data, int key) {
        int index = key%arrSize;
        bool wasEmpty = arr[index]->getRoot() == NULL;
        try {
            arr[index]->insert(data,key);
        } catch (AVL<Data,int>::KeyAlreadyExists& error){
            throw KeyAlreadyExists();
        }
        if (wasEmpty) {
            numOfVars++;
        }
        if (arrSize==numOfVars) {
            this->expand();
        }
    }

    void remove(int key) {
        int index = key%arrSize;
        bool wasEmpty = arr[index]->getRoot() == NULL;
        if (wasEmpty) {
            throw KeyDoesNotExist();
        }
        try {
            arr[index]->remove(key);
        } catch (AVL<Data,int>::KeyDoesNotExist& error){
            throw KeyDoesNotExist();
        }
        if (!wasEmpty && !arr[index]->getRoot()) {
            numOfVars--;
        }
        if ((arrSize/4)==numOfVars) {
            this->shrink();
        }
    }
    const bool doesExist(int key) const {
        int index = key%arrSize;
        try {
            arr[index]->find(key);
        } catch (AVL<Data,int>::KeyDoesNotExist& error){
            return false;
        }
        return true;
    }

    const Data& get(int key) const {
        int index = key%arrSize;
        try {
            arr[index]->find(key);
        } catch (AVL<Data,int>::KeyDoesNotExist& error){
            throw KeyDoesNotExist();
        }
        return arr[index]->find(key);
    }

    void expand() {
        resizeCount*=2;
        int oldSize=arrSize;
        arrSize=(SIZE*resizeCount);
        numOfVars=0;
        AVL<Data,int>** oldArr = arr;
        arr = new AVL<Data,int>*[arrSize];
        for (int i=0 ; i<arrSize ; i++) {
            arr[i]= new AVL<Data,int>();
        }
        for (int i=0 ; i<oldSize ; i++) {
            if (oldArr[i]->getRoot()) {
                insert(oldArr[i]->getData(),oldArr[i]->getKey());
                delete oldArr[i];
            }
        }
        delete[] oldArr;
        delete[] oldIsTaken;
    }

    void shrink() {
        if (resizeCount == 1) {
            return;
        }
        resizeCount /= 2;
        int oldSize=arrSize;
        arrSize=(SIZE*resizeCount)-1;
        numOfVars=0;
        HashElement** oldArr = arr;
        arr = new HashElement*[arrSize];
        bool* oldIsTaken = isTakenForSearch;
        isTakenForSearch = new bool[arrSize];
        for (int i=0 ; i<arrSize ; i++) {
            arr[i]=NULL;
            isTakenForSearch[i]=false;
        }
        for (int i=0 ; i<oldSize ; i++) {
            if (oldArr[i]) {
                insert(oldArr[i]->getData(), oldArr[i]->getKey());
                delete oldArr[i];
            }
        }
        delete[] oldArr;
        delete[] oldIsTaken;
    }
    template<class Function>
    void forEach(Function func) {
        for (int i=0 ; i<arrSize ; i++) {
            if (arr[i]) {
                func(this->arr[i]->getData());
            }
        }
    }
    class KeyAlreadyExists {};
    class KeyDoesNotExist {};
};
template <class Data>
int HashTable<Data>::resizeCount=1;

//template <class Data>
//HashTable<Data>::HashElement::~HashElement() {
//    delete data;
//}
#endif //WET2SPRING17_GENERICHASHTABLE_H
