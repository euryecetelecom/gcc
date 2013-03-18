/* {dg-do compile } */
/* {dg-options } */

int main (int argc, char **argv)
{
  int x = 0;
  if (argc == 1)
    {
      const char *array[] = {"a.out", "5"};
      x = main2 (2, array);
    }
  else
    x = main2 (argc, argv);

  return x;
}

int main2 (int argc, char **argv)
{
  int x = 0;
  int array[10][10], array2[10];

  array[:][:] = array[:]; /* { dg-error "rank mismatch between" } */

  x = array2[:]; /* { dg-error "cannot be scalar when" } */

  return 0;
}
