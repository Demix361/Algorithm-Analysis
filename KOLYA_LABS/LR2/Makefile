CFLAGS := -Wall -std=c99 -pedantic

CSOURCES := memory.o matrio.o matrproc.o errors.o

%.o: %.c
	gcc -c $(CFLAGS) $< -lm
	
app.%: $(CSOURCES)
	gcc $(CFLAGS) $(CSOURCES) main.c -o $@ -lm
	
test.%:  $(CSOURCES)
	gcc $(CFLAGS) $(CSOURCES) test.c -o $@ -lm
	
clean:
	rm *.o *.exe *.out
