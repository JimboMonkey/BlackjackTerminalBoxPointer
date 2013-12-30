
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

#include "Card.hpp"

/* Set the suit of the card object */
void Card::SetSuit(const char *NewSuit)
{
	Suit = NewSuit;
}

/* Set the name of the card object */
void Card::SetName(const char *NewName)
{
	Name = NewName;
}

/* Set the value of the card object */
void Card::SetValue(const int NewValue)
{
	Value = NewValue;
}

/* Get the suit of the card object */
const char *Card::GetSuit() const
{
	return Suit;
}

/* Get the name of the card object */
const char *Card::GetName() const
{
	return Name;
}

/* Get the value of the card object */
const int Card::GetValue() const
{
	return Value;
}
