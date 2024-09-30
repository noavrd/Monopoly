#include "ChanceCard.hpp"
#include <iostream>

std::vector<ChanceCard> initializeChanceCards() {
    return {
        {"Advance to Go (Collect $200)", [](Player& player, std::vector<Player>&, int&) {
            player.position = 0;  // Go to "Go"
            player.addCash(200);
            std::cout << player.name << " advances to Go and collects $200!" << std::endl;
        }},
        {"Bank pays you dividend of $50", [](Player& player, std::vector<Player>&, int&) {
            player.addCash(50);
            std::cout << player.name << " receives $50 dividend from the bank!" << std::endl;
        }},
        {"Go back 3 spaces", [](Player& player, std::vector<Player>&, int&) {
            player.move(-3);  // Move back 3 spaces
            std::cout << player.name << " goes back 3 spaces!" << std::endl;
        }},
        {"Go directly to Jail – do not pass Go, do not collect $200", [](Player& player, std::vector<Player>&, int&) {
            player.goToJail();
            std::cout << player.name << " is sent directly to jail!" << std::endl;
        }},
        {"Make general repairs on all your property – For each house pay $25 – For each hotel $100", [](Player& player, std::vector<Player>&, int&) {
            int houseCost = 25;
            int hotelCost = 100;
            int totalCost = 0;
            for (auto& tile : player.ownedProperties) {
                Property* property = dynamic_cast<Property*>(tile);
                if (property) {
                    totalCost += property->houses * houseCost;
                    if (property->hasHotel) {
                        totalCost += hotelCost;
                    }
                }
            }
            player.subtractCash(totalCost);
            std::cout << player.name << " pays $" << totalCost << " for property repairs!" << std::endl;
        }},
        {"Pay poor tax of $15", [](Player& player, std::vector<Player>&, int&) {
            player.subtractCash(15);
            std::cout << player.name << " pays poor tax of $15!" << std::endl;
        }},
        {"Take a trip to Reading Railroad – If you pass Go collect $200", [](Player& player, std::vector<Player>&, int&) {
            if (player.position > 5) player.addCash(200);  // Pass Go
            player.position = 5;  // Go to Reading Railroad
            std::cout << player.name << " takes a trip to Reading Railroad!" << std::endl;
        }},
        {"Take a walk on the Boardwalk – Advance token to Boardwalk", [](Player& player, std::vector<Player>&, int&) {
            player.position = 39;  // Move to Boardwalk
            std::cout << player.name << " advances to Boardwalk!" << std::endl;
        }},
        {"You have been elected Chairman of the Board – Pay each player $50", [](Player& player, std::vector<Player>& players, int&) {
            int totalCost = 50 * (players.size() - 1);  // Pay each player $50
            player.subtractCash(totalCost);
            for (auto& otherPlayer : players) {
                if (&otherPlayer != &player) {
                    otherPlayer.addCash(50);
                }
            }
            std::cout << player.name << " pays $50 to each player!" << std::endl;
        }},
        {"Your building loan matures – Collect $150", [](Player& player, std::vector<Player>&, int&) {
            player.addCash(150);
            std::cout << player.name << " collects $150!" << std::endl;
        }},
        // {"Get out of Jail Free – This card may be kept until needed or traded", [](Player& player, std::vector<Player>&, int&) {
        //     player.getOutOfJailFreeCard = true;
        //     std::cout << player.name << " receives a Get Out of Jail Free card!" << std::endl;
        // }},
        {"Advance to Illinois Ave. – If you pass Go, collect $200", [](Player& player, std::vector<Player>&, int&) {
            if (player.position > 24) player.addCash(200);  // Pass Go
            player.position = 24;  // Move to Illinois Ave.
            std::cout << player.name << " advances to Illinois Ave!" << std::endl;
        }},
        {"Advance to St. Charles Place – If you pass Go, collect $200", [](Player& player, std::vector<Player>&, int&) {
            if (player.position > 11) player.addCash(200);  // Pass Go
            player.position = 11;  // Move to St. Charles Place
            std::cout << player.name << " advances to St. Charles Place!" << std::endl;
        }},
        {"You are assessed for street repairs – $40 per house, $115 per hotel", [](Player& player, std::vector<Player>&, int&) {
            int houseCost = 40;
            int hotelCost = 115;
            int totalCost = 0;
            for (auto& tile : player.ownedProperties) {
                Property* property = dynamic_cast<Property*>(tile);
                if (property) {
                    totalCost += property->houses * houseCost;
                    if (property->hasHotel) {
                        totalCost += hotelCost;
                    }
                }
            }
            player.subtractCash(totalCost);
            std::cout << player.name << " pays $" << totalCost << " for street repairs!" << std::endl;
        }},
    };
}
