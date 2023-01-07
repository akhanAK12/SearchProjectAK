// Project 2 - Search Engine

//  File name: main.cpp Author: Arij Khan
//  NetId: akhan342  System: Visual Studio

#include <iostream>
#include "search.h"
using namespace std;

int main() {

   
    searchEngine("cplusplus.txt"); 

    return 0;


    /*
        Milestone 1 Test Cases:

             string ans = "hello";
             cout << "1. " << (ans == cleanToken(".hello")) << endl;
             cout << "2. " << (ans == cleanToken("...hello")) << endl;

             string name = "....2312^#@@@....";
             cout << "Before function:" << name << endl;
             string cleaned = cleanToken(name);
             cout << isalpha('2') << endl;
             cout << cleaned << endl;

             cleanToken("...hello..."); 
             cleanToken("egg!s!!!!"); 
             cleanToken("!!!!fi.sh..h!!!!."); 


        Milestone 2 Test Cases:

            set<string> tokens = gatherTokens("to be or not to be");
            set<string> tokensANS;
            tokensANS.insert("to");
            tokensANS.insert("be");
            tokensANS.insert("or");
            tokensANS.insert("not");
            cout << "1. " << (tokens.size() == 4) << endl;
            cout << "2. " << (tokens == tokensANS) << endl;

            //gatherTokens("Memories, follow, me, left, and, right, I, can, feel, you, over, here, I, can, feel, you, over, here, You, take, up, every, corner, of, my, tablet, oldest, on, over, a, talking, dog, and, much, more, than, a, pet, he, keeps, Stewie, in, check, whilst, sipping, Martinis, and, sorting, through, his, own, life, issue ");


        Milestone 3 Test Cases:

        gatherTokens("Memories, follow, me, left, and, right, I, can, feel, you, over, here, I, can, feel, you, over, here, You, take, up, every, corner, of, my, tablet, oldest, on, over, a, talking, dog, and, much, more, than, a, pet, he, keeps, Stewie, in, check, whilst, sipping, Martinis, and, sorting, through, his, own, life, issue ");

        input in search:
        for(auto &e: tokens)
        {
        cout << e << endl; 
        }

         map<string, set<string>> testingIndex;
         int totalUrl = buildIndex("uiccs-news.txt", testingIndex);
        cout << "Result here is " << totalUrl << " and number of tokens is " << testingIndex.size() << endl;



        Milestone 4 Test Cases:  

        searchEngine("cplusplus.txt");
        vector +bool -vector vector bool ratio
        vector +bool +ratio

    */


}

