# Wesley Makcey's Makefile for string_set with slight modifications
# Juan Gonzalez 1497521
# Cmps 104a

GPP      = g++ -std=gnu++14 -g -O0 -Wall -Wextra
MKDEPS    = g++ -std=gnu++14 -MM

MKFILE   = Makefile
DEPSFILE = Makefile.deps
SOURCES  = auxlib.cpp stringset.cpp main.cpp
HEADERS  = auxlib.h stringset.h
OBJECTS  = ${SOURCES:.cpp=.o}
EXECBIN  = oc
SRCFILES = ${HEADERS} ${SOURCES} ${MKFILE}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GPP} ${OBJECTS} -o ${EXECBIN}

%.o : %.cpp
	${GPP} -c $<

ci :
	cid + ${SRCFILES}

clean :
	-rm ${OBJECTS} ${DEPSFILE}

spotless : clean
	- rm ${EXECBIN}

${DEPSFILE} :
	${MKDEPS} ${SOURCES} >${DEPSFILE}

deps :
	-rm ${DEPSFILE}
	${MAKE} --no-print-directory ${DEPSFILE}

include ${DEPSFILE}
