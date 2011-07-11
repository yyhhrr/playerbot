DROP TABLE IF EXISTS `ahbot_history`;

CREATE TABLE `ahbot_history` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `buytime` bigint(20) NOT NULL,
  `item` bigint(20) NOT NULL,
  `bid` bigint(20) NOT NULL,
  `buyout` bigint(20) NOT NULL,
  `won` bigint(20) NOT NULL,
  `category` varchar(45) DEFAULT NULL,
  `auction_house` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `won` (`won`),
  KEY `category` (`category`),
  KEY `auction_house` (`auction_house`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8

