// ID: *****11541
// MAIL: Tomer5469@gmail.com

#include <iostream>
#include <stdexcept>

#include "Catan.hpp"
#include "Player.hpp"

using namespace ariel;
using namespace std;

int main() {
    string name1, name2, name3;

    cout << "\nWelcome to a Catan Game!\n\nPlease insert your names:" << endl;
    cout << "Player 1 (You're Blue):" << endl;
    cin >> name1;
    cout << "Player 2 (You're Red):" << endl;
    cin >> name2;
    cout << "Player 3 (You're Green):" << endl;
    cin >> name3;

    // Creating the players for the game
    Player p1(name1, "\033[0;34m"); // Blue color
    Player p2(name2, "\033[0;31m"); // Red color
    Player p3(name3, "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3); // Creating the game

    Player *player = catan.ChooseStartingPlayer(); // Prints the name of the first player


    // Settlement assignment for the start of the game
    catan.firstTurn(*player);

    catan.getBoard()->printBoard(); // The start of the game
    cout << player->getName() << "'s turn!" << endl;

    int dice, menu;
    unsigned int from, to, place;
    string name, get, give;
    int getNum, giveNum;
    Player* pForTrade = player;

    // While we don't have a winner we keep playing
    while (!catan.hasWinner()) {
        dice = player->rollDice(); // Dice result
        catan.updateResources(dice); // Updating the players resources based on the dice result

        menu = 9;

        while (menu != 8) { // Every step the player can see its resources and cards
            cout << "==============================" << endl;
            cout << player->getName() << ", your resources: " << endl;
            cout << "Wood: " << player->getResource("wood") << endl;
            cout << "Brick: " << player->getResource("brick") << endl;
            cout << "Sheep: " << player->getResource("sheep") << endl;
            cout << "Stone: " << player->getResource("stone") << endl;
            cout << "Wheat: " << player->getResource("wheat") << endl;
            cout << "------------------------------" << endl;
            cout << "Your cards: " << endl;
            cout << "Monopoly: " << player->getCard("monopoly") << endl;
            cout << "Build 2 Roads: " << player->getCard("build2roads") << endl;
            cout << "Year of Plenty: " << player->getCard("yearofplenty") << endl;
            cout << "Knight: " << player->getCard("knight") << endl;
            cout << "Victory Point: " << player->getCard("victorypoint") << endl;
            cout << "------------------------------" << endl;
            cout << "Points: " << player->getPoints() << endl;
            cout << "==============================" << endl;
            cout << "Choose your move:" << endl;
            cout << "1 - Build road" << endl;
            cout << "2 - Build settlement" << endl;
            cout << "3 - Upgrade to city" << endl;
            cout << "4 - Trade resources with another player" << endl;
            cout << "5 - Trade with bank" << endl;
            cout << "6 - Buy development card" << endl;
            cout << "7 - Use development card" << endl;
            cout << "8 - End turn" << endl;
            cout << "0 - Exit game" << endl;

            cin >> menu;

            switch (menu) {
                case 1:
                    cout << "Where do you want to build the road? (0 to change move)" << endl;

                    cout << "From: " << endl;
                    cin >> from;

                    if(from == 0)
                        break;

                    cout << "To: " << endl;
                    cin >> to;

                    player->placeRoad(from, to, *catan.getBoard());
                    break;
                case 2:
                    cout << "Where do you want to build the settlement? (0 to change move)" << endl;

                    cin >> place;

                    if(place == 0)
                        break;

                    player->placeSettlement(place, *catan.getBoard());
                    break;
                case 3:
                    cout << "Choose settlement's place to upgrade it. (0 to change move)" << endl;

                    cin >> place;

                    if(place == 0)
                        break;

                    player->placeCity(place, *catan.getBoard());
                    break;
                case 4:
                    cout << "Who do you wanna trade with? (0 to change move)" << endl;

                    cin >> name;

                    if(name == "0")
                        break;

                    if(player->getName() == name) {
                        cout << "Can't make a trade with yourself" << endl;
                        break;
                    }

                    if(catan.getPlayer(1)->getName() == name)
                        pForTrade = catan.getPlayer(1);

                    else if(catan.getPlayer(2)->getName() == name)
                        pForTrade = catan.getPlayer(2);

                    else if(catan.getPlayer(3)->getName() == name)
                        pForTrade = catan.getPlayer(3);

                    else{
                        cout << "Not a valid name!" << endl;
                        break;
                    }

                    cout << "What do you want to get and how many?" << endl;

                    cout << "What: " << endl;
                    cin >> get;

                    cout << "How many: " << endl;
                    cin >> getNum;

                    cout << "What do you want to give and how many?" << endl;

                    cout << "What: " << endl;
                    cin >> give;

                    cout << "How many: " << endl;
                    cin >> giveNum;

                    if(player->getName() != pForTrade->getName())
                        player->trade(*pForTrade, give, get, giveNum, getNum);
                    else
                        cout << "The same" << endl;
                    break;
                case 5:
                    cout << "What do you want to give? (0 to change move)" << endl;

                    cin >> give;

                    if(give == "0")
                        break;

                    cout << "What do you want to get?" << endl;
                    cin >> get;

                    player->tradeBank(give, get);
                    break;
                case 6:
                    catan.buyDevelopmentCard(*player);
                    break;
                case 7:
                    catan.useDevelopmentCard(*player);
                    break;
                case 8:
                    player = catan.endTurn();
                    break;
                case 0:
                    cout << "Exiting game." << endl;
                    return 0; // Exit the game loop and end the program
                default:
                    cout << "Invalid choice. Please choose a valid option." << endl;
                    break;
            }
            catan.getBoard()->printBoard();
        }
    }
    catan.printWinner();
    return 0;
}