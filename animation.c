#include <stddef.h>
#include "mandelbrot.h"

unsigned int pick_color(float x0, float y0) {
  unsigned char r,g,b;
  float x = 0.0;
  float y = 0.0;
  unsigned i;
  const unsigned MAX_ITERATIONS = 100;

  for (i = 0; x*x + y*y < 4 && i < MAX_ITERATIONS; ++i) {
    float tmp = x*x - y*y + x0;
    y = 2*x*y + y0;
    x = tmp;
  }

  if (i == MAX_ITERATIONS) {
    r = 0;
    g = 0;
    b = 0;
  } else {
    unsigned bgr = (i * (float)0xFFFF / MAX_ITERATIONS) * (float)0xFF;
    r = bgr & 0xFF;//0x77;
    g = (bgr >> 8) & 0xFF;//0x77;
    b = (bgr >> 16) & 0xFF;//0x77;
  }

  return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

/** Draw the fractal in a byte array
 * \param pix byte array in RGBA order
 * \param width of the picture in pixels
 * \param height of the picture in pixels
 */
export void fill(unsigned char * pix, int width, int height) {
  const float M_X = -2.0;
  const float M_Y = -1.0;
  const float M_WIDTH = 3.0;
  const float M_HEIGHT = 2.0;
  unsigned x, y;

  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      // Map coordinates to Mandelbrot plane
      float x_m = M_X + M_WIDTH * x / width;
      float y_m = M_Y + M_HEIGHT * y / height;
      unsigned rgba = pick_color(x_m, y_m);
      *(pix++) = (rgba >> 24) & 0xFF;
      *(pix++) = (rgba >> 16) & 0xFF;
      *(pix++) = (rgba >> 8)  & 0xFF;
      *(pix++) =  rgba        & 0xFF;
    }
  }

  refresh(); // Render
}

