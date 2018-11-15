#define export __attribute__ ((visibility("default"))) 

void init(unsigned char * pix, int width, int height);
void fill(void);
void zoom_step(double timestamp);

/* Functions imported from JS into WASM */
void refresh(void);
void print_fps(float fps);
