CPP = g++
CPPFLAGS = -std=c++11

vishalfm: delete.o file_status.o scrolling_printing.o command_handling.o creating_file.o global.h new_code.o
	$(CPP) $(CPPFLAGS) delete.o file_status.o scrolling_printing.o command_handling.o creating_file.o global.h new_code.o -o vishalfm

new_code.o: new_code.cpp global.h
	$(CPP) $(CPPFLAGS) -c new_code.cpp

delete.o: delete.cpp global.h
	$(CPP) $(CPPFLAGS) -c delete.cpp

file_status.o: file_status.cpp global.h
	$(CPP) $(	CPPFLAGS) -c file_status.cpp

scrolling_printing.o: scrolling_printing.cpp global.h
	$(CPP) $(CPPFLAGS) -c scrolling_printing.cpp

command_handling.o: command_handling.cpp global.h
	$(CPP) $(CPPFLAGS) -c command_handling.cpp
	
creating_file.o: creating_file.cpp global.h
	$(CPP) $(CPPFLAGS) -c creating_file.cpp

fix:vishalfm
	chmod +x vishalfm
