#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH*SCREEN_HEIGHT)

#define INPUT_STATUS_1 0x03DA
#define VRETRACE       0x08

void vsync(void);

void SetMode(unsigned char mode);
