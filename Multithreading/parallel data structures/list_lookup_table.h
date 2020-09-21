#ifndef _LIST_LOOKUP_TABLE_H_
#define _LIST_LOOKUP_TABLE_H_

#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>

#define MIN(x, y) x > y ? y : x

namespace parallel
{
	template<typename KEY, typename VALUE, size_t CLUSTERS_COUNT, typename HASH = std::hash<KEY>>
	class list_lookup_table
	{
	private:

		class cluster_type
		{
		private:

			using cluster_value = std::pair<KEY, VALUE>;
			using cluster_data = std::list<cluster_value>;
			using cluster_iter = typename cluster_data::iterator;

		public:
			cluster_type() = default;
			~cluster_type() = default;

		private:

			cluster_iter _FindEntryByKey(const KEY& key)
			{
				return std::find_if(begin(_data), end(_data),
					[&](const cluster_value& value)
					{
						return value.first == key;
					});
			}

		public:

			VALUE GetValueByKey(const KEY& key, const VALUE& default_value)
			{
				std::shared_lock<std::shared_mutex> sl{ _mutex_data };
				auto data = _FindEntryByKey(key);
				if (data != end(_data)) {
					return data->second;
				}
				return default_value;
			}

			void AddOrUpdateByKey(const KEY& key, const VALUE& value)
			{
				std::lock_guard<std::shared_mutex> lg{ _mutex_data };
				auto found = _FindEntryByKey(key);
				if (found == end(_data)) {
					_data.push_back(cluster_value{ key, value });
				}
				else {
					found->second = value;
				}
			}

			void RemoveByKey(const KEY& key)
			{
				std::lock_guard<std::shared_mutex> lg{ _mutex_data };
				auto found = _FindEntryByKey(key);
				if (found != end(_data)) {
					_data.erase(found);
				}
			}

		private:
			cluster_data		_data{};
			std::shared_mutex	_mutex_data{};
		};

	public:
		list_lookup_table(const HASH& hash = HASH{})
			:_CLUSTERS_COUNT(CLUSTERS_COUNT),
			_clusters(_CLUSTERS_COUNT),
			_hasher(hash)
		{
			_Init();
		}
		list_lookup_table(const list_lookup_table&) = delete;
		list_lookup_table(list_lookup_table&&) = delete;
		list_lookup_table& operator=(const list_lookup_table&) = delete;
		list_lookup_table& operator=(list_lookup_table&&) = delete;
		~list_lookup_table() = default;

	private:

		void _Init()
		{
			for (size_t i = 0; i < _CLUSTERS_COUNT; i++)
			{
				_clusters[i].reset(new cluster_type{});
			}
		}

		cluster_type& _GetCluster(const KEY& key) const
		{
			size_t index = _hasher(key) % _CLUSTERS_COUNT;
			return *_clusters[index];
		}

	public:

		VALUE GetValue(const KEY& key, const VALUE& default_value = VALUE{})
		{
			return std::move(_GetCluster(key).GetValueByKey(key, default_value));
		}

		void AddOrUpdate(const KEY& key, const VALUE& value)
		{
			_GetCluster(key).AddOrUpdateByKey(key, value);
		}

		void Remove(const KEY& key)
		{
			_GetCluster(key).RemoveByKey(key);
		}

	private:
		const size_t								_CLUSTERS_COUNT{};
		std::vector<std::unique_ptr<cluster_type>>	_clusters{};
		HASH										_hasher{};
	};
};

#endif