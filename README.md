# Software for manage course in a Gym

The General Manager of a large warehouse needs a program to manage the products in stock in his warehouse. Specifically, the program must make available the following features:

1. Inserting a new product. A product is characterized by a code (6-digit number), a name, a description, a purchase price (unit), a number of product units in stock (quantity), and a minimum stock. The units of product in the warehouse are initially zero.

2. Loading / Unloading of a product. The function takes as input the product code, a date, and the product units (quantity) to be loaded / unloaded, displays the name of the product and asks for confirmation of the load. Note: if the quantity is positive, it is a load, otherwise it will be a discharge.

3. View extract loading / unloading. The function takes the product code as input and displays: the name of the product and the list of all product loading and unloading operations.

4. Display list of products in reserve. View the list of all products in reserve (the quantity of which is less than the minimum stock) with an estimate of the expense to be faced to recharge the entire warehouse. To estimate spending:
  a. calculate the expense to reload each product in reserve, multiplying the unit purchase price by the number of minimum  
  units to bring back the quantity of product in stock equal to 110% of the minimum stock.
  b. add up all the amounts to top up each product in reserve.
