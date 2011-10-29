package org.playerbot.ai;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Date;
import java.util.LinkedList;
import java.util.Queue;

import javax.inject.Inject;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.PosixParser;
import org.apache.commons.lang.time.DateUtils;
import org.playerbot.ai.dao.LogDao;
import org.playerbot.ai.domain.Log;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

@Component
public class ImportLog {

    @Inject
    private LogDao dao;

    @Inject
    private LineParser parser;

    private Queue<Log> buffer = new LinkedList<Log>();
    private boolean parsed = false;
    private boolean merged = false;

    public static void main(String[] args) throws Exception {
        Options options = new Options();
        options.addOption("in", true, "Input file");

        CommandLineParser parser = new PosixParser();
        CommandLine cmd = parser.parse(options, args);

        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("classpath:/META-INF/context.xml");
        ImportLog bean = ctx.getBean(ImportLog.class);
        bean.run(cmd.getOptionValue("in"));
    }

    private void run(String fileName) {
        new Thread(new LogFileParser(fileName)).start();

        new Thread(new LogDbFlusher()).start();
        new Thread(new LogDbFlusher()).start();

        new Thread(new Watcher()).start();
    }

    private class Watcher implements Runnable {

        public void run() {
            while (!merged) {
                int size = buffer.size();
                System.out.println(size + " updates left");

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                }
            }
        }

    }

    private class LogDbFlusher implements Runnable {

        public void run() {
            while (true) {
                Log log;
                synchronized (buffer) {
                    log = buffer.poll();
                }

                if (log == null) {
                    if (parsed)
                        break;
                    Thread.yield();
                    continue;
                }

                dao.merge(log);
            }

            merged = true;
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

                synchronized (buffer) {
                    buffer.add(log);
                }
            }
            reader.close();

            parsed = true;
        }

    }
}
