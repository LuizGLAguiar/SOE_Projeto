!/bin/bash

for i in {1..3}; do fswebcam -r 1280x720 /home/pi/Desktop/SOE/SOE_Projeto/photos/pics_taken/foto_$i.jpg; done

/home/pi/Desktop/SOE/SOE_Projeto/sources/people_detection.out /home/pi/Desktop/SOE/SOE_Projeto/photos/pics_taken/*.jpg

/home/pi/Desktop/SOE/SOE_Projeto/sources/grafico.out 
