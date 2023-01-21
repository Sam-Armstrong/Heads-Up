#include <iostream>
#include <vector>
#include <algorithm>
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

int Game::winningHand(string hole_cards1[2], string hole_cards2[2], string current_board[5])
{
    // Create the two full hands
    
    string hand1[7];
    string hand2[7];

    std::copy(hole_cards1, hole_cards1 + 2, hand1);
    std::copy(current_board, current_board + 5, hand1 + 2);
    std::copy(hole_cards2, hole_cards2 + 2, hand2);
    std::copy(current_board, current_board + 5, hand2 + 2);


    // Check for a straight flush

    bool hand1StraightFlush = true;
    bool hand2StraightFlush = true;

    for (int i = 0; i < 7; i++) 
    {
        if (hand1[i][1] != hand1[0][1]) 
        {
            hand1StraightFlush = false;
        }
        if (hand2[i][1] != hand2[0][1]) 
        {
            hand2StraightFlush = false;
        }
    }

    if (hand1StraightFlush && !hand2StraightFlush) 
    {
        return 1;
    } 
    else if (!hand1StraightFlush && hand2StraightFlush) 
    {
        return 2;
    } 
    else if (hand1StraightFlush && hand2StraightFlush) 
    {
        return 0;
    }

    // Check for four of a kind

    int hand1FourOfAKind = 0;
    int hand2FourOfAKind = 0;

    for (int i = 0; i < 7; i++) 
    {
        int hand1Count = 0;
        int hand2Count = 0;
        for (int j = 0; j < 7; j++) 
        {
            if (hand1[i][0] == hand1[j][0])
            {
                hand1Count++;
            }
            if (hand2[i][0] == hand2[j][0]) 
            {
                hand2Count++;
            }
        }
        if (hand1Count == 4) 
        {
            hand1FourOfAKind = i;
        }
        if (hand2Count == 4) 
        {
            hand2FourOfAKind = i;
        }
    }

    if (hand1FourOfAKind > hand2FourOfAKind) 
    {
        return 1;
    } 
    else if (hand1FourOfAKind < hand2FourOfAKind) 
    {
        return 2;
    } 
    else if (hand1FourOfAKind == hand2FourOfAKind) 
    {
        return 0;
    }


    // Check for a full house

    bool hand1FullHouse = false;
    bool hand2FullHouse = false;
    int hand1ThreeOfAKind = 0;
    int hand2ThreeOfAKind = 0;
    int hand1Pair = 0;
    int hand2Pair = 0;

    for (int i = 0; i < 7; i++) 
    {
        int hand1Count = 0;
        int hand2Count = 0;
        for (int j = 0; j < 7; j++) 
        {
            if (hand1[i][0] == hand1[j][0]) 
            {
                hand1Count++;
            }
            if (hand2[i][0] == hand2[j][0]) 
            {
                hand2Count++;
            }
        }
        if (hand1Count == 3) 
        {
            hand1ThreeOfAKind = i;
        } 
        else if (hand1Count == 2) 
        {
            hand1Pair = i;
        }
        if (hand2Count == 3) 
        {
            hand2ThreeOfAKind = i;
        } 
        else if (hand2Count == 2) 
        {
            hand2Pair = i;
        }
    }

    if (hand1ThreeOfAKind > 0 && hand1Pair > 0) 
    {
        hand1FullHouse = true;
    }
    if (hand2ThreeOfAKind > 0 && hand2Pair > 0) 
    {
        hand2FullHouse = true;
    }
    if (hand1FullHouse && !hand2FullHouse) 
    {
        return 1;
    } 
    else if (!hand1FullHouse && hand2FullHouse) 
    {
        return 2;
    } 
    else if (hand1FullHouse && hand2FullHouse) 
    {
        return 0;
    }


    // Check for a flush

    bool hand1Flush = true;
    bool hand2Flush = true;

    for (int i = 1; i < 7; i++) 
    {
        if (hand1[i][1] != hand1[0][1]) 
        {
            hand1Flush = false;
        }
        if (hand2[i][1] != hand2[0][1]) 
        {
            hand2Flush = false;
        }
    }
    if (hand1Flush && !hand2Flush) 
    {
        return 1;
    } 
    else if (!hand1Flush && hand2Flush) 
    {
        return 2;
    } 
    else if (hand1Flush && hand2Flush) 
    {
        return 0;
    }


    // Check for a straight

    std::string hand1Values = "";
    std::string hand2Values = "";

    for (int i = 0; i < 7; i++) 
    {
        hand1Values += hand1[i][0];
        hand2Values += hand2[i][0];
    }

    std::string straight = "A23456789TJQKA";
    bool hand1Straight = false;
    bool hand2Straight = false;

    for (int i = 0; i < 10; i++) 
    {
        if (hand1Values.find(straight.substr(i, 5)) != std::string::npos) 
        {
        hand1Straight = true;
        }
        if (hand2Values.find(straight.substr(i, 5)) != std::string::npos) 
        {
        hand2Straight = true;
        }
    }

    if (hand1Straight && !hand2Straight) 
    {
        return 1;
    } 
    else if (!hand1Straight && hand2Straight) 
    {
        return 2;
    } 
    else if (hand1Straight && hand2Straight) 
    {
        return 0;
    }


    // Check for three of a kind

    if (hand1ThreeOfAKind > hand2ThreeOfAKind) 
    {
        return 1;
    } 
    else if (hand1ThreeOfAKind < hand2ThreeOfAKind) 
    {
        return 2;
    } 
    else if (hand1ThreeOfAKind == hand2ThreeOfAKind)
    {
        return 0;
    }


    // Check for two pairs

    int hand1PairCount = 0;
    int hand2PairCount = 0;

    for (int i = 0; i < 7; i++) 
    {
        int hand1Count = 0;
        int hand2Count = 0;
        for (int j = 0; j < 7; j++) 
        {
            if (hand1[i][0] == hand1[j][0]) 
            {
                hand1Count++;
            }
            if (hand2[i][0] == hand2[j][0]) 
            {
                hand2Count++;
            }
        }
        if (hand1Count == 2) 
        {
            hand1PairCount++;
        }
        if (hand2Count == 2) 
        {
            hand2PairCount++;
        }
    }

    if (hand1PairCount > hand2PairCount)
    {
        return 1;
    } 
    else if (hand1PairCount < hand2PairCount) 
    {
        return 2;
    }
    else if (hand1PairCount == hand2PairCount) 
    {
        return 0;
    }


    // Check for a pair

    if (hand1Pair > hand2Pair) 
    {
        return 1;
    } 
    else if (hand1Pair < hand2Pair) 
    {
        return 2;
    } 
    else if (hand1Pair == hand2Pair) 
    {
        return 0;
    }


    // If all else fails, compare the highest card in each hand

    std::string hand1Sorted[7];
    std::string hand2Sorted[7];

    for (int i = 0; i < 7; i++) 
    {
        hand1Sorted[i] = hand1[i];
        hand2Sorted[i] = hand2[i];
    }

    std::sort(hand1Sorted, hand1Sorted + 7);
    std::sort(hand2Sorted, hand2Sorted + 7);
    
    if (hand1Sorted[6][0] > hand2Sorted[6][0]) 
    {
        return 1;
    } 
    else if (hand1Sorted[6][0] < hand2Sorted[6][0]) 
    {
        return 2;
    }
    else 
    {
        return 0;
    }
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
