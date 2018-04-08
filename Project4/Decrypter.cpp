#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl(): tokenizer("1234567890 ,;:.!()[]{}-\"#$%^&"){ }
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList wordlist;
    Tokenizer tokenizer;
    void helper(Translator* translator, const string& ciphertext, vector<string> &answer);
};


bool DecrypterImpl::load(string filename)
{
    return wordlist.loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector<string> answer;
    for(int i = 0; i<ciphertext.size(); i++){
        if(isalnum(ciphertext[i]) || ciphertext[i]==',' || ciphertext[i]==';' || ciphertext[i]==':' || ciphertext[i]=='.' || ciphertext[i]=='!' || ciphertext[i]=='(' || ciphertext[i]==')' || ciphertext[i]=='[' || ciphertext[i]==']' || ciphertext[i]=='{' || ciphertext[i]=='}' || ciphertext[i]=='-' || ciphertext[i]=='"' || ciphertext[i]=='#' || ciphertext[i]=='$' ||ciphertext[i]=='%' || ciphertext[i]=='^' || ciphertext[i]=='&' || ciphertext[i]==' ' || ciphertext[i]=='\''){
            
        }else{
            return answer;
        }
    }
    Translator* trans = new Translator();
    
    
    
    helper(trans, ciphertext, answer);
    delete trans;
    
    sort(answer.begin(), answer.end());
    
    return answer;
}

void DecrypterImpl::helper(Translator* translator, const string& ciphertext, vector<string> &answer){
    
    //TOKENIZE
    vector<string> words = tokenizer.tokenize(ciphertext);
//    //PICK THE CHOSEN WORD W
//    bool chosenWords[words.size()];
//    for(int i = 0; i<words.size(); i++){
//        chosenWords[i] = false;
//    }
    
    int maxQ = 0;
    int index = 0;
    for(int i = 0; i<words.size(); i++){
        //if(!chosenWords[i]){
            int numQ = 0;
            string translation = translator->getTranslation(words[i]);
            for(int j =0; j<words[i].size(); j++){
                if(translation[j]=='?') numQ++;////
            }
            if (maxQ<numQ){
                maxQ = numQ;
                index = i;
            }
       // }
    }
    //INDEX IS THE INDEX IN WORDS OF MY CHOSEN WORD W
    //chosenWords[index] = true;
    string translation = translator->getTranslation(words[index]);
    
    
    vector<string> C = wordlist.findCandidates(words[index], translation);
    
    if(C.size()==0){
        translator->popMapping();
        return;
    }
    for(int i = 0; i<C.size(); i++){
        if(!(translator->pushMapping(words[index], C[i]))){
            continue;
        }else{
            string propPlain = translator->getTranslation(ciphertext);
            vector<string> translatedWords = tokenizer.tokenize(propPlain);
            bool partiallyTranslated = false;
            bool fullyTranslated = true;
            bool allWordsFound = true;
            for(int j = 0; j<translatedWords.size(); j++){
                int numQ = 0;
                string w = translatedWords[j];
                for(int q = 0; q<w.size(); q++){
                    if(w[q]=='?'){
                        numQ++;
                        partiallyTranslated = true;
                        fullyTranslated = false;
                    }
                }
                if(numQ==0){
                    if(!wordlist.contains(w)){
                        translator->popMapping();
                        allWordsFound =false;
                        continue;
                    }
                }
            }
            if(partiallyTranslated && allWordsFound){
                helper(translator, ciphertext, answer);
            }else if(fullyTranslated && allWordsFound){
                answer.push_back(propPlain);
                translator->popMapping();
            }
        }
    }
    translator->popMapping();
    return;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
