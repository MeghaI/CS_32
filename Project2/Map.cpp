//
//  Map.cpp
//  project2
//
//  Created by Megha Ilango on 1/27/18.
//  Copyright © 2018 Megha Ilango. All rights reserved.
//

#include "Map.h"
#include <iostream>
using namespace std;

Map::Map(){
    head = NULL;
    tail = NULL;
    length = 0;
}

Map::Map(const Map& other){
    //intialize new Map
    length = other.length;
    head = NULL;
    tail = NULL;
    if(other.head != NULL){
        //set head
        head = new MapItem();
        head->key = other.head->key;
        head->value = other.head->value;
        head->next = other.head->next;
        head->prev = other.head->prev;
        MapItem* here = head;
        MapItem* there = other.head;
        //traverse through Map
        while(there->next != NULL){
            //set each Node of List
            here->next = new MapItem();
            here->next->key = there->next->key;
            here->next->value = there->next->value;
            here->next->next = there->next->next;
            here->next->prev = there->next->prev;
            
            //update pointers for traversal
            here = here->next;
            there = there->next;
        }
        //set tail
        tail = here;
    }
}

Map& Map::operator=(const Map& other){
    //prevent aliasing
    if(&other==this) return (*this);
    
    //delete current contents of list
    MapItem *del = head;
    while(del!=NULL){
        MapItem* temp = del->next;
        delete del;
        del = temp;
    }
    
    //reinitialize Map
    length = other.length;
    head = NULL;
    tail = NULL;
    if(other.head != NULL){
        //set head
        head = new MapItem();
        head->key = other.head->key;
        head->value = other.head->value;
        head->next = other.head->next;
        head->prev = other.head->prev;
        MapItem* here = head;
        MapItem* there = other.head;
        //traverse through Map
        while(there->next != NULL){
            //set each Node of List
            here->next = new MapItem();
            here->next->key = there->next->key;
            here->next->value = there->next->value;
            here->next->next = there->next->next;
            here->next->prev = there->next->prev;
            
            //update pointers for traversal
            here = here->next;
            there = there->next;
        }
        tail = here;
    }

    return (*this);
}

bool Map::empty() const{
    if(length==0) return true;
    return false;
}

int Map::size() const{
    return length;
}

bool Map::insert(const KeyType& key, const ValueType& value){
    //check if key is contained in list
    MapItem *p = head;
    bool keyIn = false;
    while(p!=NULL){
        if(p->key==key) keyIn = true;
        p = p->next;
    }
    if(keyIn) return false;
    
    //initialize new MapItem
    MapItem* newItem = new MapItem();
    newItem->key = key;
    newItem->value = value;
    newItem->prev = NULL;
    newItem->next = NULL;
    
    //add new item to list, set pointers that link to it correctly
    if(head==NULL){
        newItem->prev = NULL;
        head = newItem;
        tail = newItem;
    }else{
        newItem->prev = tail;
        tail->next = newItem;
        tail = newItem;
    }
    //increment our count of how many MapItems are in Map
    length++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value){
    MapItem *p = head;
    //traverse through list
    while(p!=NULL){
        //if key is found, update value
        if(p->key==key){
            p->value = value;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    //if updates, then return true
    if(this->update(key, value)) return true;
    //otherwise, return insert
    return (this->insert(key, value));
}

bool Map::contains(const KeyType& key) const{
    //traverse through list, checking for target key
    MapItem *p = head;
    bool keyIn = false;
    while(p!=NULL){
        if(p->key==key) keyIn = true;
        p = p->next;
    }
    return keyIn;
}

bool Map::erase(const KeyType& key){
    //if(!this->contains(key)) return false;
    MapItem *p = head;
    //traverse through list
    while(p!=NULL){
        //find item to be deleted
        if(p->key==key){
            //set new head or tail if they are being erased
            if(p==head){
                head = p->next;
            }
            if(p==tail){
                tail = p->prev;
            }
            //set pointers to erased item to correct values
            if(p->prev!=NULL) p->prev->next = p->next;
            if(p->next!=NULL) p->next->prev = p->prev;
            delete p;
            //decrement length
            length--;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const{
    MapItem *p = head;
    //traverse list
    while(p!=NULL){
        //if key is found, set param value
        if(p->key==key){
            value = p->value;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const{
    if(i>=length || i<0) return false;
    int place = 0;
    MapItem *p = head;
    //traverse through list i times
    while(place<i && p!=NULL){
        p = p->next;
        place++;
    }
    //set key and value
    if(p!=NULL){
        key = p->key;
        value = p->value;
    }
    return true;
}

void Map::swap(Map& other){
    Map temp;
    temp = *this;
    *this = other;
    other = temp;
}

Map::~Map(){
    MapItem *p = head;
    //delete each item, first storing its next in a temporary value so it is not lost
    while(p!=NULL){
        MapItem* temp = p->next;
        delete p;
        p = temp;
    }
}


void Map::dump() const{
    MapItem *p = head;
    while(p!=NULL){
        cerr << p->key << ", " << p->value << endl;
        p = p->next;
    }
    cerr << endl;
}

bool combine(const Map& m1, const Map& m2, Map& result){
    //prevent aliasing
    Map map1 = m1;
    Map map2 = m2;
    
    //delete contents of result
    for(int i = 0; i<result.size(); i++){
        KeyType key;
        ValueType val;
        result.get(i, key, val);
        result.erase(key);
        i--;
    }
    //track whether same key in two lists has different value
    bool mismatch = false;
    //go through m1
    for(int i = 0; i<map1.size(); i++){
        KeyType key1;
        ValueType val1;
        map1.get(i, key1, val1);
        //if m2 has the item, either insert it if values match or update boolean if not
        if(map2.contains(key1)){
            ValueType val2;
            map2.get(key1, val2);
            if(val2==val1){
                result.insert(key1, val2);
            }else{
                mismatch = true;
            }
        //if m2 doesn't have item, add to result
        }else{
            result.insert(key1, val1);
        }
        
    }
    //go through m2 and add items not in m1 to result
    for(int i = 0; i<map2.size(); i++){
        KeyType key2;
        ValueType val2;
        map2.get(i, key2, val2);
        if(!map1.contains(key2)){
            result.insert(key2, val2);
        }
    }
    return !mismatch;
}

void subtract(const Map& m1, const Map& m2, Map& result){
   //prevent aliasing
    Map map1 = m1;
    Map map2 = m2;
    
    //delete contents of result
    for(int i = 0; i<result.size(); i++){
        KeyType key;
        ValueType val;
        result.get(i, key, val);
        result.erase(key);
        i--;
    }
    //go through m1, adding items not in m2 to result
    for(int i = 0; i<map1.size(); i++){
        KeyType key1;
        ValueType val1;
        map1.get(i, key1, val1);
        if(!map2.contains(key1)){
            result.insert(key1, val1);
        }
    }
}

