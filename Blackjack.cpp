
/*
 * Copyright 2013 James O'Hea
 *
 * This file is part of Blackjack.
 *
 * Blackjack is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Blackjack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Blackjack.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <sstream>

#include "Table.hpp"
#include "Croupier.hpp"
#include "Box.hpp"

using namespace std;

#define MinimumBet 5

/* Use ANSI escape codes to clear the screen */
void ClearScreen()
{
	cout << "\033[2J\033[2;1H";
}

/* Return the number of players */
const int CountPlayers()
{
	string UserEntry;
	int NumberOfPlayers;

	/* Ensure the user enters a valid number (loop question until they do) */
	do
	{
		ClearScreen();
		cout << "How many players? (1 - 7)" << endl;
		getline(cin, UserEntry);
		stringstream StrToInt(UserEntry); 
		StrToInt >> NumberOfPlayers;
		/* Number must be between 1 and 7 and only 1 character long */
	}while(!(NumberOfPlayers > 0 && NumberOfPlayers < 8 && UserEntry.size() == 1));
	
	return NumberOfPlayers;
}

/* Create a box for every player at the table */
void SeatPlayers(Table& BlackJackTable, const int NumberOfPlayers)
{
	int i;
	string PlayerName;
	Player *pPlayer;
	Box *pBox;

	/* Request each player's name */
	for(i = 0; i < NumberOfPlayers; i++)
	{
		ClearScreen();
		cout << "Player " << (i + 1) << "'s name:" << endl;
		getline(cin, PlayerName);
		/* Create a player object to link to each box */
		pPlayer = new Player(PlayerName);
		pBox = new Box(pPlayer, false);
		/* Add every box to the table */
		BlackJackTable.AddBox(pBox, i);
	}
	ClearScreen();
}

/* Collect bets from every player */
void CollectBets(Table& BlackJackTable)
{
	int BoxIndex;
	string UserEntry;
	int NewBet;

	/* Loop through all players at the table */
	for(BoxIndex = 0; BoxIndex < BlackJackTable.CountBoxes(); BoxIndex++)
	{
		Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
		do
		{
			cout << CurrentBox->GetOwner() << ", place your bet (" << CurrentBox->CountStack() << " in your stack. Multiples of " << MinimumBet << " only):" << endl;
	   		getline(cin, UserEntry);
			stringstream StrToInt(UserEntry); 
			StrToInt >> NewBet;
			/* ClearScreen needs to be at bottom of this loop to avoid the summary screen being hidden at the end of a round */
			ClearScreen();
		/* Player must be able to afford the bet and it must be at least the minimum bet value or a multiple of it */
		}while(!(NewBet <= CurrentBox->CountStack() && NewBet >= MinimumBet && (int)NewBet % MinimumBet == 0));
		CurrentBox->PlaceBet(NewBet);
	}
}

/* Deal everyone their first two cards (including the dealer) */
void InitialDeal(Table& BlackJackTable, Croupier& Dealer)
{
	int Deal;
	int BoxIndex;
	Card DealtCard;

	for(Deal = 0; Deal < 2; Deal++)
	{
		for(BoxIndex = 0; BoxIndex < BlackJackTable.CountBoxes(); BoxIndex++)
		{
			Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
	    	DealtCard = Dealer.Deal();
			CurrentBox->TakeCard(DealtCard);
		}
	    DealtCard = Dealer.Deal();
		Dealer.TakeCard(DealtCard);
	}
}

/* Check for player blackjack and state any insurance options */
void InsuranceOffers(Table& BlackJackTable, Croupier& Dealer)
{
	int BoxIndex;
	string Choice;

	for(BoxIndex = 0; BoxIndex < BlackJackTable.CountBoxes(); BoxIndex++)
	{
		Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
		
		/* Player has blackjack - display message */
		if(CurrentBox->CheckHand() == 21)
		{
			Dealer.InitialStatus();
			cout << CurrentBox->GetOwner() << ": (" << CurrentBox->CountStack() << " in your stack, ";
			cout << CurrentBox->CountBet() << " on the table) You are holding: " << endl << endl;	
			CurrentBox->ListHand();
			cout << "  Blackjack!" << endl << endl;
			sleep(2);
		}
				
		/* If dealer has an ace as their upcard, and they have enough money, offer insurance */
		if (Dealer.CheckCard(0) == "Ace" and (CurrentBox->CountStack() >= (CurrentBox->CountBet() / 2)))
		{
			/* If the player has blackjack their status will already be displayed */
			if(CurrentBox->CheckHand() != 21)
			{
				Dealer.InitialStatus();
				CurrentBox->Status();
			}
			do
			{
				cout << CurrentBox->GetOwner() << ", the dealer is showing an ace. ";
				/* Hands of blackjack receive different message for same offer */
				if (CurrentBox->CheckHand() == 21)
				{
					cout <<	"Even money? (y or n)" << endl;
				}
				else
				{
					cout << "Would you like insurance? (y or n)" << endl;
				}
				getline(cin, Choice);

				if(Choice == "y")
				{
					CurrentBox->PlaceInsurance();
				}
				ClearScreen();
			/* Loop until they give a valid answer */
			}while(Choice != "y" && Choice != "n");
		}
		ClearScreen();
	}
}

/* Check for any blackjacks and handle insurance claims accordingly */
bool CheckForBlackJack(Table& BlackJackTable, Croupier& Dealer)
{
	int BoxIndex;
	bool DealerBlackjack = false;
	bool PauseForMessage = false;

	/* If the dealer has blackjack, show it! */
	if (Dealer.CheckHand() == 21)
	{
		cout << "Dealer is holding: " << endl << endl;	
		Dealer.ListHand();
		cout << "  Blackjack!" << endl << endl;
		DealerBlackjack = true;
		sleep(2);
	}
	else
	{
		DealerBlackjack = false;
	}

	/* Check for push or even money condition for every player and list each result */
	for(BoxIndex = 0; BoxIndex < BlackJackTable.CountBoxes(); BoxIndex++)
	{
		Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);

		/* Player has blackjack */
		if (CurrentBox->CheckHand() == 21)
		{
			/* Player has taken out insurance */
			if (CurrentBox->CheckInsurance() == true)
			{
				cout << "Even money for " << CurrentBox->GetOwner() << endl;
				PauseForMessage = true;
			}
			/* Player hasn't taken out insurance */
			else
			{
				/* Dealer has blackjack */
				if (DealerBlackjack == true)
				{
					cout << "Dealer and " << CurrentBox->GetOwner() << " both have blackjack!  Push!" << endl;
					PauseForMessage = true;
				}
			}
		}
	}

	/* Keep any messages on the screen for a bit */
	if (PauseForMessage == true)
	{
		sleep(2);
		cout << endl;
	}

	/* Also check insurance situation for every player but only display resulting message once */
	for(BoxIndex = 0; BoxIndex < BlackJackTable.CountBoxes(); BoxIndex++)
	{
		Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);

		/* Player has taken out insurance and doesn't have blackjack */
		if (CurrentBox->CheckInsurance() == true and CurrentBox->CheckHand() != 21)
		{
			/* Dealer doesn't have blackjack */
			if (DealerBlackjack == false)
			{
				cout << "Dealer doesn't have blackjack.  Insurance bets lost" << endl;
			}
			/* Dealer has blackjack */
			else
			{
				cout << "Dealer has blackjack. Insurance bets pay out" << endl;
			}
			sleep(2);
			break;
		}
	}
	return DealerBlackjack;
}

/* Give player options on how they can play their hand */
void StateOptions(Box* CurrentBox, bool PlayersFirstGo)
{
	string FirstCard = CurrentBox->CheckCard(0);
	string SecondCard = CurrentBox->CheckCard(1);

	cout << "Hit (h), ";
	/* If past initial hand stage */
	if (CurrentBox->CountCards() > 2)
	{
		cout << "or stand (s)?" << endl;
	}
	/* Initial hand stage */
	else
	{	
		/* Not after split */
		if (PlayersFirstGo == true and CurrentBox->CheckSplit() != true)
		{
			cout << "stand (s)";
			/* Player has enough money to double or split */
			if (CurrentBox->CountStack() >= CurrentBox->CountBet())
			{
				cout << ", double (d)";
				/* First two cards are the same */
				if (FirstCard.compare(SecondCard) == 0)
				{
					cout << ", split (p)";
				}
			}
			cout << ", or surrender (q)?" << endl;
		}
		/* After split */
		else
		{
			/* Player has enough money to double or split */
			if (CurrentBox->CountStack() >= CurrentBox->CountBet())
			{
				cout << "stand (s), ";
				/* First two cards are the same */
				if (FirstCard.compare(SecondCard) == 0)
				{
					cout << "double (d), or split (p)?" << endl;
				}
				/* Cards are not the same */
				else
				{
					cout << "or double (d)?" << endl;
				}
			}
			else
			{
				cout << "or stand (s)?" << endl;
			}
		}
	}
}

/* Every player plays their hands */
const bool PlayersPlay(Table& BlackJackTable, Croupier& Dealer)
{
	int BoxIndex;
	string Choice;
	Card DealtCard;
	int SplitIndex;
	/* Keep track of if any players are left for dealer to play against */
	bool PlayersStanding = false;
	/* Certain plays can only take place upon a player's first go */
	bool PlayersFirstGo;

	for(BoxIndex = 0; BoxIndex < BlackJackTable.CountBoxes(); BoxIndex++)
	{
		Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
		PlayersFirstGo = true;
		ClearScreen();
		/* Check player doesn't already have blackjack */
		if (CurrentBox->CheckHand() != 21)
		{			
			do
			{
				Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
				/* Check first two cards in case a split is possible */
				string FirstCard = CurrentBox->CheckCard(0);
				string SecondCard = CurrentBox->CheckCard(1);
				
				ClearScreen();
				Dealer.InitialStatus(); 
				CurrentBox->Status();
				
				/* Check for a non-blackjack 21 */
				if(CurrentBox->CheckHand() == 21)
				{
					/* Auto-stand on a 21 */
					PlayersStanding = true;
					sleep(2);
					break;
				}
				
				/* Tell the player their options of play */
				StateOptions(CurrentBox, PlayersFirstGo);
				getline(cin, Choice);

				/* Player hits */
				if(Choice == "h")
				{
					PlayersFirstGo = false;		
					DealtCard = Dealer.Deal();
					CurrentBox->TakeCard(DealtCard);
					/* If the hit causes them to go bust */
					if(CurrentBox->CheckHand() > 21)
					{
						ClearScreen();
						CurrentBox->Status();
						sleep(2);
						break;
					}	
				}
				/* Player stands */
				else if(Choice == "s")
				{
					PlayersStanding = true;
					//ClearScreen();
				}
				/* Certain plays can only happen if player is holding two cards (regardless of whether first go or not) */
				if (CurrentBox->CountCards() == 2)
				{
					/* Players can only surrender on their first go */
					if (PlayersFirstGo == true and Choice == "q")
					{
						cout << endl << CurrentBox->GetOwner() << " surrenders" << endl;
						cout << "Half of bet of " << CurrentBox->CountBet() << " returned" << endl;
						CurrentBox->Surrender();
						sleep(2);
						break;
					}
					/* Some plays are only possible if a player has enough money in their stack */
					if (CurrentBox->CountStack() >= CurrentBox->CountBet())
					{
						/* Player doubles */
						if (Choice == "d")
						{		
							cout << endl << "Initial bet doubled. Dealing one more card...." << endl;
							sleep(2);

							ClearScreen();
							/* Place bet again to double initial bet and take one last card */
							CurrentBox->PlaceBet(CurrentBox->CountBet());
							DealtCard = Dealer.Deal();
							CurrentBox->TakeCard(DealtCard);
							
							PlayersFirstGo = false;	
							if(CurrentBox->CheckHand() > 21)
							{
								PlayersStanding = false;		
							}
							else
							{
								PlayersStanding = true;
							}
							CurrentBox->Status();							
							sleep(2);
							break;
						}
						/* Players can split if they have two of the same card */
						if (FirstCard.compare(SecondCard) == 0 and Choice == "p")
						{
							PlayersFirstGo = false;		
							/* Add a new box to the table in the next position with same owner as the current box */
							Box *pBox;
							pBox = new Box(CurrentBox->GetOwnerObj(), true);
							BlackJackTable.AddBox(pBox, BoxIndex + 1);
						
							/* Have to redefine CurrentBox after the insert */						
							Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
							Box* SplitBox = BlackJackTable.GetBox(BoxIndex+1);

							/* New box places same bet as current box */
							SplitBox->PlaceBet(CurrentBox->CountBet());
							SplitBox->TakeCard(CurrentBox->MoveSplitCard());


							/* Deal a new card for both boxes */
							for(SplitIndex = BoxIndex; SplitIndex < BoxIndex + 2; SplitIndex++)
							{
								Box* CurrentBox = BlackJackTable.GetBox(SplitIndex);
								DealtCard = Dealer.Deal();
								CurrentBox->TakeCard(DealtCard);	
							}
						}
					}
				}	
			/* Keep looping until everyone stands (or goes bust) */
			}while(Choice != "s");
		}
		/* Split hands may have 21 but can't have blackjack */
		else if (CurrentBox->CheckHand() == 21 and CurrentBox->CheckSplit() == true)
		{
			CurrentBox->Status();
			sleep(2);
		}
	}
	return PlayersStanding;
}

/* Dealer plays until hand value is greater than 17 */
void DealerPlays(Croupier& Dealer)
{
	Card DealtCard;

	/* Show dealer's current status before continuing */
	ClearScreen();
	Dealer.Status();
	sleep(2);

	/* Keep taking cards until over 17 or bust */
	while (Dealer.CheckHand() < 17)
	{
		ClearScreen();
		DealtCard = Dealer.Deal();
		Dealer.TakeCard(DealtCard);
		Dealer.Status();
		sleep(2);
	}
}

/* Remove broke players from the table and report on remaining players */
void RefreshPlayerList(Table& BlackJackTable)
{
	int BoxIndex = 0;	

	/* While there are still boxes to check */
	while(BoxIndex != BlackJackTable.CountBoxes())	
	{
		Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
		/* Player doesn't have enough money to bet with */
		if (CurrentBox->CountStack() < MinimumBet)
		{
			cout << CurrentBox->GetOwner() << " has no money left to play and has left the table" << endl;
			BlackJackTable.RemoveBox(BoxIndex);
		}
		else
		{
			BoxIndex++;
		}
	}
	/* List all players left at the table, else exit the game with a message */
	if(BlackJackTable.CountBoxes() > 0)
	{
		BlackJackTable.ListPlayers();
	}
	else
	{
		cout << endl << "All players have gone bust!  Exiting the game...." << endl << endl;
	}
}

/* Work out who has won and who has lost and settle all bets */
void SettleBets(Table& BlackJackTable, Croupier& Dealer)
{
	int BoxIndex;

	ClearScreen();
	
	/* Give summary for every box at the table */
	for(BoxIndex = 0; BoxIndex < BlackJackTable.CountBoxes(); BoxIndex++)
	{
		Box* CurrentBox = BlackJackTable.GetBox(BoxIndex);
		/* Include a player's split hand results under their same name heading as their other results */
		if(CurrentBox->CheckSplit() == false)
		{
			cout << CurrentBox->GetOwner() << ":" << endl;
		}
		/* If player didn't surrender */
		if(CurrentBox->CheckSurrended() == false)
		{
			/* Start the summary with a different label if referring to a split hand */
			if(CurrentBox->CheckSplit() == false)
			{
				cout << "  Hand of ";
			}
			else
			{
				cout << "  Split hand of ";
			}
			/* Player didn't go bust */
			if (CurrentBox->CheckHand() < 22)
			{
				/* Dealer had blackjack (checking for 2 cards to ensure they don't just have a 21 score) */
				if (Dealer.CheckHand() == 21 and Dealer.CountCards() == 2)
				{
					/* Player also had blackjack */
					if (CurrentBox->CheckHand() == 21 and CurrentBox->CountCards() == 2 and CurrentBox->CheckSplit() == false)
					{
						cout << "blackjack in push with dealer's blackjack" << endl;
						CurrentBox->RetrieveBet();	
						/* Player took insurance */
						if (CurrentBox->CheckInsurance() == true)
						{
							/* Even money */
							CurrentBox->ReceiveInsurance();
						}
					}
					/* Player didn't have blackjack as well */ 
					else
					{
						cout << CurrentBox->CheckHand() << " beaten by dealer's blackjack" << endl;
						cout << "  " << "Loses bet of " << CurrentBox->CountBet() << endl;
					}
				}
				/* Dealer doesn't have blackjack */
				else
				{
					/* Player had blackjack */
					if (CurrentBox->CheckHand() == 21 and CurrentBox->CountCards() == 2 and CurrentBox->CheckSplit() == false)
					{
						cout << "blackjack beat's dealer's " << Dealer.CheckHand() << endl;
						CurrentBox->ReceiveWinnings();
					}
					/* Player didn't have blackjack */
					else
					{
						/* Player's hand is greater than dealer's hand or dealer is bust */
						if (CurrentBox->CheckHand() > Dealer.CheckHand() or Dealer.CheckHand() > 21)
						{
							cout << CurrentBox->CheckHand() << " beats dealer's " << Dealer.CheckHand() << endl;
							CurrentBox->ReceiveWinnings();
						}
						/* Player's hand in push with dealer's hand */
						else if (CurrentBox->CheckHand() == Dealer.CheckHand())
						{
							cout << CurrentBox->CheckHand() << " in push with dealer's " << Dealer.CheckHand() << endl;
							CurrentBox->RetrieveBet();
						}
						/* Player's hand is less than dealer's hand */
						else
						{
							cout  << CurrentBox->CheckHand() << " beaten by dealer's " << Dealer.CheckHand() << endl;
							cout << "  " << "Loses bet of " << CurrentBox->CountBet() << endl;
						}
					}
				}
			}				
			/* Player went bust */
			else	
			{
				cout  << CurrentBox->CheckHand() << " went bust" << endl;
				cout << "  Loses bet of " << CurrentBox->CountBet() << endl;
			}
			
			/* Player took out insurance (need to check this even if player went bust) */
			if (CurrentBox->CheckInsurance() == true)
			{
				/* Player had blackjack */
				if (CurrentBox->CheckHand() == 21 and CurrentBox->CountCards() == 2 and CurrentBox->CheckSplit() == false)
				{
					/* Even money situation already dealt with above */
				}
				/* Player didn't have blackjack */
				else
				{
					/* Dealer had blackjack */
					if (Dealer.CheckHand() == 21 and Dealer.CountCards() == 2)
					{
						/* Message displayed with function */
						CurrentBox->ReceiveInsurance();
					}
					/* Dealer didn't have blackjack */
					else
					{
						cout << "  Loses insurance bet of " << (CurrentBox->CountBet() / 2) << endl;
					}
				}
			}	
		}
		/* Player surrendered */
		else
		{
			cout << "  Surrendered" << endl << "  Half of bet of " << CurrentBox->CountBet() << " returned" << endl;
		}
		cout << endl;
		/* Player returns cards to the dealer */
		CurrentBox->ReturnCards();
	}
}

int main()
{
	/* Create table object */
	Table BlackJackTable;

	/* Seat new players at the table */
	SeatPlayers(BlackJackTable, CountPlayers());

	/* Create a dealer object which generates a shoe of cards which are then shuffled */
	Croupier Dealer;

	/* Game begins and loops until all players go bust! */
	do
	{
		/* Collect bets from all players at the table*/
		CollectBets(BlackJackTable);
		
		/* Deal out the inital two cards to every player and the dealer */
		InitialDeal(BlackJackTable, Dealer);
		
		/* If the dealer is showing an ace, and a player has enough money, offer insurance */
		InsuranceOffers(BlackJackTable, Dealer);

		/* Dealer checks for blackjack before continuing with game */		
		if(CheckForBlackJack(BlackJackTable, Dealer) == false)
		{
			/* Each player takes their turn (returns if players still in game after plays) */
			if(PlayersPlay(BlackJackTable, Dealer) != false)
			{
				/* If players are still in the game the Dealer plays his hand */
				DealerPlays(Dealer);
			}
			/* If all players go bust, display dealer's status */
			else
			{
				ClearScreen();
				Dealer.Status();
				sleep(2);
			}
		}

		/* Work out who has won and who has lost and settle all bets */
		SettleBets(BlackJackTable, Dealer);

		/* The dealer returns his cards */
		Dealer.ReturnCards();

		/* Clear all boxes containing splits */
		BlackJackTable.RemoveSplits();
		
		/* Remove broke players from the table */
		RefreshPlayerList(BlackJackTable);
	}
	while(BlackJackTable.CountBoxes() > 0);

	return 0;
}
