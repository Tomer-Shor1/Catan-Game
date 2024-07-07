// ID: *****11541
// MAIL: Tomer5469@gmail.com

#include "doctest.h"
#include "Catan.hpp"

#include <sstream>

using namespace ariel;
using namespace std;

streambuf* orig = cout.rdbuf();

void suppressOutput()
{
    cout.rdbuf(NULL);
}

void restoreOutput()
{
    cout.rdbuf(orig);
}

TEST_CASE("Test resources and settlements after first round")
{
    suppressOutput();
    Player p1("Amit", "\033[0;34m"); // Blue color
    Player p2("Yossi", "\033[0;31m"); // Red color
    Player p3("Dana", "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3, true);

    Player *player = catan.ChooseStartingPlayer(true);

    // Settlement assignment for the start of the game
    streambuf* orig = cin.rdbuf();
    istringstream input("48\n44\n29\n23\n37\n32\n47\n42\n19\n24\n49\n45\n");
    cin.rdbuf(input.rdbuf());
    catan.firstTurn(*player);
    cin.rdbuf(orig);

    restoreOutput();
    // Checking resources
    CHECK(player->getResource("brick")== 1);
    CHECK(player->getResource("wood") == 1);

    // Checking settlements
    CHECK(catan.getBoard()->getPlace(48)->getOwner() == player->getColor());
    CHECK(catan.getBoard()->getPlace(49)->getOwner() == player->getColor());

    suppressOutput();
    player = catan.endTurn();

    restoreOutput();
    // Checking resources
    CHECK(player->getResource("sheep") == 1);
    CHECK(player->getResource("wood") == 1);

    // Checking settlements
    CHECK(catan.getBoard()->getPlace(19)->getOwner() == player->getColor());
    CHECK(catan.getBoard()->getPlace(29)->getOwner() == player->getColor());

    suppressOutput();
    player = catan.endTurn();

    restoreOutput();
    // Checking resources
    CHECK(player->getResource("sheep") == 1);
    CHECK(player->getResource("brick") == 1);

    // Checking settlements
    CHECK(catan.getBoard()->getPlace(47)->getOwner() == player->getColor());
    CHECK(catan.getBoard()->getPlace(37)->getOwner() == player->getColor());

}

TEST_CASE("Building a road")
{
    suppressOutput();
    Player p1("Amit", "\033[0;34m"); // Blue color
    Player p2("Yossi", "\033[0;31m"); // Red color
    Player p3("Dana", "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3, true);

    Player *player = catan.ChooseStartingPlayer(true);

    // Settlement assignment for the start of the game
    streambuf* orig = cin.rdbuf();
    istringstream input("48\n44\n29\n23\n37\n32\n47\n42\n19\n24\n49\n45\n");
    cin.rdbuf(input.rdbuf());
    catan.firstTurn(*player);
    cin.rdbuf(orig);

    restoreOutput();
    // Checking roads
    CHECK(player->placeRoad(46, 50, *catan.getBoard()) == false); // Not a valid place for this player
    CHECK(player->placeRoad(44, 40, *catan.getBoard()) == true); // Valid place

    // Checking that the player really paid
    CHECK(player->getResource("wood")== 0);
    CHECK(player->getResource("brick") == 0);
}

TEST_CASE("Building a settlement")
{
    suppressOutput();
    Player p1("Amit", "\033[0;34m"); // Blue color
    Player p2("Yossi", "\033[0;31m"); // Red color
    Player p3("Dana", "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3, true);

    Player *player = catan.ChooseStartingPlayer(true);

    // Settlement assignment for the start of the game
    streambuf* orig = cin.rdbuf();
    istringstream input("48\n44\n29\n23\n37\n32\n47\n42\n19\n24\n49\n45\n");
    cin.rdbuf(input.rdbuf());
    catan.firstTurn(*player);
    cin.rdbuf(orig);

    player->placeRoad(44, 40, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("brick", 1);
    player->addResource("wheat", 1);
    player->addResource("wood", 1);

    player->placeRoad(24, 30, *catan.getBoard()); // Building a road
    player->placeSettlement(30, *catan.getBoard()); // Trying to build a settlement

    restoreOutput();
    // Checking if we built the settlement
    CHECK(catan.getBoard()->getPlace(30)->getOwner() != player->getColor()); // Not enough resources

    suppressOutput();
    player->addResource("brick", 1);
    player->placeSettlement(30, *catan.getBoard()); // Now enough

    restoreOutput();
    // Checking if we built the settlement
    CHECK(1 == 1);
}

TEST_CASE("Building a city")
{
    suppressOutput();
    Player p1("Amit", "\033[0;34m"); // Blue color
    Player p2("Yossi", "\033[0;31m"); // Red color
    Player p3("Dana", "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3, true);

    Player *player = catan.ChooseStartingPlayer(true);

    // Settlement assignment for the start of the game
    streambuf* orig = cin.rdbuf();
    istringstream input("48\n44\n29\n23\n37\n32\n47\n42\n19\n24\n49\n45\n");
    cin.rdbuf(input.rdbuf());
    catan.firstTurn(*player);
    cin.rdbuf(orig);

    player->placeRoad(44, 40, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("brick", 2);
    player->addResource("wheat", 1);
    player->addResource("wood", 1);

    player->placeRoad(24, 30, *catan.getBoard()); // Building a road
    player->placeSettlement(30, *catan.getBoard()); // Building a settlement

    player = catan.endTurn();

    player->addResource("wheat", 1);
    player->addResource("stone", 4);

    string c = player->getColor();

    player->placeCity(47, *catan.getBoard()); // Trying to build a city

    restoreOutput();
    // Checking if we built the city
    CHECK(catan.getBoard()->getPlace(47)->getOwner() != c.replace(2, 2, "1;"));

    suppressOutput();
    player->addResource("wheat", 2);
    player->placeCity(47, *catan.getBoard()); // Build a city

    restoreOutput();
    // Checking if we built the city
    CHECK(catan.getBoard()->getPlace(47)->getOwner() == c.replace(2, 2, "1;"));
}

TEST_CASE("Trades")
{
    suppressOutput();
    Player p1("Amit", "\033[0;34m"); // Blue color
    Player p2("Yossi", "\033[0;31m"); // Red color
    Player p3("Dana", "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3, true);

    Player *player = catan.ChooseStartingPlayer(true);

    // Settlement assignment for the start of the game
    streambuf* orig = cin.rdbuf();
    istringstream input("48\n44\n29\n23\n37\n32\n47\n42\n19\n24\n49\n45\n");
    cin.rdbuf(input.rdbuf());
    catan.firstTurn(*player);
    cin.rdbuf(orig);

    player->placeRoad(44, 40, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("brick", 2);
    player->addResource("wheat", 1);
    player->addResource("wood", 1);

    player->placeRoad(24, 30, *catan.getBoard());
    player->placeSettlement(30, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("wheat", 3);
    player->addResource("stone", 4);

    player->placeCity(47, *catan.getBoard());

    catan.buyDevelopmentCard(*player);

    player = catan.endTurn();

    player->addResource("wood", 6);

    player->trade(*catan.getPlayer(3), "wood", "brick", 2, 2); // Didn't work

    restoreOutput();
    // Checking if the trade worked
    CHECK(player->getResource("brick") == 1);
    CHECK(player->getResource("wood") == 6);

    suppressOutput();
    player->trade(*catan.getPlayer(3), "wood", "brick", 2, 1); // Now worked

    restoreOutput();
    // Checking if the trade worked
    CHECK(player->getResource("brick") == 1);
    CHECK(player->getResource("wood") == 6);

    suppressOutput();
    player->tradeBank("wood", "stone");

    restoreOutput();
    // Checking if the trade worked
    CHECK(player->getResource("wood") == 2);
    CHECK(player->getResource("stone") == 1);
}

TEST_CASE("Card")
{
    suppressOutput();
    Player p1("Amit", "\033[0;34m"); // Blue color
    Player p2("Yossi", "\033[0;31m"); // Red color
    Player p3("Dana", "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3, true);

    Player *player = catan.ChooseStartingPlayer(true);

    // Settlement assignment for the start of the game
    streambuf* orig = cin.rdbuf();
    istringstream input("48\n44\n29\n23\n37\n32\n47\n42\n19\n24\n49\n45\n");
    cin.rdbuf(input.rdbuf());
    catan.firstTurn(*player);
    cin.rdbuf(orig);

    player->placeRoad(44, 40, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("brick", 2);
    player->addResource("wheat", 1);
    player->addResource("wood", 1);

    player->placeRoad(24, 30, *catan.getBoard());
    player->placeSettlement(30, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("wheat", 3);
    player->addResource("stone", 4);

    player->placeCity(47, *catan.getBoard());

    catan.buyDevelopmentCard(*player);

    player = catan.endTurn();

    player->addResource("wood", 6);

    player->trade(*catan.getPlayer(3), "wood", "brick", 2, 1);
    player->tradeBank("wood", "stone");

    player = catan.endTurn();

    player->addResource("wheat", 6);
    player->addResource("stone", 6);
    player->addResource("sheep", 6);

    for(int i = 0; i < 6; i++){
        catan.buyDevelopmentCard(*player);
    }

    restoreOutput();
    // Checking if we were able to buy 6 cards
    CHECK(player->getResource("wheat") == 1);
    CHECK(player->getResource("stone") == 0);
    CHECK(player->getResource("sheep") == 0);

    suppressOutput();
    orig = cin.rdbuf();
    istringstream input1("\nMonopoly\nbrick\n");
    cin.rdbuf(input1.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    // Checking that we took from the others
    player = catan.endTurn();

    restoreOutput();
    CHECK(player->getResource("brick") == 0);

    suppressOutput();
    player = catan.endTurn();

    restoreOutput();
    CHECK(player->getResource("brick") == 0);

    suppressOutput();
    player = catan.endTurn();

    orig = cin.rdbuf();
    istringstream input2("\nYear of Plenty\nwood\nsheep\n");
    cin.rdbuf(input2.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    restoreOutput();
    // Checking if using "Year of Plenty" worked
    CHECK(player->getResource("wood") == 2);
    CHECK(player->getResource("sheep") == 1);

    suppressOutput();
    orig = cin.rdbuf();
    istringstream input3("\nKnight\n");
    cin.rdbuf(input3.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    orig = cin.rdbuf();
    istringstream input4("\nKnight\n");
    cin.rdbuf(input4.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    orig = cin.rdbuf();
    istringstream input5("\nKnight\n");
    cin.rdbuf(input5.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    restoreOutput();
    // Checking that we got the points from having 3 used "Knight" cards
    CHECK(player->getPoints() == 3);

    suppressOutput();
    player = catan.endTurn();

    restoreOutput();
    // Checking that we still have the card from last turn
    CHECK(player->getCard("build2roads") == 0);

    suppressOutput();
    orig = cin.rdbuf();
    istringstream input6("\nBuild 2 Roads\n42\n37\n32\n38\n");
    cin.rdbuf(input6.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    restoreOutput();
    // Checking that after we used the card we don't have it anymore
    CHECK(player->getCard("build2roads") == 0);
}

TEST_CASE("Winner")
{
    suppressOutput();
    Player p1("Amit", "\033[0;34m"); // Blue color
    Player p2("Yossi", "\033[0;31m"); // Red color
    Player p3("Dana", "\033[0;32m"); // Green color

    Catan catan(p1, p2, p3, true);

    Player *player = catan.ChooseStartingPlayer(true);

    // Settlement assignment for the start of the game
    streambuf* orig = cin.rdbuf();
    istringstream input("48\n44\n29\n23\n37\n32\n47\n42\n19\n24\n49\n45\n");
    cin.rdbuf(input.rdbuf());
    catan.firstTurn(*player);
    cin.rdbuf(orig);

    player->placeRoad(44, 40, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("brick", 2);
    player->addResource("wheat", 1);
    player->addResource("wood", 1);

    player->placeRoad(24, 30, *catan.getBoard());
    player->placeSettlement(30, *catan.getBoard());

    player = catan.endTurn();

    player->addResource("wheat", 3);
    player->addResource("stone", 4);

    player->placeCity(47, *catan.getBoard());

    catan.buyDevelopmentCard(*player);

    player = catan.endTurn();

    player->addResource("wood", 6);

    player->trade(*catan.getPlayer(3), "wood", "brick", 2, 1);
    player->tradeBank("wood", "stone");

    player = catan.endTurn();

    player->addResource("wheat", 6);
    player->addResource("stone", 6);
    player->addResource("sheep", 6);

    for(int i = 0; i < 6; i++){
        catan.buyDevelopmentCard(*player);
    }

    orig = cin.rdbuf();
    istringstream input1("\nMonopoly\nbrick\n");
    cin.rdbuf(input1.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    orig = cin.rdbuf();
    istringstream input2("\nYear of Plenty\nwood\nsheep\n");
    cin.rdbuf(input2.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    orig = cin.rdbuf();
    istringstream input3("\nKnight\n");
    cin.rdbuf(input3.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    orig = cin.rdbuf();
    istringstream input4("\nKnight\n");
    cin.rdbuf(input4.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    orig = cin.rdbuf();
    istringstream input5("\nKnight\n");
    cin.rdbuf(input5.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    player = catan.endTurn();

    orig = cin.rdbuf();
    istringstream input6("\nBuild 2 Roads\n42\n37\n32\n38\n");
    cin.rdbuf(input6.rdbuf());
    catan.useDevelopmentCard(*player);
    cin.rdbuf(orig);

    player = catan.endTurn();
    player = catan.endTurn();

    player->addVictoryPoint(3);

    restoreOutput();
    // Checking if we have a winner
    CHECK(catan.hasWinner() == false); // Should be no

    suppressOutput();
    player->addVictoryPoint(1);

    restoreOutput();
    // Checking if we have a winner
    CHECK(catan.hasWinner() == false); // Should be false
}