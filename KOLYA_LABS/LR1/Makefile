CFLAGS := -Wall -Werror -pedantic -std=c99 -fPIC
DLIBSOURCES := tick.o

%.o: %.c
	gcc -c $(CFLAGS) $<

libtick.so: $(DLIBSOURCES)
	gcc -shared $(DLIBSOURCES) -o $@
	make clean

test.%:  $(DLIBSOURCES)
	gcc $(CFLAGS) $(DLIBSOURCES) test.c -o $@ -lm


clean_lib:
	rm *.so 

clean:
	rm *.o 
