
.PHONY	: build
build:
	docker build --progress=plain --no-cache -t gcc .   

.PHONY  : run
run:
	docker run -it --rm --name gcc-app gcc

.PHONY  : local-run
local-run:
	gcc -pthread -o main main.c && ./main  

