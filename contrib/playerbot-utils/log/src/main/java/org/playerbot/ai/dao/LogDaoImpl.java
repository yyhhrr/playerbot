package org.playerbot.ai.dao;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.Collection;

import org.playerbot.ai.domain.Log;
import org.playerbot.ai.domain.RepeatedAction;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.PreparedStatementCallback;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.jdbc.core.support.JdbcDaoSupport;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
public class LogDaoImpl extends JdbcDaoSupport implements LogDao {

    private String tableName;

    @Override
    @Transactional
    public void initialize(String tableName) {
        this.tableName = tableName;
    }

    @Override
    public void clear() {
        dropTableIfExists();
        createTable();
    }

    private static final String INSERT_TEMPLATE = "INSERT INTO %s (bot, event, status, date, number, text) VALUES (?, ?, ?, ?, ?, ?)";

    @Transactional
    @Override
    public void insert(final Collection<Log> batch) {
        String sql = String.format(INSERT_TEMPLATE, tableName);
        getJdbcTemplate().execute(sql, new PreparedStatementCallback<Void>() {

            @Override
            public Void doInPreparedStatement(PreparedStatement ps) throws SQLException, DataAccessException {
                for (Log log : batch) {
                    ps.setString(1, log.getBot());
                    ps.setString(2, log.getEvent());
                    ps.setString(3, log.getStatus());
                    ps.setTimestamp(4, new Timestamp(log.getDate().getTime()));
                    ps.setLong(5, log.getNumber());
                    ps.setString(6, log.getText());
                    ps.executeUpdate();
                }
                return null;
            }
        });
    }

    private static final String DROP_TABLE_TEMPLATE = "DROP TABLE IF EXISTS %s";
    
    private void dropTableIfExists() {
        String sql = String.format(DROP_TABLE_TEMPLATE, tableName);
        getJdbcTemplate().execute(sql);
    }

    private static final String CREATE_TABLE_TEMPLATE = "CREATE TABLE `%s` (" + 
    		"  `date` datetime NOT NULL," + 
    		"  `number` int(4) NOT NULL," + 
    		"  `bot` char(10) DEFAULT NULL," + 
    		"  `event` char(4) DEFAULT NULL," + 
    		"  `text` varchar(255) DEFAULT NULL," + 
    		"  `status` char(10) DEFAULT NULL," + 
    		"  PRIMARY KEY (`date`,`number`)," + 
    		"  KEY `TEXT` (`text`)," + 
    		"  KEY `MERGED` (`bot`,`event`,`status`)" + 
    		")";
        
    private void createTable() {
        String sql = String.format(CREATE_TABLE_TEMPLATE, tableName);
        getJdbcTemplate().execute(sql);
    }

    private static final String LIST_BOTS_TEMPLATE = "SELECT DISTINCT bot FROM %s ORDER BY bot";

    private static final RowMapper<String> STRING_ROW_MAPPER = new RowMapper<String>() {
        @Override
        public String mapRow(ResultSet rs, int rowNum) throws SQLException {
            return rs.getString(1);
        }
    };
    
    @Override
    public Collection<String> listBots() {
        String sql = String.format(LIST_BOTS_TEMPLATE, tableName);
        return getJdbcTemplate().query(sql, STRING_ROW_MAPPER);
    }

    private static final RowMapper<RepeatedAction> REPEATED_ACTION_MAPPER = new RowMapper<RepeatedAction>() {
        @Override
        public RepeatedAction mapRow(ResultSet rs, int rowNum) throws SQLException {
            return new RepeatedAction(rs.getString(1), rs.getLong(2));
        }
    };
    
    private static final String LIST_ACTIONS_REPEATED_TEMPLATE = "SELECT text, COUNT(date) AS repeated " + 
            "FROM `%s` " + 
            "WHERE event = 'A' AND bot = ? AND status = ? " + 
            "GROUP BY text " + 
            "ORDER BY repeated DESC;";

    @Override
    public Collection<RepeatedAction> listActionsRepeated(String bot, String status) {
        String sql = String.format(LIST_ACTIONS_REPEATED_TEMPLATE, tableName);
        return getJdbcTemplate().query(sql, REPEATED_ACTION_MAPPER, bot, status);
    }

    private static final String LIST_TRIGGERS_REPEATED_TEMPLATE = "SELECT text, COUNT(date) AS repeated " + 
            "FROM `%s` " + 
            "WHERE event = 'T' AND bot = ? " + 
            "GROUP BY text " + 
            "ORDER BY repeated DESC;";
    
    @Override
    public Collection<RepeatedAction> listTriggersRepeated(String bot) {
        String sql = String.format(LIST_TRIGGERS_REPEATED_TEMPLATE, tableName);
        return getJdbcTemplate().query(sql, REPEATED_ACTION_MAPPER, bot);
    }

    private static final String LIST_NEVER_EXECUTED_ACTIONS_TEMPLATE = "SELECT text " + 
    		"FROM `%1$s` " + 
    		"WHERE event='A' AND status <> 'OK' " + 
    		"GROUP BY text " + 
    		"HAVING text NOT IN " + 
    		"(SELECT DISTINCT text FROM `%1$s` WHERE event='A' AND status = 'OK');" + 
    		"";
    
    @Override
    public Collection<String> listNeverExecutedActions() {
        String sql = String.format(LIST_NEVER_EXECUTED_ACTIONS_TEMPLATE, tableName);
        return getJdbcTemplate().query(sql, STRING_ROW_MAPPER);
    }

}
