FLAGS := -fdiagnostics-color=always \
		 -Wall \
		 -Wpedantic \
		 -std=c11 \
		 -Wextra \
		 -Wshadow \
		 -Wundef \
		 -fno-common

source := $(shell find ./core -name "*.c")

run: build
	./calc

build: 
	gcc $(FLAGS) $(source) main.c -o calc

clean:
	rm -fr calc
