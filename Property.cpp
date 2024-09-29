#include "Property.hpp"
#include "Player.hpp"

Property::Property(const std::string& propertyName, int propertyPrice, int propertyRent, int houseCost, int rentHouse, int rentHotel)
    : name(propertyName), price(propertyPrice), rent(propertyRent), houseCost(houseCost),
      rentWithHouse(rentHouse), rentWithHotel(rentHotel), owner(nullptr), houses(0), hasHotel(false) {}

int Property::calculateRent() const {
    if (hasHotel) {
        return rentWithHotel;
    } else if (houses > 0) {
        return rentWithHouse * (1 << (houses - 1));
    } else {
        return rent;
    }
}
