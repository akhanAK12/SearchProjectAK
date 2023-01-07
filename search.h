// Project 2 - Search Engine

//  File name: search.h Author: Arij Khan
//  NetId: akhan342  System: Visual Studio

//To use creative component, comment out the code in the "searchEngine" function 
//and input in "creative"

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;

/*-------------------- Creative Component --------------------*/
/*
set<string> creativeComponent(string file,  map<string, set<string>> &index)
{
  fstream infile; 
  int counter = 0;
  infile.open(file); 

  set<string> stopWords; 
  string tempString; 

  if(!infile.is_open())
  {
    return stopWords; 
  }

  while(!infile.eof())
  {
     infile >> tempString; 
     stopWords.insert(tempString); 
     //cout << tempString << endl; 
  }

  for(auto &mapWords: index)
  {
    //++counter;
    for(auto &s: stopWords)
    {
      if(s == mapWords.first)
      {
        index.erase(s); 
      }
    }
  }
  cout << "Stop words removed from the map" << endl;
  //say you loop through both 

  return stopWords; 


}
*/


//This function will take in a string and remove any punctuations before or after any first and last character. 
//It will keep any punctuation character within the string
//In my function I have two loops where I loop until the first and last characters are found and I then erase from the starting index of the string
//until the first characters index and vice versa to remove all punctuations after the last character. I check if no letters are found within the string
//and if they aren't any, I will return an empty string

string cleanToken(string s)
{

  if (s.size() == 0)
  {
    return "";
  }

  for (int i = 0; i < s.size(); i++)
  {

    if (ispunct(s[i]) == 0) // Condtion will be true if letter is found at index i
    {
      int index = i; // index is holding the first letter in the string

      s.erase(0, i); // erases the characters till the first letter

      break;
    }
  }

  // looping through from the backend of the string
  for (int i = s.size() - 1; i >= 0; i--)
  {
    if (ispunct(s[i]) == 0) // Condtion will be true if letter is found at index i
    {
      int indexLast = i; // index is holding the first letter in the string

      s.erase(i + 1, s.size() - 1 - i); // erases the characters till the last letter

      break;
    }
  }

  // lowers all the letters
  for (int index = 0; index < s.size(); index++)
  {
    s[index] = tolower(s[index]);
  }

  // if the string passed in is only a punct
  for (int k = 0; k < s.size(); k++)
  {
    // cout << s[k] << " " << isalpha(s[k]) << endl;
    if (isalpha(s[k]) != 0) // true if there is a char (if it is a punct)
    {
      return s;
    }
  }

  return "";

  // TODO:  update this.
}


// GATHER tokens wiil take in a line of words from buildIndex and will parse each word and put it in one set
//Before it puts the word in a set I will first clean the token, calling the "cleanToken" function. 
//If the token is a empty string then the token is inserted within a set
set<string> gatherTokens(string text)
{

  set<string> tokens;

  string temp;

  stringstream s(text);

  while (s >> temp)
  {
    // if a empty string is passed in
    if (cleanToken(temp) != "")
    {
      tokens.insert(cleanToken(temp)); // inserts each cleaned token into the set
    }
  }

  return tokens; 
}

//This function will read in the file from the user when this function is called within "searchEngine" 
//Two string variables are declared where one string will hold the url and the other will hold a line of words
//The "gatherTokens" function is called where each token is cleaned within that line and put into one set
//We know that all those tokens hold a common url, so in the function we loop thru the set of words and 
//make each token as a key and the url we have will be the value for each token within the current set
//This will create a inverted index, where a key(token) can have more than one value(our value is a set, so we can store more than one url)
int buildIndex(string filename, map<string, set<string>> &index)
{

  fstream infile;
  infile.open(filename); // opens the file
  string urlString;
  string tempString;
  int counter = 0; // returns the count of web pages that were processed and added to the index.
  set<string> tokenSet;

  //creative component
  //creativeComponent("stop.txt"); 

  if (!infile.is_open())
  {
    return 0;
  }

  while (!infile.eof())
  {
    getline(infile, urlString); //gets the url text and stores it inside urlString

    if (urlString == "")
    {
      continue;
    }

    getline(infile, tempString); //stores the line of words inside tempString 
    tokenSet = gatherTokens(tempString); // parses the line and will return each word

    for (auto s : tokenSet)
    {
      index[s].insert(urlString); // for each token in that set it will add the respective url
    }

    counter++;
  }

  return counter;
}

//This function will take care of three operations
//One of the possible operations this function can handle is finding the intersection ('+') between two tokens
//First token within the sentence will never start with a '-' or '+' character
//So we will clean the token calling the "cleanToken" function and then we will check if the token is within the map
//If so we will store the tokens values into the result set
//I is then incremented within the loop and we will see if the next token contains either ('+') or ('-') operations
//If so we repeat the same process and will store the value of the token within a set and store the result set elements into another set
//Clear the result set, compare the two sets and store the result of the two sets within the result vector
set<string> findQueryMatches(map<string, set<string>> &index, string sentence)
{
  set<string> result;
  vector<string> vec1;

  stringstream s(sentence); //parses the text
  string temp; //reads in words 
  string query; //holds the word in the text
  string wordResult;
  string tempWord;

  //sets declaration
  set<string> set1;
  set<string> set2;
  set<string> set3;
  set<string> set4;

  // fish +pizza +indico apple
  while (s >> temp)
  {
    vec1.push_back(temp); // vector will hold all parsed words
  }

  for (int i = 0; i < vec1.size(); i++)
  {
  
    query = vec1.at(i);
    // checks if first character in the word is == to '+'
    if (query.at(0) == '+')
    {
      tempWord = cleanToken(query);
      if (index.count(tempWord) == 1) // check if tempWord is within the index map
      {
        set2 = (index[tempWord]); //.begin(), index[tempWord].end()); //stores the set of urls of tempWord into set2
      }

      set1 = result; // stores set of urls in result into set1
      result.clear();

      set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(result, result.begin()));
      set2.clear();
     
    }

    else if (query.at(0) == '-')
    {
      tempWord = cleanToken(query); //cleans the word
      if (index.count(tempWord) == 1)
      {
        set4.insert(index[tempWord].begin(), index[tempWord].end()); //
      }

      set3 = result; // stores the set of urls in result into set3
      result.clear();
    
      set_difference(set3.begin(), set3.end(), set4.begin(), set4.end(), inserter(result, result.begin())); //using algorithm libary to check the difference between the sets
      set4.clear(); 
    }

    else
    {
      wordResult = cleanToken(query);
      if (index.count(wordResult) == 1)
      {
        result.insert(index[wordResult].begin(), index[wordResult].end()); //stores the keys set of urls inside the result set
      }
    }
  }

  return result;
}

//This function is where read in the file the user passes in and call "buildIndex" passing in the file and the map created in this function
//Following outputs are called within the function 
void searchEngine(string filename)
{
  int inputResult;
  string userInput;
  string input;
  set<string> finalResult;
  map<string, set<string>> index;
  inputResult = buildIndex(filename, index);

  cout << "Stand by while building index..." << endl;
  cout << "Indexed " << inputResult << " pages containing " << index.size() << " unique terms" << endl;
  cout << endl; 

  while (true)
  {
    cout << "Enter query sentence (press enter to quit): ";
    getline(cin, userInput);

   if(userInput == "")
   {
    break; 
   }
/*---------- Creative Component ----------*/
  //  else if(userInput == "creative")
  //  {
  //   string file = "stop.txt"; 
  //   creativeComponent(file, index); 
    
  //  }
    
    finalResult = findQueryMatches(index, userInput);

    int numberOfMatches = finalResult.size();

    cout << "Found " << numberOfMatches << " matching pages" << endl;
    //loop thru the set of token values(urls)
    for (auto &display : finalResult)
    {
      cout << display << endl;
    }
    cout << endl; 
    
  }

  cout << "Thank you for searching!" << endl;

}
