#include <iostream>
#include <cassert>
#include <toml.hpp>

// Simple bubbling test from https://github.com/ToruNiina/toml11#finding-a-toml-value
// See another package named "toml11-tests" for complete testing.

template<typename TimeComponentType>
long long get_datetime_component(std::chrono::system_clock::time_point timepoint)
{
    auto time_since_1970 = timepoint.time_since_epoch();
    auto duration = std::chrono::duration_cast<TimeComponentType>(time_since_1970);
    return duration.count();
}

int main(int argc, char* argv[])
{
    try
    {
        char* toml_file_path = argv[1];
        const auto data      = toml::parse(toml_file_path);
        const auto answer    = toml::find<std::int64_t>(data, "answer");
        const auto pi        = toml::find<double>(data, "pi");
        const auto numbers   = toml::find<std::vector<int>>(data, "numbers");
        const auto timepoint = toml::find<std::chrono::system_clock::time_point>(data, "time");
        
        assert(answer == 42);
        assert(pi == 3.14);
        assert(numbers == std::vector<int>({1, 2, 3}));
        
        // 1979-05-27 07:32:00 UTC
        // hours
        assert(get_datetime_component<std::chrono::hours>(timepoint) % 24 == 7);
        // minutes
        assert(get_datetime_component<std::chrono::minutes>(timepoint) % 60 == 32);
        // seconds
        assert(get_datetime_component<std::chrono::seconds>(timepoint) % 60 == 0);
        // timestamp in seconds
        assert(get_datetime_component<std::chrono::seconds>(timepoint) == 296638320);
    }
    catch(std::runtime_error const& e)
    {
        assert(false);
    }
    return 0;
}