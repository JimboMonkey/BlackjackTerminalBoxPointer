
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

#include "Player.hpp"

#define DefaultStackValue 100

/* Constructor for the player object */
Player::Player(const string NewName)
{
	/* Set chosen name and default stack value */
	Name = NewName;
	Stack = DefaultStackValue;
}

/* Destructor for the player object */
Player::~Player()
{
	/* Destroy player object */
}

/* Return the player's name */
const string Player::GetName() const
{
	return Name;
}

/* Return the player's stack value */
const float Player::CountStack() const
{
	return Stack;
}

/* Reduce the stack by the bet value */
void Player::PlaceBet(const float NewBet)
{
	Stack -= NewBet;
}

/* Add to the stack value */
void Player::AddToStack(const float Winnings)
{
	Stack += Winnings;
}
