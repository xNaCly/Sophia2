FLAGS := -fdiagnostics-color=always \
		 -Wall \
		 -Wpedantic \
		 -std=c11 \
		 -Wextra \
		 -Wshadow \
		 -Wundef \
		 -g3 \
		 -fno-common

source := $(shell find ./sophia -name "*.c")

run: build
	./sophia2 $(arg)

build: 
	gcc $(FLAGS) $(source) main.c -o sophia2

clean:
	rm -fr sophia2
