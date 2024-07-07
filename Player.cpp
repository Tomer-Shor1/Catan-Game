// ID: *****11541
// MAIL: Tomer5469@gmail.com

#include "Player.hpp"

namespace ariel
{
    int Player::_turn = 1;

    Player::Player(string name, string color) : _name(name), _color(color), _index(0)
    {
        // Initialize resources and cards
        _resources = {
            {"wood", 0},
            {"brick", 0},
            {"sheep", 0},
            {"stone", 0},
            {"wheat", 0}};

        _cards = {
            {"victorypoints", 0},
            {"knights", 0},
            {"monopoly", 0},
            {"build2roads", 0},
            {"yearofplenty", 0},
            {"usedKnights", 0}};
    }

    void Player::placeSettlement(unsigned int place_id, Board &board)
    {
        if (this->_resources.at("brick") < 1 || this->_resources.at("wood") < 1 || this->_resources.at("sheep") < 1 || this->_resources.at("wheat") < 1)
        {
            cout << "You don't have enough resources!" << endl;
            return;
        }

        // Check for valid place
        if (place_id < 1 || place_id > 54)
        {
            cout << "Not a valid place id" << endl;
            return;
        }

        if (board.getPlace(place_id)->getOwner() != "")
        {
            cout << "This place is not empty" << endl;
            return;
        }

        vector<unsigned int> neighbors = board.getPlace(place_id)->getNeighbors();
        for (unsigned int i = 0; i < neighbors.size(); i++)
        {
            if (board.getPlace(neighbors[i])->getOwner() != "")
            {
                cout << "There is a neighbor settlement" << endl;
                return;
            }
        }

        vector<string> roads = board.getPlace(place_id)->getRoads();
        bool neighborRoad = false;

        for (unsigned int i = 0; i < roads.size(); i++)
        {
            if (roads[i] == this->_color)
            {
                neighborRoad = true;
            }
        }

        if (!neighborRoad)
        {
            cout << "Cant place a settlement that is not connected to a road" << endl;
            return;
        }

        this->_resources.at("brick")--;
        this->_resources.at("wood")--;
        this->_resources.at("wheat")--;
        this->_resources.at("sheep")--;

        // Place the settlement
        board.setOwner(place_id, this->_color);

        this->_numOfSettlements++;
        this->_points++;
    }

    void Player::placeCity(unsigned int place_id, Board &board)
    {
        if (this->_resources.at("stone") < 3 || this->_resources.at("wheat") < 2)
        {
            cout << "You don't have enough resources!" << endl;
            return;
        }

        // Check for valid place
        if (place_id < 1 || place_id > 54)
        {
            cout << "Not a valid place id" << endl;
            return;
        }

        if (board.getPlace(place_id)->getOwner() != this->_color)
        {
            cout << "This place is not yours" << endl;
            return;
        }

        this->_resources.at("stone") -= 3;
        this->_resources.at("wheat") -= 2;

        // Place the city
        string c = this->_color;
        board.setOwner(place_id, c.replace(2, 2, "1;"));

        this->_numOfCities++;
        this->_numOfSettlements--;
        this->_points++;
    }

    bool Player::placeRoad(unsigned int from, unsigned int to, Board &board)
    {
        if (this->_resources.at("brick") < 1 || this->_resources.at("wood") < 1)
        {
            cout << "You don't have 1 Brick and 1 Wood!" << endl;
            return false;
        }

        // Check for valid place
        if (from < 1 || from > 54 || to < 1 || to > 54)
        {
            cout << "Not a valid place for a road" << endl;
            return false;
        }

        if (!board.getPlace(from)->closeTo(*board.getPlace(to)) && !board.getPlace(to)->closeTo(*board.getPlace(from)))
        {
            cout << "There is no road from " << from << " to " << to << endl;
            return false;
        }

        vector<string> roads = board.getPlace(from)->getRoads();
        bool neighborRoad = false;

        for (unsigned int i = 0; i < roads.size(); i++)
        {
            if (roads[i] == this->_color)
            {
                neighborRoad = true;
            }
        }

        roads = board.getPlace(to)->getRoads();

        for (unsigned int i = 0; i < roads.size(); i++)
        {
            if (roads[i] == this->_color)
            {
                neighborRoad = true;
            }
        }

        if (!neighborRoad)
        {
            cout << "Cant place a road that is not connected to a settlement or a road" << endl;
            return false;
        }

        // Place the road
        //  I own "from" or "to"
        if (this->_color == board.getPlace(from)->getOwner() || this->_color == board.getPlace(to)->getOwner())
        {
            vector<unsigned int> neighbors = board.getPlace(from)->getNeighbors();

            for (unsigned int i = 0; i < neighbors.size(); i++)
            {
                if (board.getPlace(neighbors[i]) == board.getPlace(to))
                {
                    if (board.getPlace(from)->getRoadOwner(i) == "")
                    {
                        board.getPlace(from)->setRoadOwner(this->_color, i);

                        vector<unsigned int> neighbors2 = board.getPlace(to)->getNeighbors();
                        for (unsigned int i = 0; i < neighbors2.size(); i++)
                        {
                            if (board.getPlace(neighbors2[i]) == board.getPlace(from))
                            {
                                board.getPlace(to)->setRoadOwner(this->_color, i);
                            }
                        }

                        this->_resources.at("brick")--;
                        this->_resources.at("wood")--;
                        return true;
                    }
                    cout << "The road is already occupied" << endl;
                    return false;
                }
            }
        }

        // No one owns "from" or "to" and I also don't have a city there
        if ((board.getPlace(from)->getOwner() == "" || this->_color != board.getPlace(from)->getOwner().replace(2, 2, "0;")) && (board.getPlace(to)->getOwner() == "" || this->_color != board.getPlace(to)->getOwner().replace(2, 2, "0;")))
        {
            vector<unsigned int> neighbors = board.getPlace(from)->getNeighbors();

            for (unsigned int i = 0; i < neighbors.size(); i++)
            {
                if (board.getPlace(neighbors[i]) == board.getPlace(to))
                {
                    if (board.getPlace(from)->getRoadOwner(i) == "")
                    {
                        board.getPlace(from)->setRoadOwner(this->_color, i);

                        vector<unsigned int> neighbors2 = board.getPlace(to)->getNeighbors();
                        for (unsigned int i = 0; i < neighbors2.size(); i++)
                        {
                            if (board.getPlace(neighbors2[i]) == board.getPlace(from))
                            {
                                board.getPlace(to)->setRoadOwner(this->_color, i);
                            }
                        }

                        this->_resources.at("brick")--;
                        this->_resources.at("wood")--;
                        return true;
                    }
                    cout << "The road is already occupied" << endl;
                    return false;
                }
            }
        }
        return false;
    }

    int Player::rollDice()
    {
        // Create a random device and seed the random number generator
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform integer distribution from 2 to 12
        uniform_int_distribution<> dis(2, 12);

        // Generate a random integer in the range [2, 12]
        int random_number = dis(gen);

        // Output the random number
        cout << "Dice roll result: " << random_number << std::endl;
        return random_number;
    }

    void Player::trade(Player &p2, string give, string get, int give_num, int get_num)
    {
        if (give == "wood")
        {
            if (this->_resources.at("wood") < give_num)
            {
                cout << "You don't have enough wood!" << endl;
                return;
            }

            if (get == "wood")
            {
                if (p2.getResource("wood") < get_num)
                {
                    cout << "P2 don't have enough wood!" << endl;
                    return;
                }

                this->_resources.at("wood") += get_num;
                p2.subResource("wood", get_num);

                this->_resources.at("wood") -= give_num;
                p2.addResource("wood", give_num);

                return;
            }
            if (get == "brick")
            {
                if (p2.getResource("brick") < get_num)
                {
                    cout << "P2 don't have enough brick!" << endl;
                    return;
                }

                this->_resources.at("brick") += get_num;
                p2.subResource("brick", get_num);

                this->_resources.at("wood") -= give_num;
                p2.addResource("wood", give_num);

                return;
            }
            if (get == "sheep")
            {
                if (p2._resources.at("sheep") < get_num)
                {
                    cout << "P2 don't have enough sheep!" << endl;
                    return;
                }

                this->_resources.at("sheep") += get_num;
                p2.subResource("sheep", get_num);

                this->_resources.at("wood") -= give_num;
                p2.addResource("wood", give_num);

                return;
            }
            if (get == "stone")
            {
                if (p2.getResource("stone") < get_num)
                {
                    cout << "P2 don't have enough stone!" << endl;
                    return;
                }

                this->_resources.at("stone") += get_num;
                p2.subResource("stone", get_num);

                this->_resources.at("wood") -= give_num;
                p2.addResource("wood", give_num);

                return;
            }
            if (get == "wheat")
            {
                if (p2._resources.at("wheat") < get_num)
                {
                    cout << "P2 don't have enough wheat!" << endl;
                    return;
                }

                this->_resources.at("wheat") += get_num;
                p2.subResource("wheat", get_num);

                this->_resources.at("wood") -= give_num;
                p2.addResource("wood", give_num);

                return;
            }
        }

        if (give == "brick")
        {
            if (this->_resources.at("brick") < give_num)
            {
                cout << "You don't have enough brick!" << endl;
                return;
            }

            if (get == "wood")
            {
                if (p2._resources.at("wood") < get_num)
                {
                    cout << "P2 don't have enough wood!" << endl;
                    return;
                }

                this->_resources.at("wood") += get_num;
                p2.subResource("wood", get_num);

                this->_resources.at("brick") -= give_num;
                p2.addResource("brick", give_num);

                return;
            }
            if (get == "brick")
            {
                if (p2._resources.at("brick") < get_num)
                {
                    cout << "P2 don't have enough brick!" << endl;
                    return;
                }

                this->_resources.at("brick") += get_num;
                p2.subResource("brick", get_num);

                this->_resources.at("brick") -= give_num;
                p2.addResource("brick", give_num);

                return;
            }
            if (get == "sheep")
            {
                if (p2._resources.at("sheep") < get_num)
                {
                    cout << "P2 don't have enough sheep!" << endl;
                    return;
                }

                this->_resources.at("sheep") += get_num;
                p2.subResource("sheep", get_num);

                this->_resources.at("brick") -= give_num;
                p2.addResource("brick", give_num);

                return;
            }
            if (get == "stone")
            {
                if (p2._resources.at("stone") < get_num)
                {
                    cout << "P2 don't have enough stone!" << endl;
                    return;
                }

                this->_resources.at("stone") += get_num;
                p2.subResource("stone", get_num);

                this->_resources.at("brick") -= give_num;
                p2.addResource("brick", give_num);

                return;
            }
            if (get == "wheat")
            {
                if (p2._resources.at("wheat") < get_num)
                {
                    cout << "P2 don't have enough wheat!" << endl;
                    return;
                }

                this->_resources.at("wheat") += get_num;
                p2.subResource("wheat", get_num);

                this->_resources.at("brick") -= give_num;
                p2.addResource("brick", give_num);

                return;
            }
        }

        if (give == "sheep")
        {
            if (this->_resources.at("sheep") < give_num)
            {
                cout << "You don't have enough sheep!" << endl;
                return;
            }

            if (get == "wood")
            {
                if (p2._resources.at("wood") < get_num)
                {
                    cout << "P2 don't have enough wood!" << endl;
                    return;
                }

                this->_resources.at("wood") += get_num;
                p2.subResource("wood", get_num);

                this->_resources.at("sheep") -= give_num;
                p2.addResource("sheep", give_num);

                return;
            }
            if (get == "brick")
            {
                if (p2._resources.at("brick") < get_num)
                {
                    cout << "P2 don't have enough brick!" << endl;
                    return;
                }

                this->_resources.at("brick") += get_num;
                p2.subResource("brick", get_num);

                this->_resources.at("sheep") -= give_num;
                p2.addResource("sheep", give_num);

                return;
            }
            if (get == "sheep")
            {
                if (p2._resources.at("sheep") < get_num)
                {
                    cout << "P2 don't have enough sheep!" << endl;
                    return;
                }

                this->_resources.at("sheep") += get_num;
                p2.subResource("sheep", get_num);

                this->_resources.at("sheep") -= give_num;
                p2.addResource("sheep", give_num);

                return;
            }
            if (get == "stone")
            {
                if (p2._resources.at("stone") < get_num)
                {
                    cout << "P2 don't have enough stone!" << endl;
                    return;
                }

                this->_resources.at("stone") += get_num;
                p2.subResource("stone", get_num);

                this->_resources.at("sheep") -= give_num;
                p2.addResource("sheep", give_num);

                return;
            }
            if (get == "wheat")
            {
                if (p2._resources.at("wheat") < get_num)
                {
                    cout << "P2 don't have enough wheat!" << endl;
                    return;
                }

                this->_resources.at("wheat") += get_num;
                p2.subResource("wheat", get_num);

                this->_resources.at("sheep") -= give_num;
                p2.addResource("sheep", give_num);

                return;
            }
        }

        if (give == "stone")
        {
            if (this->_resources.at("stone") < give_num)
            {
                cout << "You don't have enough stone!" << endl;
                return;
            }

            if (get == "wood")
            {
                if (p2._resources.at("wood") < get_num)
                {
                    cout << "P2 don't have enough wood!" << endl;
                    return;
                }

                this->_resources.at("wood") += get_num;
                p2.subResource("wood", get_num);

                this->_resources.at("stone") -= give_num;
                p2.addResource("stone", give_num);

                return;
            }
            if (get == "brick")
            {
                if (p2._resources.at("brick") < get_num)
                {
                    cout << "P2 don't have enough brick!" << endl;
                    return;
                }

                this->_resources.at("brick") += get_num;
                p2.subResource("brick", get_num);

                this->_resources.at("stone") -= give_num;
                p2.addResource("stone", give_num);

                return;
            }
            if (get == "sheep")
            {
                if (p2._resources.at("sheep") < get_num)
                {
                    cout << "P2 don't have enough sheep!" << endl;
                    return;
                }

                this->_resources.at("sheep") += get_num;
                p2.subResource("sheep", get_num);

                this->_resources.at("stone") -= give_num;
                p2.addResource("stone", give_num);

                return;
            }
            if (get == "stone")
            {
                if (p2._resources.at("stone") < get_num)
                {
                    cout << "P2 don't have enough stone!" << endl;
                    return;
                }

                this->_resources.at("stone") += get_num;
                p2.subResource("stone", get_num);

                this->_resources.at("stone") -= give_num;
                p2.addResource("stone", give_num);

                return;
            }
            if (get == "wheat")
            {
                if (p2._resources.at("wheat") < get_num)
                {
                    cout << "P2 don't have enough wheat!" << endl;
                    return;
                }

                this->_resources.at("wheat") += get_num;
                p2.subResource("wheat", get_num);

                this->_resources.at("stone") -= give_num;
                p2.addResource("stone", give_num);

                return;
            }
        }

        if (give == "wheat")
        {
            if (this->_resources.at("wheat") < give_num)
            {
                cout << "You don't have enough wheat!" << endl;
                return;
            }

            if (get == "wood")
            {
                if (p2._resources.at("wood") < get_num)
                {
                    cout << "P2 don't have enough wood!" << endl;
                    return;
                }

                this->_resources.at("wood") += get_num;
                p2.subResource("wood", get_num);

                this->_resources.at("wheat") -= give_num;
                p2.addResource("wheat", give_num);

                return;
            }
            if (get == "brick")
            {
                if (p2._resources.at("brick") < get_num)
                {
                    cout << "P2 don't have enough brick!" << endl;
                    return;
                }

                this->_resources.at("brick") += get_num;
                p2.subResource("brick", get_num);

                this->_resources.at("wheat") -= give_num;
                p2.addResource("wheat", give_num);

                return;
            }
            if (get == "sheep")
            {
                if (p2._resources.at("sheep") < get_num)
                {
                    cout << "P2 don't have enough sheep!" << endl;
                    return;
                }

                this->_resources.at("sheep") += get_num;
                p2.subResource("sheep", get_num);

                this->_resources.at("wheat") -= give_num;
                p2.addResource("wheat", give_num);

                return;
            }
            if (get == "stone")
            {
                if (p2._resources.at("stone") < get_num)
                {
                    cout << "P2 don't have enough stone!" << endl;
                    return;
                }

                this->_resources.at("stone") += get_num;
                p2.subResource("stone", get_num);

                this->_resources.at("wheat") -= give_num;
                p2.addResource("wheat", give_num);

                return;
            }
            if (get == "wheat")
            {
                if (p2._resources.at("wheat") < get_num)
                {
                    cout << "P2 don't have enough wheat!" << endl;
                    return;
                }

                this->_resources.at("wheat") += get_num;
                p2.subResource("wheat", get_num);

                this->_resources.at("wheat") -= give_num;
                p2.addResource("wheat", give_num);

                return;
            }
        }
    }

    void Player::tradeBank(string give, string get)
    {
        if (give == "wood")
        {
            if (this->_resources.at("wood") < 4)
            {
                cout << "You don't have enough wood!" << endl;
                return;
            }

            if (get == "brick")
            {
                addResource("brick", 1);
                subResource("wood", 4);
            }
            else if (get == "sheep")
            {
                addResource("sheep", 1);
                subResource("wood", 4);
            }
            else if (get == "stone")
            {
                addResource("stone", 1);
                subResource("wood", 4);
            }
            else if (get == "wheat")
            {
                addResource("wheat", 1);
                subResource("wood", 4);
            }
            else
                cout << "Not a valid get value!" << endl;
        }
        else if (give == "brick")
        {
            if (this->_resources.at("brick") < 4)
            {
                cout << "You don't have enough brick!" << endl;
                return;
            }

            if (get == "wood")
            {
                addResource("wood", 1);
                subResource("brick", 4);
            }
            else if (get == "sheep")
            {
                addResource("sheep", 1);
                subResource("brick", 4);
            }
            else if (get == "stone")
            {
                addResource("stone", 1);
                subResource("brick", 4);
            }
            else if (get == "wheat")
            {
                addResource("wheat", 1);
                subResource("brick", 4);
            }
            else
                cout << "Not a valid get value!" << endl;
        }
        else if (give == "sheep")
        {
            if (this->_resources.at("sheep") < 4)
            {
                cout << "You don't have enough sheep!" << endl;
                return;
            }

            if (get == "wood")
            {
                addResource("wood", 1);
                subResource("sheep", 4);
            }
            else if (get == "brick")
            {
                addResource("brick", 1);
                subResource("sheep", 4);
            }
            else if (get == "stone")
            {
                addResource("stone", 1);
                subResource("sheep", 4);
            }
            else if (get == "wheat")
            {
                addResource("wheat", 1);
                subResource("sheep", 4);
            }
            else
                cout << "Not a valid get value!" << endl;
        }
        else if (give == "stone")
        {
            if (this->_resources.at("stone") < 4)
            {
                cout << "You don't have enough stone!" << endl;
                return;
            }

            if (get == "wood")
            {
                addResource("wood", 1);
                subResource("stone", 4);
            }
            else if (get == "brick")
            {
                addResource("brick", 1);
                subResource("stone", 4);
            }
            else if (get == "sheep")
            {
                addResource("sheep", 1);
                subResource("stone", 4);
            }
            else if (get == "wheat")
            {
                addResource("wheat", 1);
                subResource("stone", 4);
            }
            else
                cout << "Not a valid get value!" << endl;
        }
        else if (give == "wheat")
        {
            if (this->_resources.at("wheat") < 4)
            {
                cout << "You don't have enough wheat!" << endl;
                return;
            }

            if (get == "wood")
            {
                addResource("wood", 1);
                subResource("wheat", 4);
            }
            else if (get == "brick")
            {
                addResource("brick", 1);
                subResource("wheat", 4);
            }
            else if (get == "sheep")
            {
                addResource("sheep", 1);
                subResource("wheat", 4);
            }
            else if (get == "stone")
            {
                addResource("stone", 1);
                subResource("wheat", 4);
            }
            else
                cout << "Not a valid get value!" << endl;
        }
        else
            cout << "Not a valid give value!" << endl;
    }

    void Player::printPoints() const
    {
        cout << this->_name << " has " << this->_points;
        cout << " points because he/she has: " << endl;
        cout << this->_numOfSettlements << " settlements" << endl;
        cout << this->_numOfCities << " cities" << endl;
        if (this->_cards.at("knights") == 3)
            cout << "2 points for having the largest army card" << endl;
        cout << this->_cards.at("victorypoints") << " victory points" << endl;
    }
}