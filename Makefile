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
CMAKE_SOURCE_DIR = /mnt/hgfs/shared/socket

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/shared/socket

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
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/hgfs/shared/socket/CMakeFiles /mnt/hgfs/shared/socket/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/hgfs/shared/socket/CMakeFiles 0
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
# Target rules for targets named scheduler

# Build rule for target.
scheduler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 scheduler
.PHONY : scheduler

# fast build rule for target.
scheduler/fast:
	$(MAKE) -f CMakeFiles/scheduler.dir/build.make CMakeFiles/scheduler.dir/build
.PHONY : scheduler/fast

#=============================================================================
# Target rules for targets named hospitalB

# Build rule for target.
hospitalB: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 hospitalB
.PHONY : hospitalB

# fast build rule for target.
hospitalB/fast:
	$(MAKE) -f CMakeFiles/hospitalB.dir/build.make CMakeFiles/hospitalB.dir/build
.PHONY : hospitalB/fast

#=============================================================================
# Target rules for targets named hospitalA

# Build rule for target.
hospitalA: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 hospitalA
.PHONY : hospitalA

# fast build rule for target.
hospitalA/fast:
	$(MAKE) -f CMakeFiles/hospitalA.dir/build.make CMakeFiles/hospitalA.dir/build
.PHONY : hospitalA/fast

#=============================================================================
# Target rules for targets named hospitalC

# Build rule for target.
hospitalC: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 hospitalC
.PHONY : hospitalC

# fast build rule for target.
hospitalC/fast:
	$(MAKE) -f CMakeFiles/hospitalC.dir/build.make CMakeFiles/hospitalC.dir/build
.PHONY : hospitalC/fast

#=============================================================================
# Target rules for targets named client

# Build rule for target.
client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 client
.PHONY : client

# fast build rule for target.
client/fast:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/build
.PHONY : client/fast

client.o: client.cpp.o

.PHONY : client.o

# target to build an object file
client.cpp.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.cpp.o
.PHONY : client.cpp.o

client.i: client.cpp.i

.PHONY : client.i

# target to preprocess a source file
client.cpp.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.cpp.i
.PHONY : client.cpp.i

client.s: client.cpp.s

.PHONY : client.s

# target to generate assembly for a file
client.cpp.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.cpp.s
.PHONY : client.cpp.s

hospitalA.o: hospitalA.cpp.o

.PHONY : hospitalA.o

# target to build an object file
hospitalA.cpp.o:
	$(MAKE) -f CMakeFiles/hospitalA.dir/build.make CMakeFiles/hospitalA.dir/hospitalA.cpp.o
.PHONY : hospitalA.cpp.o

hospitalA.i: hospitalA.cpp.i

.PHONY : hospitalA.i

# target to preprocess a source file
hospitalA.cpp.i:
	$(MAKE) -f CMakeFiles/hospitalA.dir/build.make CMakeFiles/hospitalA.dir/hospitalA.cpp.i
.PHONY : hospitalA.cpp.i

hospitalA.s: hospitalA.cpp.s

.PHONY : hospitalA.s

# target to generate assembly for a file
hospitalA.cpp.s:
	$(MAKE) -f CMakeFiles/hospitalA.dir/build.make CMakeFiles/hospitalA.dir/hospitalA.cpp.s
.PHONY : hospitalA.cpp.s

hospitalB.o: hospitalB.cpp.o

.PHONY : hospitalB.o

# target to build an object file
hospitalB.cpp.o:
	$(MAKE) -f CMakeFiles/hospitalB.dir/build.make CMakeFiles/hospitalB.dir/hospitalB.cpp.o
.PHONY : hospitalB.cpp.o

hospitalB.i: hospitalB.cpp.i

.PHONY : hospitalB.i

# target to preprocess a source file
hospitalB.cpp.i:
	$(MAKE) -f CMakeFiles/hospitalB.dir/build.make CMakeFiles/hospitalB.dir/hospitalB.cpp.i
.PHONY : hospitalB.cpp.i

hospitalB.s: hospitalB.cpp.s

.PHONY : hospitalB.s

# target to generate assembly for a file
hospitalB.cpp.s:
	$(MAKE) -f CMakeFiles/hospitalB.dir/build.make CMakeFiles/hospitalB.dir/hospitalB.cpp.s
.PHONY : hospitalB.cpp.s

hospitalC.o: hospitalC.cpp.o

.PHONY : hospitalC.o

# target to build an object file
hospitalC.cpp.o:
	$(MAKE) -f CMakeFiles/hospitalC.dir/build.make CMakeFiles/hospitalC.dir/hospitalC.cpp.o
.PHONY : hospitalC.cpp.o

hospitalC.i: hospitalC.cpp.i

.PHONY : hospitalC.i

# target to preprocess a source file
hospitalC.cpp.i:
	$(MAKE) -f CMakeFiles/hospitalC.dir/build.make CMakeFiles/hospitalC.dir/hospitalC.cpp.i
.PHONY : hospitalC.cpp.i

hospitalC.s: hospitalC.cpp.s

.PHONY : hospitalC.s

# target to generate assembly for a file
hospitalC.cpp.s:
	$(MAKE) -f CMakeFiles/hospitalC.dir/build.make CMakeFiles/hospitalC.dir/hospitalC.cpp.s
.PHONY : hospitalC.cpp.s

scheduler.o: scheduler.cpp.o

.PHONY : scheduler.o

# target to build an object file
scheduler.cpp.o:
	$(MAKE) -f CMakeFiles/scheduler.dir/build.make CMakeFiles/scheduler.dir/scheduler.cpp.o
.PHONY : scheduler.cpp.o

scheduler.i: scheduler.cpp.i

.PHONY : scheduler.i

# target to preprocess a source file
scheduler.cpp.i:
	$(MAKE) -f CMakeFiles/scheduler.dir/build.make CMakeFiles/scheduler.dir/scheduler.cpp.i
.PHONY : scheduler.cpp.i

scheduler.s: scheduler.cpp.s

.PHONY : scheduler.s

# target to generate assembly for a file
scheduler.cpp.s:
	$(MAKE) -f CMakeFiles/scheduler.dir/build.make CMakeFiles/scheduler.dir/scheduler.cpp.s
.PHONY : scheduler.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... scheduler"
	@echo "... hospitalB"
	@echo "... edit_cache"
	@echo "... hospitalA"
	@echo "... hospitalC"
	@echo "... client"
	@echo "... client.o"
	@echo "... client.i"
	@echo "... client.s"
	@echo "... hospitalA.o"
	@echo "... hospitalA.i"
	@echo "... hospitalA.s"
	@echo "... hospitalB.o"
	@echo "... hospitalB.i"
	@echo "... hospitalB.s"
	@echo "... hospitalC.o"
	@echo "... hospitalC.i"
	@echo "... hospitalC.s"
	@echo "... scheduler.o"
	@echo "... scheduler.i"
	@echo "... scheduler.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
