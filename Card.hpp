
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

#ifndef CARD_HPP
#define CARD_HPP

class Card
{
	public:
		const char *GetSuit() const;
		const char *GetName() const;
		const int GetValue() const;

		void SetSuit(const char *NewSuit);
		void SetName(const char *NewName);
		void SetValue(const int NewValue);

	private:
		const char *Suit;
		const char *Name;
		int Value;
};

#endif
