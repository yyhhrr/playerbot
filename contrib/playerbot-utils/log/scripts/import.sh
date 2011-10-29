#!/bin/bash
INPUT="$1/Server.log"
CP="$M2_REPO/org/playerbot/ai/playerbot-log-utils/0.0.1-SNAPSHOT/playerbot-log-utils-0.0.1-SNAPSHOT-with-dependencies.jar"
JAVA_CMD="java -cp \"$CP\" org.playerbot.ai.ImportLog -in \"$INPUT\""

echo $JAVA_CMD
eval $JAVA_CMD