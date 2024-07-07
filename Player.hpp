#pragma once

#include "Board.hpp"

#include <iostream>
#include <map>
#include <random>
#include <string>

using namespace std;

namespace ariel {

    class Player
    {
        // Fields

        string _name; // Players name
        int _index; // Players index in the game
        string _color; // Players color

        int _points = 2;
        int _numOfCities = 0;
        int _numOfSettlements = 2;
        int used_knights = 0;

        map<string, int> _resources; // Resources map
        map<string, int> _cards; // Development cards map

    public:
        static int _turn; // Current turn index

        Player(string name, string color);

        ~Player() {}

        void placeCity(unsigned int place_id, Board& board);
        void placeSettlement(unsigned int place_id, Board& board);
        bool placeRoad(unsigned int from, unsigned int to, Board& board); // Bool because of the first turn
        int rollDice();
        inline static void endTurn() { _turn = (_turn % 3) + 1; }
        void trade(Player& p2, string give, string get, int give_num, int get_num);
        void tradeBank(string give, string get);
        void printPoints() const;

        inline string getName() const { return this->_name; }
        inline string getColor() const { return this->_color; }
        inline void setIdx(int num) { this->_index = num; }
        inline int getIdx() const { return this->_index; }
        inline int getNumOfSettlements() const { return this->_numOfSettlements; }
        inline int getNumOfResources() const {
            int total = 0;
            for (const auto& resource : _resources) {
                total += resource.second;
            }
            return total;
        }

        inline void addResource(const string& resource, int num) { this->_resources[resource] += num; }
        inline void subResource(const string& resource, int num) { this->_resources[resource] -= num; }

        inline int getResource(const string& resource) const { return this->_resources.at(resource); }

        inline int getPoints() const { return this->_points; }

        inline int getCard(const string& card) const { return this->_cards.at(card); }

        inline void addCard(const string& card, int num) { this->_cards[card] += num; }
        inline void useCard(const string& card) { this->_cards[card]--; }

        inline void addVictoryPoint(int num) { this->_cards["victoryPoints"] += num; this->_points += num; }
        inline void useKnight() { this->_cards["usedKnights"]++; }
        inline void KnightsPoints() { this->_points += 2; }
        int getUsedKnights() const { return this->used_knights; }
    };
}
