#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

void swap1(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition1 (int *arr, int low, int high,int *rrr,int *prr,int *srr)
{
    int pivot = arr[high];   
    int i = (low - 1); 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;    
          swap1(&arr[i], &arr[j]);
          swap1(&rrr[i], &rrr[j]);
          swap1(&prr[i], &prr[j]);
          swap1(&srr[i], &srr[j]);
        }
    }

    swap1(&arr[i + 1], &arr[high]);
    swap1(&rrr[i+1], &rrr[high]);
        swap1(&prr[i+1], &prr[high]);
        swap1(&srr[i+1], &srr[high]);
    return (i + 1);
}

void quickSort1(int *arr, int low, int high,int *rrr,int *prr,int *srr)
{
    if (low < high)
    {
        
        int pi = partition1(arr, low, high,rrr,prr,srr);

        quickSort1(arr, low, pi - 1,rrr,prr,srr);
        quickSort1(arr, pi + 1, high,rrr,prr,srr);
    }
}

void FCFS(int num)
{
  int n,*a,*r,*p,*s,*aw;
    n=num;
    a=(int *)malloc(n*sizeof(int));
    r=(int *)malloc(n*sizeof(int));
    p=(int *)malloc(n*sizeof(int));
    s=(int *)malloc(n*sizeof(int));
    aw=(int *)malloc(n*sizeof(int));
    
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

  quickSort1(a,0,n-1,r,p,s);    //sorting jobs based on arrival time
  
  for (int j=0;j<n;j++)       // sorting jobs based on priority for the jobs with same arrival time.
  {

    for(int k=0;k<n;k++)
    {
      if ( a[j] == a[k] && j!=k)
      {
        if(p[k]>p[j])
        {
          swap1(&a[j], &a[k]);
          swap1(&r[j], &r[k]);
          swap1(&p[j], &p[k]);
          swap1(&s[j], &s[k]);
        }
      }
    }
  }

   for (int j=0;j<n;j++)
    {
       printf("P%-3d %-4d %-4d %-4d \n",s[j],a[j],r[j],p[j]);
    }

    printf("\n");
   
    int job=0,i=0,jobs_done=0,count=0;
    while(job<n)      // First come first serve process execution
    {
        if(a[job]<100 && job<=n-1)
        {
          if( a[job]==i || a[job]<i)
          {
            if ( a[job]<i)
            {
                aw[job]= i-a[job];
            }
            else
            {
                aw[job]= 0;
            }
            for (int j=0;j<r[job];j++)
            {
    if((count%10) ==0) printf("\n");
                printf("%-3d --> P%-3d  ",j+i,s[job]);
    count++;
            }
              i=i+r[job]-1;
              job++;
              jobs_done++;
          }
          else
          {
      if((count%10) ==0) printf("\n");
            printf("%-3d --> IDLE  ",i);
      count++;
          }
        }
        else
        {
            job++;
        }
      i++;
    }
    i--;
   printf("\n");
   printf("\n%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n","Process","Arrivaltime","Runtime","Priority","Waitingtime","Turnaround_time","Response_time");
   for (int j=0;j<n;j++)
   {
      printf("P%-14d %-15d %-15d %-15d %-15d %-15d %-15d\n",s[j],a[j],r[j],p[j],aw[j],aw[j]+r[j],aw[j]);
   }

  float avgw=0.0,avgr=0.0,thr=0.0;
  for(int p=0;p<n;p++)
  {
    avgw= avgw +(float)aw[p];
    avgr= avgr + (float)aw[p] + (float)r[p];
  }

  avgw=(float)avgw/jobs_done;
  avgr=(float)avgr/jobs_done;
  thr= (float)jobs_done/i;
  printf("Average Waiting time = %.2f\n",avgw);
  printf("Average Turnaround time = %.2f\n",avgr);
  printf("Average Response time= %.2f\n",avgw);
  printf("Throughput = %.4f \n ",thr*100.0);
}

