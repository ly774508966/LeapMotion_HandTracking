OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := ../lib/x64/libLeap.so -Wl,-rpath,../lib/x64
  else
    LEAP_LIBRARY := ../lib/x86/libLeap.so -Wl,-rpath,../lib/x86
  endif
else
  # OS X
  LEAP_LIBRARY := ../lib/libLeap.dylib
endif

Sample: Sample.o Play.o Record.o LeapRecorder.o
	$(CXX) -Wall -g -w  Sample.o Play.o Record.o LeapRecorder.o -o Sample $(LEAP_LIBRARY)

Sample.o: Sample.cpp Play.hpp Record.hpp
	$(CXX) -Wall -c -g -w -I../include Sample.cpp $(LEAP_LIBRARY)

Play.o: Play.cpp Play.hpp LeapRecorder.hpp
	$(CXX) -Wall -c -g -w -I../include Play.cpp $(LEAP_LIBRARY)

Record.o: Record.cpp Record.hpp LeapRecorder.hpp
	$(CXX) -Wall -c -g -w -I../include Record.cpp $(LEAP_LIBRARY)

LeapRecorder.o: LeapRecorder.hpp LeapRecorder.cpp
	$(CXX) -Wall -c -g -w -I../include LeapRecorder.cpp $(LEAP_LIBRARY)

clean:
	rm -rf *.o Sample Sample.dSYM
