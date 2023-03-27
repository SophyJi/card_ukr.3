// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

//EFFECTS Initializes Card to the Two of Spades
Card :: Card() : rank(RANK_TWO), suit(SUIT_SPADES){}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card :: Card(const std::string &rank_in, const std::string &suit_in) :
rank(rank_in), suit(suit_in){}

//EFFECTS Returns the rank
string Card :: get_rank() const{
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
string Card :: get_suit() const{
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card :: get_suit(const std::string &trump) const{
    if (rank == RANK_JACK && suit == Suit_next(trump)){
            return trump;
    }
    return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card :: is_face() const{
    if (rank == RANK_ACE || rank == RANK_JACK
        || rank == RANK_QUEEN || rank == RANK_KING){
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card :: is_right_bower(const std::string &trump) const{
    if (rank == RANK_JACK && suit == trump){
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card :: is_left_bower(const std::string &trump) const{
    if (rank == RANK_JACK && suit == Suit_next(trump)){
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card :: is_trump(const std::string &trump) const{
    if (get_suit() == trump || is_left_bower(trump)){
        return true;
    }
    return false;
}

int get_index(const Card &c1) {
    for(size_t i = 0; i < NUM_RANKS; i++) {
        if(c1.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            return static_cast<int>(i);
        }
    }
    return 0;

}

int get_suit_index(const Card &c1){
    for(size_t i = 0; i < NUM_SUITS; i++) {
        if(c1.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
            return static_cast<int>(i);
        }
    }
    return 0;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    if (get_index(lhs) == get_index(rhs)){
        if (get_suit_index(lhs) < get_suit_index(rhs)){
            return true;
        }else{
            return false;
        }
    }else if (get_index(lhs) < get_index(rhs)){
        return true;
    }else{
        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    return (operator<(lhs, rhs) || operator==(lhs, rhs));
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
    if (get_index(lhs) == get_index(rhs)){
        if (get_suit_index(lhs) > get_suit_index(rhs)){
            return true;
        }else{
            return false;
        }
    }else if (get_index(lhs) > get_index(rhs)){
        return true;
    }else{
        return false;
    }
    //return get_index(lhs) > get_index(rhs);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
    return (operator>(lhs, rhs) || operator==(lhs, rhs));
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    return (get_index(lhs) == get_index(rhs)
            && lhs.get_suit() == rhs.get_suit());
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    return (get_index(lhs) != get_index(rhs)
            || get_suit_index(lhs) != get_suit_index(rhs));
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
    if(suit == "Hearts") {
        return "Diamonds";
    } else if (suit == "Diamonds") {
        return "Hearts";
    } else if (suit == "Spades") {
        return "Clubs";
    } else {
        return "Spades";
    }
    return "";
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if (a.is_trump(trump) && b.is_trump(trump)){
    if (a.is_right_bower(trump)){
           return false;
    }else if (b.is_right_bower(trump)){
           return true;
    }else if (a.is_left_bower(trump)){
           return false;
    }else if (b.is_left_bower(trump)){
           return true;
    }else{
        return operator<(a, b);
    }
    }else if (a.is_trump(trump)) {
        return false;
    }else if (b.is_trump(trump)) {
        return true;
    }else {
        return operator<(a, b);
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if (a.is_trump(trump) && b.is_trump(trump)){
    if (a.is_right_bower(trump)){
           return false;
    }else if (b.is_right_bower(trump)){
           return true;
    }else if (a.is_left_bower(trump)){
           return false;
    }else if (b.is_left_bower(trump)){
           return true;
    }else{
        return operator<(a, b);
    }
    }else if (a.is_trump(trump)) {
        return false;
    }else if (b.is_trump(trump)) {
        return true;
    }else if (a.get_suit() == led_card.get_suit()
              && b.get_suit() == led_card.get_suit()){
        return operator<(a, b);
    }else if (a.get_suit() == led_card.get_suit()){
        return false;
    }else if (b.get_suit() == led_card.get_suit()){
        return true;
    }else{
        return operator<(a, b);
    }
    return operator<(a, b);
}
// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
