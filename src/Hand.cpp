#include <iostream>
#include <vector>
#include <string>
#ifndef GAME_H
#define GAME_H
#include "Game.h"
#endif

using namespace std;

class Hand
{

    private:
        vector<string> deck = 
                        { 
                            "AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH",
                            "AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC",
                            "AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD",
                            "AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS",
                        };

        string board[5] = { "TBD", "TBD", "TBD", "TBD", "TBD" };
        string player1_hand[2] = { "TBD", "TBD" };
        string player2_hand[2] = { "TBD", "TBD" };
        float pot = 0.0f;


    public:
        string * Hand::getPlayer1Hand()
        {
            return player1_hand;
        }

        string * Hand::getPlayer2Hand()
        {
            return player2_hand;
        }

        string * Hand::getBoard()
        {
            return board;
        }

        string * Hand::getPossibleActions()
        {
            return nullptr;
        }

};

