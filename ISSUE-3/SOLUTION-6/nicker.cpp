//This program is a solution for http://olimex.wordpress.com/2013/04/05/weekend-programming-challenge-issue-3/
//by Mikhail Soloviev, owner of http://www.vestochka.com
//Compile this file using Visual Studio Express 2010
//When running either use console redirection from file, or manually type-in words separated with Enter
//All spaces will be removed due to the task is about "words"; finish input with EOF or empty line
//Several known issues e.g. Ansi/Unicode not fixed due to out of contest
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

list<string> Words, Nicks;

void ReadWords(void) {
  string st;
  list<string>::iterator it;
  cout << "Enter words ended with empty line:"  << endl;
  while (getline(cin, st)) {
    st.erase(remove_if(st.begin(), st.end(), isspace), st.end()); //remove spaces; we could trim&cut if task would be defined better
    if (st.empty())
      return;
    transform(st.begin(), st.end(), st.begin(), ::tolower);
    if (Words.end() != (it = find(Words.begin(), Words.end(), st))) { 
      //cout << "<WARNING>Duplicated word was ignored: " << st << endl; 
      continue; //remove not allowed duplicates
    }
    else {
      Words.push_back(st);
    }
  } //while
}

string MakeOneNick(const list<string>::iterator itw) {
  string str;
  size_t wlen=(*itw).length();
  for (size_t size=1; size<wlen; size++) {
    for (size_t off=0; off<=(wlen-size); off++) {
      str = (*itw).substr(off, size);
      bool suitable=true;
      //cout << *itw << " wlen="<< wlen << " size=" << size << " off=" << off << " str=" << str << endl;
      for (list<string>::iterator it = Words.begin(); it != Words.end(); it = next(it)) {
        if ((*it != *itw) && (string::npos != (*it).find(str))) {
          suitable = false; //found as usual ;-(
          break;
        }
      }//for all other words
      if (suitable)
        return str; //bingo
    }//for off
  }//for size
  return *itw;
}

void TypeResults(void) {
  while (Words.size() && Nicks.size()){
    cout << Words.front() << " -> " << Nicks.front() << endl;
    Words.pop_front(); Nicks.pop_front();
  }
}

int main() {
  ReadWords();
  for (list<string>::iterator itw = Words.begin(); itw != Words.end(); itw = next(itw))
    Nicks.push_back(MakeOneNick(itw));
  TypeResults();
  return 0;
}