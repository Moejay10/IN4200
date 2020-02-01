#include <stdio.h>
#include <math.h>


int main(){

int nx, ny, nz;
nx = ny = nz = 5;

double temp, temp2;
temp = 1/(nx-1)/(ny-1)/(nz-1);

double u[nx][ny][nz];
double v[nx][ny][nz];

double pi;
pi = 4*atan(1);

for (int i = 0; i < nx; i++){
  for (int j = 0; j < ny; j++){
    for (int k = 0; k < nz; k++){
      temp2 = sin(i*j*k*pi*temp);
      v[i][j][k] = 2 + temp2;
      u[i][j][k] = 0;
    }
  }
}
temp = 1/((double) 6);
for (int i = 1; i <= nx-2; i++){
  for (int j = 1; j <= ny-2; j++){
    for (int k = 1; k <= nz-2; k++){
      u[i][j][k] = v[i][j][k] + (v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1] - 6*v[i][j][k] + v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1])*temp;
      v[i][j][k] = u[i][j][k];
    }
  }
}
  return 0;
}
