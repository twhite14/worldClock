clean: 
	rm -rf *.o worldClock timeDisplay clear

worldClock: worldClock.c
	gcc -Wall -g -o worldClock worldClock.c -lwiringPi --std=gnu99

timeDisplay: timeDisplay.c
	gcc -Wall -g -o timeDisplay timeDisplay.c -lwiringPi  --std=gnu99

clear: clear.c
	gcc -Wall -g -o clear clear.c -lwiringPi --std=gnu99
