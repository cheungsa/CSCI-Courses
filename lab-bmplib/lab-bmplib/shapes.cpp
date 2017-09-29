#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) 
{
   int bottom = top + height;
   int right = left + width;
   for (int i = top; i < bottom; i++) 
   {
      if (i > 0 && i < 255)
      {
         if (left > 0 && left < 255)
         {image[i][left] = 0;}
         if (right > 0 && right < 255)
         {
      image[i][right] = 0;
      }
      }
   }
   for (int j = left; j < right; j++) 
   {
      if (j > 0 && j < 255)
      {
         if (top > 0 && top < 255)
         {
      image[top][j] = 0;
      }
      if (bottom > 0 && bottom < 255)
      {
      image[bottom][j] = 0;
      }
      }
   }
   return;
}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) 
{
   double r_w = width / 2;
   double r_h = height / 2;
   for (double theta = 0.0; theta < 2 * M_PI; theta += .01) 
   { 
      double x = r_w * cos(theta) + cx;
      double y = r_h * sin(theta) + cy;
      x += width/2;
      y += height/2;
      if ((x > 0 && x < 255) && (y > 0 && y < 255))
      {
      image[(int)y][(int)x] = 0;
      }
   }  
   return;
}

int main() 
{
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) 
   {
      for (int j=0; j < SIZE; j++) 
      {
         image[i][j] = 255;
      }
   }
   
   // Main program loop here

   cout << "To draw a rectangle, enter: 0 top left height width" << endl;
   cout << "To draw an ellipse, enter: 1 cy cx height width" << endl;
   cout << "To save your drawing as output.bmp and quit, enter: 2" << endl;
   int input, top, left, height, width, cy, cx;
   while (cin >> input)
   {
      if (input == 0)
      {
         cin >> top >> left >> height >> width;
         draw_rectangle(top, left, height, width);
      }
      if (input == 1)
      {
         cin >> cy >> cx >> height >> width;
         draw_ellipse(cy, cx, height, width);
      }
      if (input == 2)
      {         
         // Write the resulting image to the .bmp file
         writeGSBMP("output.bmp", image);
         return 0; 
      }
   }  
}
