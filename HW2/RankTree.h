#ifndef WET1_AVL_H
#define WET1_AVL_H

#include <iostream>
#include <cmath>

/*
 * return the max between two integers
 */
static int max(int a, int b){
    return (a>b?a:b);
}

template <class Data, class Key>
class RankTree {
public:
    /*-------------------------------------------------------------------------*
     *------------------------INNER NODE IMPLEMENTATION------------------------*
     *-------------------------------------------------------------------------*/
    class node {
    private:
        Data data;
        Key key;
        node* father;
        node* leftSon;
        int hl;
        node* rightSon;
        int hr;
        int rank;
        int sumOfPowers;
        int power;
    public:
        /*
         * C'tor
         */
        node( node *father, Data data , Key key, int power ) :
                data(data), key(key), father(father), leftSon(NULL), hl(0),
                rightSon(NULL), hr(0), rank(1), sumOfPowers(power), power(power) {};
        /*
         * C'tor for empty tree
         */
        node() :
                father(NULL), leftSon(NULL), hl(0),rightSon(NULL), hr(0),
                rank(1), sumOfPowers(0), power(0) {};
        /*
         * get current node data
         */
        Data& getData() {
            return data;
        }

        const Data& getData() const {
            return data;
        }
        /*
         * sets the current node data
         */
        void setData(Data d) {
            this->data=d;
        }
        /*
         * get current node key
         */
        Key getKey() {
            return key;
        }

        const Key getKey() const {
            return key;
        }
        /*
         * sets the current node key
         */
        void setKey(Key k) {
            this->key=k;
        }
        /*
         * get current node's left son pointer
         */
        node *getLeftSon() {
            return this->leftSon;
        }

        /*
         * sets current node's left son pointer
         */
        void setLeftSon(node *left) {
            this->leftSon = left;
        }

        /*
         * get current node's left son pointer
         */
        node *getRightSon() {
            return this->rightSon;
        }

        /*
         * sets current node's left son pointer
         */
        void setRightSon(node *right) {
            this->rightSon = right;
        }

        /*
         * returns the height of the left son
         */
        int getHl() {
            return this->hl;
        }

        /*
         * returns the height of the right son
         */
        int getHr() {
            return this->hr;
        }

        /*
         * sets the height of the left son
         */
        void setHl(int n) {
            this->hl = n;
        }

        /*
         * sets the height of the right son
         */
        void setHr(int n) {
            this->hr = n;
        }

        int getRank() const {
            return (!this ? 0 : rank);
        }

        void setRank(int rank) {
            this->rank = rank;
        }

        int getSumOfPowers() const {
            return sumOfPowers;
        }

        void setSumOfPowers(int sumOfPowers) {
            node::sumOfPowers = sumOfPowers;
        }
        /*
         * get current node's father pointer
         */
        node *getFather() {
            return this->father;
        }

        /*
         * sets the current node's father pointer
         */
        void setFather(node *node) {
            this->father = node;
        }

        int getPower() const {
            return power;
        }

        void setPower(int power) {
            node::power = power;
        }

        /*
         * returns true if the current node is a root, false otherwise
         */
        bool isRoot() {
            return (getFather() == NULL);
        }

        /*
         * returns true if the current node is a left son to it's father (node),
         * false otherwise
         */
        bool isLeftSon() {
            if (isRoot())
                return false;
            return (this->getFather()->leftSon == this);
        }

        /*
         * returns true if the current node has a left son, false otherwise
         */
        bool hasLeftSon() {
            return (this->getLeftSon() != NULL);
        }

        /*
         * returns true if the current node is a right son to it's father,
         * false otherwise
         */
        bool isRightSon() {
            if (isRoot)
                return false;
            return (this->getFather()->rightSon == this);
        }

        /*
         * returns true if the current node has a right son, false otherwise
         */
        bool hasRightSon() {
            return (this->getRightSon() != NULL);
        }

        /*
         * returns true if the current node is a leaf, false otherwise
         */
        bool isLeaf() {
            return ((this->getLeftSon() == NULL)) &&
                   (this->getRightSon() == NULL);
        }

        /*
         * returns the next node (inorder)
         */
        node *getMinNode() {
            if (!(hasLeftSon())) {
                return this;
            } else {
                return (this->getLeftSon()->getMinNode());
            }
            return NULL;
        }
        /*---------------------------------------------------------------------*
         *------------------ROTATION MECHANISM IMPLEMENTATION------------------*
         *--------------------------------------------------------------------*/
        /*
         * fixes the heights after insertion\removal of nodes
         */
        void updateHeights() {
            if (this->getFather()) {
                if (this->isLeftSon()) {
                    this->getFather()->setHl(1+max(this->getHl(),this->getHr()));
                } else {
                    this->getFather()->setHr(1+max(this->getHl(),this->getHr()));
                }
            }
        }
        void updateRanks() {
            int n=1;
            if (this->getLeftSon()) {
                n+=this->getLeftSon()->getRank();
            }
            if (this->getRightSon()) {
                n+=this->getRightSon()->getRank();
            }
            setRank(n);
        }
        void updateSumOfPowers() {
            int n=this->getPower();
            this->setPower(n);
            if (this->hasRightSon()) {
                n+=this->getRightSon()->getSumOfPowers();
                node* son = this->getRightSon();
                while (son->hasLeftSon()) {
                    n+=son->getLeftSon()->getSumOfPowers();
                    son=son->getLeftSon();
                }
            }
            setSumOfPowers(n);
        }
        /*
         * returns the current node's balance factor
         */
        int getBalanceFactor() {
            return (hl - hr);
        }
        /*
         * balances the tree along the search path.
         * this method chooses the right rotation to perform in each node
         * in the search path
         */
        node* balanceAux(node** newRoot) {
            if (!this) {
                return NULL;
            }
            node* n = this;
            if (getBalanceFactor() > 1) {
                if (getLeftSon()->getBalanceFactor() >= 0) {
                    n = LLRotation();
                    if (n->getLeftSon()) {
                        n = n->getLeftSon();
                    }

                } else {
                    n = this->leftSon->LRRotation();
                }
            } else if (getBalanceFactor() < -1) {
                if (getRightSon()->getBalanceFactor() <= 0) {
                    n = RRRotation();
                    if (n->getRightSon() ) {
                        n = n->getRightSon();
                    }
                } else {
                    n = this->rightSon->RLRotation();
                }
            }
            *newRoot=n;
            updateHeights();
            updateRanks();
            updateSumOfPowers();
            n->getFather()->balanceAux(newRoot);
            return n;
        }

        /*
         * performs a LL rotation on a given subtree.
         */
        node* LLRotation() { //this==B==root in sub tree
            node* A = this->getLeftSon();
            node* temp = A->getRightSon();
            int BrHeight = this->hr;
            int ArHeight = A->hr;

            A->father = this->getFather();
            if (this->father) {//if this is not a root
                (this->isLeftSon())?(this->getFather()->leftSon = A):(this->getFather()->rightSon = A);
            }

            A->rightSon = this;
            this->father = A;

            this->leftSon = temp;
            if (temp) {
                temp->father=this;
            }

            this->hl = ArHeight;
            A->hr = 1 + max(ArHeight, BrHeight);
            this->updateRanks();
            this->updateSumOfPowers();
            A->updateRanks();
            A->updateSumOfPowers();
            return A;
        }

        /*
         * performs a RR rotation on a given subtree.
         */
        node* RRRotation() { //this==A==root in sub tree
            node *B = this->getRightSon();
            node *temp = B->getLeftSon();
            int AlHeight = this->hl;
            int BlHeight = B->hl;

            B->father = this->getFather();
            if (this->father) {//if this is not a root
                (this->isLeftSon())?(this->getFather()->leftSon = B):(this->getFather()->rightSon = B);
            }

            B->leftSon = this;
            this->father = B;

            this->rightSon = temp;
            if (temp) {
                temp->father=this;
            }
            this->hr = BlHeight;
            B->hl = 1 + max(BlHeight, AlHeight);
            this->updateRanks();
            this->updateSumOfPowers();
            B->updateRanks();
            B->updateSumOfPowers();
            return B;
        }

        /*
         * performs a LR rotation on a given subtree.
         */
        node* LRRotation() {
            node* n = this->RRRotation();
            return n->father->LLRotation();
        }

        /*
         * performs a LR rotation on a given subtree.
         */
        node* RLRotation() {
            node* n = this->LLRotation();
            return n->father->RRRotation();
        }
    };
    /*
     * balance
     */
    void balance(node* n) {
        node* newRoot;
        n->balanceAux(&newRoot);
        this->root = newRoot;
    }
    /*
     * AVL C'tor
     */
    RankTree():root(NULL) {};
    /*
     * Helper function for the tree destructor
     */
    void RankDestroy(node* current) {
        if (!current)
            return;
        RankDestroy(current->getLeftSon());
        RankDestroy(current->getRightSon());
        delete current;
    }
    /*
     * AVL D'tor
     */
    ~RankTree() {
        RankDestroy(root);
    };
    /*
     * find a node with certain key in the tree.
     * return: the relevant node or NULL if not found
     */
    Data& find(Key key){
        node* found = findAux(key, this->root);
        if (!found) {
            throw KeyDoesNotExist();
        }
        return found->getData();
    }
    /*
     * finds the rank of a node with certain key in the tree.
     * return: the rnode's rank or an error if not found
     */
    int rank(Key key){
        int rank = rankAux(key, this->root, rank);
        return rank;
    }
    /*
     * find a node with certain key in the tree.
     * return: the relevant node or NULL if not found
     */
    const Data& select(int index) const {
        node* found = selectAux(index, this->root);
        if (!found) {
            throw KeyDoesNotExist();
        }
        return found->getData();
    }
    node* getRoot() {
        return this->root;
    }
    /*
     * find a node with certain key in the tree.
     * return: the relevant node or NULL if not found
     */
    node* nodeFind(Key key){
        return findAux(key, this->root);
    }
    /*
     * inserts a given data+key to the tree
     */
    void insert(Data data, Key key, int power) {
        node* newNode = new node(NULL, data, key, power);
        if (!root) {
            root = newNode;
            return;
        }
        if (!nodeFind(key)) {
            insertAux(newNode, root, NULL);
        } else {
            delete newNode;
            throw (KeyAlreadyExists());
        }
        balance(nodeFind(key));
    }
    /*
     * removes a node from the tree
     */
    void remove(Key key) {
        node* target = nodeFind(key);
        node* father;
        if (target) {
            father = target->getFather();
        } else {
            father=NULL;
        }
        if (target) {
            removeAux(target);
        } else {
            throw KeyDoesNotExist();
        }
        if (father) {
            balance(father);
        } else {
            if (this->getRoot()){
                this->root->updateHeights();
                this->root->updateRanks();
                this->root->updateSumOfPowers();
            }
        }
    }
    /*
     * returns the "bigget" data
     */
    Data getMax() {
        node* current = this->getRoot();
        while (current) {
            if (!current->getRightSon()) {
                return current->getData();
            } else {
                current = current->getRightSon();
            }
        }
        return current->getData();
    }
    /*
     *inorder traverse
     */
    void inorderWrite(Data* dataArr, Key* keyArr, int* powerArr) {
        int i=0;
        inorderWriteAux(this->root, dataArr, keyArr, powerArr, &i);
    }
    /*
     *inorder traverse
     */
    template<class Function>
    void inorder(Function func) {
        inorderAux(this->root, func);
    }
    /*
     *preorder traverse
     */
    template<class Function>
    void preorder(Function func){
        preorderAux(this->root,func);
    }
    /*
     *postorder traverse
     */
    template<class Function>
    void postorder(Function func){
        postorderAux(this->root,func);
    }
    /*
     * calculates the depth of a balanced binary tree with n nodes
     */
    double calculateDepth(int n){
        if (n==0){
            return 0;
        }
        return ceil(log2(n+1)-1)<0?0:ceil(log2(n+1)-1);
    }
    /*
     * complete tree builder
     */
    node* createCompleteEmptyTreeAux(int depth,node* father) {
        if(depth < 0){
            return NULL;
        }
        node* current = new node();
        current->setFather(father);
        current->setLeftSon((createCompleteEmptyTreeAux(depth-1,current)));
        current->setRightSon((createCompleteEmptyTreeAux(depth-1,current)));
        return current;
    }
    /*
     * removes nodes from the empty tree
     */
    int RemoveNodes(int num, node* node){
        if(!node){
            return num;
        }
        int newNum = RemoveNodes(num,node->getRightSon());
        if(newNum <= 0){
            return 0;
        }
        if(node->isLeaf()){
            node->isLeftSon()?node->getFather()->setLeftSon(NULL) : node->getFather()->setRightSon(NULL);
            delete node;
            return num-1;
        }
        return RemoveNodes(newNum,node->getLeftSon());
    }
    static int pow2(int num) {
    	int sum = 1;
    	for (int i = 0; i < num; i++){
    		sum *= 2;
    	}
    	return sum;
    }
    void fixRanksAndHeights(node* current) {
        if (!current)
            return;
        fixRanksAndHeights(current->getLeftSon());
        fixRanksAndHeights(current->getRightSon());
        current->updateHeights();
        current->updateRanks();
    }
    void fixPowers(node* current) {
        if (!current)
            return;
        fixPowers(current->getLeftSon());
        fixPowers(current->getRightSon());
        current->updateSumOfPowers();
    }
    /*
     * create an empty tree with n nodes
     */
    RankTree<Data,Key>* createCompleteEmptyTree(int n){
        int depth = calculateDepth(n);
        RankTree<Data,Key>* newTree = new RankTree<Data,Key>;
        newTree->root = createCompleteEmptyTreeAux(depth,newTree->root);

        int check = (pow2(depth+1)-1-n);
        RemoveNodes(check,newTree->root);
        fixRanksAndHeights(newTree->root);

        return newTree;
    }
    /*
     * a helper function to fill the empty tree with data
     */
    node* fillEmptyTreeAux(node* current, Data* dataArr, Key* keyArr, int start, int end) {
        if (!current || (start > end))
            return NULL;

        int mid = (start + end)/2;
        current->setData(dataArr[mid]);
        current->setKey(keyArr[mid]);

        fillEmptyTreeAux(current->getLeftSon(),dataArr, keyArr, start, mid-1);
        fillEmptyTreeAux(current->getRightSon(),dataArr, keyArr, start, mid-1);

        return current;
    }
    /*
     * this function get pointers to arrays and fill the empty tree
     * with there content
     */
    void fillEmptyTree(Data* dataArray, Key* keyArray, int num){
        fillEmptyTreeAux(this->getRoot(),dataArray,keyArray,0,num);

    }
    int sumToRoot(node* current){
        return current->getSumOfPowers() + sumToRootAux(current);
    }
    int sumToRootAux(node* current){
    	if (!current->getFather()){
    		return 0;
    	}
    	if(current->isLeftSon()){
            return sumToRootAux(current->getFather()) + current->getFather()->getSumOfPowers();
    	} else {
            return sumToRootAux(current->getFather());
    	}
    }
    /*-------------------------------------------------------------------------*
 *-----------------------------HELPER FUNCTIONS----------------------------*
 *-------------------------------------------------------------------------*/
    /*
    * rank helper function
    */
    int rankAux(Key key, node* current, int rank) {
        if (!(current)) {
            throw KeyDoesNotExist();
        }
        if (key == current->getKey()) {
            return rank+current->getLeftSon()->getRank()+1;
        }
        if (key > current->getKey()) {
            return rankAux(key, current->getRightSon(), rank + current->getLeftSon()->getRank() + 1);
        } else {
            return rankAux(key, current->getLeftSon(), rank);
        }
    }
    /*
     * select helper function
     */
    node* selectAux(int index, node* current) const{
        if (!(current)) {
            return NULL;
        }
        int r;
        if (current->getLeftSon()) {
        	r=current->getLeftSon()->getRank();
        } else {
        	r=0;
        }
        if (index-1 == r) {
            return current;
        }
        return (index-1 > r)?
               selectAux(index-r-1,current->getRightSon()):
               selectAux(index,current->getLeftSon());
    }
    /*
     * find helper function
     */
    node* findAux(Key key, node* current) {
        if (!(current)) {
            return NULL;
        }
        if (key == current->getKey()) {
            return current;
        }
        return (key > current->getKey())?
               findAux(key,current->getRightSon()):findAux(key,current->getLeftSon());
    }
    /*
     * insert helper function
     */
    node* insertAux(node* n, node* current, node* father) {
        if (!(current)) {
            current = n;
            n->setFather(father);
            (father->getKey() > current->getKey())?father->setLeftSon(current):father->setRightSon(current);

            return current;
        }
        return (n->getKey() > current->getKey())?
               insertAux(n ,current->getRightSon(),current):insertAux(n ,current->getLeftSon(),current);
    }
    /*
     * remove helper function
     */
    void removeAux(node* target) {
        //case has no sons
        if (target->isLeaf()) {
            if (!target->getFather()) {
                this->root=NULL;
                delete target;
                return;
            }
            if(target->isLeftSon()){
                target->getFather()->setHl(0);
                target->getFather()->setLeftSon(NULL);
            } else {
                target->getFather()->setHr(0);
                target->getFather()->setRightSon(NULL);
            }
            balance(target->getFather());
        }
            //case has one son
        else if ( (( target->hasLeftSon() ) && (!(target->hasRightSon()) ) ) ||
                  (!( target->hasLeftSon() ) && ((target->hasRightSon()) ) )) {

            int sonHeight=(target->hasLeftSon())?target->getHl():target->getHr();

            node* son = ( target->hasLeftSon() )?target->getLeftSon():
                        target->getRightSon();
            if (!(target->getFather())) {
                this->root=son;
                root->setFather(NULL);
                delete target;
                return;
            }
            if (target->isLeftSon()) {
                target->getFather()->setLeftSon(son);
                target->getFather()->setHl(sonHeight);
            } else {
                target->getFather()->setRightSon(son);
                target->getFather()->setHr(sonHeight);
            }
            son->setFather(target->getFather());
            balance(son->getFather());
        }
            //case has two sons
        else if (( target->hasLeftSon() ) && ( target->hasRightSon() ) ) {
            node* toSwap = target->getRightSon()->getMinNode();
            Data tempData = target->getData();
            Key tempKey = target->getKey();
            int tempPower = target->getPower();

            target->setData(toSwap->getData());
            target->setKey(toSwap->getKey());
            target->setPower(toSwap->getPower());

            toSwap->setData(tempData);
            toSwap->setKey(tempKey);
            toSwap->setPower(tempPower);

            node* swapFather = toSwap->getFather();
            target->updateSumOfPowers();
            toSwap->updateSumOfPowers();
            removeAux(toSwap);
            balance(swapFather);
            return;
        }

        delete target;
    }
    /*
     * helper function to inorder traverse
     */
    void inorderWriteAux(node* current, Data* dataArr, Key* keyArr, int* powerArr, int* i) {
        if (!current)
            return;
        inorderWriteAux(current->getLeftSon(), dataArr, keyArr, powerArr, i);
        current->setData(dataArr[*i]);
        current->setKey(keyArr[*i]);
        current->setPower(powerArr[*i]);
        (*i)++;
        inorderWriteAux(current->getRightSon(), dataArr, keyArr, powerArr, i);
    }
    /*
     * helper function to inorder traverse
     */
    template<class Function>
    void inorderAux(node* current, Function& func) {
        if (!current)
            return;
        inorderAux(current->getLeftSon(), func);
        func(current->getData());
        inorderAux(current->getRightSon(), func);
    }
    /*
     * helper function to preorder traverse
     */
    template<class Function>
    void preorderAux(node* current, Function& func) {
        if (!current)
            return;
        func(current->getData());
        preorderAux(current->getLeftSon(), func);
        preorderAux(current->getRightSon(), func);
    }
    /*
     * helper function to postorder traverse
     */
    template<class Function>
    void postorderAux(node* current, Function& func) {
        if (!current)
            return;
        postorderAux(current->getLeftSon(), func);
        postorderAux(current->getRightSon(), func);
        func(current->getData());
    }
    /*-------------------------------------------------------------------------*
     *-------------------------END OF HELPER FUNCTIONS-------------------------*
     *-------------------------------------------------------------------------*/
    void print(node* current) {
        if (!current) {
            return;
        }
        std::cout << current->getKey() << "[" << current->getHl()<<","<<current->getHr() << "] ->" <<
                  (current->getLeftSon()?current->getLeftSon()->getKey():-1)
                  << ";" << (current->getRightSon()?current->getRightSon()->getKey():-1) << std::endl;
        print(current->getLeftSon());
        print(current->getRightSon());
    }
    class KeyAlreadyExists {};
    class KeyDoesNotExist {};
private:
    node* root;
};


#endif //WET1_AVL_H
