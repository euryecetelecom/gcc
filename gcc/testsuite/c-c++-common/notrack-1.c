/* { dg-do compile } */

int func (int) __attribute__ ((notrack));
int (*fptr) (int) __attribute__ ((notrack));
typedef void (*notrack_t) (void) __attribute__ ((notrack));

int
foo1 (int arg)
{
  return func (arg) + fptr (arg);
}

void
foo2 (void (*foo) (void))
{
  void (*func) (void) __attribute__((notrack)) = foo;
  func ();
}

void
foo3 (notrack_t foo)
{
  foo ();
}

void
foo4 (void (*foo) (void) __attribute__((notrack)))
{
  foo ();
}
