package org.playerbot.ai.dao;

import java.util.Collection;

import org.playerbot.ai.domain.Log;
import org.playerbot.ai.domain.RepeatedAction;

public interface LogDao {
    
    void initialize(String tableName);

    void insert(Collection<Log> log);

    void clear();

    Collection<String> listBots();

    Collection<RepeatedAction> listActionsRepeated(String bot, String status);

    Collection<RepeatedAction> listTriggersRepeated(String bot);

    Collection<String> listNeverExecutedActions();


}