
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

#include "Croupier.hpp"

/* Declare the names and values of all cards in a deck */
const char* Suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
const int Values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const char* Names[] = {"Ace",
		       "Two",
		       "Three",
		       "Four",
		       "Five",
		       "Six",
		       "Seven",
		       "Eight",
		       "Nine",
		       "Ten",
		       "Jack",
		       "Queen",
		       "King"};

/* Constructor for the Croupier object */
Croupier::Croupier()
{
	int DeckNumber;
	int SuitNumber;
	int CardNumber;
	int ShoePosition;
	NextCard = -1;

	HandValue = 0;
	AcesHeld = 0;

	/* Populate the shoe with cards for all decks */
	for(DeckNumber = 0; DeckNumber < NumberOfDecks; DeckNumber++)
	{	
		for(SuitNumber = 0; SuitNumber < SuitsPerDeck; SuitNumber++)
		{
			for(CardNumber = 0; CardNumber < CardsPerSuit; CardNumber++)
			{
				ShoePosition = (DeckNumber * (CardsPerDeck)) + (CardNumber + (SuitNumber * CardsPerSuit));
				Shoe[ShoePosition].SetSuit(Suits[SuitNumber]);
				Shoe[ShoePosition].SetName(Names[CardNumber]);
				Shoe[ShoePosition].SetValue(Values[CardNumber]);
			}
		}
	}
	/* Place the cut card at the back of the shoe ready to be placed during the shuffle */
	Shoe[ShoeSize].SetSuit("Cut");
	Shoe[ShoeSize].SetName("Cut");
	Shoe[ShoeSize].SetValue(0);
	/* Shuffle the complete shoe */
	Shuffle();
}

/* Deal out the next card of the shoe */
const Card Croupier::Deal()
{
	Card TempStore;

	NextCard++;
	/* When the cut card is reached, reshuffle the shoe */
	string CompareString = Shoe[NextCard].GetName();
	if (CompareString.compare("Cut") == 0)
	{	
		cout << "Cut card reached. Reshuffling cards...." << endl << endl;
		/* Move the cut card to the end of the pack so that it isn't shuffled */
		TempStore = Shoe[ShoeSize];
		Shoe[ShoeSize] = Shoe[NextCard];
		Shoe[NextCard] = TempStore;
		Shuffle();
		NextCard = 0;
	}
	return Shoe[NextCard];
}

/* Take the ordered shoe and shuffle it */
void Croupier::Shuffle()
{
	int i, k;
	int RandomNumber;
	Card TempStore;
	
	/* Initialise the random number generator using time as a seed */
	srand (time(NULL));

	/* Use the Fisher-Yates / Knuth algorithm to shuffle the shoe */
	for(i = ShoeSize; i > 0; i--)
	{
		/* Generate a random between 1 and the available shoe size */
		RandomNumber = rand() % i;

		/* Pick out a random card */
		TempStore = Shoe[RandomNumber];

		/* Shift all sequential cards down by one position to fill the gap */
		for(k = RandomNumber; k < (ShoeSize - 1); k++)
		{
			Shoe[k] = Shoe[k + 1];
		}
		/* Place the chosen card at the end of the pack */
		Shoe[ShoeSize - 1] = TempStore;	
	}

	/* Place the cut card randomly in the last quater of the shoe */
	/* Find the first card of the last quarter of the shoe */
	int Minimum = (ShoeSize - (ShoeSize / 4));
	/* Pick a random card from the last quarter of the pack /*
	/* Swap it with the cut card (which always starts as the/*
	/* the last card in the shoe) */
	RandomNumber = rand() % (ShoeSize - Minimum) +  Minimum;
	TempStore = Shoe[RandomNumber];
	Shoe[RandomNumber] = Shoe[ShoeSize];
	Shoe[ShoeSize] = TempStore;
}

/* List all the cards in the shoe */
void Croupier::List() const
{
	int i;

	/* Run through all the cards in the shoe (including the cut card, hence the +1) */
	for(i = 0; i < ShoeSize + 1; i++)
	{
		cout << i << "	" << Shoe[i].GetName() << " of " << Shoe[i].GetSuit() << " has the value " << Shoe[i].GetValue() << endl;
	}
}

/* Declare the dealers upcard */
void Croupier::InitialStatus() const
{
	cout << "Dealer's upcard is the " << Hand.front().GetName() << " of " << Hand.front().GetSuit() << endl << endl;
}

/* State the dealer's hand */
void Croupier::Status() const
{
	cout << "Dealer is holding: " << endl << endl;	
	ListHand();
	StatusResult();
}

/* Reset all flags of the dealer */
void Croupier::ReturnCards()
{
	Hand.clear();
	HandValue = 0;
	AcesHeld = 0;
}

