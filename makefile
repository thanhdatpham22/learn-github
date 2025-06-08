# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -IApp/Inc -std=c++11 -pthread

# Directories
SRCDIR := App/Src
INCDIR := App/Inc
BINDIR := bin

# Source and object files
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o, $(SRCFILES))
TARGET := $(BINDIR)/Main.exe

# Rules
all: $(TARGET)
	@echo "Build successful! Running the program..."
	./$(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJFILES)
	@echo "Linking: $@"
	$(CXX) $(OBJFILES) -o $@

# Compile source files to object files
$(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
	@echo "Compiling: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin directory if not exists
$(BINDIR):
	@if not exist $(BINDIR) mkdir $(BINDIR)

# Clean up build files (Windows co	mpatible)
clean:
	@echo "Cleaning up..."
	@rm -f $(BINDIR)/*.o
	@rm -f $(BINDIR)/*.exe

.PHONY: all clean
