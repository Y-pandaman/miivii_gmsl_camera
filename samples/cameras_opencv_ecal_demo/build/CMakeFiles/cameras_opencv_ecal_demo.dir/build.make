# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/build

# Include any dependencies generated for this target.
include CMakeFiles/cameras_opencv_ecal_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cameras_opencv_ecal_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cameras_opencv_ecal_demo.dir/flags.make

CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o: CMakeFiles/cameras_opencv_ecal_demo.dir/flags.make
CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o: ../src/cameras_opencv_ecal_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o -c /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/src/cameras_opencv_ecal_demo.cpp

CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/src/cameras_opencv_ecal_demo.cpp > CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.i

CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/src/cameras_opencv_ecal_demo.cpp -o CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.s

CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.requires:

.PHONY : CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.requires

CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.provides: CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/cameras_opencv_ecal_demo.dir/build.make CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.provides.build
.PHONY : CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.provides

CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.provides.build: CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o


# Object files for target cameras_opencv_ecal_demo
cameras_opencv_ecal_demo_OBJECTS = \
"CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o"

# External object files for target cameras_opencv_ecal_demo
cameras_opencv_ecal_demo_EXTERNAL_OBJECTS =

cameras_opencv_ecal_demo: CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o
cameras_opencv_ecal_demo: CMakeFiles/cameras_opencv_ecal_demo.dir/build.make
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_dnn.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_gapi.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_ml.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_objdetect.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_photo.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_stitching.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_video.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_videoio.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libecal_core.so.5.10.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libprotobuf.so
cameras_opencv_ecal_demo: libcameras_opencv_ecal_demo_lib.a
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_calib3d.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_features2d.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_flann.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libopencv_core.so.4.1.1
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libecal_proto.a
cameras_opencv_ecal_demo: /usr/lib/aarch64-linux-gnu/libprotobuf.so
cameras_opencv_ecal_demo: CMakeFiles/cameras_opencv_ecal_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cameras_opencv_ecal_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cameras_opencv_ecal_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cameras_opencv_ecal_demo.dir/build: cameras_opencv_ecal_demo

.PHONY : CMakeFiles/cameras_opencv_ecal_demo.dir/build

CMakeFiles/cameras_opencv_ecal_demo.dir/requires: CMakeFiles/cameras_opencv_ecal_demo.dir/src/cameras_opencv_ecal_demo.cpp.o.requires

.PHONY : CMakeFiles/cameras_opencv_ecal_demo.dir/requires

CMakeFiles/cameras_opencv_ecal_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cameras_opencv_ecal_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cameras_opencv_ecal_demo.dir/clean

CMakeFiles/cameras_opencv_ecal_demo.dir/depend:
	cd /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/build /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/build /home/nvidia/features/gmsl_camera/samples/cameras_opencv_ecal_demo/build/CMakeFiles/cameras_opencv_ecal_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cameras_opencv_ecal_demo.dir/depend

