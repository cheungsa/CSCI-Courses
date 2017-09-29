/**************************************************************************
 * File name : readme.txt
 * Author    : Sarah Cheung
 * Email     : cheungsa@usc.edu
 * Date      : 3/16/17
 * Purpose   : Answers questions for filter.cpp
 * Notes     : None
 *************************************************************************/
 
Prelab Questions
 1.   If we restrict the size of the Gaussian kernels to odd integers 
      between 3 and 11 inclusive, and we only allow 266x266 pixel images, 
      the size of the largest padded image needed to handle padding with 
      any kernel size is 11x11 because it's the largest and SIZE+10. 
      The upper-left pixel of the original image will be placed in the 
      padded image at index [5][5]. 
      The lower-right pixel of the original image will be placed in the
      padded image at [260][260]. //261
 2.   The raw Gaussian kernels for N=3, sigma=2 are:
      0.7788   0.8825   0.7788
      0.8825   1.0000   0.8825
      0.7788   0.8825   0.7788
      The normalized Gaussian kernels for N=3, sigma=2 are:
      0.1019   0.1154   0.1019
      0.1154   0.1308   0.1154
      0.1019   0.1154   0.1019
      If we used the raw kernel values, the image would appear brighter.
 
Experimentation
 1.   If I hold N constant and vary sigma, the effects of the filter 
      becomes more prominent as the value of sigma increases, because the 
      peak in the 2D Gaussian distribution becomes wider. For example, 
      as I increase the value of sigma for the Gaussian blur filter, the 
      image becomes increasingly blurred. Conversely, if I vary N and hold 
      sigma the same, the effects of the filter becomes more prominent as 
      the value of N increases. For example, as I increase the value of N 
      for the Gaussian blur filter, the image becomes increasingly 
      blurred. 
 2.   The Sobel filter detects and emphasizes the edges in an image. For 
      example, it converts all of the black and white tiles in 
      bw_tile_wikimedia.bmp to black tiles with white borderlines.
 3.   I do not get the original image back, because the Gaussian blur 
      filter and the unsharp-mask filter are not inverse operations of 
      each 
      other. To sharpen an image, the unsharp-mask filter subtracts a 
      blurred version of an image from the original image. Therefore, the 
      Gaussian blur filter would be called twice. This means that the 
      unsharp-mask filter would only sharpen an already blurred image--it
      would not return the original.

Readme.txt
 1.   The number of calculations my program does grows with the size, N, of
      the kernel, because it is directly correlated to N^2 since it is a 
      NxN kernel. 
      I also utilize for-loops to access each pixel. Since 
      the loop-limits increase with size N, the number of calculations my 
      program does will also increase. 
 
