piname=pi@192.168.0.14


scp -r ../build-evrf-Desktop-Debug $piname:/home/pi/fc3/.
scp -r ../evrf $piname:/home/pi/fc3/.
scp -r ./Makefile $piname:/home/pi/fc3/build-evrf-Desktop-Debug/.

