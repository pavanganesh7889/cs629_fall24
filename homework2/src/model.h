#pragma once

typedef struct {
	float x;
	float y;
	float z;
} Vect3;

typedef struct {
	float u;
	float v;
} Vect2;

typedef struct
{
   // coordinates
   float x;
   float y;
   float z;
   // normal
   float normal_x;
   float normal_y;
   float normal_z;
   // texture coordinates
   float u;
   float v;
} VertexInfo;

typedef struct
{
    VertexInfo v1;
    VertexInfo v2;
    VertexInfo v3;
} Triangle;


typedef struct {
    int n_vertices;
    Vect3* vertices;

    int n_normals;
    Vect3* normals;

    int n_texcoords;
    Vect2* texcoords;

    int n_triangles;
    Triangle* triangles;
} Model;
