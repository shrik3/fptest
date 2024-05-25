SRC = $(shell ls src)
BINS = $(addprefix build/, $(SRC:.c=))

all: docker

docker: $(BINS)
	docker build -t fp_tests .

build/%: src/%.c
	gcc -o $@ $^ -lm -static
