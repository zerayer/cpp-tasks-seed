#include <algorithm>
#include <array>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

#include "base85ed.h"

namespace
{

constexpr std::uint32_t BYTE_BASE = 256;
constexpr std::uint32_t BASE85 = 85;
constexpr std::uint8_t INVALID_VALUE = 255;

constexpr char ALPHABET[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

std::array<std::uint8_t, BYTE_BASE> make_reverse_table()
{
    std::array<std::uint8_t, BYTE_BASE> table{};
    table.fill(INVALID_VALUE);

    for (std::uint8_t i = 0; i < BASE85; ++i)
    {
        table[static_cast<std::uint8_t>(ALPHABET[i])] = i;
    }

    return table;
}

std::array<std::uint8_t, BYTE_BASE> const REVERSE_TABLE = make_reverse_table();

} // namespace

std::vector<std::uint8_t> base85::encode(std::vector<std::uint8_t> const& bytes)
{
    std::vector<std::uint8_t> result;

    if (bytes.empty())
    {
        return result;
    }

    result.reserve((bytes.size() + 3) / 4 * 5);

    for (std::size_t i = 0; i < bytes.size(); i += 4)
    {
        std::uint32_t value = 0;
        std::size_t chunk_size = std::min<std::size_t>(4, bytes.size() - i);

        for (std::size_t j = 0; j < chunk_size; ++j)
        {
            value = value * BYTE_BASE + bytes[i + j];
        }

        for (std::size_t j = chunk_size; j < 4; ++j)
        {
            value *= BYTE_BASE;
        }

        std::array<std::uint8_t, 5> encoded{};

        for (int j = 4; j >= 0; --j)
        {
            encoded[static_cast<std::size_t>(j)] =
                static_cast<std::uint8_t>(ALPHABET[value % BASE85]);
            value /= BASE85;
        }

        std::size_t output_size = chunk_size + 1;
        result.insert(result.end(), encoded.begin(), encoded.begin() + output_size);
    }

    return result;
}

std::vector<std::uint8_t> base85::decode(std::vector<std::uint8_t> const& b85str)
{
    std::vector<std::uint8_t> result;

    if (b85str.empty())
    {
        return result;
    }

    result.reserve(b85str.size() / 5 * 4);

    for (std::size_t i = 0; i < b85str.size(); i += 5)
    {
        std::size_t chunk_size = std::min<std::size_t>(5, b85str.size() - i);
        std::array<std::uint8_t, 5> block{};

        for (std::size_t j = 0; j < chunk_size; ++j)
        {
            std::uint8_t symbol = b85str[i + j];

            if (REVERSE_TABLE[symbol] == INVALID_VALUE)
            {
                throw std::runtime_error("invalid Base85 character");
            }

            block[j] = symbol;
        }

        for (std::size_t j = chunk_size; j < 5; ++j)
        {
            block[j] = static_cast<std::uint8_t>(ALPHABET[84]);
        }

        std::uint64_t value = 0;

        for (std::size_t j = 0; j < 5; ++j)
        {
            value = value * BASE85 + REVERSE_TABLE[block[j]];
        }

        if (value > std::numeric_limits<std::uint32_t>::max())
        {
            throw std::runtime_error("invalid Base85 block");
        }

        std::array<std::uint8_t, 4> decoded{};

        for (int j = 3; j >= 0; --j)
        {
            decoded[static_cast<std::size_t>(j)] = static_cast<std::uint8_t>(value % BYTE_BASE);
            value /= BYTE_BASE;
        }

        std::size_t output_size = chunk_size - 1;
        result.insert(result.end(), decoded.begin(), decoded.begin() + output_size);
    }

    return result;
}
