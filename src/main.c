#include <graphx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/screen.h>

#include "data.h"

#define SCALE 200

typedef struct {
  short x, y, z;
  uint8_t r, g, b;
  uint8_t palette_index;
} vertex;

typedef struct {
  short a, b, c;
} face;

uint8_t hash_rgb(uint8_t r, uint8_t g, uint8_t b);
void populate_vertex(vertex *v, char *ptr);
void populate_face(face *f, char *ptr);

int main(void) {
  os_ClrHome();
  gfx_Begin();
  gfx_SetDrawBuffer();

  // quickly pass through the obj so we can 
  // allocate enough vertices and faces
  int vertex_count = 0;
  int face_count = 0;
  for (int i = 0; i < data_len; i++) {
    if (data[i] == 'v')
      vertex_count++;
    else if (data[i] == 'f')
      face_count++;
  }

  vertex vertices[vertex_count];
  face faces[face_count];

  char *ptr = data;

  // populate vertices and faces with data from the .obj file
  for (int i = 0; i < vertex_count; i++) {
    while (*ptr++ != 'v');
    populate_vertex(&vertices[i], ptr);
  }

  for (int i = 0; i < face_count; i++) {
    while (*ptr++ != 'f');
    populate_face(&faces[i], ptr);
  }

  double x = 0;
  short half_w = GFX_LCD_WIDTH / 2;
  short half_h = GFX_LCD_HEIGHT / 2;

  // rendering loop
  while (x < M_PI * 2 && !os_GetCSC()) {
    for (int i = 0; i < face_count; i++) {
      face f = faces[i];
      vertex a = vertices[f.a - 1];
      vertex b = vertices[f.b - 1];
      vertex c = vertices[f.c - 1];

      // set draw color to the color of the first vertex
      gfx_SetColor(a.palette_index);

      double cosx = cos(x);
      double sinx = sin(x);

      // calculate x position based on rotation
      short a_w = cosx * a.x + sinx * a.z;
      short b_w = cosx * b.x + sinx * b.z;
      short c_w = cosx * c.x + sinx * c.z;
      
      gfx_FillTriangle(a_w + half_w, -a.y + half_h, b_w + half_w, -b.y + half_h,
                       c_w + half_w, -c.y + half_h);
    }

    // swap the buffer to display
    // so we can start drawing on the other one
    gfx_SwapDraw();
    gfx_SetDrawBuffer();


    // clear background to dark color without affecting palette
    // (definitely not an optimized way to do this)
    uint16_t color = gfx_palette[0];
    gfx_palette[0] = gfx_RGBTo1555(64, 64, 64);
    gfx_FillScreen(0);
    gfx_palette[0] = color;

    // rotate the model
    x += 0.1;
  }

  gfx_End();
  return 0;
}

// hash colors used in the .obj to assign unique palette indexes,
// collisions could occur, this is definitely not the best stategy
uint8_t hash_rgb(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t hash = (r * 31) + (g * 37) + (b * 41);
  return (uint8_t)(hash & 0xFF);
}

// parse through the obj data to read position and color info
void populate_vertex(vertex *v, char *ptr) {
  v->x = (short)(strtod(ptr, &ptr) * SCALE);
  v->y = (short)(strtod(ptr, &ptr) * SCALE);
  v->z = (short)(strtod(ptr, &ptr) * SCALE);

  v->r = strtod(ptr, &ptr) * 255;
  v->g = strtod(ptr, &ptr) * 255;
  v->b = strtod(ptr, &ptr) * 255;

  uint8_t hash = hash_rgb(v->r, v->g, v->b);
  v->palette_index = hash;

  gfx_palette[hash] =
      gfx_RGBTo1555(v->r, v->g, v->b);
}

// parse through the obj data to assign face vertex indices
void populate_face(face *f, char *ptr) {
  f->a = strtol(ptr, &ptr, 10);
  f->b = strtol(ptr, &ptr, 10);
  f->c = strtol(ptr, &ptr, 10);
}