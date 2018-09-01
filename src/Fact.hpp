#ifndef FACT_HPP
#define FACT_HPP

typedef enum FactStates_e {ES_FALSE, ES_TRUE, ES_UNDEFINED, ES_UNSOLVED};

class Fact {
    char    letter = 0;
    char    state = ES_UNDEFINED;

public:
    Fact(char letter, char state);
    ~Fact();

    char    getLetter() const;
    char    getState() const;
};

#endif // FACT_HPP