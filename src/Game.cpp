#include <iostream>
#include <vector>
#ifndef GAME_H
#define GAME_H
#include "Game.h"
#endif
#ifndef DECK_H
#define DECK_H
#include "Deck.h"
#endif

using namespace std;

/**
 * @brief Construct a new Game object
 */
Game::Game(float stack1, float stack2, float big_blind) // Game constructor
{
    player1_stack = stack1;
    player2_stack = stack2;
    bb = big_blind;
    sb = floor(big_blind / 2);
    resetHands();
    int game_stage = 0; // Defines the stage the hand is at - how many cards have been revealed, etc
    int dealer = 1;
}

void Game::runGame(int maxHands)
{
    for (int i = 0; i < maxHands; i++)
    {
        if (i % 2 == 1)
        {
            dealer = 1;
        }
        else
        {
            dealer = 2;
        }

        resetHands();
        nextHand();
    }
}

/**
 * @brief One hand of play in the context of the game 
 */
void Game::nextHand()
{
    player1_hand[0] = deck.drawCard();
    player1_hand[1] = deck.drawCard();
    player2_hand[0] = deck.drawCard();
    player2_hand[1] = deck.drawCard();

    continuing = bettingRound();

    if (continuing)
    {
        board[0] = deck.drawCard();
        board[1] = deck.drawCard();
        board[2] = deck.drawCard();
        continuing = bettingRound();

        if (continuing)
        {
            board[3] = deck.drawCard();
            continuing = bettingRound();

            if (continuing)
            {
                board[4] = deck.drawCard();
                continuing = bettingRound();

                if (continuing)
                {
                    winner = winningHand(player1_hand, player2_hand, board);
                }
            }
        }
    }
}

void Game::resetHands()
{
    player1_hand[0] = "TBD";
    player1_hand[1] = "TBD";
    player2_hand[0] = "TBD";
    player2_hand[1] = "TBD";
    board[0] = "TBD";
    board[1] = "TBD";
    board[2] = "TBD";
    board[3] = "TBD";
    board[4] = "TBD";
    winner = 0;
    continuing = true; // True when no one has folded, False when one player has
}

/**
 * @brief Logic for a single round of betting
 * 
 * @return true if the hand should continue after this round (nobody folded)
 * @return false if the hand should not continue after this hand (player folded)
 */
bool Game::bettingRound()
{
    // TODO: Add correct logic for pre-flop (big-blind)
    // TODO: Add logic for if a player has called more than their stack

    bool each_player_been = false;
    float player1_pot_commit = 0;
    float player2_pot_commit = 0;
    int player_pot_commit[] = {0, 0};
    int player_to_act = playerToGo(dealer);
    bool player_folded = false;
    int it = 0;
    string decision;

    while (each_player_been == false || player1_pot_commit != player1_pot_commit)
    {
        decision = getPlayerDecision(player_to_act);

        if (decision == "fold")
        {
            player_folded = true;
            break; // TODO: Check that break cuts out of the loop
        }
        else if (decision == "call")
        {
            // Removes the call amount from the stack of the player who called, and adds to the pot

            if (player_to_act == 1)
            {
                player1_pot_commit = player2_pot_commit;
                player1_stack -= player2_pot_commit - player1_pot_commit;
            }
            else
            {
                player2_pot_commit = player1_pot_commit;
                player2_stack -= player1_pot_commit - player2_pot_commit;
            }
        }
        else if (decision.find("bet") != string::npos) // Check if the decision string contains the word 'bet'
        {

        }
        else if (decision == "check")
        {

        }
        else if (decision.find("raise") != string::npos)
        {

        }

        player_to_act = playerToGo(player_to_act);
        it++;

        if (it == 2)
        {
            each_player_been = true;
        }
    }

    return player_folded;
}

int Game::winningHand(string hole_cards1[2], string hole_cards2[2], string current_board[2])
{
    // Hand showndown logic goes here
    return 0;
}

string Game::getPlayerDecision(int player_num)
{
    if (player_num == 1)
    {
        cout << "Player 1 Enter Your Decision: ";
    }
    else
    {
        cout << "Player 2 Enter Your Decision: ";
    }

    string player_dec_str;
    cin >> player_dec_str;
    return player_dec_str;
}

int Game::playerToGo(int previous_player)
{
    if (previous_player == 1)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}
