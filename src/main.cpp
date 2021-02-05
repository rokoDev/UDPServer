#include <fmt/format.h>
#include <ndt/address.h>
#include <ndt/socket.h>
#include <ndt/udp.h>
#include <ndt/utils.h>
#include <ndt/version_info.h>

#include <iostream>
#include <string_view>

#include "server/version_info.h"

// Max length of buffer
constexpr ndt::dlen_t kBufSize = 512;

// The port on which to send data
constexpr uint16_t kPort = 8888;

int main(void)
{
    try
    {
        fmt::print("{}", server::version_info());
        fmt::print("{}", ndt::version_info());
        std::string userMsg;
        ndt::UDP::Socket s = ndt::UDP::Socket(ndt::UDP::V4(), kPort);
        ndt::Address sender;
        char buf[kBufSize] = {0};
        while (1)
        {
            fmt::print("\nWaiting for data...");
            // try to receive some data, this is a blocking call
            const std::size_t kRecievedLen = s.recvFrom(buf, kBufSize, sender);

            // print details of the the data received
            fmt::print("\n{} bytes received: {}", kRecievedLen,
                       fmt::format("{:.{}}", buf, kRecievedLen));

            // now reply the client with the same data
            const std::size_t kSentLen = s.sendTo(sender, buf, kRecievedLen);
            fmt::print("\n{} bytes sent\n", kSentLen);
        }
    }
    catch (const ndt::exception::RuntimeError &re)
    {
        std::cout << re;
    }
    catch (const ndt::exception::LogicError &le)
    {
        std::cout << le;
    }
    catch (std::exception &e)
    {
        fmt::print("Error: {}\n", e.what());
    }
    catch (...)
    {
        fmt::print("unknown error");
    }

    return 0;
}
