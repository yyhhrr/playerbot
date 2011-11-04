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

        Collection<String> bots = dao.listBots();
        String[] statuses = new String[] { "OK", "UNKNOWN", "FAILED", "IMPOSSIBLE" };
        for (String status : statuses) {
            for (String bot : bots) {
                drawTitle(status, bot);
                Collection<RepeatedAction> actions = dao.listActionsRepeated(bot, status);
                for (RepeatedAction action : actions) {
                    drawAction(action);
                }
            }
        }
    }

    private void drawAction(RepeatedAction action) {
        System.out.println(String.format("%8d %s", action.getCount(), action.getName()));
    }

    private void drawTitle(String status, String bot) {
        System.out.println("======================================================================");
        System.out.println(bot + " - " + status);
        System.out.println("======================================================================");
    }

}
