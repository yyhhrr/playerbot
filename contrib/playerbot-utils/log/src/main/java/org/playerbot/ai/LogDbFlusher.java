package org.playerbot.ai;

import java.util.ArrayList;
import java.util.List;

import javax.inject.Inject;

import org.playerbot.ai.dao.LogDao;
import org.playerbot.ai.domain.Log;
import org.springframework.stereotype.Component;

@Component
public class LogDbFlusher implements Runnable {
    
    @Inject
    private LogBuffer buffer;

    @Inject
    private LogDao dao;
    
    public void run() {
        while (!buffer.isClosed() || !buffer.isEmpty()) {
            if (buffer.isEmpty()) {
                Thread.yield();
                continue;
            }
            List<Log> copy;
            synchronized (buffer) {
                copy = new ArrayList<Log>(buffer.getData());
                buffer.clear();
            }
            try {
                dao.insert(copy);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public Thread startFlushing() {
        Thread thread = new Thread(this);
        thread.start();
        return thread;

    }

}
