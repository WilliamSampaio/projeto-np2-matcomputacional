CREATE DATABASE  IF NOT EXISTS `imc01` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `imc01`;
-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: imc01
-- ------------------------------------------------------
-- Server version	5.5.5-10.1.34-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `registros`
--

DROP TABLE IF EXISTS `registros`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `registros` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `usuarios_id` int(10) unsigned NOT NULL,
  `imc` decimal(4,2) NOT NULL,
  `datahora` varchar(22) NOT NULL,
  PRIMARY KEY (`id`,`usuarios_id`),
  KEY `fk_registros_usuarios_idx` (`usuarios_id`),
  CONSTRAINT `fk_registros_usuarios` FOREIGN KEY (`usuarios_id`) REFERENCES `usuarios` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `registros`
--

LOCK TABLES `registros` WRITE;
/*!40000 ALTER TABLE `registros` DISABLE KEYS */;
INSERT INTO `registros` VALUES (19,1,15.00,'Oct 23 2018 - 00:40:52'),(20,1,15.43,'Oct 23 2018 - 00:42:37'),(21,1,15.43,'Oct 23 2018 - 02:48:24'),(34,1,15.43,'Oct 25 2018 - 15:37:14'),(36,1,15.43,'Oct 25 2018 - 17:20:57'),(37,1,15.43,'Oct 25 2018 - 17:23:32'),(38,9,15.63,'Oct 25 2018 - 17:27:01'),(39,9,15.63,'Oct 25 2018 - 17:27:01');
/*!40000 ALTER TABLE `registros` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `usuarios`
--

DROP TABLE IF EXISTS `usuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `usuarios` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `nome` varchar(60) NOT NULL,
  `sexo` enum('M','F') NOT NULL,
  `login` varchar(20) NOT NULL,
  `senha` int(5) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `login_UNIQUE` (`login`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `usuarios`
--

LOCK TABLES `usuarios` WRITE;
/*!40000 ALTER TABLE `usuarios` DISABLE KEYS */;
INSERT INTO `usuarios` VALUES (1,'BONNER BONNER','F','bonner',123),(3,'ANTONIO SILVA','M','silva',123),(4,'JESSICA CARVALHO','F','jessie',123),(5,'MARCOS VINICIUS','F','marcola',123),(8,'BENJAMIM MENEZES','M','ben',123),(9,'REGINA BRAGA DE MENEZES','F','reh',123);
/*!40000 ALTER TABLE `usuarios` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-10-25 22:20:44
