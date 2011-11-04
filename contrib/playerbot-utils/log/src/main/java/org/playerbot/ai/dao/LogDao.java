package org.playerbot.ai.dao;

import java.util.Collection;

import org.playerbot.ai.domain.Log;

public interface LogDao {
    
    void initialize(String tableName);

    void insert(Collection<Log> log);


}