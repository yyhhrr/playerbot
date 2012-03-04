package org.playerbot.ai;

import javax.inject.Inject;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.PosixParser;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

@Component
public class Launcher {
    
    @Inject
    private FileParser parser;

    @Inject
    private Watcher watcher;
    
    @Inject
    private LogProcessor processor;
    

    public static void main(String[] args) throws Exception {
        Options options = new Options();
        options.addOption("in", true, "Input file");

        CommandLineParser parser = new PosixParser();
        CommandLine cmd = parser.parse(options, args);

        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("classpath:/META-INF/context.xml");
        Launcher bean = ctx.getBean(Launcher.class);
        bean.run(cmd.getOptionValue("in"));
    }

    private void run(String fileName) {
        parser.startParsing(fileName);
        watcher.startWatching();
        processor.startProcessing();
    }

}
