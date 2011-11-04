package org.playerbot.ai;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

import javax.inject.Inject;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.PosixParser;
import org.playerbot.ai.dao.LogDao;
import org.playerbot.ai.domain.Log;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

@Component
public class ImportLog {

    protected static final int MAX_BUFFER_SIZE = 5000;

    @Inject
    private LogDao dao;

    @Inject
    private LineParser parser;

    private Queue<Log> buffer = new LinkedList<Log>();
    private volatile boolean finished = false;
    private volatile long saved = 0; 

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
        
        new Thread(new LogFileParser(fileName)).start();

        new Thread(new LogDbFlusher()).start();
        new Thread(new LogDbFlusher()).start();

        new Thread(new Watcher()).start();
    }

    private class Watcher implements Runnable {

        public void run() {
            while (!finished || !buffer.isEmpty()) {
                System.out.println(saved + " updates done, " + Runtime.getRuntime().totalMemory() / 1024 / 1024 + "M");

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                }
            }
        }

    }

    private class LogDbFlusher implements Runnable {

        public LogDbFlusher() {
        }

        public void run() {
            while (!finished || !buffer.isEmpty()) {
                if (buffer.isEmpty()) {
                    Thread.yield();
                    continue;
                }
                List<Log> copy;
                synchronized (buffer) {
                    copy = new ArrayList<Log>(buffer);
                    saved += buffer.size();
                    buffer.clear();
                }
                dao.insert(copy);
            }
        }

    }

    private class LogFileParser implements Runnable {

        private String fileName;

        public LogFileParser(String fileName) {
            super();
            this.fileName = fileName;
        }

        public void run() {
            try {
                runInternal();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }

        private void runInternal() throws FileNotFoundException, IOException {
            BufferedReader reader = new BufferedReader(new FileReader(fileName));
            String line;
            Date previoslyParsed = new Date();
            int millisToAdd = 0;
            while ((line = reader.readLine()) != null) {
                Log log = parser.parse(line);
                if (log == null)
                    continue;

                if (log.getDate().equals(previoslyParsed)) {
                    log.setNumber(++millisToAdd);
                }
                else {
                    millisToAdd = 0;
                }
                
                previoslyParsed = log.getDate();
                
                while (buffer.size() > MAX_BUFFER_SIZE) {
                    Thread.yield();
                }

                synchronized (buffer) {
                    buffer.add(log);
                }
            }
            reader.close();

            finished = true;
        }

    }
}
