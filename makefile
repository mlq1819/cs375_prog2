P=program2
R=Filereader
Q=minheap
CFLAGS= -g -Wall

all: $(P)

$(P): $(P).o $(R).o $(Q).o
	g++ $(CFLAGS) $(P).o $(R).o $(Q).o -o $(P)

$(P).o: $(P).cpp $(P).h $(R).h $(Q).h
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o

$(R).o: $(R).cpp $(R).h
	g++ $(CFLAGS) -c $(R).cpp -o $(R).o
	
$(Q).o: $(Q).cpp $(Q).h
	g++ $(CFLAGS) -c $(Q).cpp -o $(Q).o
	
clean:
	rm -rf $(P)
	rm -rf $(P).o
	rm -rf $(R).o
	rm -rf output.txt