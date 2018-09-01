#include "Fact.hpp"

Fact::Fact(char letter, char state = ES_UNDEFINED) {
    this->letter = letter;
    this->state = state;
}

Fact::~Fact() {}

char    Fact::getLetter() const {
    return (this->letter);
}

char    Fact::getState() const {
    return (this->state);
}