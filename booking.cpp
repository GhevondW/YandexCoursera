#if 0
#if 0
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <queue>


struct Action
{
    int64_t time;
    std::string hotel;
    int client;
    int rooms_count;
};


class HotelManager
{
public:
    HotelManager() : _current_time(0){}

    void Book(const int64_t& time, const std::string& hotel_name,
        const int& client_id, const int& room_count)
    {
        _current_time = time;

        if (_events.empty())
        {
            inserter(time, hotel_name, client_id, room_count);
        }
        else
        {
            deleter(time, hotel_name, client_id, room_count);

            inserter(time, hotel_name, client_id, room_count);
        }
    }

    int64_t Clients(const std::string& hotel_name) const
    {
        if (_hotel_to_clients.count(hotel_name) == 0)
        {
            return 0;
        }

        return _hotel_to_clients.at(hotel_name).size();
    }

    int64_t Rooms(const std::string& hotel_name) const
    {
        if (_hotel_to_rooms.count(hotel_name) == 0)
        {
            return 0;
        }

        return _hotel_to_rooms.at(hotel_name);
    }

private:
    void inserter(const int64_t& time, const std::string& hotel_name,
        const int& client_id, const int& room_count)
    {
        _events.push({ time, hotel_name, client_id, room_count });
        _hotel_to_clients[hotel_name].insert(client_id);
        _hotel_to_rooms[hotel_name] += room_count;
    }

    void deleter(const int64_t& time, const std::string& hotel_name,
        const int& client_id, const int& room_count)
    {
        auto event_ = _events.front();

        while (true)
        {
            if (event_.time > (_current_time - sec))
            {
                break;
            }
            
            
            _hotel_to_clients.at(event_.hotel).erase(event_.client);
            _hotel_to_rooms.at(event_.hotel) -= event_.rooms_count;
            _events.pop();

            if (_events.empty())
            {
                break;
            }

            event_ = _events.front();
        }
    }
private:
    int64_t _current_time;
    std::queue<Action> _events;
    std::unordered_map<std::string, std::unordered_set<int>> _hotel_to_clients;
    std::unordered_map<std::string, int> _hotel_to_rooms;

    static const int64_t sec = 86400;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    HotelManager hotel_manager;
    int q;
    std::string command, hotel_name;
    int64_t time;
    int client_id;
    int room_count;
    std::cin >> q;
    for (int i = 0; i < q; ++i)
    {
        std::cin >> command;
        if (command == "BOOK")
        {
            std::cin >> time >> hotel_name >> client_id >> room_count;
            hotel_manager.Book(time, hotel_name, client_id, room_count);
        }
        if (command == "CLIENTS")
        {
            std::cin >> hotel_name;
            std::cout << hotel_manager.Clients(hotel_name) << "\n";
        }
        if (command == "ROOMS")
        {
            std::cin >> hotel_name;
            std::cout << hotel_manager.Rooms(hotel_name) << "\n";
        }
    }
    return 0;
}
#endif

#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

using namespace std;


class HotelManager {
public:
  void Book(int64_t time, const string& hotel_name,
            int client_id, int room_count) {
    current_time_ = time;
    hotels_[hotel_name].Book({time, client_id, room_count});
  }
  int ComputeClientCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeClientCount(current_time_);
  }
  int ComputeRoomCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeRoomCount(current_time_);
  }

private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };

  class HotelInfo {
  public:
    void Book(const Booking& booking) {
      last_bookings_.push(booking);
      room_count_ += booking.room_count;
      ++client_booking_counts_[booking.client_id];
    }
    int ComputeClientCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return client_booking_counts_.size();
    }
    int ComputeRoomCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return room_count_;
    }
  private:
    static const int TIME_WINDOW_SIZE = 86400;
    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;

    void PopBooking() {
      const Booking& booking = last_bookings_.front();
      room_count_ -= booking.room_count;
      const auto client_stat_it =
          client_booking_counts_.find(booking.client_id);
      if (--client_stat_it->second == 0) {
        client_booking_counts_.erase(client_stat_it);
      }
      last_bookings_.pop();
    }
    void RemoveOldBookings(int64_t current_time) {
      while (
          !last_bookings_.empty()
          && last_bookings_.front().time
             <= current_time - TIME_WINDOW_SIZE
      ) {
        PopBooking();
      }
    }
  };

  int64_t current_time_ = 0;
  map<string, HotelInfo> hotels_;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  HotelManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
      cin >> time;
      string hotel_name;
      cin >> hotel_name;
      int client_id, room_count;
      cin >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);
    } else {
      string hotel_name;
      cin >> hotel_name;
      if (query_type == "CLIENTS") {
        cout << manager.ComputeClientCount(hotel_name) << "\n";
      } else if (query_type == "ROOMS") {
        cout << manager.ComputeRoomCount(hotel_name) << "\n";
      }
    }
  }

  return 0;
}
#endif
