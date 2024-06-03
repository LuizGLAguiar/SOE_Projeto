#!/bin/bash

for i in {1..10}; do fswebcam -r 1280x720 ../photos/pics_taken/foto_$i.jpg; done

./people_detection.out ../photos/pics_taken/*.jpg