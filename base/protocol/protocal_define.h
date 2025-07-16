#ifndef __PROTOCOL_DEFINE_H__
#define __PROTOCOL_DEFINE_H__

#include <cstddef>
#include <cstdint>

namespace Chat::Base {
using MessageTypeT = uint32_t;
inline constexpr size_t MESSAGE_HEAD_LEN = sizeof(MessageTypeT);

inline constexpr MessageTypeT HEARTBEAT = 0;
inline constexpr MessageTypeT TIMEOUT = 1;
// size(4) + data
inline constexpr MessageTypeT SIGN_IN_NAME = 2;
// 1 byte, 0 or 1
inline constexpr MessageTypeT SIGN_IN_NAME_RESPONSE = 3;
// size(4) + data
inline constexpr MessageTypeT VERIFY_PASSWORD = 4;
// 1 byte, 0 or 1
inline constexpr MessageTypeT VERIFY_PASSWORD_RESPONSE = 5;

}  // namespace Chat::Base

#endif
