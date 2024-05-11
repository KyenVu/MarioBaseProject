#pragma once
#ifdef _LevelMap_H
#define _LevelMap_H
#endif // _LevelMap_H
#include "constants.h"


class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int colunm, unsigned int new_value);
private:
	int** m_map;
};

