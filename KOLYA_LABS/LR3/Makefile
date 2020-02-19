CFLAGS := -Wall -Werror -pedantic -std=c99 
CSOURCES := mysort.o filter.o fileproc.o printarr.o errors.o menu.o

%.o: %.c
	gcc -c $(CFLAGS) $<
	
app.%: $(CSOURCES)
	gcc $(CFLAGS) $(CSOURCES) main.c -o $@
	
test.%:  $(CSOURCES)
	gcc $(CFLAGS) $(CSOURCES) test.c -o $@

time.%:  $(CSOURCES)
	gcc $(CFLAGS) $(CSOURCES) time.c -o $@
	
clean:
	rm *.o *.exe *.out
