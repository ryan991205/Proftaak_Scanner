
CC = g++
CFLAGS = -g -Wall
SOURCES = main.cpp Camera.cpp ImageImporter.cpp ImageConverter/ColorFilter.cpp ImageConverter/GridCalculator.cpp ImageConverter/ImageCropper.cpp ImageConverter/ReferencePointFinder.cpp ImageConverter/WallVectorsCalculator.cpp
PROG = Proftaak

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SOURCES)
	$(CC) $(CFLAGS) -o $(PROG) $(SOURCES) $(LIBS)