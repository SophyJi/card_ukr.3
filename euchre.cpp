// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cassert>
#include "Player.h"
#include "Card.h"
#include "Pack.h"
using namespace std;
struct winner {
    int whoOrder;
    int trick1;
    int trick2;
};
struct Initial {
    string pack_filename;
    string shuf;
    int points;
    int times; //count for Hand
    int count1; //player0 and 2
    int count2; //player1 and 3
    int dealer;
    Pack pack;
    vector<Player*> players;

};
struct Starter {
    int index;
    int countRound;
    int nextLed;
    int firstLeader;
    bool is_dealer;
    int round;
    bool order;
    Card trump;
    string order_up_suit;

};
bool error_message(int argc, char *argv[]);
void play_game(Initial* init, Starter *start, winner *win);
void initial(Initial *init);
void start_play(Initial* init, Starter *start);
void start_while(Starter *start, Initial* init);
void dealer(Starter *start, Initial* init);
void play_win(Initial* init, Starter *start, winner *win);
void cout_winner(winner *win, Initial* init);
void output_win(Initial* init);
void dealCards(Pack &pack, vector<Player*> &players, int dealer);
int playAround(vector<Player*> &players, string order_up_suit,
               int leaderIndex);
void countWinner(winner *win, int &count1,
                 int &count2, vector<Player*> &players);
int getNextIn(int leaderIndex, vector<Player*> &players, int next);

int main(int argc, char *argv[]) {
    if(error_message(argc, argv)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
    }
    for (int i = 0; i < 12; ++i) {
        cout << argv[i] << " ";
    }
    winner *win = new winner;
    Initial *init = new Initial;
    cout << endl;
    init -> pack_filename = argv[1];
    init -> shuf = argv[2];
    init -> points = atoi(argv[3]);
    initial(init);
    ifstream input;
    input.open(init -> pack_filename);
    if (!input.is_open()){
        cout << "Error opening " << init -> pack_filename << endl;
        return -1;
    }
    init -> pack = Pack(input);
    //initial1(init, argv);
    Player *player0 = Player_factory(argv[4], argv[5]);
    Player *player1 = Player_factory(argv[6], argv[7]);
    Player *player2 = Player_factory(argv[8], argv[9]);
    Player *player3 = Player_factory(argv[10], argv[11]);
    init -> players.push_back(player0);
    init -> players.push_back(player1);
    init -> players.push_back(player2);
    init -> players.push_back(player3);
    Starter *start = new Starter;
    play_game(init, start, win);
    output_win(init);
    delete start;
    delete init;
    delete win;
    return 0;
    
}
bool error_message(int argc, char *argv[]) {
    string shuf1 = "shuffle";
    string shuf2 = "noshuffle";
    string play1 = "Simple";
    string play2 = "Human";
    if (argc != 12) {
        return true;
    } else if (atoi(argv[3]) > 100 ||  atoi(argv[3]) < 1) {
        return true;
    } else if (argv[2] != shuf1 && argv[2] != shuf2) {
        return true;
    } else if (argv[5] != play1 && argv[5] != play2) {
        return true;
    } else {
        return false;
    }

}
void play_game(Initial* init, Starter *start, winner *win) {
    while (init -> count1 < init -> points && init -> count2 < init -> points){
        start_play(init, start);
        while(!start -> order) {
            start_while(start, init);
        }
        dealer(start, init);
        play_win(init, start, win);
        cout_winner(win, init);
    }
}
void initial(Initial* init) {
    init -> times = 0; //count for Hand
    init -> count1 = 0; //player0 and 2
    init -> count2 = 0; //player1 and 3
    init -> dealer = 0; //dealer is the index of dealer each hand
}
void start_play(Initial* init, Starter *start) {
    cout << "Hand " << init -> times << endl;
    cout << init -> players[init -> dealer] -> get_name() << " deals" << endl;
    start -> index = 0;
    start -> countRound = 0;
    start -> nextLed = 0;
    if (init -> shuf == "shuffle"){
        init -> pack.shuffle();
    }
    dealCards(init -> pack, init -> players, init -> dealer);
    ++(init -> times);
    start -> is_dealer = false;
    start -> round = 1;
    start -> order_up_suit = "";
    start -> trump = init -> pack.deal_one();
    cout << start -> trump << " turned up" << endl;
    start -> order = false;
    start -> index = init -> dealer + 1;
    start -> firstLeader = init -> dealer + 1;
    if (start -> firstLeader == 4){
        start -> firstLeader = 0;
    }
}
void start_while(Starter *start, Initial* init) {
            if (start -> index == 4){
                start -> index = 0;
            }
            if (start -> index == init -> dealer){
                start -> is_dealer = true;
            }
            if (start -> countRound == 4){
                ++(start -> round);
            }
            ++(start -> countRound);
            start -> order = init ->
    players[start -> index] -> make_trump(start -> trump,
            start -> is_dealer, start -> round, start -> order_up_suit);
            if (!start -> order){
                cout << init -> players[start -> index] -> get_name() << " passes" << endl;
            }else{
                cout << init -> players[start -> index] -> get_name() << " orders up "
                << start -> order_up_suit << endl;
            }
            ++(start -> index);
            start -> is_dealer = false;
}
void dealer(Starter *start, Initial* init) {
    if (start -> round == 1){
        init -> players[init -> dealer] -> add_and_discard(start -> trump);
        }
        ++(init -> dealer);
        if ((init -> dealer) == 4){
            (init -> dealer) = 0;
        }
        cout << endl;
}
void play_win(Initial* init, Starter *start, winner *win) {
        win -> trick1 = 0;
        win -> trick2 = 0;
        --(start -> index);
        win -> whoOrder = start -> index;
        start -> nextLed = playAround(init -> players, start -> order_up_suit,
        start -> firstLeader);
        start -> index = start -> nextLed;
        if (start -> index == 1 || start -> index == 3){
            win -> trick2 = win -> trick2 + 1;
        }else{
            win -> trick1 = win -> trick1 + 1;
        }
        for (int i = 1; i < 5; ++i){
            start -> nextLed = playAround(init -> players, start -> order_up_suit,
            start -> index);
            start -> index = start -> nextLed;
            if (start -> index == 1 || start -> index == 3){
                win -> trick2 = win -> trick2 + 1;
            }else{
                win -> trick1 = win -> trick1 + 1;
            }
        }

}
void cout_winner(winner *win, Initial* init) {
    countWinner(win, init -> count1, init -> count2, init -> players);
        cout << init -> players[0] -> get_name() << " and "
        << init -> players[2] -> get_name() << " have " << init -> count1
        << " points" << endl;
        cout << init -> players[1] -> get_name() << " and "
        << init -> players[3] -> get_name() << " have " << init -> count2
        << " points" << endl << endl;
        if (init -> shuf != "shuffle"){
            init -> pack.reset();
        }
}
void output_win(Initial* init) {
    if (init -> count1 > init -> count2){
        cout << init -> players[0] -> get_name() << " and "
        << init -> players[2] -> get_name() << " win!" << endl;
    }else if (init -> count2 > init -> count1){
        cout << init -> players[1] -> get_name() << " and "
        << init -> players[3] -> get_name() << " win!" << endl;
    }
    for (int i = 0; i < int(init -> players.size()); ++i) {
      delete init -> players[i];
    }
}
void dealCards(Pack &pack, vector<Player*> &players, int dealer){
    int countForRound = 0;
    int dealIn = dealer + 1;
    while (countForRound < 4){
        if (dealIn == 4){
            dealIn = 0;
        }
        if (countForRound % 2 == 0){
            for (int i = 0; i < 3; ++i){
                players[dealIn] -> add_card(pack.deal_one());
            }
        }else{
            for (int i = 0; i < 2; ++i){
                players[dealIn] -> add_card(pack.deal_one());
            }
        }
        ++dealIn;
        ++countForRound;
    }
    countForRound = 0;
    dealIn = dealer + 1;
    while (countForRound < 4){
        if (dealIn == 4){
            dealIn = 0;
        }
        if (countForRound % 2 == 0){
            for (int i = 0; i < 2; ++i){
                players[dealIn] -> add_card(pack.deal_one());
            }
        }else{
            for (int i = 0; i < 3; ++i){
                players[dealIn] -> add_card(pack.deal_one());
            }
        }
        ++dealIn;
        ++countForRound;
    }
}
int playAround(vector<Player*> &players, string order_up_suit,
               int leaderIndex){
    Card led = players[leaderIndex] -> lead_card(order_up_suit);
    cout << led << " led by " << players[leaderIndex] -> get_name() << endl;
    vector<Card> cards;
    cards.push_back(led);
    Card playCard;
    int nextLed = 0;
    int countForRound = 0;
    int playerIn = leaderIndex + 1;
    while (countForRound < 3){
        if (playerIn == 4){
            playerIn = 0;
        }
        playCard = players[playerIn] -> play_card(led, order_up_suit);
        cards.push_back(playCard);
        cout << playCard << " played by "
        << players[playerIn] -> get_name() << endl;
        ++playerIn;
        ++countForRound;
    }
    Card *high = &cards[0];
    for (size_t i = 0; i < cards.size(); ++i){
        if (Card_less(*high, cards[i], led, order_up_suit)){
            high = &cards[i];
            nextLed = static_cast<int>(i);
        }
    }
    nextLed = getNextIn(leaderIndex, players, nextLed);
    return nextLed;
}

void countWinner(winner *win, int &count1,
                 int &count2, vector<Player*> &players){
    if (win -> whoOrder == 0 || win -> whoOrder == 2){
        if (win -> trick1 > win -> trick2 && win -> trick1 != 5){
            ++count1;
            cout << players[0] -> get_name() << " and "
            << players[2] -> get_name() << " win the hand" << endl;
        }else if (win -> trick1 > win -> trick2 && win -> trick1 == 5){
            count1 = count1 + 2;
            cout << players[0] -> get_name() << " and "
            << players[2] -> get_name() << " win the hand" << endl;
            cout << "march!" << endl;
        }else{
            count2 = count2 + 2;
            cout << players[1] -> get_name() << " and "
            << players[3] -> get_name() << " win the hand" << endl;
            cout << "euchred!" << endl;
        }
    }else{
        if (win -> trick2 > win -> trick1 && win -> trick2 != 5){
            ++count2;
            cout << players[1] -> get_name() << " and "
            << players[3] -> get_name() << " win the hand" << endl;
        }else if (win -> trick2 > win -> trick1 && win -> trick2 == 5){
            count2 = count2 + 2;
            cout << players[1] -> get_name() << " and "
            << players[3] -> get_name() << " win the hand" << endl;
            cout << "march!" << endl;
        }else{
            count1 = count1 + 2;
            cout << players[0] -> get_name() << " and "
            << players[2] -> get_name() << " win the hand" << endl;
            cout << "euchred!" << endl;
        }
    }
}

int getNextIn(int leaderIndex, vector<Player*> &players, int next){
    int nextLed = next;
    if (leaderIndex == 1){
        if (nextLed != 3){
            nextLed = nextLed + 1;
        }else{
            nextLed = 0;
        }
    }else if (leaderIndex == 2){
        if (nextLed < 2){
            nextLed = nextLed + 2;
        }else{
            nextLed = nextLed - 2;
        }
    }else if (leaderIndex == 3){
        if (nextLed == 0){
            nextLed = 3;
        }else{
            nextLed = nextLed - 1;
        }
    }
    cout << players[nextLed] -> get_name()
    << " takes the trick" << endl << endl;
    return nextLed;
}
