// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "cassert"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;
// Project UID 1d9f47bfc76643019cfbf037641defe1


#include "Card.h"
#include "cassert"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}
TEST(test_card1) {
    Card c1(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump1 = Card :: SUIT_CLUBS;
    ASSERT_FALSE(c2.is_right_bower(trump1));
    ASSERT_TRUE(c2.is_left_bower(trump1));
    ASSERT_TRUE(c1.is_trump(trump1));
    ASSERT_EQUAL(Card ::SUIT_CLUBS,c2.get_suit(trump1))
    Card led1(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(c1, c2, led1, trump1));
    ASSERT_EQUAL(Card::RANK_EIGHT, c1.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, c1.get_suit());

}
TEST(test_card2) {
    Card c1(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump1 = Card :: SUIT_CLUBS;
    ASSERT_FALSE(c1.is_right_bower(trump1));
    ASSERT_FALSE(c2.is_left_bower(trump1));
    Card led2(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(c2, c1, led2, trump1));
    ASSERT_EQUAL(Card::RANK_ACE, c1.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c1.get_suit());

}
TEST(test_difference) {
    Card c1(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_FALSE(operator<(c2, c3));
    ASSERT_TRUE(operator!=(c1, c2));
    ASSERT_FALSE(operator>(c1, c3));
    ASSERT_FALSE(operator==(c1, c2));
    ASSERT_TRUE(c3.is_face());
    ASSERT_FALSE(c1.is_face());
}
TEST(test_os_less) {
    Card c1(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c3(Card::RANK_KING, Card::SUIT_SPADES );
    ASSERT_TRUE(operator>(c1, c3));
    ASSERT_TRUE(operator>=(c1, c3));
    ASSERT_FALSE(operator<(c2, c3));
    ASSERT_FALSE(operator<=(c2, c3));
    string suit = "Hearts";
    cout << "Assert : Diamonds, the actural output is " << Suit_next(suit) <<
    endl;
    cout << "Assert : Ace of Hearts, the actural output is ";
    operator<<(cout, c1);
}
TEST(test_less) {
    Card c1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump2 = Card :: SUIT_HEARTS;
    ASSERT_TRUE(operator>=(c1, c2));
    ASSERT_TRUE(operator<=(c1, c2));
    ASSERT_TRUE(operator==(c1, c2));
    ASSERT_TRUE(Card_less(c2, c3, trump2));
    Card led3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(operator==(c1, led3));
    ASSERT_TRUE(Card_less(c1, c3, led3, trump2));

}
TEST(test_cardless) {
    Card c1(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c4(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card c6(Card::RANK_KING, Card::SUIT_SPADES);
    string trump1 = Card :: SUIT_DIAMONDS;
    ASSERT_TRUE(Card_less(c1, c2, trump1));
    ASSERT_FALSE(Card_less(c1, c3, trump1));
    ASSERT_FALSE(Card_less(c4, c1, trump1));
    ASSERT_TRUE(Card_less(c5, c6, trump1));
    Card led4(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(c2, c1, led4, trump1));
    ASSERT_TRUE(Card_less(c3, c2, led4, trump1));
    ASSERT_TRUE(Card_less(c3, c1, led4, trump1));
    ASSERT_TRUE(Card_less(c3, c4, led4, trump1));
    ASSERT_TRUE(Card_less(c6, c2, led4, trump1));
    ASSERT_TRUE(Card_less(c5, c6, led4, trump1));


}
TEST(same1){
    Card c1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c3(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(operator<=(c2, c1));
    ASSERT_TRUE(operator>=(c3, c2));
    string trump1 = Card :: SUIT_SPADES;
    ASSERT_TRUE(c4.is_right_bower(trump1));
    ASSERT_TRUE(c3.is_left_bower(trump1));
    ASSERT_FALSE(Card_less(c1, c2, trump1));
    ASSERT_TRUE(Card_less(c1, c3, trump1));
    ASSERT_TRUE(Card_less(c2, c4, trump1));
    ASSERT_TRUE(Card_less(c3, c4, trump1));
    Card led4(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(c2, c1, led4, trump1));
    ASSERT_FALSE(Card_less(c1, c2, led4, trump1));
    ASSERT_TRUE(Card_less(c3, c4, led4, trump1));
}
TEST(same2){
    Card c1(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card c2(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c3(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(operator<=(c1, c2));
    ASSERT_TRUE(operator>=(c3, c2));
    string trump1 = Card :: SUIT_SPADES;
    ASSERT_TRUE(c4.is_left_bower(trump1));
    ASSERT_TRUE(Card_less(c1, c2, trump1));
    ASSERT_TRUE(Card_less(c2, c4, trump1));
    ASSERT_TRUE(Card_less(c3, c4, trump1));
    Card led4(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(c1, c2, led4, trump1));
    ASSERT_FALSE(Card_less(c3, c2, led4, trump1));
    ASSERT_TRUE(Card_less(c3, c4, led4, trump1));
}
//Add more test cases here

TEST_MAIN()
