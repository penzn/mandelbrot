#define export __attribute__ ((visibility("default"))) 

void init(unsigned char * pix, int width, int height);
void fill(void);

/* Functions imported from JS into WASM */
void refresh(void);
