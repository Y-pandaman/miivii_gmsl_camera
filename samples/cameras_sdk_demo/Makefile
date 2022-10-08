###############################################################################
#
# Copyright (c) 2016-2017, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################

include ../../Rules.mk

EXAMPLE := cameras_sdk_demo

EXAMPLE_SRC := \
	 cameras_sdk_demo.cpp

EXAMPLE_OBJS := $(EXAMPLE_SRC:.cpp=.o)
CPPFLAGS += -I "/opt/miivii/include" `pkg-config --cflags opencv4`
LDFLAGS += -L"/opt/miivii/lib" `pkg-config --libs opencv4`

all: $(EXAMPLE)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $<

$(EXAMPLE): $(EXAMPLE_OBJS)
	@echo $(TOP_DIR)/source
	$(CPP) -o $@ $(EXAMPLE_OBJS) -L"$(TOP_DIR)/source" -lmvgmslcamera $(CPPFLAGS) $(LDFLAGS)
	@mkdir -p $(TOP_DIR)/bin
	@cp -rf $(EXAMPLE) $(TOP_DIR)/bin
clean:
	$(AT)rm -rf $(OBJS) $(LIB_OBJS) $(EXAMPLE) $(EXAMPLE_OBJS)
