
worldClock: worldClock.c
	gcc -Wall -o worldClock worldClock.c -lwiringPi --std=gnu99

clean: 
	rm -rf *.o worldClock
