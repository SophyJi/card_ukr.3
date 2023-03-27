// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

class SimplePlayer : public Player{
private:
    string name;
    vector<Card> cards;
public:
    SimplePlayer(string player_name) : name(player_name){}
    
    virtual const std::string & get_name() const{
        return name;
    }
    
    virtual void add_card(const Card &c){
        assert(cards.size() < MAX_HAND_SIZE);
        cards.push_back(c);
    }
    
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std :: string &order_up_suit) const{
        assert(round == 1 || round == 2);
        if (round == 1){
            int count = 0;
            for (size_t i = 0; i < cards.size(); ++i){
                if (cards[i].is_face() &&
                    cards[i].is_trump(upcard.get_suit())){
                    ++count;
                }
            }
            if (count >= 2){
                order_up_suit = upcard.get_suit();
                return true;
            }else{
                return false;
            }
        }else{
            string temp;
            temp = Suit_next(upcard.get_suit());
            for (size_t i = 0; i < cards.size(); ++i){
                if (cards[i].is_face() && cards[i].is_trump(temp)){
                    order_up_suit = temp;
                    return true;
                }
            }
            if (is_dealer){
                order_up_suit = temp;
                return true;
            }
            return false;
        }
    }
    
    virtual void add_and_discard(const Card &upcard){
        assert(cards.size() >= 1);
        Card *lowestCard = &cards[0];
        for (size_t i = 0; i < cards.size(); ++i){
            if (Card_less(cards[i], *lowestCard, upcard.get_suit())){
                lowestCard = &cards[i];
            }
        }
        if (Card_less(upcard, *lowestCard, upcard.get_suit())){
            return;
        }
        for (size_t i = 0; i < cards.size(); ++i){
            if (cards[i] == *lowestCard){
                cards.erase(cards.begin() + i);
            }
        }
        add_card(upcard);
    }
    
    virtual Card lead_card(const std::string &trump){
        assert(cards.size() >= 1);
        Card *lead_card = &cards[0];
        bool all_trump = true;
        int index = 0;
        for (size_t i = 0; i < cards.size(); ++i){
            if (!cards[i].is_trump(trump)){
                all_trump = false;
            }
        }
        if (all_trump){
            for (size_t i = 0; i < cards.size(); ++i){
                if (Card_less(*lead_card, cards[i], trump)){
                    lead_card = &cards[i];
                    index = static_cast<int>(i);
                }
            }
            Card c = *lead_card;
            cards.erase(cards.begin() + index);
            return c;
        }else{
            vector<Card> not_cards;
            for (size_t i = 0; i < cards.size(); ++i){
                if (!cards[i].is_trump(trump)){
                    not_cards.push_back(cards[i]);
                }
            }
            Card *lead1 = &not_cards[0];
            for (size_t i = 0; i < not_cards.size(); ++i){
                if (not_cards[i] > *lead1){
                    lead1 = &not_cards[i];
                    //index = static_cast<int>(i);
                }
            }
            for (size_t i = 0; i < cards.size(); ++i){
                if (cards[i] == *lead1){
                    index = static_cast<int>(i);
                }
            }
            Card c = *lead1;
            cards.erase(cards.begin() + index);
            return c;
        }
    }
    
    virtual Card play_card(const Card &led_card, const std::string &trump){
        assert(cards.size() >= 1);
        bool all_trump = true;
        bool fit_suit = false;
        bool leadCard_istrump = false;
        bool has_trump = false;
        vector<Card> suit_cards;
        vector<Card> not_cards;
        vector<Card> trump_cards;
        int index = 0;
        for (size_t i = 0; i < cards.size(); ++i){
            if (!cards[i].is_trump(trump)){
                all_trump = false;
            }
            if (cards[i].get_suit() == led_card.get_suit()
                && !cards[i].is_trump(trump)){
                fit_suit = true;
                suit_cards.push_back(cards[i]);
            }
            if (led_card.is_trump(trump)){
                leadCard_istrump = true;
            }
            if (cards[i].is_trump(trump)){
                has_trump = true;
                trump_cards.push_back(cards[i]);
            }
        }
        if (!all_trump && fit_suit && !leadCard_istrump){
            Card *play_card = &suit_cards[0];
            for (size_t i = 0; i < suit_cards.size(); ++i){
                if (suit_cards[i] > *play_card){
                    play_card = &suit_cards[i];
                }
            }
            //cout << *play_card << " played by " << get_name() << endl;
            Card p = *play_card;
            //find the index of play_card
            for (size_t i = 0; i < cards.size(); ++i){
                if (cards[i] == *play_card){
                    cards.erase(cards.begin() + i);
                }
            }
            return p;
        }else if((!all_trump && !fit_suit && !leadCard_istrump)
                 || (leadCard_istrump && !has_trump)){
            for (size_t i = 0; i < cards.size(); ++i){
                if (!cards[i].is_trump(trump)){
                    not_cards.push_back(cards[i]);
                }
            }
            Card *play_card = &not_cards[0];
            for (size_t i = 0; i < not_cards.size(); ++i){
                if (not_cards[i] < *play_card){
                    play_card = &not_cards[i];
                }
            }
            //cout << *play_card << " played by " << get_name() << endl;
            Card p = *play_card;
            //find the index of play_card
            for (size_t i = 0; i < cards.size(); ++i){
                if (cards[i] == *play_card){
                    cards.erase(cards.begin() + i);
                }
            }
            return p;
        }else if (leadCard_istrump && has_trump){
            Card *play_card = &trump_cards[0];
            for (size_t i = 0; i < trump_cards.size(); ++i){
                if (Card_less(*play_card, trump_cards[i], trump)){
                    play_card = &trump_cards[i];
                }
            }
            //cout << *play_card << " played by " << get_name() << endl;
            Card p = *play_card;
            //find the index of play_card
            for (size_t i = 0; i < cards.size(); ++i){
                if (cards[i] == *play_card){
                    cards.erase(cards.begin() + i);
                }
            }
            return p;
        }
        else{
            Card *play_card = &cards[0];
            for (size_t i = 0; i < cards.size(); ++i){
               // cout << cards[i] << endl;
                //cout << Card_less(cards[i], *play_card, trump) << endl;
                if (Card_less(cards[i], *play_card, trump)){
                    play_card = &cards[i];
                    index = static_cast<int>(i);
                   // cout << cards[i] << endl;
                    //cout << Card_less(cards[i], *play_card, trump) << endl;
                }
            }
            //cout << *play_card << " played by " << get_name() << endl;
            Card p = *play_card;
            cards.erase(cards.begin() + index);
            return p;
        }
    }
        
};

class HumanPlayer : public Player{
private:
    string name;
    vector<Card> cards;
    virtual void printCard (vector<Card> in_cards) const{
        for (size_t i = 0; i < in_cards.size() - 1; ++i){
            for (size_t j = i + 1; j < in_cards.size(); ++j){
                if (in_cards[i] > in_cards[j]){
                    Card temp = in_cards[i];
                    in_cards[i] = in_cards[j];
                    in_cards[j] = temp;
                }
            }
        }
        for (size_t i = 0; i < in_cards.size(); ++i){
            cout << "Human player " << get_name()
            << "'s hand: [" << i << "] " << in_cards[i] << endl;
        }
    }
    
    virtual int findOrigin(int index, vector<Card> in_cards) const{
        for (size_t i = 0; i < in_cards.size() - 1; ++i){
            for (size_t j = i + 1; j < in_cards.size(); ++j){
                if (in_cards[i] > in_cards[j]){
                    Card temp = in_cards[i];
                    in_cards[i] = in_cards[j];
                    in_cards[j] = temp;
                }
            }
        }
        for (size_t i = 0; i < cards.size(); ++i){
            if (cards[i] == in_cards[index]){
                return static_cast<int>(i);
            }
        }
        return 0;
    }
    
public:
    HumanPlayer(string name_in) : name(name_in){}
    
    virtual const std::string & get_name() const{
        return name;
    }
    
    virtual void add_card(const Card &c){
        assert(cards.size() < MAX_HAND_SIZE);
        cards.push_back(c);
    }
    
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const{
        assert(round == 1 || round == 2);
        printCard(cards);
        if (round == 1){
            string suit_name = "";
            cout << "Human player " << get_name()
            << ", please enter a suit, or \"pass\":" << endl;
            cin >> suit_name;
            if (suit_name == upcard.get_suit()){
                order_up_suit = suit_name;
               // cout << get_name() << " orders up " << order_up_suit << endl;
                return true;
            }else{
              //  cout << get_name() << " passes" << endl;
                return false;
            }
        }else{
            string suit_name = "";
            cout << "Human player " << get_name()
            << ", please enter a suit, or \"pass\":" << endl;
            cin >> suit_name;
            if (suit_name == Suit_next(upcard.get_suit())){
                order_up_suit = suit_name;
                //cout << get_name() << " orders up " << order_up_suit << endl;
                return true;
            }else if(is_dealer){
                order_up_suit = Suit_next(upcard.get_suit());
                //cout << get_name() << " orders up " << order_up_suit << endl;
                return true;
            }else{
               // cout << get_name() << " passes" << endl;
                return false;
            }
        }
    }
    
    virtual void add_and_discard(const Card &upcard){
        assert(cards.size() >= 1);
        printCard(cards);
        cout << "Discard upcard: [-1]" << endl;
        int index = 0;
        cout << "Human player " << get_name()
        << ", please select a card to discard:" << endl;
        cin >> index;
        cards.erase(cards.begin() + findOrigin(index, cards));
        cards.push_back(upcard);
    }
    
    virtual Card lead_card(const std::string &trump){
        assert(cards.size() >= 1);
        printCard(cards);
        int index = 0;
        cout << "Human player " << get_name()
        << ", please select a card:" << endl;
        cin >> index;
        Card led_c = cards[findOrigin(index, cards)];
        cards.erase(cards.begin() + findOrigin(index, cards));
        //cout << led_c << " led by " << get_name() << endl;
        return led_c;
    }
    
    virtual Card play_card(const Card &led_card, const std::string &trump){
        assert(cards.size() >= 1);
        printCard(cards);
        int index = 0;
        cout << "Human player " << get_name()
        << ", please select a card:" << endl;
        cin >> index;
        Card play_c = cards[findOrigin(index, cards)];
        cards.erase(cards.begin() + findOrigin(index, cards));
        //cout << play_c << " played by " << get_name() << endl;
        return play_c;
    }
};

Player * Player_factory(const std::string &name, const std::string &strategy){
    if (strategy == "Simple"){
        return new SimplePlayer(name);
    }
    if (strategy == "Human"){
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}
