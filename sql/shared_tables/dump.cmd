mysqldump -uroot -p1 characters70 character_achievement character_achievement_progress character_queststatus character_queststatus_daily character_queststatus_monthly character_queststatus_weekly character_reputation character_social instance instance_reset > backup.sql
mysql -uroot -p1 -e "drop database if exists characters_common"
mysql -uroot -p1 -e "create database characters_common"
mysql -uroot -p1 characters_common < backup.sql
mysql -uroot -p1 characters_common < move.sql
mysql -uroot -p1 characters20 < characters_common.sql
mysql -uroot -p1 characters60 < characters_common.sql
mysql -uroot -p1 characters70 < characters_common.sql
mysql -uroot -p1 characters80 < characters_common.sql
