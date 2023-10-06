#include "card.h"

Card::Card() : value(0), suite("INVALID") {}

Card::Card(int val, const std::string& suit) : value(val), suite(suit) {}