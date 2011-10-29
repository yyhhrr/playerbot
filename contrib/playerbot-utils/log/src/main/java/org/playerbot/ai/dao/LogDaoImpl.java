package org.playerbot.ai.dao;

import org.playerbot.ai.domain.Log;
import org.springframework.orm.jpa.support.JpaDaoSupport;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
public class LogDaoImpl extends JpaDaoSupport implements LogDao {

    @Transactional
    public Log merge(Log log) {
        return getJpaTemplate().merge(log);
    }

}
