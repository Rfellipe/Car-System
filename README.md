# Car_System
This little program is just something I wanted to create to test my knowledge with SQL and C++, which are two languages I love. And connecting both were super awesome. The program is like an inventory software that uses cars as an example of products! Hope you like it.

# Installation
First you need to create an admin user in MariaDB

```
CREATE USER IF NOT EXISTS 'admin'@'localhost'
  IDENTIFIED BY 'admin';
```

Give it privileges
```
GRANT ALL PRIVILEGES
  ON car_system.*
  TO 'admin'@'localhost';
```

Then you need to run the "setup.sql" inside of your MariaDB server.

```
source /path/to/setup.sql
```

After that compile the source code:

```
g++ -o car_system car_system.cpp -std=c++11 -lmariadbcpp
```

# Usage
When running the program you have five functions:
* Register client
* Make an order
* Register a new car
* Print inventory
* Print orders

In the directory run the script without parameters to print this message.

```
./car_system
```

To register a client just add the parameters:

```
./car_system Register name surname address cpf phone
```

Make an order:

```
./car_system makeOrder brand model kilometers year name surname cpf
```

Register a new car:

```
./car_system addCar brand model kilometers years name surname cpf
```

Print Inventory:

```
./car_system printInventory
```

Print orders:

```
./car_system printOrders
```
