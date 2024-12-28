int a;
int b;

void main() {
  /*!npk b between 0 and 1 */
  if(b == 0) {
    a = 1;
  }
  assert(a == 1);
  assert(b >= 0);
  assert(b <= 1);
}
