# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jmx/project/tinyhttpd4cpp/httpd_ver4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build

# Include any dependencies generated for this target.
include test/simple/CMakeFiles/echoServer.dir/depend.make

# Include the progress variables for this target.
include test/simple/CMakeFiles/echoServer.dir/progress.make

# Include the compile flags for this target's objects.
include test/simple/CMakeFiles/echoServer.dir/flags.make

test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o: test/simple/CMakeFiles/echoServer.dir/flags.make
test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o: ../test/simple/echoServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o"
	cd /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/test/simple && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echoServer.dir/echoServer.cc.o -c /home/jmx/project/tinyhttpd4cpp/httpd_ver4/test/simple/echoServer.cc

test/simple/CMakeFiles/echoServer.dir/echoServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echoServer.dir/echoServer.cc.i"
	cd /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/test/simple && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/httpd_ver4/test/simple/echoServer.cc > CMakeFiles/echoServer.dir/echoServer.cc.i

test/simple/CMakeFiles/echoServer.dir/echoServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echoServer.dir/echoServer.cc.s"
	cd /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/test/simple && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/httpd_ver4/test/simple/echoServer.cc -o CMakeFiles/echoServer.dir/echoServer.cc.s

test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.requires:

.PHONY : test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.requires

test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.provides: test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.requires
	$(MAKE) -f test/simple/CMakeFiles/echoServer.dir/build.make test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.provides.build
.PHONY : test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.provides

test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.provides.build: test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o


# Object files for target echoServer
echoServer_OBJECTS = \
"CMakeFiles/echoServer.dir/echoServer.cc.o"

# External object files for target echoServer
echoServer_EXTERNAL_OBJECTS =

test/bin/echoServer: test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o
test/bin/echoServer: test/simple/CMakeFiles/echoServer.dir/build.make
test/bin/echoServer: ../lib/libsingsing_net.a
test/bin/echoServer: ../lib/libsingsing_base.a
test/bin/echoServer: test/simple/CMakeFiles/echoServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/echoServer"
	cd /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/test/simple && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echoServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/simple/CMakeFiles/echoServer.dir/build: test/bin/echoServer

.PHONY : test/simple/CMakeFiles/echoServer.dir/build

test/simple/CMakeFiles/echoServer.dir/requires: test/simple/CMakeFiles/echoServer.dir/echoServer.cc.o.requires

.PHONY : test/simple/CMakeFiles/echoServer.dir/requires

test/simple/CMakeFiles/echoServer.dir/clean:
	cd /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/test/simple && $(CMAKE_COMMAND) -P CMakeFiles/echoServer.dir/cmake_clean.cmake
.PHONY : test/simple/CMakeFiles/echoServer.dir/clean

test/simple/CMakeFiles/echoServer.dir/depend:
	cd /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmx/project/tinyhttpd4cpp/httpd_ver4 /home/jmx/project/tinyhttpd4cpp/httpd_ver4/test/simple /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/test/simple /home/jmx/project/tinyhttpd4cpp/httpd_ver4/build/test/simple/CMakeFiles/echoServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/simple/CMakeFiles/echoServer.dir/depend

