#!/bin/bash

ffmpeg -i $1/%d.png $1/$(basename $1).$2
