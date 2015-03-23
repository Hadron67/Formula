XX=gcc
OBJECTS=mstring.o formula_typedef.o main.o formula_core.o formula_float.o
ARGS= -std=c99 -g -ggdb -lm
main:$(OBJECTS)
	$(XX) -o main $(OBJECTS) $(ARGS)
	rm $(OBJECTS)
mstring.o:mstring.c
	$(XX) -c -o mstring.o $(ARGS) mstring.c 
formula_typedef.o:formula_typedef.c
	$(XX) -c -o formula_typedef.o $(ARGS) formula_typedef.c 
main.o:Test.c
	$(XX) -c -o main.o $(ARGS) Test.c
formula_core.o:formula_core.c
	$(XX) -c -o formula_core.o formula_core.c $(ARGS)
formula_float.o:formula_float.c
	$(XX) -c -o formula_float.o formula_float.c $(ARGS)
soor:
	-rm $(OBJECTS)
	-rm main
