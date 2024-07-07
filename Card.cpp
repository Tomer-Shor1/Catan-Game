// ID: *****11541
// MAIL: Tomer5469@gmail.com

#include "Card.hpp"
#include "Catan.hpp"

namespace ariel{

    Card::~Card() {}

    // The way each type uses itself
    Monopoly::Monopoly() : Card("Monopoly") {}
    void Monopoly::use_card(Player &p, Catan &c) {
        string choice;
        bool check = false;
        int sum = 0;

        while (!check){
            cout << "What do you want to get?" << endl;
            cin >> choice;

            if(choice == "wood"){
                if(c.getPlayer(1)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(1)->getResource("wood");
                    c.getPlayer(1)->subResource("wood",c.getPlayer(1)->getResource("wood"));
                }
                if(c.getPlayer(2)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(2)->getResource("wood");
                    c.getPlayer(2)->subResource("wood",c.getPlayer(2)->getResource("wood"));
                }
                if(c.getPlayer(3)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(3)->getResource("wood");
                    c.getPlayer(3)->subResource("wood",c.getPlayer(3)->getResource("wood"));
                }

                p.addResource("wood",sum);
                check = true;

            } else if(choice == "brick"){
                if(c.getPlayer(1)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(1)->getResource("brick");
                    c.getPlayer(1)->subResource("brick", c.getPlayer(1)->getResource("brick"));
                }
                if(c.getPlayer(2)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(2)->getResource("brick");
                    c.getPlayer(2)->subResource("brick",c.getPlayer(2)->getResource("brick"));
                }
                if(c.getPlayer(3)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(3)->getResource("brick");
                    c.getPlayer(3)->subResource("brick", c.getPlayer(3)->getResource("brick"));
                }

                p.addResource("brick",sum);
                check = true;

            } else if(choice == "sheep"){
                if(c.getPlayer(1)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(1)->getResource("sheep");
                    c.getPlayer(1)->subResource("sheep",c.getPlayer(1)->getResource("sheep"));
                }
                if(c.getPlayer(2)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(2)->getResource("sheep");
                    c.getPlayer(2)->subResource("sheep", c.getPlayer(2)->getResource("sheep"));
                }
                if(c.getPlayer(3)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(3)->getResource("sheep");
                    c.getPlayer(3)->subResource("sheep",c.getPlayer(3)->getResource("sheep"));
                }

                p.addResource("sheep",sum);
                check = true;

            } else if(choice == "stone"){
                if(c.getPlayer(1)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(1)->getResource("stone");
                    c.getPlayer(1)->subResource("stone", c.getPlayer(1)->getResource("stone"));
                }
                if(c.getPlayer(2)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(2)->getResource("stone");
                    c.getPlayer(2)->subResource("stone", c.getPlayer(2)->getResource("stone"));
                }
                if(c.getPlayer(3)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(3)->getResource("stone");
                    c.getPlayer(3)->subResource("stone",c.getPlayer(3)->getResource("stone"));
                }

                p.addResource("stone",sum);
                check = true;

            } else if(choice == "wheat"){
                if(c.getPlayer(1)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(1)->getResource("wheat");
                    c.getPlayer(1)->subResource("wheat", c.getPlayer(1)->getResource("wheat"));
                }
                if(c.getPlayer(2)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(2)->getResource("wheat");
                    c.getPlayer(2)->subResource("wheat", c.getPlayer(2)->getResource("wheat"));
                }
                if(c.getPlayer(3)->getIdx() != p.getIdx()){
                    sum += c.getPlayer(3)->getResource("wheat");
                    c.getPlayer(3)->subResource("wheat", c.getPlayer(3)->getResource("wheat"));
                }

                p.addResource("wheat",sum);
                check = true;

            } else
                cout << "Not a valid resource. Try again." << endl;
        }

        p.useCard("monopoly");
    }

    Build2Roads::Build2Roads() : Card("Build 2 Roads") {}
    void Build2Roads::use_card(Player &p, Catan &c) {
        p.addResource("wood", 2);
        p.addResource("brick", 2);

        bool check = false;
        unsigned int from, to;

        cout << "First road" << endl;
        while (!check) {
            cout << "From: " << endl;
            cin >> from;
            cout << "To: " << endl;
            cin >> to;

            if(p.placeRoad(from, to, *c.getBoard()))
                check = true;
            else
                cout << "Try again!" << endl;
        }

        check = false;

        cout << "Second road" << endl;
        while (!check){
            cout << "From: " << endl;
            cin >> from;
            cout << "To: " << endl;
            cin >> to;

            if(p.placeRoad(from, to, *c.getBoard()))
                check = true;
            else
                cout << "Try again!" << endl;
        }

        p.useCard("build2Roads");
    }

    YearOfPlenty::YearOfPlenty() : Card("Year of Plenty") {}
    void YearOfPlenty::use_card(Player &p, Catan &c) {
        string choice;
        bool check = false;

        while (!check) {
            cout << "Choose the first resource to get: " << endl;
            cin >> choice;

            if (choice == "wood") {
                p.addResource("wood", 1);
                check = true;
            }
            else if (choice == "brick") {
                p.addResource("brick", 1);
                check = true;
            }
            else if (choice == "sheep") {
                p.addResource("sheep", 1);
                check = true;
            }
            else if (choice == "stone") {
                p.addResource("stone", 1);
                check = true;
            }
            else if (choice == "wheat") {
                p.addResource("wheat", 1);
                check = true;
            }
            else
                cout << "Not a valid type. Try again." << endl;
        }

        check = false;

        while (!check) {
            cout << "Choose the second resource to get: " << endl;
            cin >> choice;

            if (choice == "wood") {
                p.addResource("wood", 1);
                check = true;
            }
            else if (choice == "brick") {
                p.addResource("brick", 1);
                check = true;
            }
            else if (choice == "sheep") {
                p.addResource("sheep", 1);
                check = true;
            }
            else if (choice == "stone") {
                p.addResource("stone", 1);
                check = true;
            }
            else if (choice == "wheat") {
                p.addResource("wheat", 1);
                check = true;
            }
            else
                cout << "Not a valid type. Try again." << endl;
        }

        p.useCard("yearofplenty");
    }

    Knight::Knight() : Card("Knight") {}
    void Knight::use_card(Player &p, Catan &c) {
        cout << "Added a Knight" << endl;

        p.useKnight();

        if(p.getUsedKnights() == 3)
            p.KnightsPoints();
    }

    VictoryPoint::VictoryPoint() : Card("Victory Point") {}
    void VictoryPoint::use_card(Player &p, Catan &c) {
        cout << "Added a Victory Point" << endl;
    }
}
