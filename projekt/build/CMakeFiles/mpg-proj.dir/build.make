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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hedweger/Vut/mgr-second/mpg/projekt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hedweger/Vut/mgr-second/mpg/projekt/build

# Include any dependencies generated for this target.
include CMakeFiles/mpg-proj.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mpg-proj.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mpg-proj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mpg-proj.dir/flags.make

CMakeFiles/mpg-proj.dir/codegen:
.PHONY : CMakeFiles/mpg-proj.dir/codegen

CMakeFiles/mpg-proj.dir/main.cpp.o: CMakeFiles/mpg-proj.dir/flags.make
CMakeFiles/mpg-proj.dir/main.cpp.o: /Users/hedweger/Vut/mgr-second/mpg/projekt/main.cpp
CMakeFiles/mpg-proj.dir/main.cpp.o: CMakeFiles/mpg-proj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hedweger/Vut/mgr-second/mpg/projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mpg-proj.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mpg-proj.dir/main.cpp.o -MF CMakeFiles/mpg-proj.dir/main.cpp.o.d -o CMakeFiles/mpg-proj.dir/main.cpp.o -c /Users/hedweger/Vut/mgr-second/mpg/projekt/main.cpp

CMakeFiles/mpg-proj.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mpg-proj.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hedweger/Vut/mgr-second/mpg/projekt/main.cpp > CMakeFiles/mpg-proj.dir/main.cpp.i

CMakeFiles/mpg-proj.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mpg-proj.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hedweger/Vut/mgr-second/mpg/projekt/main.cpp -o CMakeFiles/mpg-proj.dir/main.cpp.s

CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o: CMakeFiles/mpg-proj.dir/flags.make
CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o: /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/draw.cpp
CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o: CMakeFiles/mpg-proj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hedweger/Vut/mgr-second/mpg/projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o -MF CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o.d -o CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o -c /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/draw.cpp

CMakeFiles/mpg-proj.dir/include/src/draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mpg-proj.dir/include/src/draw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/draw.cpp > CMakeFiles/mpg-proj.dir/include/src/draw.cpp.i

CMakeFiles/mpg-proj.dir/include/src/draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mpg-proj.dir/include/src/draw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/draw.cpp -o CMakeFiles/mpg-proj.dir/include/src/draw.cpp.s

CMakeFiles/mpg-proj.dir/include/src/input.cpp.o: CMakeFiles/mpg-proj.dir/flags.make
CMakeFiles/mpg-proj.dir/include/src/input.cpp.o: /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/input.cpp
CMakeFiles/mpg-proj.dir/include/src/input.cpp.o: CMakeFiles/mpg-proj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hedweger/Vut/mgr-second/mpg/projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mpg-proj.dir/include/src/input.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mpg-proj.dir/include/src/input.cpp.o -MF CMakeFiles/mpg-proj.dir/include/src/input.cpp.o.d -o CMakeFiles/mpg-proj.dir/include/src/input.cpp.o -c /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/input.cpp

CMakeFiles/mpg-proj.dir/include/src/input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mpg-proj.dir/include/src/input.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/input.cpp > CMakeFiles/mpg-proj.dir/include/src/input.cpp.i

CMakeFiles/mpg-proj.dir/include/src/input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mpg-proj.dir/include/src/input.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/input.cpp -o CMakeFiles/mpg-proj.dir/include/src/input.cpp.s

CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o: CMakeFiles/mpg-proj.dir/flags.make
CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o: /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/bezier.cpp
CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o: CMakeFiles/mpg-proj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hedweger/Vut/mgr-second/mpg/projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o -MF CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o.d -o CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o -c /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/bezier.cpp

CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/bezier.cpp > CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.i

CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hedweger/Vut/mgr-second/mpg/projekt/include/src/bezier.cpp -o CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.s

# Object files for target mpg-proj
mpg__proj_OBJECTS = \
"CMakeFiles/mpg-proj.dir/main.cpp.o" \
"CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o" \
"CMakeFiles/mpg-proj.dir/include/src/input.cpp.o" \
"CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o"

# External object files for target mpg-proj
mpg__proj_EXTERNAL_OBJECTS =

mpg-proj: CMakeFiles/mpg-proj.dir/main.cpp.o
mpg-proj: CMakeFiles/mpg-proj.dir/include/src/draw.cpp.o
mpg-proj: CMakeFiles/mpg-proj.dir/include/src/input.cpp.o
mpg-proj: CMakeFiles/mpg-proj.dir/include/src/bezier.cpp.o
mpg-proj: CMakeFiles/mpg-proj.dir/build.make
mpg-proj: CMakeFiles/mpg-proj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/hedweger/Vut/mgr-second/mpg/projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable mpg-proj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpg-proj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mpg-proj.dir/build: mpg-proj
.PHONY : CMakeFiles/mpg-proj.dir/build

CMakeFiles/mpg-proj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mpg-proj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mpg-proj.dir/clean

CMakeFiles/mpg-proj.dir/depend:
	cd /Users/hedweger/Vut/mgr-second/mpg/projekt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hedweger/Vut/mgr-second/mpg/projekt /Users/hedweger/Vut/mgr-second/mpg/projekt /Users/hedweger/Vut/mgr-second/mpg/projekt/build /Users/hedweger/Vut/mgr-second/mpg/projekt/build /Users/hedweger/Vut/mgr-second/mpg/projekt/build/CMakeFiles/mpg-proj.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/mpg-proj.dir/depend

