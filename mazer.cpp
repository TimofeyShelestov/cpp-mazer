#include <iostream>
#include "maze_tools.h"
#include <string>

using namespace std;

bool is_number(const string& str) {
  if (str.empty()) return false;
  for (char c : str) {
    if (!isdigit(c)) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  int rows, cols; 

  if (argc == 1) {
    cerr << "No arguments provided. Type --help for help" << endl;
  }

  for (int i = 1; i < argc; ++i) {
    string arg = argv[i];

    if (arg == "--help") {
      cout << "To generate maze provide arguments for rows and cols of the maze. (Either -r and -c or --rows and --cols)" << endl;
      return 1;
    }

    if (arg == "-r" || arg == "--rows") {
      if (i + 1 < argc && is_number(argv[i+1])) {
        rows = stoi(argv[++i]);
      } else {
        cerr << "No value was provided for argument 'rows'" << endl;
        return 1;
      }
    } else if (arg == "-c" || arg == "--cols") {
      if (i + 1 < argc && is_number(argv[i+1])) {
        cols = stoi(argv[++i]);
      } else {
        cerr << "No value was provided for argument 'cols'" << endl;
        return 1;
      }
    } else {
      cerr << "Please provide values for rows and cols of the maze. --help for help" << endl;
      return 1;
    }
  }
  runMazer(rows, cols);
  return 0;
}