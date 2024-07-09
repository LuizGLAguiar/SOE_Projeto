!/bin/bash

for i in {1..3}; do fswebcam -r 1280x720 /home/aguiar/Desktop/SOE_Projeto/photos/pics_taken/foto_$i.jpg; done

/home/aguiar/Desktop/SOE_Projeto/sources/people_detection.out /home/aguiar/Desktop/SOE_Projeto/photos/pics_taken/*.jpg

/home/aguiar/Desktop/SOE_Projeto/sources/grafico.out 
