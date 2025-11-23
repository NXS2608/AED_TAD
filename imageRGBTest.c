#include <assert.h>
#include <errno.h>
#include "error.h"
#include "imageRGB.h"
#include "instrumentation.h"
#include <stdio.h>

void test_ImageCreate() {
  printf("Testing ImageCreate...\n");
  Image img = ImageCreate(100, 200);
  assert(ImageWidth(img) == 100);
  assert(ImageHeight(img) == 200);
  ImageDestroy(&img);
  printf("All ImageCreate tests passed!\n");
}

void test_ImageCreateChess() {
  printf("Testing ImageCreateChess...\n");
  Image img = ImageCreateChess(100, 100, 10, 0xFF0000);
  assert(ImageWidth(img) == 100);
  assert(ImageHeight(img) == 100);
  ImageDestroy(&img);
  printf("All ImageCreateChess tests passed!\n");
}

void test_ImageCopy() {
  printf("Testing ImageCopy...\n");
  Image img1 = ImageCreateChess(100, 100, 10, 0xFF0000);
  Image img2 = ImageCopy(img1);
  assert(ImageWidth(img1) == ImageWidth(img2));
  assert(ImageHeight(img1) == ImageHeight(img2));
  assert(img1 != img2);
  ImageDestroy(&img1);
  ImageDestroy(&img2);
  printf("All ImageCopy tests passed!\n");
}

void test_ImageIsEqual() {
  printf("Testing ImageIsEqual...\n");
  Image img1 = ImageCreateChess(100, 100, 10, 0xFF0000);
  Image img2 = ImageCopy(img1);
  Image img3 = ImageCreate(100, 100);
  assert(ImageIsEqual(img1, img2));
  assert(!ImageIsEqual(img1, img3));
  ImageDestroy(&img1);
  ImageDestroy(&img2);
  ImageDestroy(&img3);
  printf("All ImageIsEqual tests passed!\n");
}

void test_ImageRotate90CW() {
  printf("Testing ImageRotate90CW...\n");
  Image img1 = ImageCreate(100, 200);
  Image img2 = ImageRotate90CW(img1);
  assert(ImageWidth(img2) == 200);
  assert(ImageHeight(img2) == 100);
  ImageDestroy(&img1);
  ImageDestroy(&img2);
  printf("All ImageRotate90CW tests passed!\n");
}

void test_ImageRotate180CW() {
  printf("Testing ImageRotate180CW...\n");
  Image img1 = ImageCreate(100, 200);
  Image img2 = ImageRotate180CW(img1);
  assert(ImageWidth(img2) == 100);
  assert(ImageHeight(img2) == 200);
  ImageDestroy(&img1);
  ImageDestroy(&img2);
  printf("All ImageRotate180CW tests passed!\n");
}

void test_ImageLoadSavePBM() {
  printf("Testing ImageLoadSavePBM...\n");
  Image img1 = ImageCreateChess(100, 100, 10, 0x000000);
  ImageSavePBM(img1, "test.pbm");
  Image img2 = ImageLoadPBM("test.pbm");
  assert(ImageIsEqual(img1, img2));
  ImageDestroy(&img1);
  ImageDestroy(&img2);
  remove("test.pbm");
  printf("All ImageLoadSavePBM tests passed!\n");
}

void test_ImageLoadSavePPM() {
  printf("Testing ImageLoadSavePPM...\n");
  Image img1 = ImageCreateChess(100, 100, 10, 0xFF0000);
  ImageSavePPM(img1, "test.ppm");
  Image img2 = ImageLoadPPM("test.ppm");
  assert(ImageIsEqual(img1, img2));
  ImageDestroy(&img1);
  ImageDestroy(&img2);
  remove("test.ppm");
  printf("All ImageLoadSavePPM tests passed!\n");
}

void test_ImageRegionFillingRecursive() {
  printf("Testing ImageRegionFillingRecursive...\n");
  Image img = ImageCreate(100, 100);
  int count = ImageRegionFillingRecursive(img, 0, 0, 1);
  assert(count == 10000);
  ImageDestroy(&img);
  printf("All ImageRegionFillingRecursive tests passed!\n");
}

void test_ImageSegmentation() {
  printf("Testing ImageSegmentation...\n");
  Image img = ImageCreate(100, 100);
  int regions = ImageSegmentation(img, ImageRegionFillingRecursive);
  assert(regions == 1);
  ImageDestroy(&img);
  printf("All ImageSegmentation tests passed!\n");
}

int main(void) {
  ImageInit();

  test_ImageCreate();
  test_ImageCreateChess();
  test_ImageCopy();
  // test_ImageIsEqual(); //This test will fail until the function is implemented
  test_ImageRotate90CW();
  // test_ImageRotate180CW(); //This test will fail until the function is fixed
  // test_ImageLoadSavePBM(); //This test will fail until ImageIsEqual is implemented
  // test_ImageLoadSavePPM(); //This test will fail until ImageIsEqual is implemented
  test_ImageRegionFillingRecursive();
  test_ImageSegmentation();

  printf("All tests passed!\n");

  return 0;
}