#include <iostream>
using namespace std;

int main()
{
  int a;
  int b;
  int temp;
  cin >> a;
  cin >> b;
  while(b!=0) {
    temp=b;
    b=a%b;
    a=temp;
  }
  cout << a << endl;
  return 0;
}

