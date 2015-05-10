CXX = g++
CXXFLAGS = -g -Wall -Wextra -O3 -pthread -I . -I ./3rd_party/ -std=c++0x

OUTDIR := bin

SRCS := 3rd_party/gtest/gtest_all.cpp 3rd_party/gtest/gtest_main.cpp *_test.cpp
OBJS := $(SRCS:%.cpp=$(OUTDIR)/%.o)
DEPS := $(SRCS:%.cpp=$(OUTDIR)/%.d)

.PHONY: clean test

all: bin/test

-include $(DEPS)

test: bin/test
	./bin/test

clean:
	rm -rf bin

bin/test: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OUTDIR)/%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<
