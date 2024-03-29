#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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

void initialize_array(int* arr, int arr_size, int Initial_value)
{
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = Initial_value;
	}
}

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

int main()
{
	int length = 9;
	int counts = 0;
	printf("Please input the problem map:\nNote: 9 lines, numbers in each line should be separated by one space\n");
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			scanf("%d[^\n]", &problem_user_map[i][j]);
			if(problem_user_map[i][j] != 0)
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
	for (int i = 0; i < counts; i++)
	{
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
	printf("-----------------\nSolution:\n");
	print_map(problem_user_map, length);
	system("pause");
}