////
////  main.cpp
////  project2
////
////  Created by Megha Ilango on 1/27/18.
////  Copyright © 2018 Megha Ilango. All rights reserved.
////
//
//
//#include "Map.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main() {
//    Map map;
//    assert(map.empty()==true);
//    
//    KeyType key1 = "hello";
//    ValueType value1 = 10;
//    map.insert(key1, value1);
//    assert(map.size()==1);
//    map.insertOrUpdate(key1, 1);
//    assert(map.size()==1);
//    
//    KeyType key2 = "helloo";
//    ValueType value2 = 002;
//    map.insert(key2, value2);
//    map.update(key2, 003);
//    map.insertOrUpdate(key1, 002);
//    assert(map.size()==2);
//    assert(map.contains("helloo")==true);
//    
//    assert(map.contains("hello")==true);
//    
//    assert(map.erase("hello"));
//    
//    assert(map.contains("hello")==false);
//    assert(map.size()==1);
//    
//    assert(map.contains("helloo")==true);
//
//    ValueType valueGet = 500;
//    assert(map.get("helllo", valueGet)==false);
//    assert(valueGet==500);
//    assert(map.get("helloo", valueGet)==true);
//    assert(valueGet==003);
//
//    Map m;  // maps strings to doubles
//    assert(m.empty());
//    ValueType v = -1234.5;
//    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
//    m.insert("xyz", 9876.5);
//    assert(m.size() == 1);
//    KeyType k = "hello";
//    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
//    assert(m.get(1, k, v)==false);
//    assert(m.get(-1,k,v)==false);
//    assert(m.insertOrUpdate("hahaha", 200));
//    assert(m.size()==2);
//    assert(m.get(1,k,v) && k=="hahaha" && v==200);
//    
//    Map map2;
//    assert(map2.empty());
//    assert(map.size()==1);
//    map.insert("HELLO", 5);
//    map.insert("HALO", 11);
//    assert(map.size()==3);
//    map2.insert("bye", 2);
//    map2.insert("byeee", 4);
//    assert(map2.size()==2);
//    map.swap(map2);
//    assert(map.size()==2);
//    assert(map2.size()==3);
//    map.insert("LOLOLOL", 500);
//    assert(map.size()==3 && map2.size()==3);
//    
//    Map c1;
//    c1.insert("Fred", 123);
//    c1.insert("Ethel", 456);
//    c1.insert("Lucy", 789);
//    Map c2;
//    c2.insert("Lucy", 789);
//    c2.insert("Ricky", 321);
//    Map result;
//    result.insert("lalala", 1);
//    assert(combine(c1, c2, result));
//    assert(combine(c1, c2, c2));
//    assert(c2.size()==result.size());
//    //result.dump();
//    
//    c2.erase("Ricky");
//    c2.update("Lucy", 654);
//    assert(!combine(c1, c2, result));
//    //result.dump();
//    
//    c2.update("Lucy", 789);
//    c2.erase("Fred");
//    c2.insert("Ethel", 654);
//    subtract(c1, c2, result);
//    subtract(c1, c2, c1);
//    assert(result.size()==c1.size());
//    //result.dump();
//    
//    
// 
//    Map d = c1;
//    Map a;
//    a.insert("HOLA", 222);
//    a = d;
//    assert(d.size()==a.size());
//    d.erase("Fred");
//
//    assert(d.size()<a.size());
//    
//    Map c;
//    a = c;
//    assert(a.size()==c.size());
//    c.insert("LOL", 23);
//    assert(c.size()>a.size());
//    Map b = a;
//    assert(a.size()==b.size() );
//    
//    
//    
//    
////            Map m;  // maps ints to strings <----------------
////            assert(m.empty());
////            ValueType v = "Ouch";
////            assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
////            m.insert(123456789, "Wow!");
////            assert(m.size() == 1);
////            KeyType k = 9876543;
////            assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
////            cout << "Passed all tests" << endl;
//    
//    cout << "Passed all tests" << endl;
//    
//}
////
////  main.cpp
////  project2
////
////  Created by Megha Ilango on 1/27/18.
////  Copyright © 2018 Megha Ilango. All rights reserved.
////
//
//
//#include "Map.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main() {
//    Map map;
//    assert(map.empty()==true);
//
//    KeyType key1 = "hello";
//    ValueType value1 = 10;
//    map.insert(key1, value1);
//    assert(map.size()==1);
//    map.insertOrUpdate(key1, 1);
//    assert(map.size()==1);
//
//    KeyType key2 = "helloo";
//    ValueType value2 = 002;
//    map.insert(key2, value2);
//    map.update(key2, 003);
//    map.insertOrUpdate(key1, 002);
//    assert(map.size()==2);
//    assert(map.contains("helloo")==true);
//
//    assert(map.contains("hello")==true);
//
//    assert(map.erase("hello"));
//
//    assert(map.contains("hello")==false);
//    assert(map.size()==1);
//
//    assert(map.contains("helloo")==true);
//
//    ValueType valueGet = 500;
//    assert(map.get("helllo", valueGet)==false);
//    assert(valueGet==500);
//    assert(map.get("helloo", valueGet)==true);
//    assert(valueGet==003);
//
//    Map m;  // maps strings to doubles
//    assert(m.empty());
//    ValueType v = -1234.5;
//    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
//    m.insert("xyz", 9876.5);
//    assert(m.size() == 1);
//    KeyType k = "hello";
//    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
//    assert(m.get(1, k, v)==false);
//    assert(m.get(-1,k,v)==false);
//    assert(m.insertOrUpdate("hahaha", 200));
//    assert(m.size()==2);
//    assert(m.get(1,k,v) && k=="hahaha" && v==200);
//
//    Map map2;
//    assert(map2.empty());
//    assert(map.size()==1);
//    map.insert("HELLO", 5);
//    map.insert("HALO", 11);
//    assert(map.size()==3);
//    map2.insert("bye", 2);
//    map2.insert("byeee", 4);
//    assert(map2.size()==2);
//    map.swap(map2);
//    assert(map.size()==2);
//    assert(map2.size()==3);
//    map.insert("LOLOLOL", 500);
//    assert(map.size()==3 && map2.size()==3);
//
//    Map c1;
//    c1.insert("Fred", 123);
//    c1.insert("Ethel", 456);
//    c1.insert("Lucy", 789);
//    Map c2;
//    c2.insert("Lucy", 789);
//    c2.insert("Ricky", 321);
//    Map result;
//    result.insert("lalala", 1);
//    assert(combine(c1, c2, result));
//    assert(combine(c1, c2, c2));
//    assert(c2.size()==result.size());
//    //result.dump();
//
//    c2.erase("Ricky");
//    c2.update("Lucy", 654);
//    assert(!combine(c1, c2, result));
//    //result.dump();
//
//    c2.update("Lucy", 789);
//    c2.erase("Fred");
//    c2.insert("Ethel", 654);
//    subtract(c1, c2, result);
//    subtract(c1, c2, c1);
//    assert(result.size()==c1.size());
//    //result.dump();
//
//
//
//    Map d = c1;
//    Map a;
//    a.insert("HOLA", 222);
//    a = d;
//    assert(d.size()==a.size());
//    d.erase("Fred");
//
//    assert(d.size()<a.size());
//
//    Map c;
//    a = c;
//    assert(a.size()==c.size());
//    c.insert("LOL", 23);
//    assert(c.size()>a.size());
//    Map b = a;
//    assert(a.size()==b.size() );
//
//
//
//
////            Map m;  // maps ints to strings <----------------
////            assert(m.empty());
////            ValueType v = "Ouch";
////            assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
////            m.insert(123456789, "Wow!");
////            assert(m.size() == 1);
////            KeyType k = 9876543;
////            assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
////            cout << "Passed all tests" << endl;
//
//    cout << "Passed all tests" << endl;
//
//}
