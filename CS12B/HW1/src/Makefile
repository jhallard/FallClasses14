# Author - John Allard
# Info	 For CS12B HW#1
# Makefile for Business Search program.

JAVASRC = BusinessSearch.java BusinessRecord.java
SOURCES = README makefile ${JAVASRC}
MAINCLASS = BusinessSearch
CLASSES = BusinessSearch.class BusinessRecord.class
JARFILE = BusinessSearch
JARCLASSES = ${CLASSES}

all: ${JARFILE}
${JARFILE}: ${CLASSES}
	echo "Main-class: ${MAINCLASS}" > Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	rm Manifest
	chmod +x ${JARFILE}


${CLASSES}: ${JAVASRC}
	javac -Xlint ${JAVASRC}
clean:
	rm ${CLASSES} ${JARFILE}
.PHONY:clean-all
