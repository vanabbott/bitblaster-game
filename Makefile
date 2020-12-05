CMP = g++
CLASS = game
MAIN = project
EXEC = play

$(EXEC): $(CLASS).o $(MAIN).o gfx.o
				$(CMP) $(CLASS).o $(MAIN).o gfx.o -lX11 -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
				$(CMP) -std=c++11 -c $(CLASS).cpp -lX11 -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
				$(CMP) -std=c++11 -c $(MAIN).cpp -lX11 -o $(MAIN).o

clean:
				rm $(MAIN).o
				rm $(CLASS).o
				rm $(EXEC)
