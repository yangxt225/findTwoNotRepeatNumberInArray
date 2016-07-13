#include <iostream>
//在一个数组中除三个数字,假设为a, b, c 只出现1次外，其它数字都出现了2次， 要求尽快找出这三个数字.
#define MAX 1024

// Method1
void findTwoUniqueNumber(int array[], int num, int *p2, int *p3)
{
	int XORTwo=0, i, j;
	for(i=0; i<num; ++i)
		XORTwo = XORTwo ^ array[i];

	for(j=0; j<sizeof(int)*8; ++j)
		if((XORTwo>>j & 1) == 1)
			break;
	
	*p2 = 0, *p3 = 0;
	for(i=0; i<num; ++i)
	{
		if(((array[i]>>j) & 1) == 0)
			*p2 ^= array[i];
		else
			*p3 ^= array[i];
	}
}

// 保留数字number的二进制表示中的最后一位1，而把其他所有位都变成0
int lastBitOf1(int number)
{
	return number & ~(number-1);
}

// Method2
void findTwoUniqueNumber2(int array[], int num, int *p2, int *p3)
{
	int xorTwo = 0, i;
	for(i=0; i<num; ++i)
		xorTwo ^= array[i];
	
	int flag = lastBitOf1(xorTwo);

	*p2 = 0, *p3 = 0;
	for(i=0; i<num; ++i)
	{
		if(array[i] & flag)
			*p2 ^= array[i];
		else
			*p3 ^= array[i];
	}
}

// 
void findThreeUniqueNumber(int array[], int num, int *p1, int *p2, int *p3)
{
	if(num<3) return;

	int xorResult=0, i;
	for(i=0; i<num; ++i)
		xorResult ^= array[i];
	
	int flags=0;
	// XORResult = f(XORThree^a) ^ f(XORThree^b) ^ f(XORThree^c)
	for(i=0; i<num; ++i)
		flags ^= lastBitOf1(xorResult ^ array[i]);

	flags = lastBitOf1(flags);
	
	*p1 = 0;
	for(i=0; i<num; ++i)
	{
		if(lastBitOf1(array[i] ^ xorResult) == flags)
		{
			// (假设这里找到的第1个唯一数就是a)除了a之外,也可能有其他数(不唯一),也满足"(lastBitOf1(array[i] ^ xorResult) == flags)"
			// 故而,这里不能使用"*p1 = array[i];"赋值语句而应该使用"异或"操作;同时,也就不能在第1次满足此条件就break.
			*p1 ^= array[i];
		}
	}

	// 将找到的第一个数放到数组的最后
	for(i=0; i<num; ++i)
	{
		if(array[i] == *p1)
		{
			array[i] = array[num-1];
			array[num-1] = *p1;
			break;
		}
	}

	//findTwoUniqueNumber(array, num-1, p2, p3);
	findTwoUniqueNumber2(array, num-1, p2, p3);
}

int main()
{	
	int len = 17;
	int array[17] = {2, 4, 65, 7, 23, 4, 54, 41, 67, 86, 7, 99, 54, 2, 65, 86, 67}; // 23 41 99
	int num1, num2, num3;
	for(int i=0; i<len; ++i)
	{
		std::cout << array[i] << ", ";
	}
	findThreeUniqueNumber(array, len, &num1, &num2, &num3);
	//findTwoUniqueNumber(array, len, &num1, &num2);

	std::cout << "\nthree not repeat numbers is: " << num1 << ", " << num2 << ", " << num3 << std::endl;
	return 0;
}


