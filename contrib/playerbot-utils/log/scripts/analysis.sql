SELECT *, COUNT(date) AS REPEATED
FROM `playerbot_log`.`log` 
WHERE 
    event = 'A'
    AND bot IN ('Jeni')
    AND status IN ('OK') -- , 'FAILED', 'IMPOSSIBLE', 'USELESS')
    
    -- Serpenshrine Cavern
    -- AND date BETWEEN '2011-10-23 14:07:50' AND '2011-10-23 14:32:02'
    
    -- Underbog
    -- AND date BETWEEN '2011-10-22 12:39:37' AND '2011-10-22 13:28:11'
    -- AND date BETWEEN '2011-10-23 18:24:44' AND '2011-10-23 19:16:09'
    
    -- Shadow labyrinth
    -- AND date BETWEEN '2011-10-22 15:14:37' AND '2011-10-22 17:30:25'
   
    -- Shadow labyrinth
    AND date BETWEEN '2011-10-28 19:28:55' AND '2011-10-28 21:44:52'
GROUP BY text, status
ORDER BY REPEATED DESC;
