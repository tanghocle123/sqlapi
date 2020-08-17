### find and replace temp with your name of library
src = main.cpp temp.cpp
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d) 

INSTALL_DIR = /usr/local/bin
OUTPUTFILE = final.o
CXXFLAGS=  -O2 -g -std=c++14 -I/usr/local/lib/SQLAPI/include # Flags option used for compiling C++ files
LIBS= 
LDFLAGS =  -lsqlite3 -L/usr/local/lib/SQLAPI/lib -lsqlapi -ldl
# Compiler Options
CC       = g++ # compiler used for compiling C files 
CXX      = g++   # compiler used for compiling C++ files

$(OUTPUTFILE): $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Generate dependencies of .cpp files 
-include $(dep)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@
	
.PHONY: clean
clean:
	rm -f $(obj) $(OUTPUTFILE)
.PHONY: cleandep
cleandep:
	rm -f $(dep)
	
.PHONY: run
run:
	./$(OUTPUTFILE)
	
.PHONY: install
install:
	sudo cp $(OUTPUTFILE) $(INSTALL_DIR) 
	
