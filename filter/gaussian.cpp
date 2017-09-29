#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include "bmplib.h"

using namespace std;

void gaussian(double k[][11], int N, double sigma);

int main()
{
double k[11][11]; 
gaussian(k, 3 , 2.0); 

}

void gaussian(double k[][11], int N, double sigma){
  double total = 0; 
  for(int x=0; x<N; x++)
  {
    for(int y=0; y<N; y++)
    {
      double k_num = -1*((pow(x-(N/2),2)/(2*pow(sigma,2))+(pow(y-(N/2),2)/(2*pow(sigma,2)))));
      k[x][y]= exp(k_num);
      total += k[x][y];
    }
  }
   
  for (int i=0; i<N; i++)
  {
     for (int j=0; j<N; j++)
     {
        k[i][j] = k[i][j] / total;
     }
  }
  
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      cout << setprecision(4) << fixed << k[i][j] << " "; 
    }
    cout << endl; 

  }
}
