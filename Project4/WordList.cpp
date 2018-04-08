#include "provided.h"
#include <string>
#include <vector>
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include "MyHash.h"
using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, vector<string>> hashmap;
    string stringPattern(string s) const;
    bool translates(string word, string translation, string cipherWord) const;
};

bool WordListImpl::loadWordList(string filename)
{
    hashmap.reset();
    ifstream infile(filename);
    if(!infile){
        return false;
    }
    string s;
    while(getline(infile, s)){
        bool toPush = true;
        for(int i = 0; i<s.size(); i++){
            if(!isalpha(s[i]) && s[i]!='\''){
                toPush = false;
            }
            s[i] = tolower(s[i]);
        }
        vector<string> possibilities;
        if(hashmap.find(stringPattern(s))!=nullptr){
            possibilities = *(hashmap.find(stringPattern(s)));
        }
            possibilities.push_back(s);
            if(s.size()>0 && toPush){
//                cout << stringPattern(s) << ": ";
//                for(int i = 0; i<possibilities.size(); i++){
//                    cout << possibilities[i] << " ";
//                }
//                cout << endl;
                hashmap.associate(stringPattern(s), possibilities);
            }
    }
    return true;
}

bool WordListImpl::contains(string word) const
{
    for(int i = 0; i<word.size(); i++){
        word[i] = tolower(word[i]);
    }
    vector<string> possibilities;
    if(hashmap.find(stringPattern(word))==nullptr) return false;
    if(hashmap.find(stringPattern(word))!=nullptr)  possibilities = *(hashmap.find(stringPattern(word)));
    for(int i = 0; i < possibilities.size(); i++){
        if(word==possibilities[i]) return true;
    }
    return false;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> candidates;
    if(currTranslation.size()!=cipherWord.size()) return candidates;
    
    vector<string> possibilities;
    
    for(int i = 0; i<cipherWord.size(); i++){
        cipherWord[i]=tolower(cipherWord[i]);
    }
    
    if(hashmap.find(stringPattern(cipherWord))!=nullptr){
        possibilities = *hashmap.find(stringPattern(cipherWord));
    }
    for(int i = 0; i<possibilities.size(); i++){
        if(translates(possibilities[i], currTranslation, cipherWord))
            candidates.push_back(possibilities[i]);
    }
    
    return candidates;
}

bool WordListImpl::translates(string word, string translation, string cipherWord) const{
    if(word.size()!=translation.size()) return false;
    for(int i = 0; i<word.size(); i++){
        if(translation[i]=='?'){
            if(!isalpha(word[i]) || !isalpha(cipherWord[i])) return false;
        }else if(isalpha(translation[i])){
            if(tolower(translation[i])!=tolower(word[i]) || !isalpha(cipherWord[i])) return false;
        }else if(translation[i]=='\''){
            if(translation[i]!=word[i] || cipherWord[i]!=translation[i]) return false;
        }
    }
    return true;
}

string WordListImpl::stringPattern(string s) const{
    for(int i = 0; i<s.size(); i++){
        tolower(s[i]);
    }
    string pattern;
    int code = 0;
    for(int i = 0; i<s.size(); i++){
        bool multiple = false;
        for(int j = 0; j<i; j++){
            if(s[i]==s[j]){
                pattern = pattern + pattern[j];
                multiple=true;
                break;
            }
        }
        if(!multiple){
            pattern = pattern + static_cast<char>('a'+code);
            code++;
        }
    }
    return pattern;
}

//bool WordListImpl::contains(string word) const
//{
//    return false; // This compiles, but may not be correct
//}
//
//vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
//{
//    return vector<string>();  // This compiles, but may not be correct
//}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}
