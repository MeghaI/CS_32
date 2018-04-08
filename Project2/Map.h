//
//  Map.h
//  project2
//
//  Created by Megha Ilango on 1/27/18.
//  Copyright © 2018 Megha Ilango. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();
    Map(const Map& other);
    Map& operator=(const Map& other);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;
    ~Map();
private:
    int length;
    struct MapItem{
        KeyType key;
        ValueType value;
        MapItem* next;
        MapItem* prev;
    };
    MapItem* head;
    MapItem* tail;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);


#include <stdio.h>

#endif /* Map_h */
