#!/bin/bash

set -e

cpplint --linelength=80 --counting=detailed --root=. $(find reap -name "*.h" -or -name "*.cc")