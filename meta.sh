#!/bin/bash

printf "Meta Analysis"

STEP=1
if ! [[ -z "$4" ]]; then
  STEP=$4
fi

for i in $(seq $2 $STEP $3); do
  python3 ./main.py --no-print --save $1 $i >>> data.$i
done
