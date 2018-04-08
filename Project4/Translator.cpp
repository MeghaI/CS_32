#include "provided.h"
#include <string>
#include <list>
#include <map>
#include <cctype>
#include "MyHash.h"
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    list<map<char, char>> myMaps;
    int numPushes = 0;
    int numPops = 0;
    map<char, char> currentMap;
};

TranslatorImpl::TranslatorImpl(){
    map<char, char> toAdd;
    for(int i = 'a'; i < 'a'+26; i++){
        toAdd[i] = '?';
    }
    myMaps.push_front(toAdd);
    currentMap = toAdd;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    //CHECK IF SIZES ARE EQUAL
    if(ciphertext.size()!=plaintext.size()) return false;
    
    //LOWERCASE ERRYTHING
    for(int i = 0; i<ciphertext.size(); i++){
        ciphertext[i] = tolower(ciphertext[i]);
        plaintext[i] = tolower(plaintext[i]);
        if(!isalpha(ciphertext[i])) return false;
        if(!isalpha(plaintext[i])) return false;
    }
    
    //MAKE A COPY
    map<char,char> copy = currentMap;
    vector<char> decoded;
    for(int i = 'a'; i < 'a'+26; i++){
        if(isalpha(copy[i])) decoded.push_back(copy[i]);
    }
    
    //GO THROUGH CIPHERTEXT
    for(int i = 0; i<ciphertext.size(); i++){
        char current = copy[ciphertext[i]];
        //?
        if(current=='?'){
            //checking if the character has already been mapped to
            for(int j = 0; j<decoded.size(); j++){
                if(plaintext[i]==decoded[j]) return false;
            }
            copy[ciphertext[i]] = plaintext[i];
            decoded.push_back(plaintext[i]);
        }else if(current!=plaintext[i]){
            return false;
        }
    }
    
    map<char,char> oldCurrent = currentMap;
    myMaps.push_front(oldCurrent);
    currentMap = copy;
    numPushes++;
    
    
    return true;
}

bool TranslatorImpl::popMapping()
{
    if(numPushes==numPops) return false;
    currentMap = myMaps.front();
    myMaps.pop_front();
    numPops++;
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string answer = "";
    for(int i = 0; i<ciphertext.size(); i++){
        char curr = ciphertext[i];
        bool upper = false;
        if(isupper(curr)) upper = true;
        map<char,char>::const_iterator it = currentMap.begin();
        it = currentMap.find(tolower(curr));
        if(it==currentMap.end()){
            answer = answer + curr;
        }else{
            char toAdd = it->second;
            if(upper) toAdd = toupper(toAdd);
            answer = answer+toAdd;
        }
        
    }
    return answer;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
