#include <stdio.h>
#include <stdlib.h>



int main() {
	FILE* f = fopen("input.bin", "wb");
	u_int16_t temp1 = 0x2F07;
	u_int16_t temp2 = 0x0005;
	fwrite(&temp1, sizeof(u_int16_t), 1, f);
	fwrite(&temp2, sizeof(u_int16_t), 1, f);
	fclose(f);
	FILE* f_in = fopen("input.bin", "rb");
	u_int32_t buffer = 0xFA00;
	fread(&buffer, sizeof(u_int16_t), 1, f_in);
	printf("%x\n", buffer);
	return 1;
}