#ifndef _LOOKUP_TABLE_H_
#define _LOOKUP_TABLE_H_

#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <map>
#include <unordered_map>

#define MIN(x, y) x > y ? y : x

namespace parallel 
{
	template<typename KEY, typename VALUE, size_t CL_COUNT = 19, typename HASH = std::hash<KEY>>
	class lookup_table
	{
	public:
		lookup_table()
			:CLUSTERS_COUNT(MIN(10, CL_COUNT))
		{
			_Init();
		}

		~lookup_table() = default;

	public:

		size_t GetClustersCount() const { return CLUSTERS_COUNT; }

	private:

		void _Init() 
		{
			for (size_t i = 0; i < CLUSTERS_COUNT; i++)
			{
				_data[i];
				_data_mutex[i];
			}
		}

	private:
		const size_t										CLUSTERS_COUNT;
		HASH												_hasher;
		std::map<size_t, std::unordered_map<KEY, VALUE>>	_data;
		mutable std::map<size_t, std::mutex>				_data_mutex;
	};

};

#endif // !_LOOKUP_TABLE_H_

