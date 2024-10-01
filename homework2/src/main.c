#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "model.h"

void count_things(Model* m, char* filename);
void read_data(Model* m, char* filename);
void print_model(Model* m);

int main(int argc, char **argv)
{
   if (argc < 2) {
      printf("USAGE: homework2_exe [filename]\n");
      return 1;
   }
   char* filename = argv[1];
   Model m;

   count_things(&m, filename);
   read_data(&m, filename);
   print_model(&m);

   free(m.vertices);
   free(m.normals);
   free(m.texcoords);
   free(m.triangles);

   exit(0);
}

void count_things(Model* m, char* filename) {
   // Implement this function
       FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    // Initialize counts
    m->n_vertices = 0;
    m->n_normals = 0;
    m->n_texcoords = 0;
    m->n_triangles = 0;

    char line[128];

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            m->n_vertices++;    // Count vertices
        } else if (strncmp(line, "vn ", 3) == 0) {
            m->n_normals++;     // Count normals
        } else if (strncmp(line, "vt ", 3) == 0) {
            m->n_texcoords++;   // Count texture coordinates
        } else if (strncmp(line, "f ", 2) == 0) {
            m->n_triangles++;   // Count triangles (faces)
        }
    }

    fclose(file);
}

void read_data(Model* m, char* filename) {   
   // Implement this function
   FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    // Allocate memory based on the counts
    m->vertices = (Vect3*)malloc(m->n_vertices * sizeof(Vect3));
    m->normals = (Vect3*)malloc(m->n_normals * sizeof(Vect3));
    m->texcoords = (Vect2*)malloc(m->n_texcoords * sizeof(Vect2));
    m->triangles = (Triangle*)malloc(m->n_triangles * sizeof(Triangle));

    int v_index = 0, vn_index = 0, vt_index = 0, f_index = 0;
    char line[128];

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            // Parse vertex
            sscanf(line, "v %f %f %f", &m->vertices[v_index].x, &m->vertices[v_index].y, &m->vertices[v_index].z);
            v_index++;
        } else if (strncmp(line, "vn ", 3) == 0) {
            // Parse normal
            sscanf(line, "vn %f %f %f", &m->normals[vn_index].x, &m->normals[vn_index].y, &m->normals[vn_index].z);
            vn_index++;
        } else if (strncmp(line, "vt ", 3) == 0) {
            // Parse texture coordinate
            sscanf(line, "vt %f %f", &m->texcoords[vt_index].u, &m->texcoords[vt_index].v);
            vt_index++;
        } else if (strncmp(line, "f ", 2) == 0) {
            // Parse face (triangle)
            int v[3], vn[3], vt[3];
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                   &v[0], &vt[0], &vn[0],
                   &v[1], &vt[1], &vn[1],
                   &v[2], &vt[2], &vn[2]);

            // Assign vertex information to triangle
            m->triangles[f_index].v1.x = m->vertices[v[0] - 1].x;
            m->triangles[f_index].v1.y = m->vertices[v[0] - 1].y;
            m->triangles[f_index].v1.z = m->vertices[v[0] - 1].z;
            m->triangles[f_index].v1.normal_x = m->normals[vn[0] - 1].x;
            m->triangles[f_index].v1.normal_y = m->normals[vn[0] - 1].y;
            m->triangles[f_index].v1.normal_z = m->normals[vn[0] - 1].z;
            m->triangles[f_index].v1.u = m->texcoords[vt[0] - 1].u;
            m->triangles[f_index].v1.v = m->texcoords[vt[0] - 1].v;

            m->triangles[f_index].v2.x = m->vertices[v[1] - 1].x;
            m->triangles[f_index].v2.y = m->vertices[v[1] - 1].y;
            m->triangles[f_index].v2.z = m->vertices[v[1] - 1].z;
            m->triangles[f_index].v2.normal_x = m->normals[vn[1] - 1].x;
            m->triangles[f_index].v2.normal_y = m->normals[vn[1] - 1].y;
            m->triangles[f_index].v2.normal_z = m->normals[vn[1] - 1].z;
            m->triangles[f_index].v2.u = m->texcoords[vt[1] - 1].u;
            m->triangles[f_index].v2.v = m->texcoords[vt[1] - 1].v;

            m->triangles[f_index].v3.x = m->vertices[v[2] - 1].x;
            m->triangles[f_index].v3.y = m->vertices[v[2] - 1].y;
            m->triangles[f_index].v3.z = m->vertices[v[2] - 1].z;
            m->triangles[f_index].v3.normal_x = m->normals[vn[2] - 1].x;
            m->triangles[f_index].v3.normal_y = m->normals[vn[2] - 1].y;
            m->triangles[f_index].v3.normal_z = m->normals[vn[2] - 1].z;
            m->triangles[f_index].v3.u = m->texcoords[vt[2] - 1].u;
            m->triangles[f_index].v3.v = m->texcoords[vt[2] - 1].v;

            f_index++;
        }
    }

    fclose(file);
}

void print_model(Model* m) {
   for (int i = 0; i < m->n_triangles; i++) {
      printf("t:\n");
      Triangle t = m->triangles[i];
      printf("v:\n");
      printf("x=%f\n", t.v1.x);
      printf("y=%f\n", t.v1.y);
      printf("z=%f\n", t.v1.z);
      printf("nx=%f\n", t.v1.normal_x);
      printf("ny=%f\n", t.v1.normal_y);
      printf("nz=%f\n", t.v1.normal_z);
      printf("u=%f\n", t.v1.u);
      printf("v=%f\n", t.v1.v);

      printf("v:\n");
      printf("x=%f\n", t.v2.x);
      printf("y=%f\n", t.v2.y);
      printf("z=%f\n", t.v2.z);
      printf("nx=%f\n", t.v2.normal_x);
      printf("ny=%f\n", t.v2.normal_y);
      printf("nz=%f\n", t.v2.normal_z);
      printf("u=%f\n", t.v2.u);
      printf("v=%f\n", t.v2.v);

      printf("v:\n");
      printf("x=%f\n", t.v3.x);
      printf("y=%f\n", t.v3.y);
      printf("z=%f\n", t.v3.z);
      printf("nx=%f\n", t.v3.normal_x);
      printf("ny=%f\n", t.v3.normal_y);
      printf("nz=%f\n", t.v3.normal_z);
      printf("u=%f\n", t.v3.u);
      printf("v=%f\n", t.v3.v);
   }
}
