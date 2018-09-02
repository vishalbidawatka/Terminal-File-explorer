#ROll No: 2018201004
#Name: VISHAL BIDAWATKA
CC = g++
CFLAGS =  -std=c++11
DEPS = global.h
OBJ =delete.o file_status.o scrolling_printing.o command_handling.o creating_file.o global.h main_file.o copy_files.o goto_dir.o recursion_list.o search.o snapshot.o move_files.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

vishalfm: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o
fix:vishalfm
	chmod +x vishalfm
