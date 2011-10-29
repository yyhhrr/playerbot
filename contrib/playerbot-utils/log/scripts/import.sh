#!/bin/bash
INPUT="$1/Server.log"
JAVA_OPTS="-Xmx512m -XX:MaxPermSize=128m"
CP="$M2_REPO/org/playerbot/ai/playerbot-log-utils/0.0.1-SNAPSHOT/playerbot-log-utils-0.0.1-SNAPSHOT-with-dependencies.jar"
JAVA_CMD="java -cp \"$CP\" $JAVA_OPTS org.playerbot.ai.ImportLog -in \"$INPUT\""

echo $JAVA_CMD
eval $JAVA_CMD