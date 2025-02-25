// ID: *****11541
// MAIL: Tomer5469@gmail.com

#include "Catan.hpp"

using namespace std;

namespace ariel {

    Catan::Catan(Player& p1, Player& p2, Player& p3) {

        this->_p1 = &p1;
        this->_p2 = &p2;
        this->_p3 = &p3;
        this->_GameBoard = Board();
        vector<unique_ptr<Card>> cards;

        // 10 From these
        for(int i = 0; i < 10; i++) {
            cards.push_back(make_unique<Monopoly>());
            cards.push_back(make_unique<Build2Roads>());
            cards.push_back(make_unique<YearOfPlenty>());
        }

        // 3 Knights
        cards.push_back(make_unique<Knight>());
        cards.push_back(make_unique<Knight>());
        cards.push_back(make_unique<Knight>());

        // 4 Victory Points
        cards.push_back(make_unique<VictoryPoint>());
        cards.push_back(make_unique<VictoryPoint>());
        cards.push_back(make_unique<VictoryPoint>());
        cards.push_back(make_unique<VictoryPoint>());

        // Shuffle the cards
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));

        // Transfer ownership of shuffled cards to _cards stack
        for (auto& card : cards) {
            this->_cards.push(std::move(card));
        }
    }

    // For the demo and tests (without shuffling)
    Catan::Catan(Player& p1, Player& p2, Player& p3, bool test){
        this->_p1 = &p1;
        this->_p2 = &p2;
        this->_p3 = &p3;
        this->_GameBoard = Board(test);
        vector<unique_ptr<Card>> cards;

        cards.push_back(make_unique<Monopoly>());

        cards.push_back(make_unique<YearOfPlenty>());

        cards.push_back(make_unique<VictoryPoint>());

        cards.push_back(make_unique<Knight>());
        cards.push_back(make_unique<Knight>());
        cards.push_back(make_unique<Knight>());

        cards.push_back(make_unique<Build2Roads>());

        for (auto& card : cards) {
            this->_cards.push(std::move(card));
        }
    }

    Catan::~Catan() {}

    Player* Catan::ChooseStartingPlayer() {
        // Create a random device and seed the random number generator
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform integer distribution from 1 to 3
        uniform_int_distribution<> dis(1, 3);

        // Generate a random integer in the range [1, 3]
        int random_number = dis(gen);

        if (random_number == 1) {
            this->_p1->setIdx(1);
            this->_p2->setIdx(2);
            this->_p3->setIdx(3);

            cout << "\nThe player that starts is: " << this->_p1->getName() << endl;
            return this->_p1;
        } else if (random_number == 2) {
            this->_p2->setIdx(1);
            this->_p3->setIdx(2);
            this->_p1->setIdx(3);

            cout << "\nThe player that starts is: " << this->_p2->getName() << endl;
            return this->_p2;
        } else {
            this->_p3->setIdx(1);
            this->_p1->setIdx(2);
            this->_p2->setIdx(3);

            cout << "\nThe player that starts is: " << this->_p3->getName() << endl;
            return this->_p3;
        }
    }

    // For the demo and tests (regular order)
    Player* Catan::ChooseStartingPlayer(bool test){
        this->_p1->setIdx(1);
        this->_p2->setIdx(2);
        this->_p3->setIdx(3);

        cout << "\nThe player that starts is: " << this->_p1->getName() << endl;
        return this->_p1;
    }

    Board* Catan::getBoard() {
        return &this->_GameBoard;
    }

    void Catan::printWinner() const {
        if (!hasWinner())
            return;

        if (this->_p1->getPoints() >= 10)
            cout << "The winner is: " << this->_p1->getName() << endl;

        else if (this->_p2->getPoints() >= 10)
            cout << "The winner is: " << this->_p2->getName() << endl;

        else
            cout << "The winner is: " << this->_p3->getName() << endl;
    }

    bool Catan::hasWinner() const {
        if (this->_p1->getPoints() >= 10 || this->_p2->getPoints() >= 10 || this->_p3->getPoints() >= 10)
            return true;

        cout << "None of the players has 10 points" << endl;
        return false;
    }

    // Moving the turn to the next player
    Player* Catan::endTurn() const {
        Player::endTurn();
        int turn = Player::_turn;

        if (this->_p1->getIdx() == turn) {
            cout << this->_p1->getName() << "'s turn!" << endl;
            return this->_p1;
        } else if (this->_p2->getIdx() == turn) {
            cout << this->_p2->getName() << "'s turn!" << endl;
            return this->_p2;
        } else {
            cout << this->_p3->getName() << "'s turn!" << endl;
            return this->_p3;
        }
    }

    // Updating all the players resources based on the dice result
    void Catan::updateResources(int dice) {
        // 7 case (may need to remove cards)
        if (dice == 7) {
            int n, count = 0;
            if (this->_p1->getNumOfResources() > 7) {
                n = this->_p1->getNumOfResources() / 2;

                cout << this->_p1->getName() << ", you need to return to the bank " << n << " cards" << endl;

                cout << "Your resources: " << endl;
                cout << "Wood: " << this->_p1->getResource("wood") << endl;
                cout << "Brick: " << this->_p1->getResource("brick") << endl;
                cout << "Sheep: " << this->_p1->getResource("sheep") << endl;
                cout << "Stone: " << this->_p1->getResource("stone") << endl;
                cout << "Wheat: " << this->_p1->getResource("wheat") << endl;

                string type;
                int num;

                while (count != n) {
                    cout << "Choose resource: " << endl;
                    cin >> type;
                    cout << "How many to remove: " << endl;
                    cin >> num;

                    if (type == "wood") {
                        if (this->_p1->getResource("wood") >= num) {
                            this->_p1->subResource("wood", num);
                            cout << "New amount - " << this->_p1->getResource("wood") << endl;
                            count += num;
                        } else
                            cout << "You don't have enough wood" << endl;
                    }

                    if (type == "brick") {
                        if (this->_p1->getResource("brick") >= num) {
                            this->_p1->subResource("brick", num);
                            count += num;
                        } else
                            cout << "You don't have enough brick" << endl;
                    }

                    if (type == "sheep") {
                        if (this->_p1->getResource("sheep") >= num) {
                            this->_p1->subResource("sheep", num);
                            count += num;
                        } else
                            cout << "You don't have enough sheep" << endl;
                    }

                    if (type == "stone") {
                        if (this->_p1->getResource("stone") >= num) {
                            this->_p1->subResource("stone", num);
                            count += num;
                        } else
                            cout << "You don't have enough stone" << endl;
                    }

                    if (type == "wheat") {
                        if (this->_p1->getResource("wheat") >= num) {
                            this->_p1->subResource("wheat", num);
                            count += num;
                        } else
                            cout << "You don't have enough wheat" << endl;
                    }
                }
            }

            count = 0;
            n = 0;

            if (this->_p2->getNumOfResources() > 7) {
                n = this->_p2->getNumOfResources() / 2;

                cout << this->_p2->getName() << ", you need to return to the bank " << n << " cards" << endl;

                cout << "Your resources: " << endl;
                cout << "Wood: " << this->_p2->getResource("wood") << endl;
                cout << "Brick: " << this->_p2->getResource("brick") << endl;
                cout << "Sheep: " << this->_p2->getResource("sheep") << endl;
                cout << "Stone: " << this->_p2->getResource("stone") << endl;
                cout << "Wheat: " << this->_p2->getResource("wheat") << endl;

                string type;
                int num;

                while (count != n) {
                    cout << "Choose resource: " << endl;
                    cin >> type;
                    cout << "How many to remove: " << endl;
                    cin >> num;

                    if (type == "wood") {
                        if (this->_p2->getResource("wood") >= num) {
                            this->_p2->subResource("wood", num);
                            count += num;
                        } else
                            cout << "You don't have enough wood" << endl;
                    }

                    if (type == "brick") {
                        if (this->_p2->getResource("brick") >= num) {
                            this->_p2->subResource("brick", num);
                            count += num;
                        } else
                            cout << "You don't have enough brick" << endl;
                    }

                    if (type == "sheep") {
                        if (this->_p2->getResource("sheep") >= num) {
                            this->_p2->subResource("sheep", num);
                            count += num;
                        } else
                            cout << "You don't have enough sheep" << endl;
                    }

                    if (type == "stone") {
                        if (this->_p2->getResource("stone") >= num) {
                            this->_p2->subResource("stone", num);
                            count += num;
                        } else
                            cout << "You don't have enough stone" << endl;
                    }

                    if (type == "wheat") {
                        if (this->_p2->getResource("wheat") >= num) {
                            this->_p2->subResource("wheat", num);
                            count += num;
                        } else
                            cout << "You don't have enough wheat" << endl;
                    }
                }
            }

            count = 0;
            n = 0;

            if (this->_p3->getNumOfResources() > 7) {
                n = this->_p3->getNumOfResources() / 2;

                cout << this->_p3->getName() << ", you need to return to the bank " << n << " cards" << endl;

                cout << "Your resources: " << endl;
                cout << "Wood: " << this->_p3->getResource("wood") << endl;
                cout << "Brick: " << this->_p3->getResource("brick") << endl;
                cout << "Sheep: " << this->_p3->getResource("sheep") << endl;
                cout << "Stone: " << this->_p3->getResource("stone") << endl;
                cout << "Wheat: " << this->_p3->getResource("wheat") << endl;

                string type;
                int num;

                while (count != n) {
                    cout << "Choose resource: " << endl;
                    cin >> type;
                    cout << "How many to remove: " << endl;
                    cin >> num;

                    if (type == "wood") {
                        if (this->_p3->getResource("wood") >= num) {
                            this->_p3->subResource("wood", num);
                            count += num;
                        } else
                            cout << "You don't have enough wood" << endl;
                    }

                    if (type == "brick") {
                        if (this->_p3->getResource("brick") >= num) {
                            this->_p3->subResource("brick", num);
                            count += num;
                        } else
                            cout << "You don't have enough brick" << endl;
                    }

                    if (type == "sheep") {
                        if (this->_p3->getResource("sheep") >= num) {
                            this->_p3->subResource("sheep", num);
                            count += num;
                        } else
                            cout << "You don't have enough sheep" << endl;
                    }

                    if (type == "stone") {
                        if (this->_p3->getResource("stone") >= num) {
                            this->_p3->subResource("stone", num);
                            count += num;
                        } else
                            cout << "You don't have enough stone" << endl;
                    }

                    if (type == "wheat") {
                        if (this->_p3->getResource("wheat") >= num) {
                            this->_p3->subResource("wheat", num);
                            count += num;
                        } else
                            cout << "You don't have enough wheat" << endl;
                    }
                }
            }
        } else { // Not 7
            string c;
            for (unsigned int i = 1; i < 55; i++) {
                if (i == 7)
                    continue;

                string typeWithNum = this->_GameBoard.getPlace(i)->diceInPlace(dice);

                if (typeWithNum != "0") {
                    c = this->_p1->getColor();
                    if (this->_GameBoard.getPlace(i)->getOwner() == this->_p1->getColor()) { // Regular settlement
                        if (typeWithNum == "Wood") { this->_p1->addResource("wood",1); }
                        if (typeWithNum == "Brick") { this->_p1->addResource("brick",1); }
                        if (typeWithNum == "Sheep") { this->_p1->addResource("sheep",1); }
                        if (typeWithNum == "Stone") { this->_p1->addResource("stone",1); }
                        if (typeWithNum == "Wheat") { this->_p1->addResource("wheat",1); }
                    } else if(this->_GameBoard.getPlace(i)->getOwner() == c.replace(2, 2, "1;")){ // City
                        if (typeWithNum == "Wood") { this->_p1->addResource("wood",2); }
                        if (typeWithNum == "Brick") { this->_p1->addResource("brick",2); }
                        if (typeWithNum == "Sheep") { this->_p1->addResource("sheep",2); }
                        if (typeWithNum == "Stone") { this->_p1->addResource("stone",2); }
                        if (typeWithNum == "Wheat") { this->_p1->addResource("wheat",2); }
                    }

                    c = this->_p2->getColor();
                    if (this->_GameBoard.getPlace(i)->getOwner() == this->_p2->getColor()) { // Regular settlement
                        if (typeWithNum == "Wood") { this->_p2->addResource("wood",1); }
                        if (typeWithNum == "Brick") { this->_p2->addResource("brick",1); }
                        if (typeWithNum == "Sheep") { this->_p2->addResource("sheep",1); }
                        if (typeWithNum == "Stone") { this->_p2->addResource("stone",1); }
                        if (typeWithNum == "Wheat") { this->_p2->addResource("wheat",1); }
                    } else if(this->_GameBoard.getPlace(i)->getOwner() == c.replace(2, 2, "1;")){ // City
                        if (typeWithNum == "Wood") { this->_p2->addResource("wood",2); }
                        if (typeWithNum == "Brick") { this->_p2->addResource("brick",2); }
                        if (typeWithNum == "Sheep") { this->_p2->addResource("sheep",2); }
                        if (typeWithNum == "Stone") { this->_p2->addResource("stone",2); }
                        if (typeWithNum == "Wheat") { this->_p2->addResource("wheat",2); }
                    }

                    c = this->_p3->getColor();
                    if (this->_GameBoard.getPlace(i)->getOwner() == this->_p3->getColor()) { // Regular settlement
                        if (typeWithNum == "Wood") { this->_p3->addResource("wood",1); }
                        if (typeWithNum == "Brick") { this->_p3->addResource("brick",1); }
                        if (typeWithNum == "Sheep") { this->_p3->addResource("sheep",1); }
                        if (typeWithNum == "Stone") { this->_p3->addResource("stone",1); }
                        if (typeWithNum == "Wheat") { this->_p3->addResource("wheat",1); }
                    } else if(this->_GameBoard.getPlace(i)->getOwner() == c.replace(2, 2, "1;")){ // City
                        if (typeWithNum == "Wood") { this->_p3->addResource("wood",2); }
                        if (typeWithNum == "Brick") { this->_p3->addResource("brick",2); }
                        if (typeWithNum == "Sheep") { this->_p3->addResource("sheep",2); }
                        if (typeWithNum == "Stone") { this->_p3->addResource("stone",2); }
                        if (typeWithNum == "Wheat") { this->_p3->addResource("wheat",2); }
                    }
                }
            }
        }
    }

    // Return the player by i (if i is 1 we return _p1)
    Player* Catan::getPlayer(int i) const {
        if (i == 1)
            return this->_p1;
        if (i == 2)
            return this->_p2;

        return this->_p3;
    }

    // The first turn in the currect order
    void Catan::firstTurn(Player &p) {
        if (p.getIdx() == this->_p1->getIdx()) {
            firstSettlements(*this->_p1, false);
            firstSettlements(*this->_p2, false);
            firstSettlements(*this->_p3, false);
            firstSettlements(*this->_p3, true);
            firstSettlements(*this->_p2, true);
            firstSettlements(*this->_p1, true);
        } else if (p.getIdx() == this->_p2->getIdx()) {
            firstSettlements(*this->_p2, false);
            firstSettlements(*this->_p3, false);
            firstSettlements(*this->_p1, false);
            firstSettlements(*this->_p1, true);
            firstSettlements(*this->_p3, true);
            firstSettlements(*this->_p2, true);
        } else {
            firstSettlements(*this->_p3, false);
            firstSettlements(*this->_p1, false);
            firstSettlements(*this->_p2, false);
            firstSettlements(*this->_p2, true);
            firstSettlements(*this->_p1, true);
            firstSettlements(*this->_p3, true);
        }
    }

    // First turn's settlement assignments with a bool type for knowing whether to give resources or not
    void Catan::firstSettlements(Player &p, bool resources) {
        bool valid_place = false, check_nei = true;
        unsigned int place;

        this->_GameBoard.printBoard();
        cout << p.getName() << ", where do you want to build the settlement?" << endl;

        while (!valid_place) {
            cin >> place;
            if (place > 0 && place < 55) {
                if (this->_GameBoard.getPlace(place)->getOwner() == "") {
                    vector<unsigned int> neighbors = this->_GameBoard.getPlace(place)->getNeighbors();
                    for (unsigned int i = 0; i < neighbors.size(); i++) {
                        if (this->_GameBoard.getPlace(neighbors[i])->getOwner() != "") {
                            cout << "Can't place a settlement neighbor to another. Enter new place!" << endl;
                            check_nei = false;
                            break; // breaks from for loop only
                        }
                    }
                    if (check_nei)
                        valid_place = true;
                    else
                        check_nei = true;
                } else
                    cout << "The place is not empty!. Enter new place!" << endl;
            } else
                cout << "Not a valid place. Enter new place!" << endl;
        }

        this->_GameBoard.setOwner(place, p.getColor());
        if (resources)
            addFirstResources(p, place);


        unsigned int to;
        bool valid_road = false;

        cout << "\nNow the road." << endl;
        while (!valid_road) {
            cout << "To: " << endl;
            cin >> to;

            if (to < 1 || to > 54) {
                cout << "Not a valid place. Try again!" << endl;
                continue;
            }

            if (!this->_GameBoard.getPlace(place)->closeTo(*this->_GameBoard.getPlace(to))) {
                cout << "There's no road between " << place << " and " << to << ". Try again!" << endl;
                continue;
            }

            valid_road = true;
        }

        // Searching for the place in the neighbors of "to" and assigning p's color
        vector<unsigned int> neighbors = this->_GameBoard.getPlace(to)->getNeighbors();
        for (unsigned int i = 0; i < neighbors.size(); i++) {
            if (this->_GameBoard.getPlace(neighbors[i]) == this->_GameBoard.getPlace(place)) {
                this->_GameBoard.getPlace(to)->setRoadOwner(p.getColor(), i);
            }
        }

        // Searching for the "to" place in the neighbors of "place" and assigning p's color
        neighbors = this->_GameBoard.getPlace(place)->getNeighbors();
        for (unsigned int i = 0; i < neighbors.size(); i++) {
            if (this->_GameBoard.getPlace(neighbors[i]) == this->_GameBoard.getPlace(to)) {
                this->_GameBoard.getPlace(place)->setRoadOwner(p.getColor(), i);
            }
        }
    }

    // Adding resources for the first turn
    void Catan::addFirstResources(Player &p, unsigned int place) {
        vector <string> types = this->_GameBoard.getPlace(place)->getAllTypes();

        for (unsigned int j = 0; j < types.size(); j++) {
            if (types[j] == "Wood") { p.addResource("wood",1); }
            if (types[j] == "Brick") { p.addResource("brick",1); }
            if (types[j] == "Sheep") { p.addResource("sheep",1); }
            if (types[j] == "Stone") { p.addResource("stone",1); }
            if (types[j] == "Wheat") { p.addResource("wheat",1); }
        }
    }

    void Catan::buyDevelopmentCard(Player &p) {
        if (this->_cards.empty()) {
            cout << "No development cards left to draw!" << endl;
            return;
        }

        if (p.getResource("sheep") > 0 && p.getResource("wheat")> 0 && p.getResource("stone") > 0) {
            unique_ptr <Card> card = std::move(this->_cards.top());
            this->_cards.pop();

            cout << "You got a " << card->get_cardType() << "!" << endl;

            if (card->get_cardType() == "Victory Point") {
                p.addVictoryPoint(1);
                card->use_card(p, *this);
            }
            else if (card->get_cardType() == "Knight") { p.addCard("knight",1); }
            else if (card->get_cardType() == "Monopoly") { p.addCard("monopoly",1); }
            else if (card->get_cardType() == "Year of Plenty") { p.addCard("yearofplenty",1); }
            else if (card->get_cardType() == "Build 2 Roads") { p.addCard("add2roads",1); }

            p.subResource("wheat",1);
            p.subResource("stone",1);
            p.subResource("sheep",1);

        } else { cout << "Not enough resources" << endl; }
    }

    void Catan::useDevelopmentCard(Player& p) {
        string cardType;

        cout << "what card do you wish to use? (0 to change move)" << endl;
        cin.ignore();
        getline(cin, cardType);

        if(cardType == "0"){ return; }

        if(cardType == "Monopoly" && p.getCard("monopoly") > 0){
            Monopoly().use_card(p, *this);
        }
        else if(cardType == "Knight" && p.getCard("knight") > 0){
            Knight().use_card(p, *this);
        }
        else if(cardType == "Year of Plenty" && p.getCard("yearofplenty") > 0){
            YearOfPlenty().use_card(p, *this);
        }
        else if(cardType == "Build 2 Roads" && p.getCard("build2roads") > 0){
            Build2Roads().use_card(p, *this);
        }
        else{ cout<< "No such card" << endl; return;}
    }
}