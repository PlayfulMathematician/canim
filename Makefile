
IMAGE := canim-build

all: build

build:
	@docker build -t $(IMAGE) .
	@id=$$(docker create $(IMAGE)); \
	docker cp $$id:/canim/out ./out; \
	docker rm $$id

clean:
	@rm -rf out

.PHONY: all build dev clean
