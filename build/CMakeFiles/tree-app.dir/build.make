# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/ansen/Documents/Programming Projects/CS 251/Project 2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/build"

# Include any dependencies generated for this target.
include CMakeFiles/tree-app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tree-app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tree-app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tree-app.dir/flags.make

CMakeFiles/tree-app.dir/src/tree_app.cpp.o: CMakeFiles/tree-app.dir/flags.make
CMakeFiles/tree-app.dir/src/tree_app.cpp.o: /Users/ansen/Documents/Programming\ Projects/CS\ 251/Project\ 2/src/tree_app.cpp
CMakeFiles/tree-app.dir/src/tree_app.cpp.o: CMakeFiles/tree-app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/ansen/Documents/Programming Projects/CS 251/Project 2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tree-app.dir/src/tree_app.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tree-app.dir/src/tree_app.cpp.o -MF CMakeFiles/tree-app.dir/src/tree_app.cpp.o.d -o CMakeFiles/tree-app.dir/src/tree_app.cpp.o -c "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/src/tree_app.cpp"

CMakeFiles/tree-app.dir/src/tree_app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tree-app.dir/src/tree_app.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/src/tree_app.cpp" > CMakeFiles/tree-app.dir/src/tree_app.cpp.i

CMakeFiles/tree-app.dir/src/tree_app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tree-app.dir/src/tree_app.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/src/tree_app.cpp" -o CMakeFiles/tree-app.dir/src/tree_app.cpp.s

# Object files for target tree-app
tree__app_OBJECTS = \
"CMakeFiles/tree-app.dir/src/tree_app.cpp.o"

# External object files for target tree-app
tree__app_EXTERNAL_OBJECTS =

tree-app: CMakeFiles/tree-app.dir/src/tree_app.cpp.o
tree-app: CMakeFiles/tree-app.dir/build.make
tree-app: libproject2.a
tree-app: CMakeFiles/tree-app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/ansen/Documents/Programming Projects/CS 251/Project 2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tree-app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tree-app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tree-app.dir/build: tree-app
.PHONY : CMakeFiles/tree-app.dir/build

CMakeFiles/tree-app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tree-app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tree-app.dir/clean

CMakeFiles/tree-app.dir/depend:
	cd "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/ansen/Documents/Programming Projects/CS 251/Project 2" "/Users/ansen/Documents/Programming Projects/CS 251/Project 2" "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/build" "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/build" "/Users/ansen/Documents/Programming Projects/CS 251/Project 2/build/CMakeFiles/tree-app.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/tree-app.dir/depend
