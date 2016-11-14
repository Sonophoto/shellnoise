shellnoise:  
        $(CC) -Wall -W -g -o shellnoise shellnoise.c

clean:
        rm -f *.o shellnoise history.txt
