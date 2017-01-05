/**
 * whodunit.c
 * 
 * Magically reveals everythang.
 *
 * usage: whodunit infile outfile
 *
 * infile is a 24-bit uncompressed BMP 4.0 that has to be decoded
 * outfile is the decoded infile
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[]) {
  // validate args
  if (argc != 3) {
    fprintf(stderr, "usage: whodunit infile outfile\n");
    return 1;
  }

  // open input file for reading
  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    fprintf(stderr, "couldn't open %s\n", argv[1]);
    return 2;
  }

  // open output file for writing
  FILE *outfile = fopen(argv[2], "w");
  if (outfile == NULL) {
    fclose(infile);
    fprintf(stderr, "couldn't create %s\n", argv[2]);
    return 3;
  }

  // read input file's BITMAPFILEHEADER
  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, infile);

  // read input file's BITMAPINFOHEADER structure
  BITMAPINFOHEADER bi;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, infile);

  // make sure input file is a 24-bit uncompressed BMP 4.0
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
    bi.biBitCount != 24 || bi.biCompression != 0) {
    fclose(outfile);
    fclose(infile);
    fprintf(stderr, "infile must be a 24-bit uncompressed BMP 4.0\n");
    return 4;
  }

  // write headers to outfile
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outfile);
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outfile);

  // determine padding for scanlines
  int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // iterate over infile's scanlines
  for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
    // iterate over pixels in scanline
    for (int j = 0; j < bi.biWidth; j++) {
      // temp
      RGBTRIPLE triple;

      // read RGB triple from infile
      fread(&triple, sizeof(RGBTRIPLE), 1, infile);

      // act like the red plastic
      triple.rgbtBlue = 0;
      triple.rgbtGreen = 0;

      // write RGB triple to outfile
      fwrite(&triple, sizeof(RGBTRIPLE), 1, outfile);
    }

    // skip over padding
    fseek(infile, padding, SEEK_CUR);

    // add padding
    for (int k = 0; k < padding; k++) {
      fputc(0x00, outfile);
    }
  }

  // close files
  fclose(infile);
  fclose(outfile);

  // success
  return 0;
}
