
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

#ifndef BOX_HPP
#define BOX_HPP

#include <vector>

#include "Player.hpp"
#include "Card.hpp"
#include "Participant.hpp"

class Box: public Participant
{
	public:
		Box(Player* NewOwner, const bool Split = false);
		string GetOwner() const;
		Player* GetOwnerObj() const;
		void Status() const;
		void PlaceBet(const float NewBet);
		const float CountBet() const;
		void RetrieveBet();
		void ReceiveWinnings();
		float CountStack() const;
		void PlaceInsurance();
		const bool CheckInsurance() const;
		void ReceiveInsurance();
		void Surrender();
		const bool CheckSurrended() const;
		const Card MoveSplitCard();
		bool CheckSplit() const;
		void ReturnCards();	

	private:
		Player *Owner;
		float Bet;
		bool UsingInsurance;
		float Insurance;
		bool Surrended;
		bool SplitBox;
};

#endif


