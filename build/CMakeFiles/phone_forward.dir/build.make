# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ja/duze

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ja/duze/build

# Include any dependencies generated for this target.
include CMakeFiles/phone_forward.dir/depend.make

# Include the compile flags for this target's objects.
include CMakeFiles/phone_forward.dir/flags.make

CMakeFiles/phone_forward.dir/src/phone_forward.c.o: CMakeFiles/phone_forward.dir/flags.make
CMakeFiles/phone_forward.dir/src/phone_forward.c.o: ../src/phone_forward.c
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/phone_forward.dir/src/phone_forward.c.o   -c /home/ja/duze/src/phone_forward.c

CMakeFiles/phone_forward.dir/src/phone_forward.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/phone_forward.dir/src/phone_forward.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ja/duze/src/phone_forward.c > CMakeFiles/phone_forward.dir/src/phone_forward.c.i

CMakeFiles/phone_forward.dir/src/phone_forward.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/phone_forward.dir/src/phone_forward.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ja/duze/src/phone_forward.c -o CMakeFiles/phone_forward.dir/src/phone_forward.c.s

CMakeFiles/phone_forward.dir/src/phone_forward_example.c.o: CMakeFiles/phone_forward.dir/flags.make
CMakeFiles/phone_forward.dir/src/phone_forward_example.c.o: ../src/phone_forward_example.c
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/phone_forward.dir/src/phone_forward_example.c.o   -c /home/ja/duze/src/phone_forward_example.c

CMakeFiles/phone_forward.dir/src/phone_forward_example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/phone_forward.dir/src/phone_forward_example.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ja/duze/src/phone_forward_example.c > CMakeFiles/phone_forward.dir/src/phone_forward_example.c.i

CMakeFiles/phone_forward.dir/src/phone_forward_example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/phone_forward.dir/src/phone_forward_example.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ja/duze/src/phone_forward_example.c -o CMakeFiles/phone_forward.dir/src/phone_forward_example.c.s

CMakeFiles/phone_forward.dir/src/vector.c.o: CMakeFiles/phone_forward.dir/flags.make
CMakeFiles/phone_forward.dir/src/vector.c.o: ../src/vector.c
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/phone_forward.dir/src/vector.c.o   -c /home/ja/duze/src/vector.c

CMakeFiles/phone_forward.dir/src/vector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/phone_forward.dir/src/vector.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ja/duze/src/vector.c > CMakeFiles/phone_forward.dir/src/vector.c.i

CMakeFiles/phone_forward.dir/src/vector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/phone_forward.dir/src/vector.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ja/duze/src/vector.c -o CMakeFiles/phone_forward.dir/src/vector.c.s

CMakeFiles/phone_forward.dir/src/strings.c.o: CMakeFiles/phone_forward.dir/flags.make
CMakeFiles/phone_forward.dir/src/strings.c.o: ../src/strings.c
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/phone_forward.dir/src/strings.c.o   -c /home/ja/duze/src/strings.c

CMakeFiles/phone_forward.dir/src/strings.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/phone_forward.dir/src/strings.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ja/duze/src/strings.c > CMakeFiles/phone_forward.dir/src/strings.c.i

CMakeFiles/phone_forward.dir/src/strings.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/phone_forward.dir/src/strings.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ja/duze/src/strings.c -o CMakeFiles/phone_forward.dir/src/strings.c.s

# Object files for target phone_forward
phone_forward_OBJECTS = \
"CMakeFiles/phone_forward.dir/src/phone_forward.c.o" \
"CMakeFiles/phone_forward.dir/src/phone_forward_example.c.o" \
"CMakeFiles/phone_forward.dir/src/vector.c.o" \
"CMakeFiles/phone_forward.dir/src/strings.c.o"

# External object files for target phone_forward
phone_forward_EXTERNAL_OBJECTS =

phone_forward: CMakeFiles/phone_forward.dir/src/phone_forward.c.o
phone_forward: CMakeFiles/phone_forward.dir/src/phone_forward_example.c.o
phone_forward: CMakeFiles/phone_forward.dir/src/vector.c.o
phone_forward: CMakeFiles/phone_forward.dir/src/strings.c.o
phone_forward: CMakeFiles/phone_forward.dir/build.make
phone_forward: CMakeFiles/phone_forward.dir/link.txt
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/phone_forward.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/phone_forward.dir/build: phone_forward

.PHONY : CMakeFiles/phone_forward.dir/build

CMakeFiles/phone_forward.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/phone_forward.dir/cmake_clean.cmake
.PHONY : CMakeFiles/phone_forward.dir/clean

CMakeFiles/phone_forward.dir/depend:
	cd /home/ja/duze/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ja/duze /home/ja/duze /home/ja/duze/build /home/ja/duze/build /home/ja/duze/build/CMakeFiles/phone_forward.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/phone_forward.dir/depend
