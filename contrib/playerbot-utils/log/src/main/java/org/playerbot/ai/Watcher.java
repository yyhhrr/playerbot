package org.playerbot.ai;

import javax.inject.Inject;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

@Component
public class Watcher implements Runnable {
    private Logger logger = LoggerFactory.getLogger(getClass());
    
    @Inject
    private FileParser parser;
    
    @Inject
    private LogBuffer buffer;

    public void run() {
        while (!buffer.isClosed()) {
            logger.info(parser.getLinesParsed() + " lines parsed, " + Runtime.getRuntime().totalMemory() / 1024 / 1024 + "M");

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
            }
        }
    }

    public Thread startWatching() {
        Thread thread = new Thread(this);
        thread.start();
        return thread;
    }
}