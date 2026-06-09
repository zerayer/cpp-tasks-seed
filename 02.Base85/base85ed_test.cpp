#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#include "base85ed.h"

using Bytes = std::vector<std::uint8_t>;

static Bytes string_to_bytes(std::string const& str)
{
    return Bytes(str.begin(), str.end());
}

static Bytes make_random_bytes(std::size_t size)
{
    Bytes data(size);

    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(0, 255);

    for (auto& item : data)
    {
        item = static_cast<std::uint8_t>(distribution(generator));
    }

    return data;
}

TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    std::vector<std::pair<std::string, std::string>> cases;

    cases.push_back(std::make_pair("", ""));
    cases.push_back(std::make_pair("F#", "1"));
    cases.push_back(std::make_pair("F){", "12"));
    cases.push_back(std::make_pair("F)}j", "123"));
    cases.push_back(std::make_pair("F)}kW", "1234"));

    for (auto const& item : cases)
    {
        EXPECT_EQ(base85::encode(string_to_bytes(item.second)), string_to_bytes(item.first));
    }
}

TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    std::vector<std::pair<std::string, std::string>> cases;

    cases.push_back(std::make_pair("", ""));
    cases.push_back(std::make_pair("F#", "1"));
    cases.push_back(std::make_pair("F){", "12"));
    cases.push_back(std::make_pair("F)}j", "123"));
    cases.push_back(std::make_pair("F)}kW", "1234"));

    for (auto const& item : cases)
    {
        EXPECT_EQ(base85::decode(string_to_bytes(item.first)), string_to_bytes(item.second));
    }
}

TEST(Base85RoundTrip, DifferentSizes)
{
    std::vector<std::size_t> sizes;

    sizes.push_back(0);
    sizes.push_back(1);
    sizes.push_back(2);
    sizes.push_back(3);
    sizes.push_back(4);
    sizes.push_back(5);
    sizes.push_back(10);
    sizes.push_back(100);
    sizes.push_back(1000);
    sizes.push_back(4096);

    for (std::size_t size : sizes)
    {
        Bytes data = make_random_bytes(size);
        Bytes encoded = base85::encode(data);
        Bytes decoded = base85::decode(encoded);

        EXPECT_EQ(decoded, data);
    }
}

TEST(Base85RoundTrip, TextData)
{
    Bytes data = string_to_bytes("Hello, Base85 encoding and decoding!");

    Bytes encoded = base85::encode(data);
    Bytes decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85Decode, InvalidCharacter)
{
    Bytes encoded = string_to_bytes("abc\"");

    EXPECT_THROW(base85::decode(encoded), std::runtime_error);
}
