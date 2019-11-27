#!/bin/bash

find . -regex '.*\.\(cpp\|h\)' -exec clang-format -style=file -i {} \;

find . -regex '.*\.\(cpp\|h\)' -exec chmod -x {} \;
