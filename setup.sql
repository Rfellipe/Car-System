DROP DATABASE IF EXISTS `car_system`;

CREATE DATABASE `car_system`;

USE car_system;

DROP TABLE IF EXISTS `cars`;

CREATE TABLE `cars` (
  `id_car` bigint(5) unsigned NOT NULL AUTO_INCREMENT,
  `brand` varchar(45) DEFAULT NULL,
  `model` varchar(45) DEFAULT NULL,
  `kilometers` float DEFAULT NULL,
  `year` int(5) DEFAULT NULL,
  `price` float DEFAULT NULL,
  PRIMARY KEY (`id_car`),
  UNIQUE KEY `idCar_UNIQUE` (`id_car`)
) AUTO_INCREMENT=118;

INSERT INTO `cars` 
  (`brand`, `model`, `kilometers`, `year`, `price`) 
VALUES
  ('Honda', 'Civic', '250000', '1995', '35000'), ('Mazda', 'MX-5', '320000', '2002', '100000'), ('Subaru', 'Impreza', '420000', '2007', '90000'), ('Toyota', 'Corolla', '80000', '1999', '30000'), ('Subaru', 'BRZ', '60000', '2022', '230000'), ('Nissan', '370Z', '125000', '2020', '500000'), ('Nissan', '350Z', '45000', '2000', '700000'), ('Toyota', 'Supra', '78000', '2000', '900000'), ('Mitsubishi', 'Eclipse', '94000', '1991', '100000'), ('Honda', 'Civic', '69000', '2017', '40000'), ('Mitsubishi', 'Lancer', '104000', '2010', '80000');

DROP TABLE IF EXISTS `clients`;

CREATE TABLE `clients` (
  `id_client` bigint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `surname` varchar(45) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  `cpf` varchar(11) DEFAULT NULL,
  `phone` int(11) DEFAULT NULL,
  PRIMARY KEY (`id_client`),
  UNIQUE KEY `idClient_UNIQUE` (`id_client`)
) AUTO_INCREMENT=33;

INSERT INTO `clients`
  (`name`, `surname`, `address`, `cpf`, `phone`)
VALUES
  ('Glenn', 'Wood', '528 Sundown Lane', '31376514095',  '35488723'), ('Joshua', 'Glisson', '3337 Candlelight Drive', '39786902092', '33345326'), ('Gary', 'Wilson', '4964 Emerson Road', '58094734096', '24166540'), ('Mary', 'Farmer', '596 Timber Oak Drive', '55182702086',  '24768088'), ('Rose', 'Farmer', '3113 Cook Hill Road', '27117922001', '35562626'), ('Calvin', 'Human', '3348 American Drive', '68489295069', '28619557'), ('Randall', 'Ortiz', '2009 Wayside Lane', '42999771061', '37559333'); 

DROP TABLE IF EXISTS `orders`;

CREATE TABLE `orders` (
  `id_order` bigint(5) unsigned NOT NULL AUTO_INCREMENT,
  `id_car` bigint(5) unsigned NOT NULL,
  `id_client` bigint(5) unsigned NOT NULL,
  PRIMARY KEY (`id_order`),
  UNIQUE KEY `id_order_UNIQUE` (`id_order`),
  KEY `buyer_idx` (`id_client`),
  KEY `car_idx` (`id_car`),
  CONSTRAINT `buyer` FOREIGN KEY (`id_client`) REFERENCES `clients` (`id_client`),
  CONSTRAINT `car` FOREIGN KEY (`id_car`) REFERENCES `cars` (`id_car`)
) AUTO_INCREMENT=19;
