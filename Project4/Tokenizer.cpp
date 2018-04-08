#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
    string mySeparators;
    bool isSeparator(char c) const;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    mySeparators = separators;
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
    int start = 0;
    int end = s.size();
    vector<string> myWords;
    
    for(int i = 0; i<=s.size(); i++){
        if(i==s.size() || isSeparator(s[i])){
            end = i;
            string toAdd = s.substr(start, end-start);
            if(toAdd!="") myWords.push_back(toAdd);
            start = end+1;
        }
    }
    return myWords;  // This compiles, but may not be correct
}

bool TokenizerImpl::isSeparator(char c) const{
    for(int i = 0; i<mySeparators.size(); i++){
        if(mySeparators[i]==c) return true;
    }
    return false;
}



//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}
