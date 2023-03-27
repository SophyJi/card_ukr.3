// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack *pack = new Pack();
    Card first = pack->deal_one();
    //cout << "sophy:" << first.get_rank()  << "!!!" << first.get_suit() << endl;
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// Add more tests here

TEST_MAIN()
