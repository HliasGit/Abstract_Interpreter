int a;
int b;

void main() {
  /*!npk a between 0 and 10 */
  /*!npk b between 0 and 2 */
  if(b == 0) {
    if(b == 1) {
      a = 2;
    }
  }
  else {
    a = 1;
  }
  assert(a <= 10);
  assert(a >= 0);
  assert(b <= 2);
  assert(b >= 0);
}
