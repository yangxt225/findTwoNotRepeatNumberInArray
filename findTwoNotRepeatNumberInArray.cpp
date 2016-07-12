#include <iostream>
//在一个数组中除两个数字只出现1次外，其它数字都出现了2次， 要求尽快找出这两个数字.
#define MAX 1024

void findTwoNotRepeatNumberInArray(int array[], int num, int *p1, int *p2)
{
	int temp, i, j;
	for(i=0; i<num; ++i)
		temp = temp^array[i];

	for(j=0; j<sizeof(int)*8; ++j)
		if((temp>>j & 1) == 1)
			break;
	
	*p1 = 0, *p2 = 0;
	for(i=0; i<num; ++i)
	{
		if(((array[i]>>j) & 1) == 0)
			*p1 ^= array[i];
		else
			*p2 ^= array[i];
	}
}

int main()
{	
	int len = 16;
	int array[16] = {2, 4, 65, 7, 23, 4, 54, 41, 67, 86, 7, 54, 2, 65, 86, 67}; // 23 41
	int num1, num2;
	for(int i=0; i<len; ++i)
	{
		std::cout << array[i] << ", ";
	}
	findTwoNotRepeatNumberInArray(array, len, &num1, &num2);

	std::cout << "\ntwo not repeat numbers is: " << num1 << ", " << num2 << std::endl;
	return 0;
}


