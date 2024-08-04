FROM gcc:8.5

WORKDIR /app

COPY . .

RUN apt-get update && apt-get install -y build-essential

RUN gcc --version