# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++
LFLAGS  = -L/usr/lib

# All Targets
all: cyber

# Tool invocations
# Executable "cyber" depends on the files: cyberpc.o ,cyberexpert.o, cyberworm.o, cyberdns.o and main.o
cyber: bin/cyberpc.o bin/cyberexpert.o bin/cyberworm.o bin/cyberdns.o bin/main.o 
	@echo 'Building target: cyber'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/cyber bin/cyberpc.o bin/cyberdns.o bin/cyberworm.o bin/cyberexpert.o bin/main.o    $(LFLAGS)
	@echo 'Finished building target: cyber' 
	@echo ' '

# Depends on the source and header files 
bin/cyberpc.o: src/cyberpc.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberpc.o src/cyberpc.cpp

bin/cyberdns.o: src/cyberdns.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberdns.o src/cyberdns.cpp
	
bin/cyberworm.o: src/cyberworm.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberworm.o src/cyberworm.cpp

bin/cyberexpert.o: src/cyberexpert.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberexpert.o src/cyberexpert.cpp
	
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/main.o src/main.cpp


#Clean the build directory
clean: 
	rm -f bin/*
