#include <iostream>
#include <vector>

using namespace std;

class sudoku_parser_dll
{
private:
	void initialize_array(int* arr, int arr_size, int Initial_value);
	vector<int> get_selectable_nums(int map[9][9], int row_index, int column_index);
public:
	sudoku_parser_dll(/* args */);
	int** solve(int problem_map[9][9]);
	~sudoku_parser_dll();
};

sudoku_parser_dll::sudoku_parser_dll(/* args */)
{
}

sudoku_parser_dll::~sudoku_parser_dll()
{
}

typedef struct Map
{
	int row_index;
	int column_index;
	int selectable_nums_index;
	vector<int> selectable_nums;
} Map;

void sudoku_parser_dll::initialize_array(int* arr, int arr_size, int Initial_value)
{
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = Initial_value;
	}
}

vector<int> sudoku_parser_dll::get_selectable_nums(int map[9][9], int row_index, int column_index)
{
	int seletable_nums[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 9; i++)
	{
		if(map[row_index][i] != 0 && i != column_index)
		{
			seletable_nums[map[row_index][i] - 1]++;
		}
		if(map[i][column_index] != 0 && i != row_index)
		{
			seletable_nums[map[i][column_index] - 1]++;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int value = map[row_index / 3 * 3 + i][column_index / 3 * 3 + j];
			if(row_index / 3 * 3 + i != row_index && column_index / 3 * 3 + j != column_index && value != 0)
			{
				seletable_nums[value - 1]++;
			}
		}
	}
	vector<int> return_nums;
	int index = 0;
	for (int i = 0; i < 9; i++)
	{
		if(seletable_nums[i] == 0)
		{
			return_nums.push_back(i + 1);
		}
	}
	return return_nums;
}

int** sudoku_parser_dll::solve(int problem_user_map[9][9])
{
	int length = 9;
	vector<Map> map;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if(problem_user_map[i][j] == 0)
			{
				Map element = {i, j, -1, vector<int>{}};
				map.push_back(element);
			}
		}
	}
	for (int i = 0; i < map.size(); i++)
	{
		if(map[i].selectable_nums.size() == 0)
		{
			auto nums = get_selectable_nums(problem_user_map, map[i].row_index, map[i].column_index);
			map[i].selectable_nums_index = -1;
			if(nums.size() == 0)
			{
				problem_user_map[map[i].row_index][map[i].column_index] = 0;
				i -= 2;
				continue;
			}
			else
			{
				map[i].selectable_nums = nums;
				problem_user_map[map[i].row_index][map[i].column_index] = map[i].selectable_nums[0];
			}
		}
		if(map[i].selectable_nums_index == map[i].selectable_nums.size() - 1)
		{
			map[i].selectable_nums_index = -1;
			map[i].selectable_nums = vector<int>{};
			problem_user_map[map[i].row_index][map[i].column_index] = 0;
			i -= 2;
		}
		else
		{
			map[i].selectable_nums_index++;
			problem_user_map[map[i].row_index][map[i].column_index] = map[i].selectable_nums[map[i].selectable_nums_index];
		}
	}
	return (int**)problem_user_map;
}