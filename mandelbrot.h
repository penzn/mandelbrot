#define export __attribute__ ((visibility("default"))) 

void fill(unsigned char * pix, int width, int height);

/* Functions imported from JS into WASM */
void refresh(void);
