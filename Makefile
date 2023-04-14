CC = clang++
SRCPATH = src
OBJPATH = objects
HEADERS = includes
CXXFLAGS = -g -MMD -Iheaders -std=c++20
LIBFLAGS = -lglfw -lGL -lGLU
#-lGLU -lm
SOURCES = $(filter-out $(SRCPATH)/main.cpp $(SRCPATH)/treetest.cpp, $(wildcard $(SRCPATH)/*.cpp))
OBJ = ${subst $(SRCPATH),$(OBJPATH),$(SOURCES:.cpp=.o)}
DEPENDS = $(SOURCES:.cpp=.d)

main : $(OBJPATH)/main.o $(OBJ)
	$(CC) $^ -o $@ $(CXXFLAGS) $(LIBFLAGS)

$(OBJPATH)/main.o : $(SRCPATH)/main.cpp
	mkdir -p $(OBJPATH)
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS) -o $@

treetest : $(OBJPATH)/treetest.o $(OBJ)
	$(CC) $^ -o $@ $(CXXFLAGS) $(LIBFLAGS)

$(OBJPATH)/treetest.o : $(SRCPATH)/treetest.cpp
	mkdir -p $(OBJPATH)
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS) -o $@

$(OBJPATH)/%.o : $(SRCPATH)/%.cpp $(HEADERS)/%.h
	mkdir -p $(OBJPATH)
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS) -o $@

-include $(DEPENDS)

clean :
	rm $(OBJPATH)/*
