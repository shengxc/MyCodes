/*
 * binary search
 * arr:		the search array
 * n:		size of arr
 * target:	the search target
 * mode:	
      1:the most left index
      2:the most right index
      3:random index(default)
 * retun: the idx that arr[idx] == target or -1 if there is not number in arr equals target
*/
template<typename T>
int binarysearch(const T* const arr,int n,const T& target,int mode = 3)
{
	int left(0),right(n - 1);
	int mid;
	while(left <= right)
	{
		mid = left + (right - left) / 2;
		if(target < arr[mid])
			right = mid - 1;
		else if(arr[mid] < target)
			left = mid + 1;
		else
		{
			switch(mode)
			{
			case 1:
				right = mid;
				while(left <= right)
				{
					mid = left + (right - left) / 2;
					if(arr[mid] < target)
						left = mid + 1;
					else
					{
						if(arr[mid - 1] == target)
							right = mid - 1;
						else
							break;
					}
				}
				break;
			case 2:
				left = mid;
				while(left <= right)
				{
					mid = left + (right - left) / 2;
					if(target < arr[mid])
						right = mid - 1;
					else
					{
						if(arr[mid + 1] == target)
							left = mid + 1;
						else
							break;
					}
				}
				break;
			default:
				break;
			}
			break;
		}
	}
	if(!(arr[mid] == target))
		mid = -1;
	return mid;
}
