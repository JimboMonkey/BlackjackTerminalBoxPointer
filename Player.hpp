
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

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

using namespace std;

class Player
{
	public:
		Player(const string NewName);
		~Player();
		const string GetName() const;
		void PlaceBet(const float NewBet);
		const float CountStack() const;
		void AddToStack(const float Winnings);

	private:
		string Name;
		float Stack;
};

#endif
