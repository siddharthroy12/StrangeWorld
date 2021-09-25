#ifndef CHUNK_HPP
#define CHUNK_HPP

#define CHUNK_SIZE_X 100
#define CHUNK_SIZE_Y 100

#include <array>

#include "../Blocks/Blocks.hpp"
#include "raylib.h"

class Chunk {
	private:
		std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks;
		int tileTextureMap[CHUNK_SIZE_X][CHUNK_SIZE_Y][2]; // Contains texture coords for tilemap
		RenderTexture2D chunkTexture; // to draw tilemap on
		Mesh mesh; // Tilemap mesh
		Model model; // Tilemap model
		Camera camera; // tilemap is drawn on 3D camera
		int posX;
		int posY;
		bool needToLoadModel;
		bool needToRenderTexture;
		bool needToLoadTexture;

	public:
		Chunk(std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks, int x, int y);
		void renderChunk();
		void loadTexture();
		void updateChunk(int x, int y, Block block);
		int getPosX() const;
		int getPosY() const;
		~Chunk();
};

#endif