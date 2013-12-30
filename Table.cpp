
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

#include "Table.hpp"

/* List all players still in the game and their stack value */
void Table::ListPlayers() const
{
	int i;

	cout << endl << "There are " << Boxes.size() << " players sat at the table: " << endl << endl;

	for (i = 0; i < Boxes.size(); i++)
	{
		cout << "  " << Boxes.at(i)->GetOwner() << " with a stack of " << Boxes.at(i)->CountStack() << endl;
	}
	cout << endl;
}

/* Add box to table list (covers both initial additions and split inserts) */
void Table::AddBox(Box* NewBox, const int BoxIndex = 0)
{
	/* BoxIndex defaults to zero for initial additions or is over ridden for split card additions */
	Boxes.insert((Boxes.begin() + BoxIndex), NewBox);
}

/* Remove chosen box from table when split play is over or player goes bust */
void Table::RemoveBox(const int BoxIndex)
{
	/* If the box isn't a temporary split card box... */
	if(Boxes.at(BoxIndex)->CheckSplit() == false)
	{
		/* delete the Player object referenced in the box object */
		delete Boxes.at(BoxIndex)->GetOwnerObj();
	}
	/* Remove the box from the list */
	delete Boxes[BoxIndex];
	Boxes.erase(Boxes.begin() + BoxIndex);
}

/* Count the number of boxes in use at the table (including split boxes) */
const int Table::CountBoxes() const
{
	return Boxes.size();
}

/* Retrieve a chosen box from the list */
Box* Table::GetBox(const int BoxIndex)
{
	return Boxes[BoxIndex];
}

/* Remove all the temporary boxes used for split play */
void Table::RemoveSplits()
{
	int BoxIndex = 0;	

	/* Cycle through all the boxes */
	while(BoxIndex != Boxes.size())	
	{
		Box *BoxPointer;
		BoxPointer = Boxes.at(BoxIndex);
		/* If a box is from split play... */
		if (BoxPointer->CheckSplit() == true)
		{
			/* ...remove it */
			RemoveBox(BoxIndex);
		}
		/* Otherwise skip over it */
		else
		{
			BoxIndex++;
		}
	}
}
