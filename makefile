LIBS = -framework GLUT -framework OpenGl -framework Cocoa

default: carGame

carGame: main.cpp car.h car.cpp cube.cpp FireCone.cpp FireCone.h sphere.cpp objreader.h objreader.cpp Texture.h Camera.h Camera.cpp Track.h Track.cpp BCurve.h BCurve.cpp Matrix4.h Matrix4.cpp Vector3.h Vector3.cpp Vector4.h Vector4.cpp
	g++ -o carGame cube.cpp main.cpp car.cpp sphere.cpp Track.cpp FireCone.cpp objreader.cpp BCurve.cpp Camera.cpp Matrix4.cpp Vector4.cpp Vector3.cpp $(LIBS)

clean :
	rm carGame 
