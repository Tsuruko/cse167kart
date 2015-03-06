LIBS = -framework GLUT -framework OpenGl -framework Cocoa

default: carGame_mac

mac: carGame_mac
	
carGame_mac: main.cpp car.h car.cpp cube.cpp FireCone.cpp FireCone.h sphere.cpp objreader.h objreader.cpp Texture.h Camera.h Camera.cpp Track.h Track.cpp BCurve.h BCurve.cpp Matrix4.h Matrix4.cpp Vector3.h Vector3.cpp Vector4.h Vector4.cpp
	g++ -o carGame cube.cpp main.cpp car.cpp sphere.cpp Track.cpp FireCone.cpp objreader.cpp BCurve.cpp Camera.cpp Matrix4.cpp Vector4.cpp Vector3.cpp $(LIBS)

clean:
	rm carGame.*

CC=/usr/local/gcc-4.8.0-qt-4.8.4-for-mingw32/win32-gcc/bin/i586-mingw32-g++

LIBS_WIN = -mwindows glut32.lib -lopengl32 -lglu32

FLAGS= -Wall -std=c++11

win: carGame_win

carGame_win: main.cpp car.h car.cpp cube.cpp FireCone.cpp FireCone.h sphere.cpp objreader.h objreader.cpp Texture.h Camera.h Camera.cpp Track.h Track.cpp BCurve.h BCurve.cpp Matrix4.h Matrix4.cpp Vector3.h Vector3.cpp Vector4.h Vector4.cpp
	$(CC) -o carGame.exe $(FLAGS) cube.cpp main.cpp car.cpp sphere.cpp Track.cpp FireCone.cpp objreader.cpp BCurve.cpp Camera.cpp Matrix4.cpp Vector4.cpp Vector3.cpp $(LIBS_WIN)
