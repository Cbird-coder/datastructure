#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define ARR_LEN 1000


void swapdata(int arr[],int i,int j)
{
	int temp;

	temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
}

void print_arr(int arr[],double time,int length)
{
	int i;
	for(i=0;i<length;i++)
		printf("%d\t",arr[i]);
	printf("\nrunning time:%.10lf s\n",time);
}

int bubble_rank1(int arr[],int length)
{
	int i,j;

	for(i=0;i<length;i++)
	{
		for(j=i+1;j<length;j++)//��i�������е�����Ԫ�ؽ�����ȣ��ҳ�������С��Ԫ��
		{
			if(arr[i]>arr[j])
				swapdata(arr,i,j);
		}
	}
	return 1;
}

int bubble_rank2(int arr[],int length)
{
	int i,j;
	int	flag=2;//���õı��λ�����ҳ�ʼ��Ϊ2

	for(i=0;i<length && flag;i++)//��flag=0���򲻽��б������������Լ��ٱȽ���������еı�������
	{                            //����2,1,3,4,5,6,7,8����������һ�ο��Եõ�������������Ĳ���Ҫ�ı���
		flag=0;                  //flagΪ0����ʾ����δ���б������˴���i�����Ԫ�ؾ��������                  

		for(j=length-2;j>=i;j--)
		{
			if(arr[j]>arr[j+1])  //����Ѱ����С��Ԫ��
			{
			   swapdata(arr,j,j+1);
				flag=1;          //������н��й��䶯
			}
		}
	}
	return 1;
}

int selectsort(int arr[],int length)
{
	int i,j;
	int minflag;   //������СԪ�صı��λ

	for(i=0;i<length;i++)
	{
		minflag=i;         //���Ϊ��ǰ��i

		for(j=i+1;j<length;j++)
		{
			if(arr[minflag]>arr[j])  //Ѱ����С��Ԫ��
				minflag=j;           //������С���λ
		}
		if(i!=minflag)               //��С���λ�Ƿ����ı�
			 swapdata(arr,i,minflag);
	}
	return 1;
}

int insertsort(int arr[],int length)//��������
{
	int i,j;
	int temp;

	for(i=1;i<length;i++)
	{
		if(arr[i-1]>arr[i])//���������н�С��Ԫ��
		{
			temp=arr[i];   //���ý������ݣ���ֵ������Ԫ�ظ�temp
			for(j=i;arr[j-1]>temp;j--)  //����a[i]���Ԫ�������λ,1`i�γ����������
				arr[j]=arr[j-1];
			            
			arr[j]=temp; //����ֵ�����ʵ�λ��
		}
	}
	return 1;
}

void shellsort(int arr[],int length)
{
	int i,j;
	int increasment=length;
	int temp;

	do
	{
		increasment=increasment/2;
		for(i=increasment;i<length;i++)
		{
			if(arr[i]<arr[i-increasment])
			{
			 	temp=arr[i];
				for(j=i-increasment;j>=0 && temp<arr[j];j-=increasment)
					arr[j+increasment]=arr[j];
				arr[j+increasment]=temp;
			}
		}
	}while(increasment>0);
}

/******heap sort*********/
void heapcreat(int arr[],int begin,int end)
{
	int temp,j;

	temp=arr[begin];
	for(j=2*begin+1;j<=end;j=j*2)
	{
		if(j<end && arr[j] < arr[j+1])
			++j;
		if(temp>=arr[j])
			break;
		arr[begin]=arr[j];
		begin=j;
	}
	arr[begin]=temp;
}
void heapsort(int arr[],int length)
{
	int i;
	int end;

	end = length-1;

	for(i=end/2;i>=0;i--)
		heapcreat(arr,i,end);
	for(i=end;i>0;i--)
	{
		swapdata(arr,0,i);
		heapcreat(arr,0,i-1);
	}
}
/*merge sort*/
void merge(int arr[],int tmp[],int begin,int mid,int end)
{
	int i,j,k;

    k=i=begin;       //ǰ�벿�ֵ���ʼ���i����mid����
	j=mid+1;         //��벿�ֵı��j����end����
	while(j<=end && i<=mid) //ǰ�벿�����벿�־�δ����ĩβ����ʼ�ϲ�ǰ��������
	{
		if(arr[i]<arr[j])   //  ǰ�벿��Ԫ�ؽ�С�����뵽�ݴ�����tmp��
			tmp[k++]=arr[i++];
		else
			tmp[k++]=arr[j++]; //��벿��С�����뵽�ݴ�����tmp��
	}
	while(i<=mid)             //���ǰ�벿����Ԫ���ձ���ں�벿��Ԫ�أ���i��Ȼδ����mid����Ҫ��ʣ�µ�Ԫ����ӵ�tmp������
		tmp[k++]=arr[i++];
	while(j<=end)           //�����벿���е�Ԫ���ձ����ǰ�벿��Ԫ�أ���jδ����end����Ҫ��ʣ�µ�Ԫ�����tmp�У�������Ҫע�����׷��Ԫ��ʱֻ�����������
		tmp[k++]=arr[j++];

	for(i=begin;i<=end;i++) //����tmp�е�Ԫ�ص�arr�У���ɹ鲢��
		arr[i]=tmp[i];
}

/*void mergesort(int arr[],int tmp[],int begin,int end)
{
    int mid,i;

    if(begin<end)
    {
        mid=(begin+end)/2;
        mergesort(arr,tmp,begin,mid);//ǰ�벿�ֹ鲢����
        mergesort(arr,tmp,mid+1,end);//��벿�ֹ鲢����

        merge(arr,tmp,begin,mid,end);//�鲢ǰ�������ֺϲ�������arr�С�
    }
}
void m_sort(int arr[],int length)
{
		int *tmp;
	    tmp=(int*)malloc(length*sizeof(int));
	    if(tmp==NULL)
	    {
		  printf("out of memery!\n");
		  return;
	     }
         mergesort(arr,tmp,0,length-1);
		 free(tmp);
}*/
void mergesort_norecurse(int arr[],int tmp[],int step,int end)
{
	int i=0,j=0;

	while(i<=end-2*step+1)
	{
		merge(arr,tmp,i,i+step-1,i+2*step-1);
		i=i+2*step;
	}
	if(i<end-step+1)//ʣ�����д�������
        merge(arr,tmp,i,i+step-1,end);
	else
		for(j=i;j<end;j++)
			tmp[j]=arr[j];
}
void m_sort_norecurse(int arr[],int length)
{
		int *tmp;
		int step=1;
	    tmp=(int*)malloc(length*sizeof(int));
	    if(tmp==NULL)
	    {
		  printf("out of memery!\n");
		  return;
	     }
		while(step<length-1)
		{
         mergesort_norecurse(arr,tmp,step,length-1);
		 step=step*2;
		}
		 free(tmp);
}
/*fast sort*/

int find_key(int arr[],int low,int high)
{
	int key;
	key=arr[low];
	int tempdata;

	while(low<high)
	{
		while(low<high && arr[high]>key)
			high--;
		swapdata(low,high);
		while(low<high && arr[low]<key)
			low++;
		swapdata(low,high);
	}
	return low;
}

void fast_sort(int arr[],int low,int high)
{
	int keylocation;

	if(low<high)
	{
       keylocation=find_key(arr,low,high);
       fast_sort(arr,low,keylocation);
       fast_sort(arr,keylocation+1,high);
	}
}

void Qsort(int arr[],int length)
{
	fast_sort(arr,0,length-1);
}


int main()
{
	srand((unsigned int)time(NULL));
	int a[ARR_LEN],i;
    double  time=0;
	time_t begin,end;
	for(i=0;i<ARR_LEN;i++)
	{
		a[i]=rand()%1000;
	}
	//int b[10]={2,3,4,7,3,1,8,3,9,21};
    begin = clock();
    m_sort_norecurse(a,ARR_LEN);
	end = clock();
    time=double(end - begin)/CLOCKS_PER_SEC;
	print_arr(a,time,ARR_LEN);
}