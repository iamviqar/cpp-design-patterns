# Simple Makefile for C++ Design Patterns
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -I./src
SRCDIR = src
DEMODIR = demos
BUILDDIR = build

# Source files
CREATIONAL_SOURCES = $(wildcard $(SRCDIR)/creational/*/*.cpp)
STRUCTURAL_SOURCES = $(wildcard $(SRCDIR)/structural/*/*.cpp)
BEHAVIORAL_SOURCES = $(wildcard $(SRCDIR)/behavioral/*/*.cpp)

ALL_SOURCES = $(CREATIONAL_SOURCES) $(STRUCTURAL_SOURCES) $(BEHAVIORAL_SOURCES)

# Object files
OBJECTS = $(ALL_SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Demo executable
DEMO_TARGET = $(BUILDDIR)/design_patterns_demo
DEMO_SOURCE = $(DEMODIR)/all_patterns_demo.cpp

# Default target
all: $(DEMO_TARGET)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/creational/singleton
	mkdir -p $(BUILDDIR)/creational/factory-method
	mkdir -p $(BUILDDIR)/creational/abstract-factory
	mkdir -p $(BUILDDIR)/creational/builder
	mkdir -p $(BUILDDIR)/creational/prototype
	mkdir -p $(BUILDDIR)/structural/adapter
	mkdir -p $(BUILDDIR)/structural/bridge
	mkdir -p $(BUILDDIR)/behavioral

# Compile object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link demo executable
$(DEMO_TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(DEMO_SOURCE) -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILDDIR)

# Run demo
run: $(DEMO_TARGET)
	./$(DEMO_TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all    - Build the demo executable"
	@echo "  clean  - Remove build artifacts"
	@echo "  run    - Build and run the demo"
	@echo "  help   - Show this help message"

.PHONY: all clean run help
