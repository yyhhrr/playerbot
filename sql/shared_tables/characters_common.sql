
-- 70
  
DROP TABLE IF EXISTS    `character_queststatus`;
DROP TABLE IF EXISTS    `character_achievement`;
DROP TABLE IF EXISTS    `character_achievement_progress`;
DROP TABLE IF EXISTS    `character_queststatus_daily`;
DROP TABLE IF EXISTS    `character_queststatus_monthly`;
DROP TABLE IF EXISTS    `character_queststatus_weekly`;
DROP TABLE IF EXISTS    `character_reputation`;
DROP TABLE IF EXISTS    `character_social`;


DROP VIEW IF EXISTS    `character_queststatus`;
DROP VIEW IF EXISTS    `character_achievement`;
DROP VIEW IF EXISTS    `character_achievement_progress`;
DROP VIEW IF EXISTS    `character_queststatus_daily`;
DROP VIEW IF EXISTS    `character_queststatus_monthly`;
DROP VIEW IF EXISTS    `character_queststatus_weekly`;
DROP VIEW IF EXISTS    `character_reputation`;
DROP VIEW IF EXISTS    `character_social`;


CREATE  VIEW `character_queststatus` AS 
SELECT * FROM `characters_common`.`character_queststatus`
WHERE quest IN (SELECT entry FROM `udb`.`quest_template` WHERE QuestLevel <= 70 AND MinLevel <= 70);


CREATE  VIEW `character_achievement` AS SELECT * FROM `characters_common`.`character_achievement`;
CREATE  VIEW `character_achievement_progress` AS SELECT * FROM `characters_common`.`character_achievement_progress`;
CREATE  VIEW `character_queststatus_daily` AS SELECT * FROM `characters_common`.`character_queststatus_daily`;
CREATE  VIEW `character_queststatus_monthly` AS SELECT * FROM `characters_common`.`character_queststatus_monthly`;
CREATE  VIEW `character_queststatus_weekly` AS SELECT * FROM `characters_common`.`character_queststatus_weekly`;
CREATE  VIEW `character_reputation` AS SELECT * FROM `characters_common`.`character_reputation`;
CREATE  VIEW `character_social` AS SELECT * FROM `characters_common`.`character_social`;
