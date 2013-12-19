#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>

#define BUFFER_SIZE 1024*1024

int main(int argc, char const *argv[])
{
	int i, j;
	double total_samples, total_diff;
	sf_count_t read;
	float* buffer = (float *)malloc(2 * BUFFER_SIZE * sizeof(float));

	for (i = 1; i < argc; i++) {
		SF_INFO sfinfo;
		SNDFILE* input = sf_open(argv[i], SFM_READ, &sfinfo);
		if (input == NULL) {
			fprintf(stderr, "ismono: `%s': %s\n", argv[i], sf_strerror(NULL));
			continue;
		}
		if (sfinfo.channels != 2) {
			sf_close(input);
			fprintf(stderr, "ismono: `%s': only dual channel files are supported.\n", argv[i]);
			continue;
		}
		total_samples = 0;
		total_diff = 0.0f;
		while (read = sf_readf_float(input, buffer, BUFFER_SIZE)) {
			for (j = 0; j < (read * 2); j += 2) {
				total_samples++;
				total_diff += powf(fabsf(buffer[j]) - fabsf(buffer[j+1]), 2.0);
			}
		}
		printf("%s: %e\n", argv[i], total_diff / total_samples);
		sf_close(input);
	}
	return 0;
}
