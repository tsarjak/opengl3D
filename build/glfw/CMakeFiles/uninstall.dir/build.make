# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build

# Utility rule file for uninstall.

# Include the progress variables for this target.
include glfw/CMakeFiles/uninstall.dir/progress.make

glfw/CMakeFiles/uninstall:
	cd /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build/glfw && /usr/local/Cellar/cmake/3.14.4/bin/cmake -P /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build/glfw/cmake_uninstall.cmake

uninstall: glfw/CMakeFiles/uninstall
uninstall: glfw/CMakeFiles/uninstall.dir/build.make

.PHONY : uninstall

# Rule to build all files generated by this target.
glfw/CMakeFiles/uninstall.dir/build: uninstall

.PHONY : glfw/CMakeFiles/uninstall.dir/build

glfw/CMakeFiles/uninstall.dir/clean:
	cd /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build/glfw && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : glfw/CMakeFiles/uninstall.dir/clean

glfw/CMakeFiles/uninstall.dir/depend:
	cd /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/ext/glfw /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build/glfw /Users/sarjakthakkar/Documents/MacBook/NYU/Lectures/ICG/opengl3D/build/glfw/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw/CMakeFiles/uninstall.dir/depend

