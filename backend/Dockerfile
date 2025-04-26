FROM frolvlad/alpine-gxx AS builder

WORKDIR /app

RUN apk add --no-cache git ninja cmake curl asio-dev spdlog-dev fmt-dev libpq-dev libsodium-dev zlib-dev

RUN curl -L https://github.com/CrowCpp/Crow/releases/download/v1.2.1.2/Crow-1.2.1-Linux.tar.gz | \
    tar -xzf -
    
RUN cp -r Crow-1.2.1-Linux/include/* /usr/include/ && \
    cp -r Crow-1.2.1-Linux/lib/* /usr/lib/ && \
    rm -rf Crow-1.2.1-Linux

COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G Ninja
RUN cmake --build build --parallel $(nproc)

FROM alpine:latest

WORKDIR /app
COPY --from=builder /app/bin/projectify .
COPY --from=builder /usr/lib/* /usr/lib/

EXPOSE 8000

CMD ["./projectify"]
