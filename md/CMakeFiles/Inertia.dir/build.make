# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/derros/Projects/Inertia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/derros/Projects/Inertia/md

# Include any dependencies generated for this target.
include CMakeFiles/Inertia.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Inertia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Inertia.dir/flags.make

CMakeFiles/Inertia.dir/src/main.c.o: CMakeFiles/Inertia.dir/flags.make
CMakeFiles/Inertia.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/derros/Projects/Inertia/md/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Inertia.dir/src/main.c.o"
	/usr/local/bin/x86_64-apple-darwin15.6.0-gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Inertia.dir/src/main.c.o   -c /Users/derros/Projects/Inertia/src/main.c

CMakeFiles/Inertia.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Inertia.dir/src/main.c.i"
	/usr/local/bin/x86_64-apple-darwin15.6.0-gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/derros/Projects/Inertia/src/main.c > CMakeFiles/Inertia.dir/src/main.c.i

CMakeFiles/Inertia.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Inertia.dir/src/main.c.s"
	/usr/local/bin/x86_64-apple-darwin15.6.0-gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/derros/Projects/Inertia/src/main.c -o CMakeFiles/Inertia.dir/src/main.c.s

CMakeFiles/Inertia.dir/src/main.c.o.requires:

.PHONY : CMakeFiles/Inertia.dir/src/main.c.o.requires

CMakeFiles/Inertia.dir/src/main.c.o.provides: CMakeFiles/Inertia.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/Inertia.dir/build.make CMakeFiles/Inertia.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/Inertia.dir/src/main.c.o.provides

CMakeFiles/Inertia.dir/src/main.c.o.provides.build: CMakeFiles/Inertia.dir/src/main.c.o


# Object files for target Inertia
Inertia_OBJECTS = \
"CMakeFiles/Inertia.dir/src/main.c.o"

# External object files for target Inertia
Inertia_EXTERNAL_OBJECTS =

Inertia: CMakeFiles/Inertia.dir/src/main.c.o
Inertia: CMakeFiles/Inertia.dir/build.make
Inertia: CMakeFiles/Inertia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/derros/Projects/Inertia/md/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Inertia"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Inertia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Inertia.dir/build: Inertia

.PHONY : CMakeFiles/Inertia.dir/build

CMakeFiles/Inertia.dir/requires: CMakeFiles/Inertia.dir/src/main.c.o.requires

.PHONY : CMakeFiles/Inertia.dir/requires

CMakeFiles/Inertia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Inertia.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Inertia.dir/clean

CMakeFiles/Inertia.dir/depend:
	cd /Users/derros/Projects/Inertia/md && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/derros/Projects/Inertia /Users/derros/Projects/Inertia /Users/derros/Projects/Inertia/md /Users/derros/Projects/Inertia/md /Users/derros/Projects/Inertia/md/CMakeFiles/Inertia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Inertia.dir/depend

