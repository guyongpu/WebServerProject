# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/yongpu/SoftWare/clion-2019.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yongpu/SoftWare/clion-2019.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yongpu/wenjian/WebServerProject/WebServer_10.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WebServer_10_0.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WebServer_10_0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WebServer_10_0.dir/flags.make

CMakeFiles/WebServer_10_0.dir/main.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WebServer_10_0.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/main.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/main.cpp

CMakeFiles/WebServer_10_0.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/main.cpp > CMakeFiles/WebServer_10_0.dir/main.cpp.i

CMakeFiles/WebServer_10_0.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/main.cpp -o CMakeFiles/WebServer_10_0.dir/main.cpp.s

CMakeFiles/WebServer_10_0.dir/Util.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/Util.cpp.o: ../Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WebServer_10_0.dir/Util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/Util.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Util.cpp

CMakeFiles/WebServer_10_0.dir/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/Util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Util.cpp > CMakeFiles/WebServer_10_0.dir/Util.cpp.i

CMakeFiles/WebServer_10_0.dir/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/Util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Util.cpp -o CMakeFiles/WebServer_10_0.dir/Util.cpp.s

CMakeFiles/WebServer_10_0.dir/Timer.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/Timer.cpp.o: ../Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/WebServer_10_0.dir/Timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/Timer.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Timer.cpp

CMakeFiles/WebServer_10_0.dir/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Timer.cpp > CMakeFiles/WebServer_10_0.dir/Timer.cpp.i

CMakeFiles/WebServer_10_0.dir/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Timer.cpp -o CMakeFiles/WebServer_10_0.dir/Timer.cpp.s

CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.o: ../ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/ThreadPool.cpp

CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/ThreadPool.cpp > CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.i

CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/ThreadPool.cpp -o CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.s

CMakeFiles/WebServer_10_0.dir/Server.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/Server.cpp.o: ../Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/WebServer_10_0.dir/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/Server.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Server.cpp

CMakeFiles/WebServer_10_0.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Server.cpp > CMakeFiles/WebServer_10_0.dir/Server.cpp.i

CMakeFiles/WebServer_10_0.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Server.cpp -o CMakeFiles/WebServer_10_0.dir/Server.cpp.s

CMakeFiles/WebServer_10_0.dir/HttpData.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/HttpData.cpp.o: ../HttpData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/WebServer_10_0.dir/HttpData.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/HttpData.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/HttpData.cpp

CMakeFiles/WebServer_10_0.dir/HttpData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/HttpData.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/HttpData.cpp > CMakeFiles/WebServer_10_0.dir/HttpData.cpp.i

CMakeFiles/WebServer_10_0.dir/HttpData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/HttpData.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/HttpData.cpp -o CMakeFiles/WebServer_10_0.dir/HttpData.cpp.s

CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.o: ../EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoop.cpp

CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoop.cpp > CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.i

CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoop.cpp -o CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.s

CMakeFiles/WebServer_10_0.dir/Epoll.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/Epoll.cpp.o: ../Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/WebServer_10_0.dir/Epoll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/Epoll.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Epoll.cpp

CMakeFiles/WebServer_10_0.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Epoll.cpp > CMakeFiles/WebServer_10_0.dir/Epoll.cpp.i

CMakeFiles/WebServer_10_0.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Epoll.cpp -o CMakeFiles/WebServer_10_0.dir/Epoll.cpp.s

CMakeFiles/WebServer_10_0.dir/Channel.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/Channel.cpp.o: ../Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/WebServer_10_0.dir/Channel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/Channel.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Channel.cpp

CMakeFiles/WebServer_10_0.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Channel.cpp > CMakeFiles/WebServer_10_0.dir/Channel.cpp.i

CMakeFiles/WebServer_10_0.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/Channel.cpp -o CMakeFiles/WebServer_10_0.dir/Channel.cpp.s

CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.o: ../EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoopThread.cpp

CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoopThread.cpp > CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.i

CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoopThread.cpp -o CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.s

CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.o: CMakeFiles/WebServer_10_0.dir/flags.make
CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.o: ../EventLoopThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.o -c /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoopThreadPool.cpp

CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoopThreadPool.cpp > CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.i

CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yongpu/wenjian/WebServerProject/WebServer_10.0/EventLoopThreadPool.cpp -o CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.s

# Object files for target WebServer_10_0
WebServer_10_0_OBJECTS = \
"CMakeFiles/WebServer_10_0.dir/main.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/Util.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/Timer.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/Server.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/HttpData.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/Epoll.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/Channel.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.o" \
"CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.o"

# External object files for target WebServer_10_0
WebServer_10_0_EXTERNAL_OBJECTS =

WebServer_10_0: CMakeFiles/WebServer_10_0.dir/main.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/Util.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/Timer.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/ThreadPool.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/Server.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/HttpData.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/EventLoop.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/Epoll.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/Channel.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/EventLoopThread.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/EventLoopThreadPool.cpp.o
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/build.make
WebServer_10_0: CMakeFiles/WebServer_10_0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable WebServer_10_0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WebServer_10_0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WebServer_10_0.dir/build: WebServer_10_0

.PHONY : CMakeFiles/WebServer_10_0.dir/build

CMakeFiles/WebServer_10_0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WebServer_10_0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WebServer_10_0.dir/clean

CMakeFiles/WebServer_10_0.dir/depend:
	cd /home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yongpu/wenjian/WebServerProject/WebServer_10.0 /home/yongpu/wenjian/WebServerProject/WebServer_10.0 /home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug /home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug /home/yongpu/wenjian/WebServerProject/WebServer_10.0/cmake-build-debug/CMakeFiles/WebServer_10_0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WebServer_10_0.dir/depend

