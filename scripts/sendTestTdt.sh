#!/bin/bash

set -e -u

while [ true ]; do
    cansend vcan0 419#18.04.04.00.90.0C.00.00
    sleep 0.1
    cansend vcan0 419#18.04.04.00.80.0C.00.00
    sleep 0.1
done

#---fin------------------------------------------------------------------------
