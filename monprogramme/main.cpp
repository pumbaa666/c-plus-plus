#include <iostream> // for std::cin and std::cout

void change_param(int* param)
{
    *param *= 2;
}

int main() {
  int* p = new int(3);
  int* q = p;

  change_param(p);

  std::cout << "avant delete\n";
  std::cout << *p << '\n';
  std::cout << *q << '\n';

  delete p; // the same as delete p

  std::cout << "après delete\n";
  std::cout << *p << '\n';
  std::cout << *q << '\n';
  return 0;
}
