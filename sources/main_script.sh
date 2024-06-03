!/bin/bash

for i in {1..10}; do fswebcam -r 1280x720 /home/luiz/Desktop/SOE_Projeto/photos/pics_taken/foto_$i.jpg; done

/home/luiz/Desktop/SOE_Projeto/sources/people_detection.out /home/luiz/Desktop/SOE_Projeto/photos/pics_taken/*.jpg
