int a;
int b;

void main() {
  a = 1;
  b = 0;
  b = a / b;
  assert(a < b);
}
