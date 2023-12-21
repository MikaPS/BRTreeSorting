//-----------------------------------------------------------------------------
// Mika Peer Shalem, mpeersha
// 2023 Winter CSE101, PA8
// DictionaryTest.cpp
// Implements a Dictionary Test that includes access and manipulation functions.
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include "Dictionary.h"

using namespace std;

int main() {
  

   string s;
   int x;
   string S[] =   {
                    "juvenile",
                    "lavish",
                    "brash",
                    "experience",
                    "caption",
                    "agonizing",
                    "ship",
                    "statement",
                    "overt",
                    "brash",
                    "victorious",
                    "charge",
                    "company",
                    "magnificent",
                    "peaceful",
                    "found",
                    "shave",
                    "daffy",
                    "chin",
                    "coil",
                    "car",
                    "materialistic",
                    "indent",
                    "lead",
                    "plain",
                    "hypnotize",
                    "handsomely",
                    "envious",
                    "skillful",
                    "hideous",
                    "warn",
                    "shorten",
                    "conclude",
                    "whistle",
                    "cows",
                  };

   Dictionary A;
   Dictionary B;
   Dictionary C;
   cout << "A.size() = " << A.size() << endl  << A << endl;

    // insert some pairs into A
    for(int i=0; i<=34; i++){
      A.setValue(S[i], i+1);
    }
    // insert some pairs into B
    for(int i=34; i>=0; i--){
      B.setValue(S[i], 34-i);
    }
   
    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << "A.size() = " << A.size() << endl  << A.pre_string() << endl;
    cout << "B.size() = " << B.size() << endl  << B << endl;

    cout << "Val of hideous: " << A.getValue("hideous") << endl;
    A.getValue("hideous") += 30; 
    cout << "Val of hideous: " << A.getValue("hideous") << endl << endl;

    // call operator=()
    C = B;
    Dictionary D = B;
   
   cout << "C.size() = " << C.size() << endl  << C << endl;
   cout << "D.size() = " << D.size() << endl  << D << endl;

   B.setValue("juvenile", 101); // first word
   B.setValue("cows", 102); // last word
   B.setValue("victorious", 103); // same word twice
   B.setValue("victorious", 104);
   cout << "B.size() = " << B.size() << endl  << B << endl;

   // contains()
   cout << "C contains 'juvenile'? (1) " << C.contains("juvenile") << endl;
   cout << "C contains 'cows'? (1) " << C.contains("cows") << endl;
   cout << "C contains 'victorious'? (1) " << C.contains("victorious") << endl;
   C.remove("victorious");
   cout << "C contains 'victorious'? (0) " << C.contains("victorious") << endl;
   cout << endl;

   // getValue()
   cout << "C get value of 'juvenile'? " << C.getValue("juvenile") << endl;
   cout << "C get value of 'cows'? " << C.getValue("cows") << endl;
   C.remove("juvenile");
   cout << "C get value of 'lavish'? " << C.getValue("lavish") << endl;
   cout << endl;

   // clear() + equals()
   cout << "A == A? " << (A==A?"true":"false") << endl;
   cout << "A == D? " << (A==D?"true":"false") << endl;
   cout << "D == A? " << (D==A?"true":"false") << endl;
   cout << "C == D? " << (C==D?"true":"false") << endl;
   C.clear();
   cout << "empty C == D? " << (C==D?"true":"false") << endl;
   D.clear();
   cout << "empty C == empty D? " << (C==D?"true":"false") << endl;
   Dictionary E;
   cout << "empty C == empty E? " << (C==E?"true":"false") << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;
   cout << "D.size() = " << D.size() << endl  << D << endl;

   // remove()
   // remove from empty dict
   try{
      E.remove("cows");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   // remove the same key twice
   A.remove("cows");
   try{
      A.remove("cows");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   // remove a non exisiting key
   try{
      A.remove("random");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }   
   cout << endl << endl;

   // current methods
   for(A.begin(); A.hasCurrent(); A.next()){
      s = A.currentKey();
      x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   // do reverse iteration on A
   for(A.end(); A.hasCurrent(); A.prev()){
      s = A.currentKey();
      x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;
   B.begin();
   cout << "B begin key: " << B.currentKey() << " | B begin val: " << B.currentVal() << endl;
   B.next();
   cout << "B begin key: " << B.currentKey() << " | B begin val: " << B.currentVal() << endl;
   B.remove("brash");
   cout << "B current exist? " << B.hasCurrent() << endl;
   B.begin();
   cout << "B begin key: " << B.currentKey() << " | B begin val: " << B.currentVal() << endl;
   B.next();
   cout << "B begin key: " << B.currentKey() << " | B begin val: " << B.currentVal() << endl;
   cout << endl << endl;

   B.end();
   cout << "B end key: " << B.currentKey() << " | B end val: " << B.currentVal() << endl;
   B.prev();
   cout << "B end key: " << B.currentKey() << " | B end val: " << B.currentVal() << endl;
   B.remove("warn");
   B.end();
   cout << "B end key: " << B.currentKey() << " | B end val: " << B.currentVal() << endl;
   B.prev();
   cout << "B end key: " << B.currentKey() << " | B end val: " << B.currentVal() << endl;
}
