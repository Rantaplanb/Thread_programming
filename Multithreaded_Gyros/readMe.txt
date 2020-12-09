//------------------------//
//  Mertzanis Loukas 4457 //
//  HY345 - Assignment 2  //
//------------------------//

In this exercice we had to simulate the functioning
of a Souvlatzidiko, taking into consideration the COVID
restrictions (only 1 customer in the shop at any time).
I used 1 thread to simulate the functioning of the chef
and N threads to simulate the functioning of the customers.

The program works like this:

A customer comes to the Souvlatzidiko: If it is empty
he/she gets in, orders souvlakia and the chef prepares the order.

If it is not empty (there is a customer in) he/she has to wait.
  |
  L--> 	If there are empty seats outside the shop, sit and wait.
	Otherwise he/she has to wait standing until someone seated
	stands up to get in the shop. When it is his/her turn,
	he/she may enter the Souvlatzidiko and place an order.

When the chef has serviced all the customers, he/she may close the shop.

Check the commends in the code and you may ask me for any technical details, thanks! :)