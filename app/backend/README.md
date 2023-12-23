# Backend

This sub-project contains the backend of the whole system of the Car Application.

It hosts the website for the Car Application and allows users and cars to connect to.

## Installation

Run the following command to build the sub-project: 

```
xmake build backend
```

## How to use

Url: `localhost:8848/#/room/example` - the room url, the website will create a room.
Url: `localhost:8848/#/` - the base url, the page will list the rooms.

## Main Technologies

- C++17
- [xmake](https://xmake.io/)
- [drogon](https://github.com/drogonframework/drogon)
- [nlohmann_json](https://github.com/nlohmann/json)
- [rapidjson](https://github.com/Tencent/rapidjson)