# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ram-user/ASDR_assignments/src/brightness_pkg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ram-user/ASDR_assignments/build/brightness_pkg

# Include any dependencies generated for this target.
include CMakeFiles/brightness_node.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/brightness_node.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/brightness_node.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/brightness_node.dir/flags.make

CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o: CMakeFiles/brightness_node.dir/flags.make
CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o: /home/ram-user/ASDR_assignments/src/brightness_pkg/src/brightness_node.cpp
CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o: CMakeFiles/brightness_node.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ram-user/ASDR_assignments/build/brightness_pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o -MF CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o.d -o CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o -c /home/ram-user/ASDR_assignments/src/brightness_pkg/src/brightness_node.cpp

CMakeFiles/brightness_node.dir/src/brightness_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/brightness_node.dir/src/brightness_node.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ram-user/ASDR_assignments/src/brightness_pkg/src/brightness_node.cpp > CMakeFiles/brightness_node.dir/src/brightness_node.cpp.i

CMakeFiles/brightness_node.dir/src/brightness_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/brightness_node.dir/src/brightness_node.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ram-user/ASDR_assignments/src/brightness_pkg/src/brightness_node.cpp -o CMakeFiles/brightness_node.dir/src/brightness_node.cpp.s

# Object files for target brightness_node
brightness_node_OBJECTS = \
"CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o"

# External object files for target brightness_node
brightness_node_EXTERNAL_OBJECTS =

brightness_node: CMakeFiles/brightness_node.dir/src/brightness_node.cpp.o
brightness_node: CMakeFiles/brightness_node.dir/build.make
brightness_node: CMakeFiles/brightness_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ram-user/ASDR_assignments/build/brightness_pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable brightness_node"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/brightness_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/brightness_node.dir/build: brightness_node
.PHONY : CMakeFiles/brightness_node.dir/build

CMakeFiles/brightness_node.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/brightness_node.dir/cmake_clean.cmake
.PHONY : CMakeFiles/brightness_node.dir/clean

CMakeFiles/brightness_node.dir/depend:
	cd /home/ram-user/ASDR_assignments/build/brightness_pkg && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ram-user/ASDR_assignments/src/brightness_pkg /home/ram-user/ASDR_assignments/src/brightness_pkg /home/ram-user/ASDR_assignments/build/brightness_pkg /home/ram-user/ASDR_assignments/build/brightness_pkg /home/ram-user/ASDR_assignments/build/brightness_pkg/CMakeFiles/brightness_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/brightness_node.dir/depend

