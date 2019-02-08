//
// Created by Yakir on 06/06/2017.
//

#ifndef WET2SPRING17_GENERICHASHTABLE_H
#define WET2SPRING17_GENERICHASHTABLE_H

#include <iostream>

#define SIZE 6
#define C 3

template <class Data>
class HashTable {
public:
    class HashElement {
        Data data;
        int key;
    public:
        HashElement(const Data& data, int key) : data(data), key(key) {};
        const Data& getData() const {
            return data;
        }
        Data& getData() {
            return data;
        }
        void setData(Data& data) {
            this->data = data;
        }
        const int& getKey() const {
            return key;
        }
        int& getKey() {
            return key;
        }
        void setKey(int key) {
            this->key = key;
        }
    };
private:
    static int resizeCount;
    int arrSize;
    int numOfVars;
    HashElement** arr;
    bool* isTakenForSearch;
public:
    HashTable() {
        arrSize=resizeCount;
        numOfVars=0;
        arr = new HashElement*[arrSize];
        isTakenForSearch = new bool[arrSize];
        for (int i=0 ; i<arrSize ; i++) {
            arr[i]=NULL;
            isTakenForSearch[i]=false;
        }
    }

    ~HashTable() {
        for (int i=0 ; i<arrSize ; i++) {
            delete arr[i];
        }
        delete[] arr;
        delete[] isTakenForSearch;
    }

    void insert(const Data& data, int key) {
        int index = key%arrSize;
        int r = 1+(key%(resizeCount/2))*2;
        while (arr[index] != NULL) {
            if (arr[index]->getKey()==key) {
                throw KeyAlreadyExists();
            }
            index=(index+r)%arrSize;
        }
        if (arr[index]!=NULL) {
            throw KeyAlreadyExists();
        }
        HashElement* newHashElement = new HashElement(data, key);
        arr[index] = newHashElement;
        numOfVars++;
        if (arrSize==numOfVars) {
            this->expand();
        }
    }

    void remove(int key) {
        int index = key%arrSize;
        int r = 1+(key%(resizeCount/2))*2;
        int count=0;
        while (count++<arrSize &&((arr[index] == NULL && isTakenForSearch[index]) || (arr[index] != NULL && arr[index]->getKey()!=key))) {
            index=(index+r)%arrSize;
        }
        if (arr[index]==NULL || count >= arrSize) {
            throw KeyDoesNotExist();
        } else {
            delete arr[index];
            arr[index]=NULL;
            isTakenForSearch[index]=true;
            numOfVars--;
        }
        if ((arrSize/4)==numOfVars) {
            this->shrink();
        }
    }
    const bool doesExist(int key) const {
        int index = key%arrSize;
        int r = 1+(key%(resizeCount/2))*2;
        int count=0;
        while (count++<arrSize &&((arr[index] == NULL && isTakenForSearch[index]) || (arr[index] != NULL && arr[index]->getKey()!=key))) {
            index=(index+r)%arrSize;
        }
        if(count >= arrSize){
        	return false;
        }
        return (arr[index] != NULL);
    }

    const Data& get(int key) const {
        int index = key%arrSize;
        int r = 1+(key%(resizeCount/2))*2;
        int count=0;
        while (count++<arrSize &&((arr[index] == NULL && isTakenForSearch[index]) || (arr[index] != NULL && arr[index]->getKey()!=key))) {
            index=(index+r)%arrSize;
        }
        if (arr[index]==NULL || count >= arrSize) {
            throw KeyDoesNotExist();
        } else {
            return arr[index]->getData();
        }
    }

    void expand() {
        resizeCount*=2;
        int oldSize=arrSize;
        arrSize=resizeCount;
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
                insert(oldArr[i]->getData(),oldArr[i]->getKey());
                delete oldArr[i];
            }
        }
        delete[] oldArr;
        delete[] oldIsTaken;
    }

    void shrink() {
    	if (resizeCount == 1){
    		return;
    	}
    	resizeCount/=2;
        int oldSize=arrSize;
        arrSize=resizeCount;
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
int HashTable<Data>::resizeCount=4;

#endif //WET2SPRING17_GENERICHASHTABLE_H
