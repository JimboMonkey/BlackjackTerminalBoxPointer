
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

#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>

#include "Box.hpp"

class Table
{
	public:
		void AddBox(Box* NewBox, const int BoxIndex);
		void RemoveBox(const int BoxIndex);
		void ListPlayers() const;
		const int CountBoxes() const;
		Box* GetBox(const int BoxIndex);
		void RemoveSplits();

	private:
		vector<Box*> Boxes;
};

#endif
