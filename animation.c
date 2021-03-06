#include <stddef.h>
#include "mandelbrot.h"

/** Settings
 * Coordinate Y increases downwards and X -- left to right
 */
struct {
  // HTML5 bitmap
  struct {
    unsigned char * ptr;
    int width;
    int height;
  } canvas;
  // Fractal
  float x; // Upper left corner
  float y;
  float width; // Size of the picture
  float height;
  // Zoom
  struct {
    float x;
    float y;
    float steps;
    float min_height;
    float max_height;
    float min_width;
    float max_width;
    float x_step;
    float y_step;
  } zoom;
} s;

// Timestamp
double ts;

/** Color selection for single pixel
 */
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

/** Initialize fractal
 * \param pix byte array in RGBA order
 * \param width of the picture in pixels
 * \param height of the picture in pixels
 */
export void init(unsigned char * pix, int width, int height) {
  s.canvas.ptr = pix;
  s.canvas.width = width;
  s.canvas.height = height;
  s.x = -2.0;
  s.y = -1.0;
  s.width = s.zoom.max_width = 3.0;
  s.height = s.zoom.max_height = 2.0;
  s.zoom.x = -1.186;
  s.zoom.y = -0.305;
  s.zoom.steps = 249;
  s.zoom.x_step = 0.012;
  s.zoom.y_step = 0.008;
  s.zoom.min_width = s.zoom.max_width - s.zoom.x_step * s.zoom.steps;
  s.zoom.min_height = s.zoom.max_height - s.zoom.y_step * s.zoom.steps;
  ts = 0;
}

/** Draw the fractal in a byte array
 */
export void fill(void) {
  unsigned char * p = s.canvas.ptr;
  int height = s.canvas.height;
  int width = s.canvas.width;
  unsigned x, y;

  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      // Map coordinates to Mandelbrot plane
      float x_m = s.x + s.width * x / width;
      float y_m = s.y + s.height * y / height;
      unsigned rgba = pick_color(x_m, y_m);
      *(p++) = (rgba >> 24) & 0xFF;
      *(p++) = (rgba >> 16) & 0xFF;
      *(p++) = (rgba >> 8)  & 0xFF;
      *(p++) =  rgba        & 0xFF;
    }
  }

  refresh(); // Render
}

/** Zoom one step
 */
export void zoom_step(double timestamp) {
  // Reverse direction if needed
  if (s.height <= s.zoom.min_height || s.height >= s.zoom.max_height) {
    s.zoom.x_step = -s.zoom.x_step;
    s.zoom.y_step = -s.zoom.y_step;
  }
  // Update parameters
  s.x += s.zoom.x_step * (s.zoom.x - s.x) / s.width;
  s.y += s.zoom.y_step * (s.zoom.y - s.y) / s.height;
  s.width -= s.zoom.x_step;
  s.height -= s.zoom.y_step;
  // Draw
  fill();

  // Calcluate frame rate
  if (ts) {
    print_fps(1000.0 / (timestamp - ts)); // FIXME correct?
  }
  ts = timestamp;

}
