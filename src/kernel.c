#include <stddef.h>
#include <stdint.h>

#if defined (__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

#define VGA_BUFFER (0xB8000)
#define VGA_COLS (80)
#define VGA_ROWS (25)
#define SCREEN_SIZE (VGA_COLS * VGA_ROWS)
#define INDEX(x, y) ((y * VGA_COLS) + x)

#define TEXT_COLOR (0x0F)
#define CHAR(c) ((uint16_t) ((TEXT_COLOR << 8) | c))

void clr_terminal();
void place_char(uint8_t x, uint8_t y, char c);
void print(char *str);
void panic(char *error);
void kernel_main();

volatile uint16_t *vga_buffer = (uint16_t *) VGA_BUFFER;
const uint8_t vga_cols = (uint8_t) VGA_COLS;
const uint8_t vga_rows = (uint8_t) VGA_ROWS;
uint8_t x_pos = 0;
uint8_t y_pos = 0;

void clr_terminal() {
	for (uint16_t i = 0; i < (uint16_t) SCREEN_SIZE; i++) {
		vga_buffer[i] = CHAR(' ');
	}
	x_pos = 0;
	y_pos = 0;
}

void place_char(uint8_t x, uint8_t y, char c) {
	vga_buffer[INDEX(x, y)] = CHAR(c);
	if (INDEX(x_pos, y_pos) >= SCREEN_SIZE) {
		char *error = "TERMINAL PRINT OUT OF BOUNDS";
		panic(error);
	}
}

void print(char *str) {
	char *term = str;
	while (*term != 0) {
		if (*term == '\n') {
			x_pos = 0;
			y_pos += 1;
		} else {
			vga_buffer[INDEX(x_pos, y_pos)] = CHAR(*term);
			x_pos++;
			x_pos %= VGA_COLS;
			if (x_pos == 0) {
				y_pos += 1;
			}
		}
		term++;
	}
}

void panic(char *error) {
	clr_terminal();
	print(error);
	for (;;) {
	
	}
}

void kernel_main() {
	clr_terminal();
	print("Hello, leafOS!\n");
	print("My name is Walter Hartwell White. I live at 308 Negra Arroyo Lane, Albuquerque, New Mexico, 87104. To all law enforcement entities, this is not an admission of guilt. I am speaking to my family now. Skyler, you are the love of my life. I hope you know that. Walter Jr., you're my big man. There are going to be some things that you'll come to learn about me in the next few years. But just know that no matter how it may look, I only had you in my heart. Goodbye.\n");
	for (;;) {
	
	}
}
