
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

#include "Participant.hpp"

/* List all cards of the current hand */
void Participant::ListHand() const
{
	int i;
	
	for(i = 0; i < Hand.size(); i++)
	{
		cout << "  " << Hand.at(i).GetName() << " of " << Hand.at(i).GetSuit() << endl;
	}
	cout << endl;
}

/* State the result of the current hand */
void Participant::StatusResult() const
{
	/* Current box is bust */
	if (HandValue > 21 and AcesHeld == 0)
	{
		cout << "  Bust with ";
	}
	/* Current box is holding aces so has a soft hand */
	else if (AcesHeld > 0 and HandValue != 21)
	{
		cout << "  Soft ";
	}
	/* State the value of the current hand */
	else
	{
		cout << "  ";
	}
	cout << HandValue << endl << endl;
}

/* Check the value of the current hand */
const int Participant::CheckHand() const
{
	return HandValue;
}

/* Return the number of cards in the current hand */
const int Participant::CountCards() const
{
	return Hand.size();
}

/* Check the name of a chosen card */
const string Participant::CheckCard(const int CardIndex) const
{
	return Hand.at(CardIndex).GetName();
}

/* Soften the value of an ace card */
void Participant::SoftenAce()
{
	HandValue -= 10;
	AcesHeld--;
}

/* Receive the card dealt to the box */
void Participant::TakeCard(const Card& DealtCard)
{
	Hand.push_back(DealtCard);
	HandValue += DealtCard.GetValue();
	/* Keep a count of the number of aces held */
	string CompareString = DealtCard.GetName();
	if (CompareString.compare("Ace") == 0)
	{
		AcesHeld++;
	}
	/* Soften any aces if required */
	if(CheckHand() > 21)
	{
		if (AcesHeld > 0)
		{
			SoftenAce();
		}
	}
}
