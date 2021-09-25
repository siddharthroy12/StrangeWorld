// C/C++ library to generate a tile mesh for raylib
#ifndef RAYTILE_H
#define RAYTILE_H

#include "rlgl.h"

static void rtl_allocate_mesh_data(Mesh* mesh, int triangleCount)
{
    mesh->vertexCount = triangleCount * 3;
    mesh->triangleCount = triangleCount;

    mesh->vertices = (float*)MemAlloc(mesh->vertexCount * 3 * sizeof(float));
    mesh->texcoords = (float*)MemAlloc(mesh->vertexCount * 2 * sizeof(float));
    mesh->normals = (float*)MemAlloc(mesh->vertexCount * 3 * sizeof(float));
}

static Mesh rtl_gen_tile_mesh(int size, int sizeX, int sizeY, int texSizeX, int texSizeY, int texCoords[100][100][2]) {
    Mesh mesh = { 0 };
  	rtl_allocate_mesh_data(&mesh, 2 * sizeX * sizeY);

    int doneVertices = 0;
    int doneTexcoords = 0;

    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            // vertex at top left
            mesh.vertices[doneVertices + 0] = -((float)size/2) + (x * size) + ((float)size/2);
            mesh.vertices[doneVertices + 1] = 0;
            mesh.vertices[doneVertices + 2] = ((float)size/2) + (y * -size) - ((float)size/2);
            mesh.normals[doneVertices + 0] = 0;
            mesh.normals[doneVertices + 1] = 1;
            mesh.normals[doneVertices + 2] = 0;
            mesh.texcoords[doneTexcoords + 0] = (1.0f/texSizeX) * texCoords[x][y][0];
            mesh.texcoords[doneTexcoords + 1] = (1.0f/texSizeY) * texCoords[x][y][1];

            // vertex at top right
            mesh.vertices[doneVertices + 3] = ((float)size/2) + (x * size) + ((float)size/2);
            mesh.vertices[doneVertices + 4] = 0;
            mesh.vertices[doneVertices + 5] = ((float)size/2) + (y * -size) - ((float)size/2);
            mesh.normals[doneVertices + 3] = 0;
            mesh.normals[doneVertices + 4] = 1;
            mesh.normals[doneVertices + 5] = 0;
            mesh.texcoords[doneTexcoords + 2] = (1.0f/texSizeX) + ((1.0f/texSizeX) * texCoords[x][y][0]);
            mesh.texcoords[doneTexcoords + 3] = (1.0f/texSizeY) * texCoords[x][y][1];

            // vertex at bottom right
            mesh.vertices[doneVertices + 6] = ((float)size/2) + (x * size) + ((float)size/2);
            mesh.vertices[doneVertices + 7] = 0;
            mesh.vertices[doneVertices + 8] = -((float)size/2) + (y * -size) - ((float)size/2);
            mesh.normals[doneVertices + 6] = 0;
            mesh.normals[doneVertices + 7] = 1;
            mesh.normals[doneVertices + 8] = 0;
            mesh.texcoords[doneTexcoords + 4] = (1.0f/texSizeX) + ((1.0f/texSizeX) * texCoords[x][y][0]);
            mesh.texcoords[doneTexcoords + 5] = (1.0f/texSizeY) + ((1.0f/texSizeY) * texCoords[x][y][1]);

            // vertex at the top left
            mesh.vertices[doneVertices + 9] = -((float)size/2) + (x * size) + ((float)size/2);
            mesh.vertices[doneVertices + 10] = 0;
            mesh.vertices[doneVertices + 11] = ((float)size/2) + (y * -size) - ((float)size/2);
            mesh.normals[doneVertices + 9] = 0;
            mesh.normals[doneVertices + 10] = 1;
            mesh.normals[doneVertices + 11] = 0;
            mesh.texcoords[doneTexcoords + 6] = (1.0f/texSizeX) * texCoords[x][y][0];
            mesh.texcoords[doneTexcoords + 7] = (1.0f/texSizeY) * texCoords[x][y][1];

            // vertex at bottom right
            mesh.vertices[doneVertices + 12] = ((float)size/2) + (x * size) + ((float)size/2);
            mesh.vertices[doneVertices + 13] = 0;
            mesh.vertices[doneVertices + 14] = -((float)size/2) + (y * -size) - ((float)size/2);
            mesh.normals[doneVertices + 12] = 0;
            mesh.normals[doneVertices + 13] = 1;
            mesh.normals[doneVertices + 14] = 0;
            mesh.texcoords[doneTexcoords + 8] = (1.0f/texSizeX) + ((1.0f/texSizeX) * texCoords[x][y][0]);
            mesh.texcoords[doneTexcoords + 9] = (1.0f/texSizeY) + ((1.0f/texSizeY) * texCoords[x][y][1]);

            // vertex at bottom left
            mesh.vertices[doneVertices + 15] = -((float)size/2) + (x * size) + ((float)size/2);
            mesh.vertices[doneVertices + 16] = 0;
            mesh.vertices[doneVertices + 17] = -((float)size/2) + (y * -size) - ((float)size/2);
            mesh.normals[doneVertices + 15] = 0;
            mesh.normals[doneVertices + 16] = 1;
            mesh.normals[doneVertices + 17] = 0;
            mesh.texcoords[doneTexcoords + 10] = (1.0f/texSizeX) * texCoords[x][y][0];
            mesh.texcoords[doneTexcoords + 11] = (1.0f/texSizeY) + ((1.0f/texSizeY) * texCoords[x][y][1]);

            doneVertices += 18;
            doneTexcoords += 12;
        }
    }

    //UploadMesh(&mesh, false);

    return mesh;
}

static Model rtl_gen_tile_model(int size, int sizeX, int sizeY, int texSizeX, int texSizeY, int texCoords[100][100][2], Texture2D texture) {
	Model tile_model = LoadModelFromMesh(rtl_gen_tile_mesh(size, sizeX, sizeY, texSizeX, texSizeY, texCoords));
	tile_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	return tile_model;
}

#endif