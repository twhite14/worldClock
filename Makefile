clean: 
	rm -rf *.o worldClock

worldClock: worldClock.c
	gcc -Wall -g -o worldClock worldClock.c -lwiringPi --std=gnu99
