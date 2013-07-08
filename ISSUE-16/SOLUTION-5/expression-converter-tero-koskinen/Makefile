ANTLR4_JAR=$(HOME)/java/libs/antlr-4.0-complete.jar

default: classes/ir/EXPRParser.class

java/EXPRParser.java: EXPR.g4
	java -jar $(ANTLR4_JAR) -o java -visitor EXPR.g4

classes/ir/EXPRParser.class: dirs java/EXPRParser.java
	javac -cp $(ANTLR4_JAR) -d classes java/*.java

test:
	java -cp classes:$(ANTLR4_JAR) org.antlr.v4.runtime.misc.TestRig expr.EXPR expr examples/add1.expr -tree

dirs:
	mkdir -p lib classes

antlr:
	wget http://www.antlr.org/download/antlr-4.0-complete.jar


.PHONY: test dirs antlr
