void print7seg(int leftNumber, int rightNumber)
{
  int sep=0;
  HCMAX7219.Clear();
  if(leftNumber>=0 && leftNumber<10){ sep = 6; }
  if(leftNumber>=10 && leftNumber<100){ sep = 6; }
  if(leftNumber>=100 && leftNumber<1000){ sep = 7; }
  if(leftNumber>=1000 && leftNumber<10000){ sep = 8; }  
  HCMAX7219.print7Seg(leftNumber,1,sep);
  if(rightNumber>=0 && rightNumber<10){ sep = 2; }
  if(rightNumber>=10 && rightNumber<100){ sep = 2; }
  if(rightNumber>=100 && rightNumber<1000){ sep = 3; }
  if(rightNumber>=1000 && rightNumber<10000){ sep = 4; }
  HCMAX7219.print7Seg(rightNumber,1,sep);
  HCMAX7219.Refresh();  
}