#include <stdio.h>
#include <stdlib.h>
void swap2(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition2 (int *arr, int low, int high,int *rrr,int *prr,int *srr)
{
    int pivot = arr[high];
    int i = (low - 1);  
    for (int j = low; j <= high- 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;  
           swap2(&arr[i], &arr[j]);
           swap2(&rrr[i], &rrr[j]);
          swap2(&prr[i], &prr[j]);
          swap2(&srr[i], &srr[j]);
        }
    }

  swap2(&arr[i + 1], &arr[high]);
  swap2(&rrr[i+1], &rrr[high]);
  swap2(&prr[i+1], &prr[high]);
  swap2(&srr[i+1], &srr[high]);
    return (i + 1);
}
void quickSort2(int *arr, int low, int high,int *rrr,int *prr,int *srr)
{
    if (low < high)
    {
        int pi = partition2(arr, low, high,rrr,prr,srr);
        quickSort2(arr, low, pi - 1,rrr,prr,srr);
        quickSort2(arr, pi + 1, high,rrr,prr,srr);
    }
}

void HPF(int num)
{
  int n,*a,*r,*p,*s;

  n=num;
    a=(int *)malloc(n*sizeof(int));
    r=(int *)malloc(n*sizeof(int));
    p=(int *)malloc(n*sizeof(int));
    s=(int *)malloc(n*sizeof(int));
    
    
    int seed = time(NULL);
    srand(seed); // guarantee consistency when debugging
    for(int i=0;i<n;i++)
    {
      s[i]=i+1;
      a[i]= rand() % 100; // will return num between 0 and 99
      r[i] = (rand() % 11); // will return num between 0 and 10
      if(r[i]==0) r[i]+=1;
      p[i] =rand()% 5;
      if(p[i]==0) p[i]+=1;
    }

  quickSort2(a,0,n-1,r,p,s); // sorting based on arrival time
   
  for(int j=0;j<n;j++)
    {
       printf("P%-3d %-3d %-3d %-3d \n",s[j],a[j],r[j],p[j]);
    }
  
  int *q1,*q2,*q3,*q4,count1=0,count2=0,count3=0,count4=0,*a1,*a2,*a3,*a4,*r1,*r2,*r3,*r4,*p1,*p2,*p3,*p4,*aw1,*aw2,*aw3,*aw4;
  q1=(int *)malloc(n*sizeof(int));
  q2=(int *)malloc(n*sizeof(int));
  q3=(int *)malloc(n*sizeof(int));
  q4=(int *)malloc(n*sizeof(int));
  a1=(int *)malloc(n*sizeof(int));
  a2=(int *)malloc(n*sizeof(int));
  a3=(int *)malloc(n*sizeof(int));
  a4=(int *)malloc(n*sizeof(int));
  r1=(int *)malloc(n*sizeof(int));
  r2=(int *)malloc(n*sizeof(int));
  r3=(int *)malloc(n*sizeof(int));
  r4=(int *)malloc(n*sizeof(int));
  p1=(int *)malloc(n*sizeof(int));
  p2=(int *)malloc(n*sizeof(int));
  p3=(int *)malloc(n*sizeof(int));
  p4=(int *)malloc(n*sizeof(int));
  aw1=(int *)malloc(n*sizeof(int));
  aw2=(int *)malloc(n*sizeof(int));
  aw3=(int *)malloc(n*sizeof(int));
  aw4=(int *)malloc(n*sizeof(int));
  
  for (int i=0;i<n;i++)    // Making queue based on priority
  {
      if( p[i] ==1) 
      {
        q1[count1] = s[i];
        a1[count1] = a[i];
        r1[count1] = r[i];
        p1[count1] = p[i];
        count1++;
      }
      else if (p[i] ==2) 
      {
        q2[count2] = s[i];
        a2[count2] = a[i];
        r2[count2] = r[i];
        p2[count2] = p[i];
        count2++;
      }
      else if (p[i] ==3)
      {  
        q3[count3] = s[i];
        a3[count3] = a[i];
        r3[count3] = r[i];
        p3[count3] = p[i];
        count3++;
      }
      else if (p[i] ==4)
      {
        q4[count4] = s[i];
        a4[count4] = a[i];
        r4[count4] = r[i];
        p4[count4] = p[i];
        count4++;
      }    
  }
  
  printf("\n Queue 1 \n");
  printf("%-13s %-13s %-13s %-13s\n","Process","Arrivaltime","Runtime","Priority");

  for(int i=0;i<count1;i++)
  {
      printf("P%-12d %-13d %-13d %-13d\n",q1[i],a1[i],r1[i],p1[i]); 
  }
  
  printf("\n Queue 2 \n");
  printf("%-13s %-13s %-13s %-13s\n","Process","Arrivaltime","Runtime","Priority");

  for(int i=0;i<count2;i++)
  {
      printf("P%-12d %-13d %-13d %-13d\n",q2[i],a2[i],r2[i],p2[i]); 
  }
  printf("\n Queue 3 \n");
  printf("%-13s %-13s %-13s %-13s\n","Process","Arrivaltime","Runtime","Priority");

  for(int i=0;i<count3;i++)
  {
      printf("P%-12d %-13d %-13d %-13d\n",q3[i],a3[i],r3[i],p3[i]); 
  }
  printf("\n Queue 4 \n");
  printf("%-13s %-13s %-13s %-13s\n","Process","Arrivaltime","Runtime","Priority");

  for(int i=0;i<count4;i++)
  {
      printf("P%-12d %-13d %-13d %-13d\n",q4[i],a4[i],r4[i],p4[i]); 
  }
  
  int job=0,jobq1=0,jobq2=0,jobq3=0,jobq4=0,i=0,entry=0;
  
  while(job<n)        // Algorithm starts
  {
    if(jobq1<count1 && a1[jobq1] <=i)
    {
      if (a1[jobq1]<i)
      {
          aw1[jobq1]= i-a1[jobq1];
      }
      else
      {
          aw1[jobq1]= 0;
      }
        for(int j=0;j<r1[jobq1];j++)
        {
      if((entry%10==0)) printf("\n");
            printf("%-3d --> P%-4d  ",j+i,q1[jobq1]);
      entry++;
        }
        i=i+r1[jobq1]-1;
        jobq1++;
        job++;
    }
    
   else if ( jobq2<count2  &&  a2[jobq2]<=i)
      {
        if (a2[jobq2]<i)
      {
          aw2[jobq2]= i-a2[jobq2];
      }
      else
      {
          aw2[jobq2]= 0;
      }
         for(int j=0;j<r2[jobq2];j++)
        {
      
            if((entry%10==0)) printf("\n");
            printf("%-3d --> P%-4d  ",j+i,q2[jobq2]);
      entry++;
        }
        i=i+r2[jobq2]-1;
        jobq2++;
        job++;
      }
    else if (jobq3<count3  &&  a3[jobq3]<=i)
      {
      
        if (a3[jobq3]<i)
      {
          aw3[jobq3]= i-a3[jobq3];
      }
      else
      {
          aw3[jobq3]= 0;
      }
         for(int j=0;j<r3[jobq3];j++)
        {
            if((entry%10==0)) printf("\n");
            printf("%-3d --> P%-4d  ",j+i,q3[jobq3]);
      entry++;
        }
        i=i+r3[jobq3]-1;
        jobq3++;
        job++;
      }
    else if (jobq4<count4  &&  a4[jobq4]<=i)
      {
      
      if (a4[jobq4]<i)
      {
          aw4[jobq4]= i-a4[jobq4];
      }
      else
      {
          aw4[jobq4]= 0;
      }
         for(int j=0;j<r4[jobq4];j++)
        {
            if((entry%10==0)) printf("\n");
            printf("%-3d --> P%-4d  ",j+i,q4[jobq4]);
      entry++;
        }
        i=i+r4[jobq4]-1;
        jobq4++;
        job++;
      }
      
      else
      {
  if((entry%10==0)) printf("\n");
        printf("%-3d --> IDLE   ",i);
  entry++;
      }
    i++;
  }
  i--;
  
  printf("\n\n Queue 1 \n");
  printf("\n%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n","Process","Arrivaltime","Runtime","Priority","Waitingtime","Turnaround_time","Response_time");
  for(int i=0;i<count1;i++)
  {
      printf("P%-14d %-15d %-15d %-15d %-15d %-15d %-15d\n",q1[i],a1[i],r1[i],p1[i],aw1[i],aw1[i]+r1[i],aw1[i]); 
  }
  float avgw1=0.0,avgr1=0.0,thr1=0.0;
  
  if(count1==0)
  {
      printf("Average Waiting time = %.2f\n",avgw1);
      printf("Average Turnaround time = %.2f\n",avgr1);
      printf("Average Response time= %.2f\n",avgw1);
      printf("Throughput = %.4f \n ",thr1*100);
  }
  else
  {
        for(int p=0;p<count1;p++)
        {
            avgw1= avgw1 +(float)aw1[p];
            avgr1= avgr1 + (float)aw1[p] + (float)r1[p];
        }
        float total1=0.0;
        total1=a1[count1-1]+aw1[count1-1]+r1[count1-1]-a1[0]-aw1[0]; 
        thr1= (float)count1/total1;
        printf("Average Waiting time = %.2f\n",(float)avgw1/count1);
        printf("Average Turnaround time = %.2f\n",(float)avgr1/count1);
        printf("Average Response time= %.2f\n",(float)avgw1/count1);
        printf("Throughput = %.4f \n ",thr1*100);
  }
  
  printf("\n Queue 2 \n");
  printf("\n%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n","Process","Arrivaltime","Runtime","Priority","Waitingtime","Turnaround_time","Response_time");
  for(int i=0;i<count2;i++)
  {
      printf("P%-14d %-15d %-15d %-15d %-15d %-15d %-15d\n",q2[i],a2[i],r2[i],p2[i],aw2[i],aw2[i]+r2[i],aw2[i]); 
  }
  float avgw2=0.0,avgr2=0.0,thr2=0.0;
  
  if(count2==0)
  {
      printf("Average Waiting time = %.2f\n",avgw2);
      printf("Average Turnaround time = %.2f\n",avgr2);
      printf("Average Response time= %.2f\n",avgw2);
      printf("Throughput = %.4f \n ",thr2*100);
  }
  else
  {
    for(int p=0;p<count2;p++)
    {
        avgw2= avgw2 +(float)aw2[p];
        avgr2= avgr2 + (float)aw2[p] + (float)r2[p];
    }
    float total2=0.0;
    total2=a2[count2-1]+aw2[count2-1]+r2[count2-1]-a2[0]-aw2[0]; 
    thr2= (float)count2/total2;
    printf("Average Waiting time = %.2f\n",(float)avgw2/count2);
    printf("Average Turnaround time = %.2f\n",(float)avgr2/count2);
    printf("Average Response time= %.2f\n",(float)avgw2/count2);
    printf("Throughput = %.4f \n ",thr2*100);
  }
  
  
  
  printf("\n Queue 3 \n");
  printf("\n%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n","Process","Arrivaltime","Runtime","Priority","Waitingtime","Turnaround_time","Response_time");
  for(int i=0;i<count3;i++)
  {
      printf("P%-14d %-15d %-15d %-15d %-15d %-15d %-15d\n",q3[i],a3[i],r3[i],p3[i],aw3[i],aw3[i]+r3[i],aw3[i]); 
  }
  float avgw3=0.0,avgr3=0.0,thr3=0.0;
  if(count3==0)
  {
      printf("Average Waiting time = %.2f\n",avgw3);
      printf("Average Turnaround time = %.2f\n",avgr3);
      printf("Average Response time= %.2f\n",avgw3);
      printf("Throughput = %.4f \n ",thr3*100);
  }
  else
  {
    for(int p=0;p<count3;p++)
    {
        avgw3= avgw3 +(float)aw3[p];
        avgr3= avgr3 + (float)aw3[p] + (float)r3[p];
    }
    float total3=0.0;
    total3=a3[count3-1]+aw3[count3-1]+r3[count3-1]-a3[0]-aw3[0]; 
    thr3= (float)count3/total3;  
    printf("Average Waiting time = %.2f\n",(float)avgw3/count3);
    printf("Average Turnaround time = %.2f\n",(float)avgr3/count3);
    printf("Average Response time= %.2f\n",(float)avgw3/count3);
    printf("Throughput = %.4f \n ",thr3*100);
  }                      
             
  printf("\n Queue 4 \n");
  printf("\n%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n","Process","Arrivaltime","Runtime","Priority","Waitingtime","Turnaround_time","Response_time");
  for(int i=0;i<count4;i++)
  {
      printf("P%-14d %-15d %-15d %-15d %-15d %-15d %-15d\n",q4[i],a4[i],r4[i],p4[i],aw4[i],aw4[i]+r4[i],aw4[i]); 
  }
  float avgw4=0.0,avgr4=0.0,thr4=0.0;
  if(count4==0)
  {
      printf("Average Waiting time = %.2f\n",avgw4);
      printf("Average Turnaround time = %.2f\n",avgr4);
      printf("Average Response time= %.2f\n",avgw4);
      printf("Throughput = %.4f \n ",thr4*100);
  }
  else
  {
    for(int p=0;p<count4;p++)
    {
        avgw4= avgw4 +(float)aw4[p];
        avgr4= avgr4 + (float)aw4[p] + (float)r4[p];
    }
    float total4=0.0;
    total4=a4[count4-1]+aw4[count4-1]+r4[count4-1]-a4[0]-aw4[0]; 
    thr4= (float)count4/total4;
  
    printf("Average Waiting time = %.2f\n",(float)avgw4/count4);
    printf("Average Turnaround time = %.2f\n",(float)avgr4/count4);
    printf("Average Response time= %.2f\n",(float)avgw4/count4);
    printf("Throughput = %.4f \n ",thr4*100);
  }
  printf("\n TOtal output  \n");
  float tw,tt,tr,tth;
  tw=avgw1+avgw2+avgw3+avgw4;
  tt=avgr1+avgr2+avgr3+avgr4;
  tr=avgw1+avgw2+avgw3+avgw4;
  tth=(float)n/i;
  
  printf("Total Average Waiting time = %.2f\n",(float)tw/n);
  printf("Total Average Turnaround time = %.2f\n",(float)tt/n);
  printf("Total Average Response time= %.2f\n",(float)tr/n);
  printf("Total Throughput = %.4f \n ",tth*100);             
}








