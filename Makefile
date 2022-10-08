
#================================================================
#   Copyright (C) 2019 All rights reserved.
#
#   filename    : Makefile
#   Author      : wjyang
#   Date        : 2019-06-20
#   Description : 
#
#================================================================
PROJECT_TOP:=$(shell pwd)
export PROJECT_TOP

all: test

help:
	@echo "make test	: make sample for test."
	@echo "make clean	: clean build project."

test:
	+@make -C samples/cameras_egl_demo
	+@make -C samples/cameras_opencv_demo
	+@make -C samples/cameras_sdk_demo
	+@make -C samples/cameras_sdk_noopencv_demo

clean:
	+@make clean -C samples/cameras_egl_demo
	+@make clean -C samples/cameras_opencv_demo
	+@make clean -C samples/cameras_sdk_demo
	+@make clean -C samples/cameras_sdk_noopencv_demo
	@rm -rf $(PROJECT_TOP)/bin
