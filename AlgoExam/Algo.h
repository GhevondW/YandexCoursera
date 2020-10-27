#ifndef _ALGO_H_
#define _ALGO_H_

#include <vector>

namespace algo
{

	template<typename T, typename FunctionCond>
	void BubbleSort(std::vector<T>& const data, FunctionCond cond)
	{
		for (size_t i = 0; i < data.size() - 1; i++)
		{
			for (size_t j = 0; j < data.size() - i - 1; j++)
			{
				if (cond(data[j], data[j + 1])) {
					T tmp = std::move(data[j]);
					data[j] = std::move(data[j + 1]);
					data[j + 1] = std::move(tmp);
				}
			}
		}
	}

	template<typename T, typename FunctionCond>
	void InsertionSort(std::vector<T>& const data, FunctionCond cond)
	{
		for (size_t i = 1; i < data.size(); ++i)
		{
			for (size_t j = i; j > 0; --j)
			{
				if (cond(data[j - 1], data[j])) {
					T tmp = std::move(data[j]);
					data[j] = std::move(data[j - 1]);
					data[j - 1] = std::move(tmp);
				}
				else
				{
					break;
				}
			}
		}
	}

	template<typename T, typename FunctionCond>
	size_t FindIndex(std::vector<T>& const data, size_t begin, size_t end, FunctionCond cond)
	{
		if (begin > end) throw "invalid parameters";;
		if (begin < 0 || begin >= data.size()) throw "invalid parameters";
		if (end < 0 || end >= data.size()) throw "invalid parameters";

		T copy = data[begin];
		size_t ret = begin;
		for (size_t i = begin + 1; i <= end; i++)
		{
			if (cond(copy, data[i])) {
				copy = data[i];
				ret = i;
			}
		}
		
		return ret;
	}

	template<typename T, typename FunctionCond>
	void SelectionSort(std::vector<T>& const data, FunctionCond cond)
	{
		for (size_t i = 0; i < data.size() - 1; i++)
		{
			auto index = FindIndex(data, i, data.size() - 1, cond);
			T tmp = std::move(data[i]);
			data[i] = std::move(data[index]);
			data[index] = std::move(tmp);
		}
	}

	template<typename T>
	int _BinarySearch(std::vector<T>& const data, size_t left, size_t right, const T& value)
	{
		if (right >= left) {
			int mid = left + (right - left) / 2;

			if (data[mid] == value)
				return mid;

			if (data[mid] > value)
				return _BinarySearch(data, left, mid - 1, value);

			return _BinarySearch(data, mid + 1, right, value);
		}

		return -1;
	}

	template<typename T>
	int BinarySearch(std::vector<T>& const data, const T& value)
	{
		if (data.empty()) throw "invalid argument";
		return _BinarySearch(data, 0, data.size() - 1, value);
	}

};

#endif // !_ALGO_H_

