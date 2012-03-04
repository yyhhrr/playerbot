package org.playerbot.ai.processors;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.TreeMap;

import org.playerbot.ai.ValueComparator;
import org.playerbot.ai.domain.Log;

public abstract class AbstractCounter implements Processor {
    
    private Map<String, Integer> count = new HashMap<String, Integer>(); 

    @Override
    public final void process(Log entry) {
        if (!isCountable(entry))
            return;
        
        String key = entry.getText();
        if (!count.containsKey(key))
            count.put(key, 0);
        
        count.put(key, count.get(key) + 1);
    }
    
    protected abstract boolean isCountable(Log entry);
  
    @Override
    public String report() {
        Map<String, Integer> map = new TreeMap<String, Integer>(new ValueComparator<Integer>(count));
        map.putAll(count);
        
        StringBuilder sb = new StringBuilder();
        for (Entry<String, Integer> entry : map.entrySet()) {
            sb.append(String.format("%8d %s", entry.getValue(), entry.getKey()));
            sb.append("\n");
        }
        return sb.toString();
    }
}
