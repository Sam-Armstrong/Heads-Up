#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <time.h>

#ifndef DECK_H
#define DECK_H
#include "Deck.h"
#endif

using namespace std;

/**
 * @brief Construct a new Deck object
 */
Deck::Deck() // Game constructor
{
}

/**
 * @brief Draw a random card and remove it from the deck
 * 
 * @return string 
 */
string Deck::drawCard()
{
    srand(time(0)); // Uses the current time to seed the random generator
    int random_idx = rand() % deck.size() - 1; // Selects random int in deck
    auto card_iterator = deck.begin();
    advance(card_iterator, random_idx); // Locates card
    string card = *card_iterator; // Converts iterator to string
    deck.remove(card); // Removes card from the deck
    return card;
}

/**
 * @brief Reset the deck to the complete set of cards
 */
void Deck::reset()
{
    deck = CARDS;
}

// int main()
// {
//     Deck d = Deck();
//     d.drawCard();
//     return 0;
// }