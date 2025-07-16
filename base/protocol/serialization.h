#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__

#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include "protocol/protocal_define.h"

namespace Chat::Base {
using BufferT = std::vector<uint8_t>;

inline BufferT BuildMessage(MessageTypeT type) {
    BufferT ret(MESSAGE_HEAD_LEN);
    std::memcpy(ret.data(), &type, MESSAGE_HEAD_LEN);
    return ret;
}

inline BufferT BuildMessage(MessageTypeT type, const BufferT &payload) {
    BufferT ret(MESSAGE_HEAD_LEN + payload.size());

    std::memcpy(ret.data(), &type, MESSAGE_HEAD_LEN);
    std::memcpy(ret.data() + MESSAGE_HEAD_LEN, payload.data(), payload.size());

    return ret;
}

inline BufferT BuildResponseMessage(MessageTypeT type, uint8_t result) {
    BufferT ret(MESSAGE_HEAD_LEN + sizeof(result));
    std::memcpy(ret.data(), &type, MESSAGE_HEAD_LEN);
    std::memcpy(ret.data() + MESSAGE_HEAD_LEN, &result, sizeof(result));
    return ret;
}

namespace Detaile {

inline BufferT BuildMessageByString(MessageTypeT type, const std::string &str) {
    BufferT ret(MESSAGE_HEAD_LEN + str.size());

    std::memcpy(ret.data(), &type, MESSAGE_HEAD_LEN);
    std::memcpy(ret.data() + MESSAGE_HEAD_LEN, str.data(), str.size());

    return ret;
}
}  // namespace Detaile

inline BufferT BuildSignInMessage(MessageTypeT type, const std::string &name) {
    return Detaile::BuildMessageByString(type, name);
}

inline BufferT BuildVerifyPasswordMessage(MessageTypeT type, const std::string &password) {
    return Detaile::BuildMessageByString(type, password);
}

}  // namespace Chat::Base

#endif