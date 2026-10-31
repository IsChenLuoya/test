

long calculate(unsigned long a[],unsigned char b[])
{
	unsigned char j;
	unsigned char i=0;
	unsigned char count=0;
	long sum=0;
	while(i<8)
	{
		if(b[i]==3)
		{
			a[i]=a[i]*a[i+1];
			for(j=i+1;j<7;j++)
			{
				a[j]=a[j+1];
				b[j-1]=b[j];
			}
			a[7-count]=0;
			b[6-count]=0;
			count++;
			continue;
		}
		if(b[i]==4)
		{
			a[i]=a[i]/a[i+1];
			for(j=i+1;j<7;j++)
			{
				a[j]=a[j+1];
				b[j-1]=b[j];
			}
			a[7-count]=0;
			b[6-count]=0;
			count++;
			continue;
		}
		i++;
	}
	sum=a[0];
		for(i=0;i<7;i++)
		{
			
			if(b[i]==1)
			{
				sum+=a[i+1];
			}
			if(b[i]==2)
			{
				sum-=a[i+1];
			}
	  }
	return sum;
}