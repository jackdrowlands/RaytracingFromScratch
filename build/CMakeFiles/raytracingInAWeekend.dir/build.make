# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/jack/raytracingInAWeekend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jack/raytracingInAWeekend/build

# Include any dependencies generated for this target.
include CMakeFiles/raytracingInAWeekend.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raytracingInAWeekend.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raytracingInAWeekend.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raytracingInAWeekend.dir/flags.make

CMakeFiles/raytracingInAWeekend.dir/codegen:
.PHONY : CMakeFiles/raytracingInAWeekend.dir/codegen

CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o: CMakeFiles/raytracingInAWeekend.dir/flags.make
CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o: /home/jack/raytracingInAWeekend/src/main.cpp
CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o: CMakeFiles/raytracingInAWeekend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jack/raytracingInAWeekend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o -MF CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o.d -o CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o -c /home/jack/raytracingInAWeekend/src/main.cpp

CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/raytracingInAWeekend/src/main.cpp > CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.i

CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/raytracingInAWeekend/src/main.cpp -o CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.s

# Object files for target raytracingInAWeekend
raytracingInAWeekend_OBJECTS = \
"CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o"

# External object files for target raytracingInAWeekend
raytracingInAWeekend_EXTERNAL_OBJECTS =

raytracingInAWeekend: CMakeFiles/raytracingInAWeekend.dir/src/main.cpp.o
raytracingInAWeekend: CMakeFiles/raytracingInAWeekend.dir/build.make
raytracingInAWeekend: CMakeFiles/raytracingInAWeekend.dir/compiler_depend.ts
raytracingInAWeekend: CMakeFiles/raytracingInAWeekend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/jack/raytracingInAWeekend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable raytracingInAWeekend"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytracingInAWeekend.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raytracingInAWeekend.dir/build: raytracingInAWeekend
.PHONY : CMakeFiles/raytracingInAWeekend.dir/build

CMakeFiles/raytracingInAWeekend.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raytracingInAWeekend.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raytracingInAWeekend.dir/clean

CMakeFiles/raytracingInAWeekend.dir/depend:
	cd /home/jack/raytracingInAWeekend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jack/raytracingInAWeekend /home/jack/raytracingInAWeekend /home/jack/raytracingInAWeekend/build /home/jack/raytracingInAWeekend/build /home/jack/raytracingInAWeekend/build/CMakeFiles/raytracingInAWeekend.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/raytracingInAWeekend.dir/depend

