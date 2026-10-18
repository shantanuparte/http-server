# HTTP SERVER

## A Simple HTTP Server in C

A basic http server in C. It accepts browser connections and gives back respose(only GET requests)

## Features

- Build in C so fast
- Makes a new process for a new client
- Uses Cmake and docker so you can run it also as it only supposd to be on linux

## Installation

Download binaires for

Download for Linux [Link for linux](https://github.com/shantanuparte/http-server/releases/download/v1.0.0/server)

## Build for yourself

Clone the repo offcourse (╥﹏╥)

```
git clone https://github.com/shantanuparte/http-server.git
```

use cmake by

```
cmake -S . -B build
cmake --build build
```

Run the server by just running tha binary

```
./build/server
```

## Through Docker

Build a Image

```
docker build -t http-server
```

Run the container

```
docker run --rm -p 6969:6969http-server
```

## Usage

go to localhost 6969 to see this

It servers the index.html from the proejct
It only supports the GET request
It was a great learning project and i learned a lot tbh

## License

I'm using the MIT License, so feel free to use and modify this project.
