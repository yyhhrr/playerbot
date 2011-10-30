SELECT text, status, COUNT(date) AS REPEATED
FROM `playerbot_log`.`log` 
WHERE 
    event = 'A'
    AND bot = 'Eve'
    AND status = 'OK' -- IN ('OK', 'FAILED', 'IMPOSSIBLE', 'USELESS')
    
    -- Serpenshrine Cavern
    -- AND date BETWEEN '2011-10-23 14:07:50' AND '2011-10-23 14:32:02'
    
    -- Underbog
    -- AND date BETWEEN '2011-10-22 12:39:37' AND '2011-10-22 13:28:11'
    -- AND date BETWEEN '2011-10-23 18:24:44' AND '2011-10-23 19:16:09'
    
    -- Shadow labyrinth
    -- AND date BETWEEN '2011-10-22 15:14:37' AND '2011-10-22 17:30:25'
   
    -- Shadow labyrinth
    -- AND date BETWEEN '2011-10-28 19:28:55' AND '2011-10-28 21:44:52'
    
    -- Slave Pens
    -- AND date BETWEEN '2011-10-29 11:50:35' AND '2011-10-29 13:20:35'

    -- Serpenshrine Cavern
    -- AND date BETWEEN '2011-10-29 13:38:27' AND '2011-10-29 14:52:19'
    
    -- Auchenai Crypts
    -- AND date BETWEEN '2011-10-29 16:24:43' AND '2011-10-29 17:06:53'

    -- Botanica
    -- AND date BETWEEN '2011-10-30 08:30:43' AND '2011-10-30 09:27:53'
    
    -- Eye
    AND date BETWEEN '2011-10-30 14:45:24' AND '2011-10-30 15:53:15'


GROUP BY text, status
ORDER BY REPEATED DESC;

SELECT * FROM `playerbot_log`.`log` 
WHERE 
    bot = 'Jeni'
    AND event IN ('A', 'T')
    AND date BETWEEN '2011-10-29 14:08:27' AND '2011-10-29 14:09:19'
ORDER BY date;