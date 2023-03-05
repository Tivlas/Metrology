#include <iostream>
#include <vector>


int main(){
   int a = 4;
   std::vector<int> v(10,0);
   for(int i = 0; i < v.size();i++){
   std::cout << i + 2;
   }
   a--;
   a = a << 3;
   std::cout << "\na = " << a;
   return 0;
}
