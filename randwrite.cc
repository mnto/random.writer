/********************************************************
 *                                                      *
 * File name: randwrite.cc                              *
 * Name: Minh To                                        *
 * Project: Random Writer                               *
 * Date: 11/05/15                                       *
 *                                                      *
 * This program takes in a command line containing a    *
 * non-zero interger k, a length, input file, and output*
 * file. If any of the arguments are invalid, the       *
 * program will throw an error. Otherwise, this program *
 * picks k consective characters from the input file as *
 * the initial seed and begin a random writing process. *
 * The output file contains the result of this process. *
 *                                                      *
 *******************************************************/

#include <fstream>
#include "list.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// size_t find_from(char, size_t, list&) 
// POST: finds the first index where the letter appears in source, given a 
// starting index
size_t find_from(char letter, size_t index, list & source)
{
  for (size_t i = index; i < source.size(); i++) {
    if (source.get(i) == letter)
      return i;
  }
  return source.size();
}

// list followers(string&, list&))
// POST: creates a list of all the possibilities following the given seed in 
// the source.
list followers(string & seed, list & source)
{
  list charlist; // list containing all possibilities
  size_t i = source.find(seed[0]); // first instance of the first character
  while (i < source.size()) {
    string letters; // possible seed
    for (size_t j = i; j < source.size() and j < i + seed.size(); j++) 
      letters += source.get(j);
    if (letters == seed and i + seed.size() < source.size()) 
      charlist.add(source.get(i+seed.size()), charlist.size());
    i = find_from(seed[0], i + 1, source); // next instance of possible seed
  }
  return charlist;
}

// size_t random(list&, size_t)
// POST: returns a random non-zero integer between 0 and source.size() - k
size_t random(list & source, size_t k)
{
  srand(time(NULL));
  return rand() % (source.size() - k);
}

int main(int argc, char ** argv)
{
  ifstream in(argv[3]); // read in input file
  ofstream out(argv[4]); // output file
  char c;
  list text; // list contains all characters in input file
  while (in.get(c)) 
    text.add(c, text.size());
  if (atoi(argv[1]) < 0) { 
    cout << "Invalid input" << endl;
    exit(1);
  }
  if (atoi(argv[2]) < 0) {
    cout << "Invalid input" << endl;
    exit(1);
  }
  size_t k = atoi(argv[1]); // number of characters in seed
  size_t length = atoi(argv[2]); // number of characters get printed out
  // test input
  if (text.size() < k){
    cout << "Invalid source" << endl;
    exit(1);
  }
  if (not in.is_open()) {
    cout << "File cannot be opened for reading" << endl;
    exit(1);
  }
  if (not out.is_open()) {
    cout << "File cannot be opened for reading" << endl;
    exit(1);
  }
  // initialize seed
  string _seed = "";
  size_t index = random(text, k);
  for (size_t i = index; i < index + k; i++) 
    _seed += text.get(i);
  // randomly generates letters as long as the desired length has not been 
  // reached
  size_t count = 0;
  while (count < length) {
    list poss = followers(_seed, text); // list of the possibilities of a seed
    if (poss.size() > 0) { // when seed is not at the end of the source
      _seed = _seed.substr(1) + poss.get(random(poss, 0)); // update seed
      out.put(_seed[k-1]); 
    }
    else { // when seed is at the end of the source
      // choose a new seed
      _seed = "";
      index = random(text, k);
      for (size_t i = index; i < index + k; i++) 
	_seed += text.get(i);
      count--;
    }
    count++;
  }
}




