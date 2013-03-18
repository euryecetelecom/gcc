void abort (void);
void exit(int);

int main(int argc, char **argv)
{
  int x = 0;
  if (argc == 1)
    {
      const char *array[] = {"a.out", "10", "15"};	     
      x = main2 (3, array);
    }
  else if (argc == 3)
    x = main2 (argc, argv);
  else
    abort ();
      
  return x;
}

int main2(int argc, char **argv)
{  
  int array[10][15], ii = 0, jj = 0,x = 0, z= 1 , y = 10 ;
  int array_2[10][15];
 

  for (ii = 0; ii < 10; ii++) {
    for (jj = 0; jj< 15; jj++) {
      array[ii][jj] = ii+jj;
      array_2[ii][jj] = 0;
    }
  }
  array_2[0:5:2][0:5:3] = array[0:5:2][0:5:3] + 1 + 5 + array[0][5] + x;

  for (ii = 0; ii < 10; ii += 2)
    {
      for (jj = 0; jj < 15; jj += 3)
	{
	  if (array_2[ii][jj] != array[ii][jj] + 1 + 5 + array[0][5] + x)
	    abort ();
	}
    }


  for (ii = 0; ii < 10; ii++) {
    for (jj = 0; jj< 15; jj++) {
      array[ii][jj] = ii+jj;
      array_2[ii][jj] = 0;
    }
  }
  x = atoi(argv[1]);
  y = atoi(argv[2]);
  array_2[0:x:1][0:y:1] = array[0:x:1][0:y:1] + x + y + array[0:x:1][0:y:1];

  for (ii = 0; ii < x; ii++)
    {
      for (jj = 0; jj < y; jj++)
	{
	  if (array_2[ii][jj] != array[ii][jj] + x + y + array[ii][jj])
	    abort ();
	}
    }

  for (ii = 0; ii < 10; ii++) {
    for (jj = 0; jj< 15; jj++) {
      array[ii][jj] = ii+jj;
      array_2[ii][jj] = 0;
    }
  }
  x = atoi(argv[1]);
  y = atoi(argv[2]);
  z = (20- atoi (argv[1]))/atoi(argv[1]);
  /* (20-10)/10 evaluates to 1 all the time :-). */
  array_2[0:x:z][0:y:z] = array[0:x:z][0:y:z] + array[0:x:z][0:y:z] + y + z;
  
  for (ii = 0; ii < x; ii += z)
    {
      for (jj = 0; jj < y; jj += z)
	{
	  if (array_2[ii][jj] != array[ii][jj] + array[ii][jj] + y + z)
	    abort ();
	}
    }


 
  for (ii = 0; ii < 10; ii++) {
    for (jj = 0; jj< 15; jj++) {
      array[ii][jj] = ii+jj;
      array_2[ii][jj] = 0;
    }
  }
  x = argc-3;
  y = 20-atoi(argv[1]);
  z = (20- atoi (argv[1]))/atoi(argv[1]);
  /* (20-10)/10 evaluates to 1 all the time :-). */
  array_2[(argc-3):(20-atoi(argv[1])):(20-atoi(argv[1]))/atoi(argv[1])][(argc-3):(30-atoi(argv[2])): ((30-atoi(argv[2]))/atoi(argv[2]))] = array[(argc-3):20-atoi(argv[1]):(20-atoi(argv[1]))/atoi(argv[1])][(argc-3):(30-atoi(argv[2])): (30-atoi(argv[2]))/atoi(argv[2])] + array[(argc-3):20-atoi(argv[1]):(20-atoi(argv[1]))/atoi(argv[1])][(argc-3):(30-atoi(argv[2])): (30-atoi(argv[2]))/atoi(argv[2])] * array[(argc-3):20-atoi(argv[1]):(20-atoi(argv[1]))/atoi(argv[1])][(argc-3):(30-atoi(argv[2])): (30-atoi(argv[2]))/atoi(argv[2])];
  
  for (ii = 0; ii < 10; ii++)
    {
      for (jj = 0; jj < 15; jj++)
	{
	  if (array_2[ii][jj] != array[ii][jj] + array[ii][jj] * array[ii][jj])
	    abort ();
	}
    }
  exit (0);
  return 0;
}
