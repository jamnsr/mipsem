CC	= gcc
C	= c

PROJECT		= smolmips

OBJECTS = ${PROJECT}.o model.o view.o controller.o

${PROJECT}:	${PROJECT}.o model.o view.o controller.o
	${CC} ${LFLAGS} -o ${PROJECT} ${OBJECTS}

%.o: %.c
	${CC} -c *.${C}

clean:
	rm -f core.* *.o *~ ${PROJECT}
