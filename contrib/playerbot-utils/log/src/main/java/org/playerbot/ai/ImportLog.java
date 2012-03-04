package org.playerbot.ai;

import javax.inject.Inject;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.PosixParser;
import org.playerbot.ai.dao.LogDao;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

@Component
public class ImportLog {

    protected static final int MAX_BUFFER_SIZE = 5000;

    @Inject
    private LogDao dao;

    @Inject
    private FileParser parser;

    @Inject
    private Watcher watcher;
    
    @Inject
    private LogDbFlusher dbFlusher;
    

    public static void main(String[] args) throws Exception {
        Options options = new Options();
        options.addOption("in", true, "Input file");
        options.addOption("out", true, "Output table name");

        CommandLineParser parser = new PosixParser();
        CommandLine cmd = parser.parse(options, args);

        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("classpath:/META-INF/context.xml");
        ImportLog bean = ctx.getBean(ImportLog.class);
        bean.run(cmd.getOptionValue("in"), cmd.getOptionValue("out"));
    }

    private void run(String fileName, String tableName) {
        dao.initialize(tableName);
        dao.clear();
        
        parser.startParsing(fileName);
        dbFlusher.startFlushing();
        watcher.startWatching();
    }



}
