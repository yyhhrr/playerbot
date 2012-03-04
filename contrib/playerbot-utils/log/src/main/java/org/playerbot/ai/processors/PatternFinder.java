package org.playerbot.ai.processors;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.playerbot.ai.domain.Log;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class PatternFinder implements Processor {
    private Logger logger = LoggerFactory.getLogger(getClass());
        
    private List<String> tmpActions = new LinkedList<String>(); 
    private String[] actions; 
    private Map<String, Integer> patterns = new HashMap<String, Integer>();
    private int minCount;

    public PatternFinder(int minCount) {
        super();
        this.minCount = minCount;
    }

    @Override
    public void process(Log entry) {
        if (!"A".equals(entry.getEvent()) || !"OK".equals(entry.getStatus()))
            return;
        
        String action = entry.getText();
        tmpActions.add(action);
    }
    
    @Override
    public String report() {
        calculate();
        
        for (String pattern : new HashSet<String>(patterns.keySet())) {
            if (patterns.get(pattern) < minCount)
                patterns.remove(pattern);
        }
        
        return CountFormatter.format(patterns);
    }

    private void calculate() {
        actions = tmpActions.toArray(new String[tmpActions.size()]);
        
        for (int i = 10; i > 3; i--)
            calculate(i);
    }
    
    private void calculate(int length) {
        logger.info(String.format("Calculating %d-patterns in %d actions", length, actions.length));
        
        for (int i = 0; i < actions.length - length; i++) {
            calculate(i, length);
        }        
    }

    private void calculate(int start, int length) {
        String formattedPattern = format(start, length);
        if (patterns.containsKey(formattedPattern))
            return;
        
        for (String existingPattern : patterns.keySet()) {
            if (existingPattern.contains(formattedPattern))
                return;
        }
        
        outer: for (int i = 1 + start; i <= actions.length - length; i++) {
            for (int j = 0; j < length; j++) {
                String patternString = actions[start + j];
                String actionString = actions[i + j];
                if (patternString.hashCode() != actionString.hashCode() && !patternString.equals(actionString))
                    continue outer;
            }
            add(formattedPattern);
        }
    }

    private String format(int start, int length) {
        StringBuilder sb = new StringBuilder();
        for (int i = start; i < start + length; i++)
            sb.append(",").append(actions[i]);
        return sb.length() > 0 ? sb.substring(1).toString() : "";
    }

    private void add(String pattern) {
        if (!patterns.containsKey(pattern))
            patterns.put(pattern, 1);
        
        patterns.put(pattern, patterns.get(pattern) + 1);
    }

    @Override
    public String getName() {
        return "Patterns";
    }
}
