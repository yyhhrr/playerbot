package org.playerbot.ai.dao;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceException;

import org.playerbot.ai.domain.Log;
import org.springframework.orm.jpa.JpaCallback;
import org.springframework.orm.jpa.support.JpaDaoSupport;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
public class LogDaoImpl extends JpaDaoSupport implements LogDao {

    @Transactional
    public Log merge(final Log log) {
        return getJpaTemplate().execute(new JpaCallback<Log>() {
            public Log doInJpa(EntityManager em) throws PersistenceException {
                Log merged = em.merge(log);
                em.flush();
                em.clear();
                return merged;
            }
        }, true);
    }

}
