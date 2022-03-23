CC=gcc
CXX=g++
LD=g++

CFLAGS=-Iinclude
CXXFLAGS=-Iinclude
LDFLAGS= -lfreeglut -lopengl32 -lglu32

LAB01_OBJECTS=include/easing.o src/lab01.o 
LAB02_OBJECTS=include/easing.o src/lab02.o 
FINAL_OBJECTS=include/easing.o src/final.o 


all: lab01.exe lab02.exe final.exe

lab01.exe: ${LAB01_OBJECTS}
	${LD} $^ ${LDFLAGS} -o $@

lab02.exe: ${LAB02_OBJECTS}
	${LD} $^ ${LDFLAGS} -o $@

final.exe: ${FINAL_OBJECTS}
	${LD} $^ ${LDFLAGS} -o $@

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ 

src/lab01.o: include/object.hpp include/objects.hpp include/vector3.hpp include/vector4.hpp include/light.hpp include/camera.hpp include/bitmap.hpp include/app.hpp include/easing.hpp
src/lab02.o: include/object.hpp include/objects.hpp include/vector3.hpp include/vector4.hpp include/light.hpp include/camera.hpp include/bitmap.hpp include/app.hpp include/easing.hpp
src/final.o: include/object.hpp include/objects.hpp include/vector3.hpp include/vector4.hpp include/light.hpp include/camera.hpp include/bitmap.hpp include/app.hpp include/easing.hpp