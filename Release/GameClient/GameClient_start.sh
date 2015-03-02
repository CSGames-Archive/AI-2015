#!/usr/bin/env bash

cd bin

# point to our libraries and run the game
LD_LIBRARY_PATH=../lib:$LD_LIBRARY_PATH ./GameClient