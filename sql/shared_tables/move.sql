delete from characters_common.character_queststatus;

insert into characters_common.character_queststatus
select distinct * from (
select * from characters60.character_queststatus
union
select * from characters70.character_queststatus
union
select * from characters80.character_queststatus
) q
group by guid, quest;



delete from characters_common.character_achievement;

insert into characters_common.character_achievement
select distinct * from (
select * from characters60.character_achievement
union
select * from characters70.character_achievement
union
select * from characters80.character_achievement
) q
group by guid, achievement;



delete from characters_common.character_reputation;

insert into characters_common.character_reputation
select guid, faction, max(standing) as standing, flags from (
select * from characters60.character_reputation
union
select * from characters70.character_reputation
union
select * from characters80.character_reputation
) q
group by guid, faction;

