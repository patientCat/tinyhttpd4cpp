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
CMAKE_SOURCE_DIR = /home/jmx/project/tinyhttpd4cpp/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmx/project/tinyhttpd4cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/httpd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/httpd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/httpd.dir/flags.make

CMakeFiles/httpd.dir/main.cc.o: CMakeFiles/httpd.dir/flags.make
CMakeFiles/httpd.dir/main.cc.o: /home/jmx/project/tinyhttpd4cpp/src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/httpd.dir/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpd.dir/main.cc.o -c /home/jmx/project/tinyhttpd4cpp/src/main.cc

CMakeFiles/httpd.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpd.dir/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/src/main.cc > CMakeFiles/httpd.dir/main.cc.i

CMakeFiles/httpd.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpd.dir/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/src/main.cc -o CMakeFiles/httpd.dir/main.cc.s

CMakeFiles/httpd.dir/main.cc.o.requires:

.PHONY : CMakeFiles/httpd.dir/main.cc.o.requires

CMakeFiles/httpd.dir/main.cc.o.provides: CMakeFiles/httpd.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/httpd.dir/build.make CMakeFiles/httpd.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/httpd.dir/main.cc.o.provides

CMakeFiles/httpd.dir/main.cc.o.provides.build: CMakeFiles/httpd.dir/main.cc.o


CMakeFiles/httpd.dir/General.cc.o: CMakeFiles/httpd.dir/flags.make
CMakeFiles/httpd.dir/General.cc.o: /home/jmx/project/tinyhttpd4cpp/src/General.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/httpd.dir/General.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpd.dir/General.cc.o -c /home/jmx/project/tinyhttpd4cpp/src/General.cc

CMakeFiles/httpd.dir/General.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpd.dir/General.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/src/General.cc > CMakeFiles/httpd.dir/General.cc.i

CMakeFiles/httpd.dir/General.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpd.dir/General.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/src/General.cc -o CMakeFiles/httpd.dir/General.cc.s

CMakeFiles/httpd.dir/General.cc.o.requires:

.PHONY : CMakeFiles/httpd.dir/General.cc.o.requires

CMakeFiles/httpd.dir/General.cc.o.provides: CMakeFiles/httpd.dir/General.cc.o.requires
	$(MAKE) -f CMakeFiles/httpd.dir/build.make CMakeFiles/httpd.dir/General.cc.o.provides.build
.PHONY : CMakeFiles/httpd.dir/General.cc.o.provides

CMakeFiles/httpd.dir/General.cc.o.provides.build: CMakeFiles/httpd.dir/General.cc.o


CMakeFiles/httpd.dir/ThreadPool.cc.o: CMakeFiles/httpd.dir/flags.make
CMakeFiles/httpd.dir/ThreadPool.cc.o: /home/jmx/project/tinyhttpd4cpp/src/ThreadPool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/httpd.dir/ThreadPool.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpd.dir/ThreadPool.cc.o -c /home/jmx/project/tinyhttpd4cpp/src/ThreadPool.cc

CMakeFiles/httpd.dir/ThreadPool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpd.dir/ThreadPool.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/src/ThreadPool.cc > CMakeFiles/httpd.dir/ThreadPool.cc.i

CMakeFiles/httpd.dir/ThreadPool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpd.dir/ThreadPool.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/src/ThreadPool.cc -o CMakeFiles/httpd.dir/ThreadPool.cc.s

CMakeFiles/httpd.dir/ThreadPool.cc.o.requires:

.PHONY : CMakeFiles/httpd.dir/ThreadPool.cc.o.requires

CMakeFiles/httpd.dir/ThreadPool.cc.o.provides: CMakeFiles/httpd.dir/ThreadPool.cc.o.requires
	$(MAKE) -f CMakeFiles/httpd.dir/build.make CMakeFiles/httpd.dir/ThreadPool.cc.o.provides.build
.PHONY : CMakeFiles/httpd.dir/ThreadPool.cc.o.provides

CMakeFiles/httpd.dir/ThreadPool.cc.o.provides.build: CMakeFiles/httpd.dir/ThreadPool.cc.o


CMakeFiles/httpd.dir/CountDownLatch.cc.o: CMakeFiles/httpd.dir/flags.make
CMakeFiles/httpd.dir/CountDownLatch.cc.o: /home/jmx/project/tinyhttpd4cpp/src/CountDownLatch.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/httpd.dir/CountDownLatch.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpd.dir/CountDownLatch.cc.o -c /home/jmx/project/tinyhttpd4cpp/src/CountDownLatch.cc

CMakeFiles/httpd.dir/CountDownLatch.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpd.dir/CountDownLatch.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/src/CountDownLatch.cc > CMakeFiles/httpd.dir/CountDownLatch.cc.i

CMakeFiles/httpd.dir/CountDownLatch.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpd.dir/CountDownLatch.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/src/CountDownLatch.cc -o CMakeFiles/httpd.dir/CountDownLatch.cc.s

CMakeFiles/httpd.dir/CountDownLatch.cc.o.requires:

.PHONY : CMakeFiles/httpd.dir/CountDownLatch.cc.o.requires

CMakeFiles/httpd.dir/CountDownLatch.cc.o.provides: CMakeFiles/httpd.dir/CountDownLatch.cc.o.requires
	$(MAKE) -f CMakeFiles/httpd.dir/build.make CMakeFiles/httpd.dir/CountDownLatch.cc.o.provides.build
.PHONY : CMakeFiles/httpd.dir/CountDownLatch.cc.o.provides

CMakeFiles/httpd.dir/CountDownLatch.cc.o.provides.build: CMakeFiles/httpd.dir/CountDownLatch.cc.o


CMakeFiles/httpd.dir/Httpd.cc.o: CMakeFiles/httpd.dir/flags.make
CMakeFiles/httpd.dir/Httpd.cc.o: /home/jmx/project/tinyhttpd4cpp/src/Httpd.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/httpd.dir/Httpd.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpd.dir/Httpd.cc.o -c /home/jmx/project/tinyhttpd4cpp/src/Httpd.cc

CMakeFiles/httpd.dir/Httpd.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpd.dir/Httpd.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/src/Httpd.cc > CMakeFiles/httpd.dir/Httpd.cc.i

CMakeFiles/httpd.dir/Httpd.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpd.dir/Httpd.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/src/Httpd.cc -o CMakeFiles/httpd.dir/Httpd.cc.s

CMakeFiles/httpd.dir/Httpd.cc.o.requires:

.PHONY : CMakeFiles/httpd.dir/Httpd.cc.o.requires

CMakeFiles/httpd.dir/Httpd.cc.o.provides: CMakeFiles/httpd.dir/Httpd.cc.o.requires
	$(MAKE) -f CMakeFiles/httpd.dir/build.make CMakeFiles/httpd.dir/Httpd.cc.o.provides.build
.PHONY : CMakeFiles/httpd.dir/Httpd.cc.o.provides

CMakeFiles/httpd.dir/Httpd.cc.o.provides.build: CMakeFiles/httpd.dir/Httpd.cc.o


CMakeFiles/httpd.dir/TcpConnection.cc.o: CMakeFiles/httpd.dir/flags.make
CMakeFiles/httpd.dir/TcpConnection.cc.o: /home/jmx/project/tinyhttpd4cpp/src/TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/httpd.dir/TcpConnection.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpd.dir/TcpConnection.cc.o -c /home/jmx/project/tinyhttpd4cpp/src/TcpConnection.cc

CMakeFiles/httpd.dir/TcpConnection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpd.dir/TcpConnection.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/src/TcpConnection.cc > CMakeFiles/httpd.dir/TcpConnection.cc.i

CMakeFiles/httpd.dir/TcpConnection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpd.dir/TcpConnection.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/src/TcpConnection.cc -o CMakeFiles/httpd.dir/TcpConnection.cc.s

CMakeFiles/httpd.dir/TcpConnection.cc.o.requires:

.PHONY : CMakeFiles/httpd.dir/TcpConnection.cc.o.requires

CMakeFiles/httpd.dir/TcpConnection.cc.o.provides: CMakeFiles/httpd.dir/TcpConnection.cc.o.requires
	$(MAKE) -f CMakeFiles/httpd.dir/build.make CMakeFiles/httpd.dir/TcpConnection.cc.o.provides.build
.PHONY : CMakeFiles/httpd.dir/TcpConnection.cc.o.provides

CMakeFiles/httpd.dir/TcpConnection.cc.o.provides.build: CMakeFiles/httpd.dir/TcpConnection.cc.o


CMakeFiles/httpd.dir/Socket.cc.o: CMakeFiles/httpd.dir/flags.make
CMakeFiles/httpd.dir/Socket.cc.o: /home/jmx/project/tinyhttpd4cpp/src/Socket.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/httpd.dir/Socket.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpd.dir/Socket.cc.o -c /home/jmx/project/tinyhttpd4cpp/src/Socket.cc

CMakeFiles/httpd.dir/Socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpd.dir/Socket.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/tinyhttpd4cpp/src/Socket.cc > CMakeFiles/httpd.dir/Socket.cc.i

CMakeFiles/httpd.dir/Socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpd.dir/Socket.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/tinyhttpd4cpp/src/Socket.cc -o CMakeFiles/httpd.dir/Socket.cc.s

CMakeFiles/httpd.dir/Socket.cc.o.requires:

.PHONY : CMakeFiles/httpd.dir/Socket.cc.o.requires

CMakeFiles/httpd.dir/Socket.cc.o.provides: CMakeFiles/httpd.dir/Socket.cc.o.requires
	$(MAKE) -f CMakeFiles/httpd.dir/build.make CMakeFiles/httpd.dir/Socket.cc.o.provides.build
.PHONY : CMakeFiles/httpd.dir/Socket.cc.o.provides

CMakeFiles/httpd.dir/Socket.cc.o.provides.build: CMakeFiles/httpd.dir/Socket.cc.o


# Object files for target httpd
httpd_OBJECTS = \
"CMakeFiles/httpd.dir/main.cc.o" \
"CMakeFiles/httpd.dir/General.cc.o" \
"CMakeFiles/httpd.dir/ThreadPool.cc.o" \
"CMakeFiles/httpd.dir/CountDownLatch.cc.o" \
"CMakeFiles/httpd.dir/Httpd.cc.o" \
"CMakeFiles/httpd.dir/TcpConnection.cc.o" \
"CMakeFiles/httpd.dir/Socket.cc.o"

# External object files for target httpd
httpd_EXTERNAL_OBJECTS =

/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/main.cc.o
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/General.cc.o
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/ThreadPool.cc.o
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/CountDownLatch.cc.o
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/Httpd.cc.o
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/TcpConnection.cc.o
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/Socket.cc.o
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/build.make
/home/jmx/project/tinyhttpd4cpp/bin/httpd: CMakeFiles/httpd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jmx/project/tinyhttpd4cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable /home/jmx/project/tinyhttpd4cpp/bin/httpd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/httpd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/httpd.dir/build: /home/jmx/project/tinyhttpd4cpp/bin/httpd

.PHONY : CMakeFiles/httpd.dir/build

CMakeFiles/httpd.dir/requires: CMakeFiles/httpd.dir/main.cc.o.requires
CMakeFiles/httpd.dir/requires: CMakeFiles/httpd.dir/General.cc.o.requires
CMakeFiles/httpd.dir/requires: CMakeFiles/httpd.dir/ThreadPool.cc.o.requires
CMakeFiles/httpd.dir/requires: CMakeFiles/httpd.dir/CountDownLatch.cc.o.requires
CMakeFiles/httpd.dir/requires: CMakeFiles/httpd.dir/Httpd.cc.o.requires
CMakeFiles/httpd.dir/requires: CMakeFiles/httpd.dir/TcpConnection.cc.o.requires
CMakeFiles/httpd.dir/requires: CMakeFiles/httpd.dir/Socket.cc.o.requires

.PHONY : CMakeFiles/httpd.dir/requires

CMakeFiles/httpd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/httpd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/httpd.dir/clean

CMakeFiles/httpd.dir/depend:
	cd /home/jmx/project/tinyhttpd4cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmx/project/tinyhttpd4cpp/src /home/jmx/project/tinyhttpd4cpp/src /home/jmx/project/tinyhttpd4cpp/build /home/jmx/project/tinyhttpd4cpp/build /home/jmx/project/tinyhttpd4cpp/build/CMakeFiles/httpd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/httpd.dir/depend

