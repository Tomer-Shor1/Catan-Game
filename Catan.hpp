// ID: *****11541
// MAIL: Tomer5469@gmail.com
#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include <memory>
#include <random>
#include <chrono>
#include <algorithm>

#include "Player.hpp"
#include "Board.hpp"
#include "Card.hpp"

using namespace std;

namespace ariel {

    class Catan
    {
        // Fields
        Player* _p1;
        Player* _p2;
        Player* _p3;
        Board _GameBoard;
        stack<unique_ptr<Card>> _cards; // Cards stack

        public:
                Catan(Player& p1, Player& p2, Player& p3);
                Catan(Player& p1, Player& p2, Player& p3, bool test); // For the demo and tests
                ~Catan();
                Player* ChooseStartingPlayer();
                Player* ChooseStartingPlayer(bool test); // For the demo and tests
                Board* getBoard();
                void printWinner() const;
                bool hasWinner() const;
                Player* endTurn () const;
                void updateResources(int dice);
                Player* getPlayer(int i) const;
                void firstTurn(Player &p);
                void firstSettlements(Player &p, bool resources);
                void addFirstResources(Player &p, unsigned int place);
                void buyDevelopmentCard(Player &p);
                void useDevelopmentCard(Player& p);
    };
}