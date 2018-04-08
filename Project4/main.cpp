//#include <string>
//#include <vector>
//#include <cstring>
//#include <cctype>
//#include <random>
//#include <algorithm>
//#include <numeric>
//#include <cassert>
//#include <iostream>
//#include <functional>
//using namespace std;
//
//#include "MyHash.h"
//#include "provided.h"
////const string WORDLIST_FILE = "wordlist.txt";
////
////string encrypt(string plaintext)
////{
////    // Generate a to z
////    char plaintextAlphabet[26+1];
////    iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
////    plaintextAlphabet[26] = '\0';
////    
////    // Generate permutation
////    string ciphertextAlphabet(plaintextAlphabet);
////    default_random_engine e((random_device()()));
////    shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);
////    
////    // Run translator (opposite to the intended direction)
////    Translator t;
////    t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
////    return t.getTranslation(plaintext);
////}
////
////bool decrypt(string ciphertext)
////{
////    Decrypter d;
////    if ( ! d.load(WORDLIST_FILE))
////    {
////        cout << "Unable to load word list file " << WORDLIST_FILE << endl;
////        return false;
////    }
////    for (const auto& s : d.crack(ciphertext))
////        cout << s << endl;
////    return true;
////}
////
////int main(int argc, char* argv[])
////{
////    if (argc == 3  &&  argv[1][0] == '-')
////    {
////        switch (tolower(argv[1][1]))
////        {
////            case 'e':
////                cout << encrypt(argv[2]) << endl;
////                return 0;
////            case 'd':
////                if (decrypt(argv[2]))
////                    return 0;
////                return 1;
////        }
////    }
////
////    cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
////    cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
////    return 1;
////}
//
//int main(){
//    MyHash<int, int> hash2;
//   assert(hash2.getLoadFactor()==0);
//    assert(hash2.getNumItems()==0);
//    
//    unsigned int hash(const int& k); //prototype
//    unsigned int h = hash(1);
//    cout << h << endl;
//    
//    hash2.associate(1, 705);
//    assert(hash2.getNumItems()==1);
//    assert(hash2.getLoadFactor()==0.01);
//    hash2.associate(2, 223);
//    assert(hash2.getLoadFactor()==0.02);
//    for(int i = 3; i<51; i++){
//        hash2.associate(2*i, i);
//    }
//    hash2.associate(2*51, 51);
//    assert(hash2.getLoadFactor()==(51.0/200));
//    
//    Tokenizer t(":. ,!?;!");
//    vector<string> words = t.tokenize("Hi! My name is Megha. Am I excited for this?");
//    
//    for(int i = 0; i<words.size(); i++){
//        cerr << ","<< words[i];
//    }
//    cout << endl;
//    
//    cerr << "YAAS" << endl;
//
////WordList w1;
////    if(!w1.loadWordList("wordlist.txt")){
////        cout << "unable to load word list";
////        return 0;
////    }
////    if(w1.contains("onomatopoeia")){
////        cout << "I found onomatopoeia!" << endl;
////    }else{
////        cout << "Onomatopoeia is not in the word list!" << endl;
////    }
////    
////    string cipher = "xyqbbq";
////    string decodedSoFar = "?r????";
////    vector<string> v = w1.findCandidates(cipher, decodedSoFar);
////    if(v.empty()){
////        cout << "No matches found" << endl;
////    }else{
////        cout << "Found these matches: " << endl;
////        for(size_t k = 0; k<v.size(); k++){
////            cout << v[k] << endl;
////        }
////    }
//}
