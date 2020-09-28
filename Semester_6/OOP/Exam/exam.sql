-- MySQL dump 10.13  Distrib 8.0.18, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: surface
-- ------------------------------------------------------
-- Server version	5.5.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `points`
--

DROP TABLE IF EXISTS `points`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `points` (
  `point_id` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  PRIMARY KEY (`point_id`),
  UNIQUE KEY `point_id_UNIQUE` (`point_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `points`
--

LOCK TABLES `points` WRITE;
/*!40000 ALTER TABLE `points` DISABLE KEYS */;
INSERT INTO `points` VALUES (1,0,0),(2,0,6),(3,6,0),(4,3,1),(5,6,8),(6,7,3),(7,2,2),(8,4,9),(9,6,2);
/*!40000 ALTER TABLE `points` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `triangles`
--

DROP TABLE IF EXISTS `triangles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `triangles` (
  `triangle_id` int(11) NOT NULL AUTO_INCREMENT,
  `p1_id` int(11) NOT NULL,
  `p2_id` int(11) NOT NULL,
  `p3_id` int(11) NOT NULL,
  PRIMARY KEY (`triangle_id`),
  UNIQUE KEY `triangle_id_UNIQUE` (`triangle_id`),
  KEY `p1_id_idx` (`p1_id`),
  KEY `p2_id_idx` (`p2_id`),
  KEY `p3_id_idx` (`p3_id`),
  CONSTRAINT `p1_id` FOREIGN KEY (`p1_id`) REFERENCES `points` (`point_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `p2_id` FOREIGN KEY (`p2_id`) REFERENCES `points` (`point_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `p3_id` FOREIGN KEY (`p3_id`) REFERENCES `points` (`point_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `triangles`
--

LOCK TABLES `triangles` WRITE;
/*!40000 ALTER TABLE `triangles` DISABLE KEYS */;
INSERT INTO `triangles` VALUES (1,1,2,3),(2,4,5,6),(3,7,8,9);
/*!40000 ALTER TABLE `triangles` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-06-13 19:40:22
