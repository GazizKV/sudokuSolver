PREFIX = /gazizkv/local/bin
TARGET = solver

.PHONY: all clean install uninstall

make: solver.c
	gcc -o $(TARGET) solver.c
s:	solver.c
	gcc -o $(TARGET) solver.c
	./solver
clean:
	rm -rf solver *.o *~ a.out
install:
	install $(TARGET) $(PREFIX)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)
