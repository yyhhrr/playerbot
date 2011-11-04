package org.playerbot.ai;

import java.util.Collection;

import javax.inject.Inject;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.PosixParser;
import org.apache.commons.lang.StringUtils;
import org.playerbot.ai.dao.LogDao;
import org.playerbot.ai.domain.RepeatedAction;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

@Component
public class AnalyseLog {
    @Inject
    private LogDao dao;
    private Collection<String> bots;

    public static void main(String[] args) throws Exception {
        Options options = new Options();
        options.addOption("in", true, "Input table name");

        CommandLineParser parser = new PosixParser();
        CommandLine cmd = parser.parse(options, args);

        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("classpath:/META-INF/context.xml");
        AnalyseLog bean = ctx.getBean(AnalyseLog.class);
        bean.run(cmd.getOptionValue("in"));
    }

    private void run(String tableName) {
        if (StringUtils.isEmpty(tableName))
            throw new RuntimeException("-in parameter is required");
        
        dao.initialize(tableName);

        analyse();
    }

    private void analyse() {
        bots = dao.listBots();
        
        analyseNeverExecutedActions();
        analyseTriggers();
        analyseRepeatedActions();
    }

    private void analyseNeverExecutedActions() {
        for (String bot : bots) {
            drawTitle("Never executed", bot);
            
            Collection<String> actions = dao.listNeverExecutedActions(bot);
            for (String action : actions) {
                System.out.println(action);
            }
        }
    }

    private void analyseTriggers() {
        for (String bot : bots) {
            drawTitle("Triggers", bot);
            
            drawActions(dao.listTriggersRepeated(bot));
        }
    }

    private void analyseRepeatedActions() {
        String[] statuses = new String[] { "OK", "UNKNOWN", "FAILED", "IMPOSSIBLE" };
        for (String status : statuses) {
            for (String bot : bots) {
                drawTitle(status, bot);
                
                drawActions(dao.listActionsRepeated(bot, status));
            }
        }
    }
    
    private void drawActions(Collection<RepeatedAction> actions) {
        for (RepeatedAction action : actions) {
            drawAction(action);
        }
    }

    private void drawAction(RepeatedAction action) {
        System.out.println(String.format("%8d %s", action.getCount(), action.getName()));
    }

    private void drawTitle(String title) {
        System.out.println("======================================================================");
        System.out.println(title);
        System.out.println("======================================================================");
    }
    
    private void drawTitle(String status, String bot) {
        drawTitle(bot + " - " + status);
    }

}
