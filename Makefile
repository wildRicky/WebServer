# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/ubantu/WebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubantu/WebServer

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ubantu/WebServer/CMakeFiles /home/ubantu/WebServer/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ubantu/WebServer/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named webserver

# Build rule for target.
webserver: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 webserver
.PHONY : webserver

# fast build rule for target.
webserver/fast:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/build
.PHONY : webserver/fast

Epoll.o: Epoll.cpp.o

.PHONY : Epoll.o

# target to build an object file
Epoll.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Epoll.cpp.o
.PHONY : Epoll.cpp.o

Epoll.i: Epoll.cpp.i

.PHONY : Epoll.i

# target to preprocess a source file
Epoll.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Epoll.cpp.i
.PHONY : Epoll.cpp.i

Epoll.s: Epoll.cpp.s

.PHONY : Epoll.s

# target to generate assembly for a file
Epoll.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Epoll.cpp.s
.PHONY : Epoll.cpp.s

HttpData.o: HttpData.cpp.o

.PHONY : HttpData.o

# target to build an object file
HttpData.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpData.cpp.o
.PHONY : HttpData.cpp.o

HttpData.i: HttpData.cpp.i

.PHONY : HttpData.i

# target to preprocess a source file
HttpData.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpData.cpp.i
.PHONY : HttpData.cpp.i

HttpData.s: HttpData.cpp.s

.PHONY : HttpData.s

# target to generate assembly for a file
HttpData.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpData.cpp.s
.PHONY : HttpData.cpp.s

HttpRequest.o: HttpRequest.cpp.o

.PHONY : HttpRequest.o

# target to build an object file
HttpRequest.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpRequest.cpp.o
.PHONY : HttpRequest.cpp.o

HttpRequest.i: HttpRequest.cpp.i

.PHONY : HttpRequest.i

# target to preprocess a source file
HttpRequest.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpRequest.cpp.i
.PHONY : HttpRequest.cpp.i

HttpRequest.s: HttpRequest.cpp.s

.PHONY : HttpRequest.s

# target to generate assembly for a file
HttpRequest.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpRequest.cpp.s
.PHONY : HttpRequest.cpp.s

HttpResponse.o: HttpResponse.cpp.o

.PHONY : HttpResponse.o

# target to build an object file
HttpResponse.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpResponse.cpp.o
.PHONY : HttpResponse.cpp.o

HttpResponse.i: HttpResponse.cpp.i

.PHONY : HttpResponse.i

# target to preprocess a source file
HttpResponse.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpResponse.cpp.i
.PHONY : HttpResponse.cpp.i

HttpResponse.s: HttpResponse.cpp.s

.PHONY : HttpResponse.s

# target to generate assembly for a file
HttpResponse.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/HttpResponse.cpp.s
.PHONY : HttpResponse.cpp.s

Server.o: Server.cpp.o

.PHONY : Server.o

# target to build an object file
Server.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Server.cpp.o
.PHONY : Server.cpp.o

Server.i: Server.cpp.i

.PHONY : Server.i

# target to preprocess a source file
Server.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Server.cpp.i
.PHONY : Server.cpp.i

Server.s: Server.cpp.s

.PHONY : Server.s

# target to generate assembly for a file
Server.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Server.cpp.s
.PHONY : Server.cpp.s

Socket.o: Socket.cpp.o

.PHONY : Socket.o

# target to build an object file
Socket.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Socket.cpp.o
.PHONY : Socket.cpp.o

Socket.i: Socket.cpp.i

.PHONY : Socket.i

# target to preprocess a source file
Socket.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Socket.cpp.i
.PHONY : Socket.cpp.i

Socket.s: Socket.cpp.s

.PHONY : Socket.s

# target to generate assembly for a file
Socket.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Socket.cpp.s
.PHONY : Socket.cpp.s

ThreadPool.o: ThreadPool.cpp.o

.PHONY : ThreadPool.o

# target to build an object file
ThreadPool.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/ThreadPool.cpp.o
.PHONY : ThreadPool.cpp.o

ThreadPool.i: ThreadPool.cpp.i

.PHONY : ThreadPool.i

# target to preprocess a source file
ThreadPool.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/ThreadPool.cpp.i
.PHONY : ThreadPool.cpp.i

ThreadPool.s: ThreadPool.cpp.s

.PHONY : ThreadPool.s

# target to generate assembly for a file
ThreadPool.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/ThreadPool.cpp.s
.PHONY : ThreadPool.cpp.s

Timer.o: Timer.cpp.o

.PHONY : Timer.o

# target to build an object file
Timer.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Timer.cpp.o
.PHONY : Timer.cpp.o

Timer.i: Timer.cpp.i

.PHONY : Timer.i

# target to preprocess a source file
Timer.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Timer.cpp.i
.PHONY : Timer.cpp.i

Timer.s: Timer.cpp.s

.PHONY : Timer.s

# target to generate assembly for a file
Timer.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/Timer.cpp.s
.PHONY : Timer.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/webserver.dir/build.make CMakeFiles/webserver.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... webserver"
	@echo "... Epoll.o"
	@echo "... Epoll.i"
	@echo "... Epoll.s"
	@echo "... HttpData.o"
	@echo "... HttpData.i"
	@echo "... HttpData.s"
	@echo "... HttpRequest.o"
	@echo "... HttpRequest.i"
	@echo "... HttpRequest.s"
	@echo "... HttpResponse.o"
	@echo "... HttpResponse.i"
	@echo "... HttpResponse.s"
	@echo "... Server.o"
	@echo "... Server.i"
	@echo "... Server.s"
	@echo "... Socket.o"
	@echo "... Socket.i"
	@echo "... Socket.s"
	@echo "... ThreadPool.o"
	@echo "... ThreadPool.i"
	@echo "... ThreadPool.s"
	@echo "... Timer.o"
	@echo "... Timer.i"
	@echo "... Timer.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

