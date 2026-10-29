
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

std::map<int, std::string> rankName = {{1, "A"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"}, {8, "8"}, {9, "9"}, {10, "10"}, {11, "J"}, {12, "Q"}, {13, "K"}, {14, "A"}};
std::map<int, std::string> suitName = {{0, "♣"}, {1, "♦"}, {2, "♥"}, {3, "♠"}};

int main()
{
  int rank = 14;
  int suit = 3;

  std::cout << rankName.at(rank) << "," << suitName.at(suit) << endl;
  cout << "♣" << "♦" << "♥" << "♠" << endl;

  return 0;
}