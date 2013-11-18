LIBS = -framework GLUT -framework OpenGl -framework Cocoa

default: car

car: main.cpp Track.h Track.cpp BCurve.h BCurve.cpp Matrix4.h Matrix4.cpp Vector3.h Vector3.cpp Vector4.h Vector4.cpp
	g++ -o car main.cpp Track.cpp BCurve.cpp Matrix4.cpp Vector4.cpp Vector3.cpp $(LIBS)

clean :
	rm car Track.o Matrix4.o Vector4.o Vector3.o BCurve.o
