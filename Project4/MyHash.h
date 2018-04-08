// MyHash.h
// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED

#include <iostream>
using namespace std;

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
private:
    struct Node{
        KeyType key;
        ValueType value;
        Node* next = nullptr;
    };
    Node** myTable = nullptr;
    double myMaxLoadFactor;
    int numItems;
    int numBuckets;
    void resizeTable();
    unsigned int getBucketNumber(const KeyType& key) const;
};

template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>::getBucketNumber(const KeyType& key) const{
    unsigned int hash(const KeyType& k); //prototype
    unsigned int h = hash(key);
    return h%numBuckets;
    return 0;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor){
    myTable = new Node*[100];
    for(int i = 0; i<100; i++){
        myTable[i] = nullptr;
    }
    numBuckets = 100;
    myMaxLoadFactor = maxLoadFactor;
    if(maxLoadFactor<=0){
        myMaxLoadFactor = 0.5;
    }
    if(maxLoadFactor>2){
        myMaxLoadFactor = 2.0;
    }
    numItems = 0;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash(){
    for(int i = 0; i<numBuckets; i++){
        while(myTable[i]!=nullptr){
            Node* temp = myTable[i];
            myTable[i] = myTable[i]->next;
            delete temp;
        }
        delete myTable[i];
    }
    delete [] myTable;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset(){
    for(int i = 0; i<numBuckets; i++){
        while(myTable[i]!=nullptr){
            Node* temp = myTable[i];
            myTable[i] = myTable[i]->next;
            delete temp;
        }
        delete myTable[i];
    }
    delete [] myTable;
    myTable = new Node*[100];
    for(int i = 0; i<100; i++){
        myTable[i] = nullptr;
    }
    numBuckets = 100;
    numItems = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value){
    int bucketNum = getBucketNumber(key);
    if(myTable[bucketNum]==nullptr){
        Node* toAdd = new Node();
        toAdd->key = key;
        toAdd->value = value;
        toAdd->next = nullptr;
        myTable[bucketNum] = toAdd;
        numItems++;
    }else{
        bool replace = false;
        Node* current = myTable[bucketNum];
        while(current!=nullptr){
            if(current->key==key){
                current->value = value;
                replace = true;
                break;
            }else{
                current = current->next;
            }
        }
        if(!replace){
            Node* toAdd = new Node();
            toAdd->key = key;
            toAdd->value = value;
            toAdd->next = nullptr;
            toAdd->next = myTable[bucketNum];
            myTable[bucketNum] = toAdd;
            numItems++;
        }
    }
    if(getLoadFactor()>myMaxLoadFactor) resizeTable();
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::resizeTable(){
    numBuckets*=2;
    Node** myNewTable= new Node*[numBuckets];
    
    for(int i = 0; i<numBuckets; i++){
        myNewTable[i] = nullptr;
    }
    
    for(int i = 0; i<numBuckets/2; i++){
        if(myTable[i]!=nullptr){
            Node* current = myTable[i];
            while(current!=nullptr){
                int bucketNum = getBucketNumber(current->key);
                if(myNewTable[bucketNum]==nullptr){
                    Node* toAdd = new Node();
                    toAdd->key = current->key;
                    toAdd->value = current->value;
                    myNewTable[bucketNum] = toAdd;
                }else{
                    Node* currentNew = myNewTable[bucketNum];
                    while(currentNew!=nullptr){
                        if(currentNew->next==nullptr){
                            Node* toAdd = new Node();
                            toAdd->key = current->key;
                            toAdd->value = current->value;
                            currentNew->next = toAdd;
                            break;
                        }
                        currentNew = currentNew->next;
                    }
                }
                current = current->next;
            }
        }
    }
    
    for(int i = 0; i<numBuckets/2; i++){
        while(myTable[i]!=nullptr){
            Node* temp = myTable[i];
            myTable[i] = myTable[i]->next;
            delete temp;
        }
        delete myTable[i];
    }
    delete [] myTable;
    
    myTable = myNewTable;
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const{
    int bucketNum = getBucketNumber(key);
    if(myTable[bucketNum]==nullptr) return nullptr;
    Node* current =myTable[bucketNum];
    while(current!=nullptr){
        if(current->key==key) return &(current->value);
        current = current->next;
    }
    return nullptr;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const{
    return ((numItems*1.0) / numBuckets);
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const{
    return numItems;
}

#endif // MYHASH_INCLUDED