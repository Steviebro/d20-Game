# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mateb/Desktop/345Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mateb/Desktop/345Project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/345Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/345Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/345Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/345Project.dir/flags.make

CMakeFiles/345Project.dir/src/main.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/main.cpp.o: /Users/mateb/Desktop/345Project/src/main.cpp
CMakeFiles/345Project.dir/src/main.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/345Project.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/main.cpp.o -MF CMakeFiles/345Project.dir/src/main.cpp.o.d -o CMakeFiles/345Project.dir/src/main.cpp.o -c /Users/mateb/Desktop/345Project/src/main.cpp

CMakeFiles/345Project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/main.cpp > CMakeFiles/345Project.dir/src/main.cpp.i

CMakeFiles/345Project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/main.cpp -o CMakeFiles/345Project.dir/src/main.cpp.s

CMakeFiles/345Project.dir/src/Static/Functions.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Static/Functions.cpp.o: /Users/mateb/Desktop/345Project/src/Static/Functions.cpp
CMakeFiles/345Project.dir/src/Static/Functions.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/345Project.dir/src/Static/Functions.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Static/Functions.cpp.o -MF CMakeFiles/345Project.dir/src/Static/Functions.cpp.o.d -o CMakeFiles/345Project.dir/src/Static/Functions.cpp.o -c /Users/mateb/Desktop/345Project/src/Static/Functions.cpp

CMakeFiles/345Project.dir/src/Static/Functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Static/Functions.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Static/Functions.cpp > CMakeFiles/345Project.dir/src/Static/Functions.cpp.i

CMakeFiles/345Project.dir/src/Static/Functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Static/Functions.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Static/Functions.cpp -o CMakeFiles/345Project.dir/src/Static/Functions.cpp.s

CMakeFiles/345Project.dir/src/Static/Dice.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Static/Dice.cpp.o: /Users/mateb/Desktop/345Project/src/Static/Dice.cpp
CMakeFiles/345Project.dir/src/Static/Dice.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/345Project.dir/src/Static/Dice.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Static/Dice.cpp.o -MF CMakeFiles/345Project.dir/src/Static/Dice.cpp.o.d -o CMakeFiles/345Project.dir/src/Static/Dice.cpp.o -c /Users/mateb/Desktop/345Project/src/Static/Dice.cpp

CMakeFiles/345Project.dir/src/Static/Dice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Static/Dice.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Static/Dice.cpp > CMakeFiles/345Project.dir/src/Static/Dice.cpp.i

CMakeFiles/345Project.dir/src/Static/Dice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Static/Dice.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Static/Dice.cpp -o CMakeFiles/345Project.dir/src/Static/Dice.cpp.s

CMakeFiles/345Project.dir/src/Components/Character.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Components/Character.cpp.o: /Users/mateb/Desktop/345Project/src/Components/Character.cpp
CMakeFiles/345Project.dir/src/Components/Character.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/345Project.dir/src/Components/Character.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Components/Character.cpp.o -MF CMakeFiles/345Project.dir/src/Components/Character.cpp.o.d -o CMakeFiles/345Project.dir/src/Components/Character.cpp.o -c /Users/mateb/Desktop/345Project/src/Components/Character.cpp

CMakeFiles/345Project.dir/src/Components/Character.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Components/Character.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Components/Character.cpp > CMakeFiles/345Project.dir/src/Components/Character.cpp.i

CMakeFiles/345Project.dir/src/Components/Character.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Components/Character.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Components/Character.cpp -o CMakeFiles/345Project.dir/src/Components/Character.cpp.s

CMakeFiles/345Project.dir/src/Components/Item.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Components/Item.cpp.o: /Users/mateb/Desktop/345Project/src/Components/Item.cpp
CMakeFiles/345Project.dir/src/Components/Item.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/345Project.dir/src/Components/Item.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Components/Item.cpp.o -MF CMakeFiles/345Project.dir/src/Components/Item.cpp.o.d -o CMakeFiles/345Project.dir/src/Components/Item.cpp.o -c /Users/mateb/Desktop/345Project/src/Components/Item.cpp

CMakeFiles/345Project.dir/src/Components/Item.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Components/Item.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Components/Item.cpp > CMakeFiles/345Project.dir/src/Components/Item.cpp.i

CMakeFiles/345Project.dir/src/Components/Item.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Components/Item.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Components/Item.cpp -o CMakeFiles/345Project.dir/src/Components/Item.cpp.s

CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o: /Users/mateb/Desktop/345Project/src/Components/Weapon.cpp
CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o -MF CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o.d -o CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o -c /Users/mateb/Desktop/345Project/src/Components/Weapon.cpp

CMakeFiles/345Project.dir/src/Components/Weapon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Components/Weapon.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Components/Weapon.cpp > CMakeFiles/345Project.dir/src/Components/Weapon.cpp.i

CMakeFiles/345Project.dir/src/Components/Weapon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Components/Weapon.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Components/Weapon.cpp -o CMakeFiles/345Project.dir/src/Components/Weapon.cpp.s

CMakeFiles/345Project.dir/src/Components/Armor.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Components/Armor.cpp.o: /Users/mateb/Desktop/345Project/src/Components/Armor.cpp
CMakeFiles/345Project.dir/src/Components/Armor.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/345Project.dir/src/Components/Armor.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Components/Armor.cpp.o -MF CMakeFiles/345Project.dir/src/Components/Armor.cpp.o.d -o CMakeFiles/345Project.dir/src/Components/Armor.cpp.o -c /Users/mateb/Desktop/345Project/src/Components/Armor.cpp

CMakeFiles/345Project.dir/src/Components/Armor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Components/Armor.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Components/Armor.cpp > CMakeFiles/345Project.dir/src/Components/Armor.cpp.i

CMakeFiles/345Project.dir/src/Components/Armor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Components/Armor.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Components/Armor.cpp -o CMakeFiles/345Project.dir/src/Components/Armor.cpp.s

CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o: /Users/mateb/Desktop/345Project/src/Components/ItemBag.cpp
CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o -MF CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o.d -o CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o -c /Users/mateb/Desktop/345Project/src/Components/ItemBag.cpp

CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Components/ItemBag.cpp > CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.i

CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Components/ItemBag.cpp -o CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.s

CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o: CMakeFiles/345Project.dir/flags.make
CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o: /Users/mateb/Desktop/345Project/src/Components/Equipment.cpp
CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o: CMakeFiles/345Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o -MF CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o.d -o CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o -c /Users/mateb/Desktop/345Project/src/Components/Equipment.cpp

CMakeFiles/345Project.dir/src/Components/Equipment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/345Project.dir/src/Components/Equipment.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mateb/Desktop/345Project/src/Components/Equipment.cpp > CMakeFiles/345Project.dir/src/Components/Equipment.cpp.i

CMakeFiles/345Project.dir/src/Components/Equipment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/345Project.dir/src/Components/Equipment.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mateb/Desktop/345Project/src/Components/Equipment.cpp -o CMakeFiles/345Project.dir/src/Components/Equipment.cpp.s

# Object files for target 345Project
345Project_OBJECTS = \
"CMakeFiles/345Project.dir/src/main.cpp.o" \
"CMakeFiles/345Project.dir/src/Static/Functions.cpp.o" \
"CMakeFiles/345Project.dir/src/Static/Dice.cpp.o" \
"CMakeFiles/345Project.dir/src/Components/Character.cpp.o" \
"CMakeFiles/345Project.dir/src/Components/Item.cpp.o" \
"CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o" \
"CMakeFiles/345Project.dir/src/Components/Armor.cpp.o" \
"CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o" \
"CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o"

# External object files for target 345Project
345Project_EXTERNAL_OBJECTS =

345Project: CMakeFiles/345Project.dir/src/main.cpp.o
345Project: CMakeFiles/345Project.dir/src/Static/Functions.cpp.o
345Project: CMakeFiles/345Project.dir/src/Static/Dice.cpp.o
345Project: CMakeFiles/345Project.dir/src/Components/Character.cpp.o
345Project: CMakeFiles/345Project.dir/src/Components/Item.cpp.o
345Project: CMakeFiles/345Project.dir/src/Components/Weapon.cpp.o
345Project: CMakeFiles/345Project.dir/src/Components/Armor.cpp.o
345Project: CMakeFiles/345Project.dir/src/Components/ItemBag.cpp.o
345Project: CMakeFiles/345Project.dir/src/Components/Equipment.cpp.o
345Project: CMakeFiles/345Project.dir/build.make
345Project: CMakeFiles/345Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable 345Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/345Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/345Project.dir/build: 345Project
.PHONY : CMakeFiles/345Project.dir/build

CMakeFiles/345Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/345Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/345Project.dir/clean

CMakeFiles/345Project.dir/depend:
	cd /Users/mateb/Desktop/345Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mateb/Desktop/345Project /Users/mateb/Desktop/345Project /Users/mateb/Desktop/345Project/cmake-build-debug /Users/mateb/Desktop/345Project/cmake-build-debug /Users/mateb/Desktop/345Project/cmake-build-debug/CMakeFiles/345Project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/345Project.dir/depend

