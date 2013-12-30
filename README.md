BlackjackTerminal
=================

A terminal based multiplayer blackjack game.  This game aims to mimic the version played 
at casinos, allowing you to double, split (infinitely), surrender, and place insurance bets

To build, just run Make from within the directory
To run, just enter ./blackjack

Up to 7 players can play (this maximum was chosen to mimic a casino blackjack table, the code
can easily be modified to extend this maximum)

Each player starts with 100 units in their stack and takes turns in placing bets in multiples 
of 5 and playing their hand.

The game will let you know what what options you have at every stage of play.

Once every player has played their turn, the dealer plays, before a summary of the scores is 
displayed.  The dealer will keep drawing to 17 or higher.

If a player runs out of money, they will leave the table.  Once all players have run out of money,
the game will end.

Hitting will draw another card for your hand.  If you draw over 21 you will go bust for that hand.

Aces are valued as either 1 or 11 to the players convinience.  If you are holding ace/s the game 
will automatically adjust your hand value to your advantage.

Standing will end your play on a round.  You will stand automatically if you draw to 21

Doubling will double your bet and will draw one more card only.  It can only be chosen
on the initial play of a hand.

Splitting is possible if you have two cards of the same value.  Splitting will seperate these twp
cards and will draw a new card against each one, creating 2 hands from one.  This game allows for
infinite splits, so if you keep drawing the same value cards, you can keep splitting (as long as
you can afford it!)  It can only be chosen on the initial play of a hand.

Surrendering returns half of your bet to the dealer and you skip the round.  

If the dealer is showing an ace on their initial hand, and you can afford it, you will be offered 
insurance.  This is a side bet of half of your original bet.  If you accept this offer, and the 
dealer has blackjack, you win this insurance bet.  If the dealer doesn't have blackjack, you lose 
this insurance bet.  

Enjoy!  

JimboMonkey





