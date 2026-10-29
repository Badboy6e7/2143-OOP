#include "poker.hpp"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  Deck deck;

  deck.shuffle();

  Hand hand;

  for (int i = 0; i < 5; i++) {
    hand.addCard(deck.deal());
  }

cout << "              =============================\n";
cout << "                   FIVE-CARD DRAW POKER\n";
cout << "              =============================\n\n";


  hand.sortHand();

  cout << "                      Your hand:\n";
  cout << hand << endl;

  return 0;
}