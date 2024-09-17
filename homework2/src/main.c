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
}

void read_data(Model* m, char* filename) {   
   // Implement this function
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
