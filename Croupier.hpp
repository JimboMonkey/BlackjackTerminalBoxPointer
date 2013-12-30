
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

#ifndef CROUPIER_HPP
#define CROUPIER_HPP

#include <iostream>
#include <stdlib.h>

#include "Participant.hpp"
#include "Card.hpp"

/* Define the card constants */
#define NumberOfDecks 4
#define SuitsPerDeck 4
#define CardsPerSuit 13
#define CardsPerDeck (SuitsPerDeck * CardsPerSuit)
#define ShoeSize (NumberOfDecks * CardsPerDeck)

class Croupier: public Participant
{
	public:
		Croupier();
		void InitialStatus() const;
		void Status() const;
		const Card Deal();
		void ReturnCards();
		
	private:
		/* Shoe size increased by 1 to accomodate cut card */
		Card Shoe[ShoeSize + 1];
		int NextCard;
		void List() const;
		void Shuffle();
};

#endif
