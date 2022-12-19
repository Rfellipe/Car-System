#include <bits/stdc++.h>
#include <mariadb/conncpp.hpp>
#include "readme.hpp"

// Register client function
void registerFunc(std::unique_ptr<sql::Connection> &conn,
                  std::string name,
                  std::string surname,
                  std::string address,
                  std::string cpf,
                  std::string phone) { //All column names in the table "clients"
    try{
        // Create a PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO clients (name, surname, address, cpf, phone) VALUES (?, ?, ?, ?, ?)"));

        // Bind values to SQL statement
        stmnt->setString(1, name);
        stmnt->setString(2, surname);
        stmnt->setString(3, address);
        stmnt->setString(4, cpf);
        stmnt->setString(5, phone);

        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e){
        std::cerr << "Error registering new client: " << e.what() << std::endl;
    }
}

// Make an order function
void makeOrder(std::unique_ptr<sql::Connection> &conn,
               std::string brand,
               std::string model,
               std::string kilometers,
               std::string years,
               std::string name,
               std::string surname,
               std::string cpf) { //All columns needed in the "cars" and "clients" tables, to filter it and make an order
    try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO orders (id_car, id_client) VALUES ((SELECT id_car FROM cars WHERE brand = ? AND model = ? AND kilometers = ? AND year = ?), (SELECT id_client FROM clients WHERE name = ? AND surname = ? AND cpf = ?))"));

        // Bind values to SQL statement
        stmnt->setString(1, brand);
        stmnt->setString(2, model);
        stmnt->setString(3, kilometers);
        stmnt->setString(4, years);
        stmnt->setString(5, name);
        stmnt->setString(6, surname);
        stmnt->setString(7, cpf);

        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e) {
        std::cerr << "Error making an order: " << e.what() << std::endl;
    }
}

// Register a new car
void addCar(std::unique_ptr<sql::Connection> &conn,
                  std::string brand,
                  std::string model,
                  std::string kilometers,
                  std::string year,
                  std::string price) { //All column names in the table "cars"
    try{
        // Create a PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO cars (brand, model, kilometers, year, price) VALUES (?, ?, ?, ?, ?)"));

        // Bind values to SQL statement
        stmnt->setString(1, brand);
        stmnt->setString(2, model);
        stmnt->setString(3, kilometers);
        stmnt->setString(4, year);
        stmnt->setString(5, price);

        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e){
        std::cerr << "Error adding a new car: " << e.what() << std::endl;
    }
}

// Print inventory function
void printInventory(std::unique_ptr<sql::Connection> &conn) {
    try{
        // Create Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());

        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM cars");

        // Loop through and print results
        while (res->next()) {
            std::cout << "id = " << res->getInt(1);
            std::cout << ", brand = " << res->getString(2);
            std::cout << ", model = " << res->getBoolean(3);
            std::cout << ", kilometers = " << res->getFloat(4);
            std::cout << ", year = " << res->getInt(5);
            std::cout << ", price = " << res->getFloat(6) << "\n";
        }
    }
    catch(sql::SQLException& e) {
        std::cerr << "Error printing inventory: " << e.what() << std::endl;
    }
}

// Print orders function
void printOrders(std::unique_ptr<sql::Connection> &conn) {
    try{
        // Create Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());

        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM orders");

        // Loop through and print results
        while (res->next()) {
            std::cout << "id_order = " << res->getInt(1);
            std::cout << ", id_car = " << res->getInt(2);
            std::cout << ", id_client = " << res->getInt(3) << "\n";
        }
    }
    catch(sql::SQLException& e) {
        std::cerr << "Error printing inventory: " << e.what() << std::endl;
    }
}

// Main Function
int main(int argc, char const *argv[]) {
    if (argc==1){
        readtxt();
    }
    else{
        try {
            // Instantiate Driver
            sql::Driver* driver = sql::mariadb::get_driver_instance();

            // Configure Connection
            sql::SQLString url("jdbc:mariadb://localhost:3306/car_system");
            sql::Properties properties({{"user", "admin"}, {"password", "admin"}});

            // Establish Connection
            std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

            if (!strcmp(argv[1],"Register")) {
                if (argc != 7) {
                    std::cout << "Invalid arguments";
                    return 1;
                }
                registerFunc(conn, argv[2], argv[3], argv[4], argv[5], argv[6]);
            }

            if(!strcmp(argv[1],"makeOrder")) {
                if (argc != 9){
                    std::cout << "Invalid arguments";
                    return 1;
                }
                makeOrder(conn, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
            }

            if (!strcmp(argv[1],"addCar")) {
                if (argc != 7) {
                    std::cout << "Invalid arguments";
                    return 1;
                }
                addCar(conn, argv[2], argv[3], argv[4], argv[5], argv[6]);
            }

            if(!strcmp(argv[1], "printInventory")){
                printInventory(conn);
            }

            if(!strcmp(argv[1], "printOrders")){
                printOrders(conn);
            }
        }

        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }   
    }
    return 0;
}
