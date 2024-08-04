#include <iostream>
#include <ostream>

#define AGA >


int main() {
  //data
  short a_[21] = {1,2,3,1,-5,-6,0,
               1,2,1,5,1,-10,-1,
               5,7,15,1,6,7,-2};
  short res[21];

  short n = 3, m = 7;

  // размер m, вместо 0 = минимальное число
  int a[7] =       {0};
  int indexes[7] = { 0, 1, 2, 3, 4,5, 6};

  // TODO delete
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << a_[i*m + j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';


  if (m <= 1)
    return 0;

  // code
getMax:
  for (short j = 0; j < m; ++j) {
    short max = 0x8000;
    for (short i = 0; i < n; ++i) {
      if (max < a_[i*m+j]) {
        max = a_[i*m+j];
      }
    }
    a[j] = max;
  }

sort:
  int left = 0;
  int right = m;

  for (int k = left; ++left < right; k = ++left) {

      //Очередную пару рядом стоя́щих элементов 
      //заносим в пару буферных переменных
      int a1 = a[k], a2 = a[left];
      int i1 = indexes[k], i2 = indexes[left];

      if (a1 AGA a2) {
        std::swap(a1, a2);
        std::swap(i1, i2);
      }
  
      //Вставляем больший элемент из пары
      while (--k >= 0 && a1 AGA a[k]) {
          a[k + 2] = a[k];
          indexes[k+2] = indexes[k];
      }
      a[++k + 1] = a1;
      indexes[k+1] = i1;
      
      while (--k >= 0 && a2 AGA a[k]) {
          a[k + 1] = a[k];
          indexes[k+1] = indexes[k];
      }
      a[k + 1] = a2;
      indexes[k+1] = i2;
}

  --right;
  int last = a[right];
  int lastI = indexes[right];
  while (--right >= 0 && last AGA a[right]) {
          a[right + 1] = a[right];
          indexes[right+1] = indexes[right];
  }
  a[right + 1] = last;
  indexes[right+1] = lastI;


  // max = a_[i*m+j];
end:
  for (int j = 0; j < m; ++j) {
    int column = indexes[j];
    for (int i = 0; i < n; ++i) {
      res[i*m + j] = a_[i*m + column];
    }
  }

  // TODO delete
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << res[i*m + j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';

  return 0;
}
