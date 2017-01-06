/**
 * recover.c
 *
 * Recovers JPEGs from a forensic image
 *
 * usage: recover image
 *
 * image is the forensic image
 */

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  // validate args
  if (argc != 2) {
    fprintf(stderr, "usage: recover image\n");
    return 1;
  }

  // open image
  FILE *image = fopen(argv[1], "r");
  if (image == NULL) {
    fprintf(stderr, "could not open image\n");
    return 2;
  }

  char buffer[512];

  FILE *outfile;
  int file_count = 0;
  bool file_status = false;

  // read through the image
  while(fread(buffer, 512, 1, image) != 0) {
    if (buffer[0] == (char) 0xff && buffer[1] == (char) 0xd8 && buffer[2] == (char) 0xff && (buffer[3] >= (char) 0xe0 && buffer[3] <= (char) 0xef)) {
      if (file_status) fclose(outfile);
      else file_status = true;

      file_count++;

      char fname[8];
      sprintf(fname, "%03i.jpg", file_count);

      outfile = fopen(fname, "w");
      if (outfile == NULL) {
        fprintf(stderr, "could not create JPEG\n");
        return 3;
      }

      fwrite(buffer, 512, 1, outfile);
    } else if (file_status) {
      fwrite(buffer, 512, 1, outfile);
    }
  }

  // close files
  fclose(outfile);
  fclose(image);

  return 0;
}
