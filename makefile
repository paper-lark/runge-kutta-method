.PHONY: all clean debug release

SRC_DIR = ./src
BUILD_DIR = ./build
DEBUG_FLAGS = -o ${BUILD_DIR}/debug.out -g -fsanitize=bounds -fsanitize=address -fsanitize=undefined -lm
RELEASE_FLAGS = -o ${BUILD_DIR}/release.out -O2 -lm

all: release debug

release: ${SRC_DIR}/main.c ${SRC_DIR}/runge-kutta.c ${SRC_DIR}/functions.c
	gcc ${RELEASE_FLAGS} ${SRC_DIR}/main.c ${SRC_DIR}/runge-kutta.c ${SRC_DIR}/functions.c

debug: ${SRC_DIR}/main.c ${SRC_DIR}/runge-kutta.c ${SRC_DIR}/functions.c
	gcc ${DEBUG_FLAGS} ${SRC_DIR}/main.c ${SRC_DIR}/runge-kutta.c ${SRC_DIR}/functions.c

clean:
	rm -rf ${BUILD_DIR}/*
