# Our project ('all') is just to build the executable file 'index'
# This line simply says that 'all' depends on 'index'.
all : index

# 'index' depends on one .o (object) file
# add any new .o files to the list
# build it using g++
index : index.o
	g++ -o index -g index.o

# index.o is dependant on one .cc file and no .h files
# IMPORTANT: when you #include a new .h file, be sure to add it here.
# Otherwise, the 'make' command may not re-build your program even
# though you changed that .h file.
# -Wall: make the compiler display all warnings it knows about;
# hopefully it'll catch something for us
# -c: only compile, don't link (we do that above)
# -g: put in debug information, for those of you who are using
# debuggers (like gdb or ddd or xxgdb)
index.o : index.cc
	g++ -Wall -c -g index.cc

# and same idea for other .o files ...



# 'clean' removes any files that were created via the Makefile,
# leaving you with only your original source code files
clean :
	rm *.o
	rm index