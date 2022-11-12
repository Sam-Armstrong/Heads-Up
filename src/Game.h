#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Game
{
    private:
        string CARDS[53] = { 
                            "TBD",
                            "AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH",
                            "AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC",
                            "AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD",
                            "AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS",
                          };
        float player1_stack;
        float player2_stack;
        float bb;
        float sb;
        string player1_hand[2];
        string player2_hand[2];
        string board[5];
        Deck deck;
        int game_stage;
        bool continuing;
        int winner;
        int dealer;
    public:
        Game();
        Game(float stack1, float stack2, float big_blind);
        void runGame(int maxIterations);
        void nextHand();
        void resetHands();
        bool bettingRound();
        int winningHand(string hole_cards1[2], string hole_cards2[2], string current_board[2]);
        string getPlayerDecision(int player_num);
};