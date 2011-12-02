mysqldump -uroot -p1 characters70 character_achievement character_achievement_progress character_queststatus character_queststatus_daily character_queststatus_monthly character_queststatus_weekly character_reputation character_social instance instance_reset > backup.sql
mysql -uroot -p1 characters_common < backup.sql
mysql -uroot -p1 characters_common < characters_common.sql

