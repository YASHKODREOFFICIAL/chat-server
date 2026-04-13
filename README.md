# Chat Server (Multi-client TCP Server)

## Overview
A simple multi-client TCP chat server written in C using POSIX sockets and pthreads.

## Features
- Multi-client support (thread-per-client)
- Broadcast messaging
- Username-based chat
- Graceful disconnect handling
- Lightweight and efficient

## Architecture
- Server uses thread-per-client model
- Shared client list protected via mutex
- Client runs receiver thread + input loop

## Build

```bash
make