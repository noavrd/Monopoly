#pragma once
#include <vector>
#include "Player.hpp"

// Declare the ChanceCard structure
struct ChanceCard {
    std::string description;
    std::function<void(Player&, std::vector<Player>&, int&)> applyEffect;
};

// Declare the function that initializes the chance cards
std::vector<ChanceCard> initializeChanceCards();
