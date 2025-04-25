FROM frolvlad/alpine-gxx AS builder

WORKDIR /app

RUN apk add --no-cache git ninja cmake asio-dev spdlog-dev fmt-dev libpq-dev libsodium-dev

COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G Ninja
RUN cmake --build build

FROM alpine:latest

WORKDIR /app
COPY --from=builder /app/bin/projectify .
COPY --from=builder /usr/lib/* /usr/lib/

EXPOSE 8000

CMD ["./projectify"]
