#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <random>


struct Room {
	bool exists = false;
	bool doorUp = false;
	bool doorDown = false;
	bool doorLeft = false;
	bool doorRight = false;
	int type = 0; // 0: empty, 1: basic, 2: treasure, 3: monster, 4: boss
};


class MapGenerator {
public:
	MapGenerator(int width, int height, int roomSize);
	void generate();
	void draw(sf::RenderWindow& window);


private:
	int width;
	int height;
	int roomSize;


	std::vector<std::vector<Room>> map;
	std::mt19937 rng;
	std::uniform_int_distribution<int> roomTypeDist;


	void generateRooms(int x, int y);
	bool isValid(int x, int y);
};


#endif