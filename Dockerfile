FROM fedora:44

RUN -dnf -y install gcc cmake && \
    dnf clearn all

WORKDIR /app

COPY CMakeLists.txt .
COPY src/ ./src/
COPY index.html .

RUN cmake -S . -B build && \
cmake --build build

EXPOSE 6969

CMD [ "./build/server" ]


