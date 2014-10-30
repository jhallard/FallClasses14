# Author - John Allard
# Info	 For CS12B Lab#3
# Makefile for RPN Calculator Program.

JAVASRC = Calc.java Stack.java CalcTest.java
SOURCES = README makefile ${JAVASRC}
MAINCLASS = Calc
CLASSES = Calc.class Stack.class CalcTest.class
JARFILE = Calc
JARCLASSES = ${CLASSES}

all: ${JARFILE}
${JARFILE}: ${CLASSES}
	echo "Main-class: ${MAINCLASS}" > Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	rm Manifest
	chmod +x ${JARFILE}

# !!!!!!!!!!! important !!!!!!!!
#if you are getting errors, it might be because you are using junit-4.12-beta-1 instead of junit-4.12-beta-2
# On the instructions it says to use beta-2, but in the /afs/ directory there was only beta-1 availble.
test: ${JAVASRC}
	javac -cp "junit-4.12-beta-2.jar:hamcrest-core-1.3.jar:." CalcTest.java
	java -cp "junit-4.12-beta-2.jar:hamcrest-core-1.3.jar:." org.junit.runner.JUnitCore CalcTest

${CLASSES}: ${JAVASRC}
	javac -Xlint ${JAVASRC}
clean:
	rm ${CLASSES} ${JARFILE}
.PHONY:clean-all
