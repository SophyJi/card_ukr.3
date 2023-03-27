// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include "Card.h"
#include <array>
#include <string>
#include <fstream>
using namespace std;



  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack :: Pack() {
      // array<Card, PACK_SIZE> cards;
      int suit = 4;
      int ranks = 13;
      int init_rank = 7;
      next = 0;
      for (int i = 0; i < suit; i++) {
          for (int j = init_rank; j < ranks; j++) {
            string ranks = RANK_NAMES_BY_WEIGHT[j];
            string suits = SUIT_NAMES_BY_WEIGHT[i];
            Card temp(ranks, suits);
            cards[(j - init_rank) + i * 6] = temp;
          }
      }


  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack :: Pack(std::istream& pack_input) {
    string rank;
    string useless;
    string suit;
    next = 0;
    for(int i = 0; i < PACK_SIZE; i++) {
      pack_input >> rank >> useless >> suit;
      Card temp(rank, suit);
      cards[i] = temp;
    }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack :: deal_one() {
    next++;
    return cards[next - 1];
  }
  // EFFECTS: Resets next index to first card in the Pack
  void Pack :: reset() {
    next = 0;
    return;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  // //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack :: shuffle() {
    int n = 0;
    next = 0;
    while(n < 7) {
      int half = PACK_SIZE / 2;
      array<Card, PACK_SIZE> temp1;
      for (int i = 0; i < PACK_SIZE; i++) {
        temp1[i] = cards[i];
      }
      for (int j = 0; j < half; j++) {
        cards[(j * 2) + 1] = temp1[j];
      }
      for (int k = half; k < PACK_SIZE; k++) {
        cards[(k - half) * 2] = temp1[k];
      }
      n++;
    }
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack :: empty() const {
      //return Pack.PACK_SIZE == 0;
      if (next == PACK_SIZE) {
        return true;
      } else {
        return false;
      }
  }

