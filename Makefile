
LIBS = -lm -lpthread -lfreetype
CFLAGS = -m64 -static-libgcc -std=c++17 -w -I"C:\mingw-w64-ramdisk\include" -pipe -O0
CC = C:/mingw-w64-ramdisk/x86_64-8.1.0-posix-seh/mingw64/bin/g++.exe
EXECUTABLEGAME = game.exe
EXECUTABLEMAPGEN = mapgen.exe

OBJECTS = ./bin/BlockState.o ./bin/Actor.o ./bin/Drawer.o ./bin/Map.o ./bin/Window.o ./bin/World.o
OBJECTS += ./bin/Character.o ./bin/DrawerPreprocessor.o ./bin/Mob.o ./bin/Perlin.o ./bin/Player.o ./bin/Projectile.o ./bin/RegisterTypes.o ./bin/World2.o ./bin/WorldGenerator.o
OBJECTS += ./bin/ArgumentParser.o ./bin/Noise.o ./bin/Perlin.o ./bin/Utility.o ./bin/Vector.o
OBJECTS += ./bin/FirstPass.o
OBJECTS += ./bin/LodePNG.o





testgame: $(EXECUTABLEGAME)
	$(EXECUTABLEGAME)

testmapgen: $(EXECUTABLEMAPGEN)
	$(EXECUTABLEMAPGEN) -o=heightmap.png -w=256 -h=256 -oct=10





game: $(EXECUTABLEGAME)
$(EXECUTABLEGAME): $(OBJECTS) ./bin/GameMain.o
	$(CC) -o $@ $^ $(CFLAGS) -L"C:\mingw-w64-ramdisk\lib" -s

mapgen: $(EXECUTABLEMAPGEN)
$(EXECUTABLEMAPGEN): $(OBJECTS) ./bin/MapgenMain.o
	$(CC) -o $@ $^ $(CFLAGS) -L"C:\mingw-w64-ramdisk\lib" -s





./bin/LodePNG.o: ./thrdlib/LodePNG.cpp ./thrdlib/LodePNG.h
	$(CC) -c -o $@ $< $(CFLAGS)





./bin/ArgumentParser.o: ./lib/ArgumentParser.cpp ./lib/ArgumentParser.h
	$(CC) -c -o $@ $< $(CFLAGS)

./bin/Noise.o: ./lib/Noise.cpp ./lib/Noise.h
	$(CC) -c -o $@ $< $(CFLAGS)

./bin/Perlin.o: ./lib/Perlin.cpp ./lib/Perlin.h ./lib/Noise.h
	$(CC) -c -o $@ $< $(CFLAGS)

./bin/Utility.o: ./lib/Utility.cpp ./lib/Utility.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

./bin/Vector.o: ./lib/Vector.cpp ./lib/Vector.hpp
	$(CC) -c -o $@ $< $(CFLAGS)





WINDOW_DEPS = ./engine/Window.h
./bin/Window.o: ./engine/Window.cpp $(WINDOW_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

DRAWER_DEPS = ./engine/Drawer.hpp $(WINDOW_DEPS)
./bin/Drawer.o: ./engine/Drawer.cpp $(DRAWER_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

BLOCKSTATE_DEPS = ./engine/BlockState.h $(DRAWER_DEPS)
./bin/BlockState.o: ./engine/BlockState.cpp $(BLOCKSTATE_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MAP_DEPS = ./engine/Map.h ./engine/Actor.h ./engine/World.h $(DRAWER_DEPS) $(BLOCKSTATE_DEPS)
./bin/Map.o: ./engine/Map.cpp $(MAP_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ACTOR_DEPS = $(MAP_DEPS) $(WINDOW_DEPS)
./bin/Actor.o: ./engine/Actor.cpp $(ACTOR_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

WORLD_DEPS = $(ACTOR_DEPS) $(DRAWER_DEPS)
./bin/World.o: ./engine/World.cpp ./engine/World.h ./lib/Utility.hpp ./engine/Actor.h ./engine/Drawer.hpp ./engine/Window.h ./lib/Vector.hpp ./engine/Map.h
	$(CC) -c -o $@ $< $(CFLAGS)





PROJECTILE_DEPS = ./game/Projectile.h ./game/Character.h $(ACTOR_DEPS)
./bin/Projectile.o: ./game/Projectile.cpp $(PROJECTILE_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

CHARACTER_DEPS = $(PROJECTILE_DEPS)
./bin/Character.o: ./game/Character.cpp $(CHARACTER_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

DRAWERPREPROCESSOR_DEPS = ./game/DrawerPreprocessor.h $(DRAWER_DEPS)
./bin/DrawerPreprocessor.o: ./game/DrawerPreprocessor.cpp $(DRAWERPREPROCESSOR_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
MOB_DEPS = ./game/Mob.h ./engine/World.h $(DRAWER_DEPS) $(CHARACTER_DEPS)
./bin/Mob.o: ./game/Mob.cpp $(MOB_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
PLAYER_DEPS = ./game/Player.h ./game/World2.h ./engine/World.h $(DRAWER_DEPS) $(CHARACTER_DEPS)
./bin/Player.o: ./game/Player.cpp $(PLAYER_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
REGISTERTYPES_DEPS = ./game/RegisterTypes.h ./game/World2.h ./engine/World.h $(DRAWER_DEPS) $(CHARACTER_DEPS)
./bin/RegisterTypes.o: ./game/RegisterTypes.cpp $(REGISTERTYPES_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
WORLD2_DEPS = ./game/World2.h $(UTILITY_DEPS) $(DRAWERPREPROCESSOR_DEPS) ./game/StringGetter.cpp ./game/DrawMenu.cpp ./game/DrawGUI.cpp" $(WORLD)
./bin/World2.o: ./game/World2.cpp $(WORLD2_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
WORLDGENERATOR_DEPS = ./game/WorldGenerator.h $(PERLIN_DEPS) $(WORLD)
./bin/WorldGenerator.o: ./game/WorldGenerator.cpp $(WORLDGENERATOR_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)





./bin/GameMain.o: ./game/Main.cpp $(DRAWERPREPROCESSOR_DEPS) ./game/RegisterTypes.cpp $(WORLDGENERATOR_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)





./bin/FirstPass.o: ./mapgen/FirstPass.cpp ./mapgen/GeneratorData.h
	$(CC) -c -o $@ $< $(CFLAGS)




./bin/MapgenMain.o: ./mapgen/Main.cpp  ./mapgen/GeneratorData.h
	$(CC) -c -o $@ $< $(CFLAGS)




.PHONY: clean
clean:
	rm -f ./bin/*.o
	rm -f main.exe
