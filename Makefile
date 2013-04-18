OBJECTS = SnakeRun.cc Snake.cc

Snake: $(OBJECTS) Snake.h
	g++ $(OBJECTS) -lglut -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f Snake
