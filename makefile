###############################################################
# Program:
#     Milestone 07, Moon Lander
#     Brother Dudley, CS165
# Author:
#     Aden Jessee
# Summary:
#     Some good stuff
# Above and Beyond
#     I made some stars and better looking features overall
#     along with a replay feature
#     I wanted to make different levels, but thats for
#     another day
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main Moon Lander game
###############################################################
a.out: driver.o ground.o game.o uiInteract.o uiDraw.o point.o lander.o velocity.o
	g++ driver.o ground.o game.o uiInteract.o uiDraw.o point.o lander.o velocity.o $(LFLAGS)
	tar -j -cf moonLander.tar makefile *.h *.cpp

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    ground.o      Handles the ground / world
#    game.o        Handles the game interaction
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

ground.o: ground.cpp ground.h
	g++ -c ground.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

lander.o: lander.h lander.cpp point.h
	g++ -c lander.cpp

game.o: game.h game.cpp uiDraw.h uiInteract.h point.h ground.h lander.h lander.cpp velocity.h velocity.cpp
	g++ -c game.cpp

driver.o: driver.cpp game.h uiInteract.h
	g++ -c driver.cpp

#######################################################################
# ADD YOUR ADDITIONAL RULES HERE!
#
# Then, don't forget to add them to the dependecy list for a.out above.
#######################################################################


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o *.tar
