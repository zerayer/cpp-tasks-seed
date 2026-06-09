#ifndef BASE85ED_H
#define BASE85ED_H

#include <cstdint>
#include <vector>

/**
 * @namespace base85
 * @brief Utilities for Base85 coding of bytes
 */
namespace base85
{

/**
 * @brief Encodes bytes into a Base85.
 *
 * @param[in] bytes A vector containing the raw bytes.
 * @return std::vector A vector of Base85-encoded bytes.
 *
 * @see decode()
 */
std::vector<std::uint8_t> encode(std::vector<std::uint8_t> const& bytes);

/**
 * @brief Decodes Base85 to bytes.
 *
 * @param[in] b85str A vector containing Base85-encoded data.
 * @return std::vector The decoded bytes.
 *
 * @throws std::runtime_error if encoded data contains invalid characters.
 *
 * @see encode()
 */
std::vector<std::uint8_t> decode(std::vector<std::uint8_t> const& b85str);

} // namespace base85

#endif // BASE85ED_H
