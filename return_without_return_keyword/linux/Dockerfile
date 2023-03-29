FROM gcc:12
COPY main.c /usr/src/main/
WORKDIR /usr/src/main
RUN gcc -S main.c
RUN cat main.s
RUN gcc -o main main.s
CMD ["./main"]
