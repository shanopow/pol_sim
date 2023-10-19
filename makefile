SRCDIR := src
CLASSLISTDIR := src/classlist
BUILDDIR := build
BINDIR := bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
CLASSLIST_SOURCES := $(wildcard $(CLASSLISTDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
CLASSLIST_OBJECTS := $(patsubst $(CLASSLISTDIR)/%.cpp,$(BUILDDIR)/%.o,$(CLASSLIST_SOURCES))

# Compile the source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(CLASSLISTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the object files into an executable
main: $(OBJECTS) $(CLASSLIST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(BINDIR)/$@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(CLASSLIST_OBJECTS) $(BINDIR)/main
