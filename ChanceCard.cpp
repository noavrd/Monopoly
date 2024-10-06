#include "ChanceCard.hpp"
#include <iostream>

using namespace std;

/*
 * Initializes the list of Chance cards with various actions.
 * Each card has a description and a corresponding lambda function
 * that defines the action performed when the card is drawn.
 * The actions affect the player drawing the card and, in some cases,
 * other players in the game.
 */
vector<ChanceCard> initializeChanceCards() {
    return {
        {"Advance to Go (Collect $200)", [](Player& player, vector<Player>&, int&) {
            player.position = 0;  // Go to "Go"
            player.addCash(200);
            cout << player.name << " advances to Go and collects $200!" << endl;
        }},
        {"Bank pays you dividend of $50", [](Player& player, vector<Player>&, int&) {
            player.addCash(50);
            cout << player.name << " receives $50 dividend from the bank!" << endl;
        }},
        {"Go back 3 spaces", [](Player& player, vector<Player>&, int&) {
            player.move(-3);  // Move back 3 spaces
            cout << player.name << " goes back 3 spaces!" << endl;
        }},
        {"Go directly to Jail – do not pass Go, do not collect $200", [](Player& player, vector<Player>&, int&) {
            player.goToJail();
        }},
        {"Pay poor tax of $15", [](Player& player, vector<Player>&, int&) {
            player.subtractCash(15);
            cout << player.name << " pays poor tax of $15!" << endl;
        }},
        {"Take a trip to Reading Railroad – If you pass Go collect $200", [](Player& player, vector<Player>&, int&) {
            if (player.position > 5) player.addCash(200);  // Pass Go
            player.position = 5;  // Go to Reading Railroad
            cout << player.name << " takes a trip to Reading Railroad!" << endl;
        }},
        {"Take a walk on the Boardwalk – Advance token to Boardwalk", [](Player& player, vector<Player>&, int&) {
            player.position = 39;  // Move to Boardwalk
            cout << player.name << " advances to Boardwalk!" << endl;
        }},
        {"You have been elected Chairman of the Board – Pay each player $50", [](Player& player, vector<Player>& players, int&) {
            int totalCost = 50 * (players.size() - 1);  // Pay each player $50
            player.subtractCash(totalCost);
            for (auto& otherPlayer : players) {
                if (&otherPlayer != &player) {
                    otherPlayer.addCash(50);
                }
            }
            cout << player.name << " pays $50 to each player!" << endl;
        }},
        {"Your building loan matures – Collect $150", [](Player& player, vector<Player>&, int&) {
            player.addCash(150);
            cout << player.name << " collects $150!" << endl;
        }},
        {"Get out of Jail Free – This card may be kept until needed or traded", [](Player& player, vector<Player>&, int&) {
            player.hasGetOutOfJailCard = true;
            cout << player.name << " receives a Get Out of Jail Free card!" << endl;
        }},
        {"Advance to Illinois Ave. – If you pass Go, collect $200", [](Player& player, vector<Player>&, int&) {
            if (player.position > 24) player.addCash(200);  // Pass Go
            player.position = 24;  // Move to Illinois Ave.
            cout << player.name << " advances to Illinois Ave!" << endl;
        }},
        {"Advance to St. Charles Place – If you pass Go, collect $200", [](Player& player, vector<Player>&, int&) {
            if (player.position > 11) player.addCash(200);  // Pass Go
            player.position = 11;  // Move to St. Charles Place
            cout << player.name << " advances to St. Charles Place!" << endl;
        }},
        {"You are assessed for street repairs – $40 per house, $115 per hotel", [](Player& player, vector<Player>&, int&) {
            int houseCost = 40;
            int hotelCost = 115;
            int totalCost = 0;
            // Loop through each owned tile and calculate repair costs based on houses and hotels
            for (auto& tile : player.ownedTiles) {
                Tile* property = dynamic_cast<Tile*>(tile);
                if (property) {
                    totalCost += property->houses * houseCost;
                    if (property->hasHotel) {
                        totalCost += hotelCost;
                    }
                }
            }
            player.subtractCash(totalCost);
            cout << player.name << " pays $" << totalCost << " for street repairs!" << endl;
        }},
    };
}
