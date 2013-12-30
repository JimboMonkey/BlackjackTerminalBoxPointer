
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

#include "Box.hpp"

/* Constructor for the Box object */
Box::Box(Player *NewOwner, const bool Split)
{
	Owner = NewOwner;
	Bet = 0;
	HandValue = 0;
	Insurance = 0;
	AcesHeld = 0;
	UsingInsurance = false;
	Surrended = false;
	SplitBox = Split;
}

/* Return the name of the owner of the box */
string Box::GetOwner() const
{
	return Owner->GetName();
}

/* Return a pointer to the owner of the box */
Player* Box::GetOwnerObj() const
{
	return Owner;
}

/* Return whether the box is used for split card play */
bool Box::CheckSplit() const
{
	return SplitBox;
}

/* Return the size of box owner's stack */
float Box::CountStack() const
{
	return Owner->CountStack();
}

/* Return the bet placed on the current box */
const float Box::CountBet() const
{
	return Bet;
}

/* Place a bet on the current box */
void Box::PlaceBet(const float NewBet)
{
	Owner->PlaceBet(NewBet);
	Bet += NewBet;
}

/* Surrender the current hand */
void Box::Surrender()
{
	Surrended = true;
	Owner->AddToStack(Bet/2);
}

/* Check to see if the current box surrended */
const bool Box::CheckSurrended() const
{
	return Surrended;
}

/* Check if the current box has taken insurance */
const bool Box::CheckInsurance() const
{
	return UsingInsurance;
}

/* Place insurance on the current box */
void Box::PlaceInsurance()
{
	Owner->PlaceBet(Bet / 2);
	Insurance = (Bet / 2);
	UsingInsurance = true;
}

/* Receive an insurance bet pay out */
void Box::ReceiveInsurance()
{
	Owner->AddToStack(Bet + Insurance);
	cout << "  Wins insurance bet and collects " << Insurance << " from the dealer" << endl;
	Insurance = 0;
}

/* Retrieve original bet after a push */
void Box::RetrieveBet()
{
	Owner->AddToStack(Bet);
	cout << "  Bet of " << Bet << " returned" << endl;
}

/* Receive winnings of a bet  - covers blackjack and 'normal' wins*/
void Box::ReceiveWinnings()
{
	/* A blackjack win */
	if(CheckHand() == 21 and Hand.size() == 2 and SplitBox == false)
	{
		Owner->AddToStack(Bet + Bet + (Bet/2));
		cout << "  Wins bet and collects " << (Bet + (Bet/2)) << " from the dealer" << endl;			
	}
	/* A non-blackjack win */
	else
	{
		Owner->AddToStack(Bet + Bet);
		cout << "  Wins bet and collects " << Bet << " from the dealer" << endl;
	}
}

/* Return the split card to be moved and reduced the current hand value */
const Card Box::MoveSplitCard()
{
	Card TempCard;

	TempCard = Hand.at(1);
	HandValue -= Hand.at(1).GetValue();
	Hand.pop_back();
	/* AcesHeld must be reassessed after a split */
	string CompareString = Hand.front().GetName();
	if (CompareString.compare("Ace") == 0)
	{
		AcesHeld = 1;
		HandValue = 11;
	}
	return TempCard;
}

/* Reset all flags of the current box */
void Box::ReturnCards()
{
	Hand.clear();
	HandValue = 0;
	AcesHeld = 0;
	Bet = 0;
	Insurance = 0;
	UsingInsurance = false;
	Surrended = false;
}

/* Declare the status of the current hand */
void Box::Status() const
{
	cout << Owner->GetName();
	/* If the current box is the result of a split hand, display a different message */
	if(CheckSplit() == true)
	{
		cout << " (Split Hand)";
	}
	cout << ": (" << Owner->CountStack() << " in your stack, " << Bet << " on the table) You are holding: " << endl << endl;	

	ListHand();
	StatusResult();
}




