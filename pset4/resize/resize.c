/**
 * resize.c
 *
 * Resizes 24-bit uncompressed BMPs by a factor of f
 *
 * usage: resize f infile outfile
 *
 * f is the factor
 * infile is the BMP to be resized
 * outfile is the resized BMP
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[]) {
  // validate args
  if (argc != 4) {
    fprintf(stderr, "usage: resize f infile outfile\n");
    return 1;
  }

  // resize factor
  float f = atof(argv[1]);
  if (f < 0.0 || f > 100.0) {
    fprintf(stderr, "factor must be between 0.0 and 100.0\n");
    return 2;
  }

  // open input file for reading
  FILE *infile = fopen(argv[2], "r");
  if (infile == NULL) {
    fprintf(stderr, "couldn't open %s\n", argv[1]);
    return 3;
  }

  // open output file for writing
  FILE *outfile = fopen(argv[3], "w");
  if (outfile == NULL) {
    fclose(infile);
    fprintf(stderr, "couldn't create %s\n", argv[2]);
    return 4;
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
    return 5;
  }

  // determine padding for infile's scanlines
  int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // copy infile's pixels
  RGBTRIPLE inpixel[abs(bi.biHeight)][bi.biWidth];

  // iterate over infile's scanlines
  for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
    // iterate over pixels in scanline
    for (int j = 0; j < bi.biWidth; j++) {
      // read RGB triple from infile
      fread(&inpixel[i][j], sizeof(RGBTRIPLE), 1, infile);
    }

    // skip over padding
    fseek(infile, padding, SEEK_CUR);
  }

  // adjust width and height
  bi.biWidth *= f;
  bi.biHeight *= f;

  // determine outfile padding for scanlines
  int padding_out =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // adjust image size
  bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_out) * abs(bi.biHeight);

  // adjust file size
  bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  // write file header to outfile
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outfile);
  
  // write info header to outfile
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outfile);

  // write to outfile
  // iterate over outfile's scanlines
  for (int i = 0, height = abs(bi.biHeight); i < height; i++) {
    // iterate over pixels in scanline
    for (int j = 0, l = i / f; j < bi.biWidth; j++) {
      fwrite(&inpixel[l][(int) (j / f)], sizeof(RGBTRIPLE), 1, outfile);
    }

    // add padding
    for (int k = 0; k < padding_out; k++) {
      fputc(0x00, outfile);
    }
  }

  // close files
  fclose(infile);
  fclose(outfile);

  // success
  return 0;
}
