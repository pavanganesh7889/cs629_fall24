# Homework 2: Create an OBJ file parser

The [OBJ file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file) is an open source file format used to describe 3D model geometry. It was originally created by Wavefront Technologies for their Advanced Visualizer animation package, but because of its simplicity has become a de-facto standard for situations where a simple geometry description is needed for CG projects.

In this homework, you will write a program in C++ that:

1. Reads an OBJ file and parses it, storing it in memory in a format that will be usable by OpenGL (format provided)
1. Call a "print_model" function (provided for you) that outputs the data to the terminal.

You will be graded on how closely your output resembles the correct output.

To test your program, you should download a free 3d model from the internet. I use [Turbosquid](https://turbosquid.com) but there are plenty of other options (GCTrader, Sketchfab). I don't recommend paying for a model because there are plenty of free models available, and at this point you're just getting started. You can download and use any kind of model you want (provided, of course, it adheres to the university code of conduct -- that goes for any third party asset you use in this class).

What you will submit:

1. the source code of your program (zip up the homework2 folder)
2. the .OBJ file that you used

The OBJ file format is simple enough that pretty much everything you need to know to implement your parser is available on the Wikipedia page (see [here](https://en.wikipedia.org/wiki/Wavefront_.obj_file) or the link above).

You can write this program in C, using C standard library functions. We went over some of these in class.

A few additional notes:

* Remember to use Blender to convert quads to triangles, or use OBJ files that have triangles only.
* Your progam can make two passes over the file: one to figure out how many vertices there are, etc., and another one to actually parse the data in the buffers that you malloc'ed based on the first pass. Read the file, close it, open it again, and read it again.
* Instead of directly using `fscanf` on the input, it's probably easier to read the input line-by-line using `fgets`, and then using `sscanf` (note the extra "s") to parse each line by itself (you can look up both these functions).
* The `strncmp` function (note the "n") might be helpful to you if you want to see if the beginning of a line starts with some string.
* Do not forget that the vertex indices in the OBJ file format are one-based, so vertex 1 will probably be stored in the "zero" index of an array.
* Make sure your line buffer is big enough (1000 bytes is probably enough).
* Please make it so I can pass in the filename via the command line (do not hardcode the file name).
* Do not forget that all the scanf functions require you to use pointers for args.

If you want to use C++ for this assignment it's fine, but you'll have to tweak the CMakeLists file.

## Data format

Your data should be stored in the following format (this is provided to you in a header file):

```
struct VertexInfo
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
};

struct Triangle
{
    VertexInfo v1;
    VertexInfo v2;
    VertexInfo v3;
}

```

If your model doesn't have texture coordinates leave those equal to zero. The vertices should be specified in the same order they appear in the OBJ file (order is important when it comes to distinguishing the front vs. back faces of the triangle). Note that if the same vertex appears in multiple triangles, the position should be copied into the VertexInfo for each triangle.

When it comes to using this in OpenGL (which we are not doing yet):

```
Triangle allTriangles[nTriangles]
```

should be castable to this:

```
VertexInfo* verticesOfTriangles = (VertexInfo*) allTriangles
```

This array will be able to be passed into OpenGL, and it should be exactly equivalent to an array of VertexInfo structs having a length of `3 * nTriangles`.

