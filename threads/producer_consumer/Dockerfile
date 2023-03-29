FROM gcc:latest AS Builder
COPY main.c /usr/src/app/
WORKDIR /usr/src/app
RUN gcc -pthread -o main main.c

FROM debian:latest
COPY --from=Builder /usr/src/app/main /usr/app/
WORKDIR /usr/app
CMD [ "./main" ]