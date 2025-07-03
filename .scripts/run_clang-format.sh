#!/usr/bin/bash

find cpp17Play -name \*.hpp -print -o -name \*.cpp -print | xargs clang-format-18 -i
