surfshark-connect: surfshark-connect.o functions.o helpers.o
	gcc surfshark-connect.o functions.o helpers.o -o surfshark-connect
	rm *.o

surfhsark-connect.o: surfshark-connect.c
	gcc -c surfshark-connect.c 

functions.o: functions.c
	gcc -c functions.c

helpers.o: helpers.c
	gcc -c helpers.c

clean:
	rm *.o surfshark-connect 
