
int leapyear(int year)
{
 if((year%4==0 && year%100!=0) || year%400==0)
  return 1;
 else
  return 0;
}
int days(int *day1, int *day2)
{
 int i=0;
 int *tmp;



 int diff = 0;
 const int month[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
 if(day1[0] == day2[0])
 {
  if(day1[1] == day2[1])
  {
   diff = day1[2] - day2[2];
   diff = (diff < 0)?(-diff):diff;
  }
  else
  {
   if(day1[1] < day2[1])    //day1=1991-5-8   day2=1991-6-2
   {
    tmp = day1;      //day1=1991-6-2   day2=1991-5-8
    day1 = day2;
    day2 = tmp;
   }
   for(i=day2[1]+1; i<day1[1]; i++)
   {
    diff +=  month[i];
   }
   diff += month[day2[1]] - day2[2] + day1[2];
   if(day2[1] <= 2 && day1[1] >2)
    if(leapyear(day2[0]))
     diff++;
  }
 }
 else
 {
  if(day1[0] < day2[0])
  {
   tmp = day1; 
   day1 = day2;
   day2 = tmp;
  }
  for(i=day2[0]+1; i<day1[0]; i++)
  {
   if(leapyear(i))
    diff += 366;
   else
    diff += 365;
  }
  for(i=day2[1]+1; i<=12; i++)     //day1=1992-1-1   day2=1991-1-1
  {
   diff += month[i];
  }
  diff += (month[day2[1]] - day2[2]);
  if(day2[1] <= 2)
   if(leapyear(day2[0]))
    diff++;
  for(i=1; i<day1[1]; i++)
  {
   diff += month[i];
  }
  diff += day1[2];
  if(day1[1] > 2)
   if(leapyear(day1[0]))
    diff++;
 }

 return diff;
}
