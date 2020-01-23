#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <malloc.h>
#include <signal.h>
#include <math.h>
#include "lodepng.h"
#include "cuda_rgb_threshold.h"

/******************************************************************************
  Loads and displays:
    1) An image
    2) The results of applying a colour threshold to the image

  This version uses standard single thread algorithms. 

  Compile with:
    nvcc -o color_threshold_04 color_threshold_04.cu lodepng.cu cuda_rgb_threshold.cu -lGL -lglut -lrt
    
  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/

unsigned char *image;
unsigned char *after_colour_threshold;
unsigned int width, height;

void tidy_and_exit() {
  free(image);
  free(after_colour_threshold);
  exit(0);
}

void sigint_callback(int signal_number){
  printf("\nInterrupt from keyboard\n");
  tidy_and_exit();
}

static void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glRasterPos4i(-1, -1, 0, 1);
  glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

  glRasterPos4i(0, -1, 0, 1);
  glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, 
               after_colour_threshold);

  glFlush();
}

static void key_pressed(unsigned char key, int x, int y) {
  switch(key){
    case 27: // escape
      tidy_and_exit();
      break;
    default: 
      printf("\nPress escape to exit\n");
      break;
  }
}

int main(int argc, char **argv) {
  signal(SIGINT, sigint_callback);

  int error = lodepng_decode32_file(&image, &width, &height, 
                                    "draughts-512.png");
  if(error) {
    printf("Error reading %u: %s\n", error, lodepng_error_text(error));
    return 1;
  }
  
  printf("Image dimensions %dx%d\n", width, height);

  cuda_rgb_threshold(image, &after_colour_threshold, width, height, 
                     249, 238, 72, 4000); // yellow
  //                 50, 52, 137, 2000); // blue

  glutInit(&argc, argv);
  glutInitWindowSize(width*2, height);                  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutCreateWindow("Color Threshold");
  glutDisplayFunc(display);
  glutKeyboardFunc(key_pressed);
  glClearColor(0.0, 1.0, 0.0, 1.0); 
  glutMainLoop(); 
  tidy_and_exit();
  
  return 0;
}