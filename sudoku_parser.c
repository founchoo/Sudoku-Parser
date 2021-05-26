#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

int problem_map_001[9][9] =
{
	{3, 0, 0, 0, 6, 0, 0, 2, 5},
	{8, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 2, 0, 5, 0, 0, 0},
	{0, 0, 5, 0, 1, 0, 9, 0, 0},
	{6, 0, 0, 3, 9, 7, 0, 0, 8},
	{0, 0, 3, 0, 5, 0, 1, 0, 0},
	{0, 0, 0, 1, 0, 4, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 9},
	{4, 1, 0, 0, 7, 0, 0, 0, 6}
};

int problem_map_002[9][9] =
{
	{0, 0, 2, 7, 0, 8, 6, 0, 0},
	{0, 3, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 5, 0, 6, 0, 0, 0},
	{5, 0, 7, 0, 0, 0, 1, 0, 4},
	{0, 0, 0, 0, 4, 0, 0, 0, 0},
	{3, 0, 4, 0, 0, 0, 7, 0, 8},
	{0, 0, 0, 2, 0, 1, 0, 0, 0},
	{0, 2, 0, 0, 0, 0, 0, 6, 0},
	{0, 0, 8, 4, 0, 9, 5, 0, 0}
};

int problem_user_map[9][9] =
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

typedef struct Map
{
	int row_index;
	int column_index;
	int selectable_nums_index;
	int* selectable_nums;
	int selectable_nums_size;
} Map;

typedef struct Struct1
{
	int size;
	int* nums;
} Struct1;

bool all_value_equal_one(int* arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		if(arr[i] != 1)
		{
			return false;
		}
	}
	return true;
}

void initialize_array(int* arr, int arr_size, int Initial_value)
{
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = Initial_value;
	}
}

bool check_maps(int maps[9][9], int maps_size)
{
	int counter[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < maps_size; i++)
	{
		for (int j = 0; j < maps_size; j++)
		{
			for (int k = 0; k < maps_size; k++)
			{
				counter[maps[i][k] - 1]++;
			}
			if(!all_value_equal_one(counter, maps_size))
			{
				return false;
			}
			initialize_array(counter, maps_size, 0);
			for (int k = 0; k < maps_size; k++)
			{
				counter[maps[k][j] - 1]++;
			}
			if(!all_value_equal_one(counter, maps_size))
			{
				return false;
			}
			initialize_array(counter, maps_size, 0);
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					int value = maps[i / 3 * 3 + k][j / 3 * 3 + l];
					counter[maps[k][l] - 1]++;
				}
			}
			if(!all_value_equal_one(counter, maps_size))
			{
				return false;
			}
		}
	}
	return true;
}

bool contain(int* arr, int arrSize, int value)
{
	for (int i = 0; i < arrSize; i++)
	{
		if(arr[i] == value)
		{
			return true;
		}
	}
	return false;
}

void print_map(int map[9][9], int map_size)
{
	for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

Struct1 get_selectable_nums_and_size(int map[9][9], int row_index, int column_index)
{
	int seletable_nums[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 9; i++)
	{
		if(i == column_index)
		{
			continue;
		}
		if(map[row_index][i] != 0)
		{
			seletable_nums[map[row_index][i] - 1]++;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if(i == row_index)
		{
			continue;
		}
		if(map[i][column_index] != 0)
		{
			seletable_nums[map[i][column_index] - 1]++;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int value = map[row_index / 3 * 3 + i][column_index / 3 * 3 + j];
			if(row_index / 3 * 3 + i == row_index && column_index / 3 * 3 + j == column_index)
			{
				continue;
			}
			if(value != 0)
			{
				seletable_nums[value - 1]++;
			}
		}
	}
	int return_size = 0;
	for (int i = 0; i < 9; i++)
	{
		if(seletable_nums[i] == 0)
		{
			return_size++;
		}
	}
	int* return_nums = (int*)malloc(sizeof(int) * return_size);
	int index = 0;
	for (int i = 0; i < 9; i++)
	{
		if(seletable_nums[i] == 0)
		{
			return_nums[index] = i + 1;
			index++;
		}
	}
	Struct1 str = 
	{
		index,
		return_nums
	};
	return str;
}

void fill_user_map(int map[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			problem_user_map[i][j] = map[i][j];
		}
	}
}

int main()
{
	time_t start_time = time(NULL);
	int length = 9;
	/*printf("Please input the problem map:");
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			scanf("%d", problem_user_map[i][j]);
		}
	}*/
	fill_user_map(problem_map_002);
	int counts = 0;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if(problem_user_map[i][j] == 0)
			{
				counts++;
			}
		}
	}
	int index = 0;
	Map* map = (Map*)malloc(sizeof(Map) * counts);
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if(problem_user_map[i][j] == 0)
			{
				map[index].row_index = i;
				map[index].column_index = j;
				map[index].selectable_nums_index = -1;
				map[index].selectable_nums = NULL;
				index++;
			}
		}
	}
	int c = 0;
	for (int i = 0; i < counts; i++)
	{
		c++;
		if(map[i].selectable_nums == NULL)
		{
			Struct1 str = get_selectable_nums_and_size(problem_user_map, map[i].row_index, map[i].column_index);
			map[i].selectable_nums_index = -1;
			if(str.size == 0)
			{
				problem_user_map[map[i].row_index][map[i].column_index] = 0;
				i -= 2;
				continue;
			}
			else
			{
				map[i].selectable_nums = str.nums;
				map[i].selectable_nums_size = str.size;
				problem_user_map[map[i].row_index][map[i].column_index] = map[i].selectable_nums[0];
			}
		}
		//达到备选数字的最后索引
		if(map[i].selectable_nums_index == map[i].selectable_nums_size - 1)
		{
			map[i].selectable_nums_index = -1;
			map[i].selectable_nums = NULL;
			problem_user_map[map[i].row_index][map[i].column_index] = 0;
			i -= 2;
		}
		else
		{
			map[i].selectable_nums_index++;
			problem_user_map[map[i].row_index][map[i].column_index] = map[i].selectable_nums[map[i].selectable_nums_index];
		}
	}
	time_t end_time = time(NULL);
	printf("循环次数：%d\n", c);
	printf("总运行时间：%lld\n", end_time - start_time);
	print_map(problem_user_map, length);
}