#!/usr/bin/bash

find . -iname '*.hpp' | xargs clang-format-18 -i
