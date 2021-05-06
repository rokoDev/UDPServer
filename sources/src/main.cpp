#include <fmt/format.h>
#include <ndt/core.h>
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
        ndt::Context<ndt::System> ctx;
        ndt::UDP::Socket s = ndt::UDP::Socket(ctx, ndt::UDP::V4(), kPort);
        ndt::Address sender;
        char buf[kBufSize] = {0};
        ndt::Buffer recvBuf(buf);
        while (1)
        {
            fmt::print("\nWaiting for data...");
            // try to receive some data, this is a blocking call
            const std::size_t kRecievedLen = s.recvFrom(recvBuf, sender);

            // print details of the the data received
            fmt::print("\n{} bytes received: {}", kRecievedLen,
                       fmt::format("{:.{}}", buf, kRecievedLen));

            // now reply the client with the same data
            const std::size_t kSentLen = s.sendTo(sender, ndt::CBuffer(buf));
            fmt::print("\n{} bytes sent\n", kSentLen);
        }
    }
    catch (const ndt::Error &e)
    {
        fmt::print("ndt::Error >> code: {}. reason: {}\n", e.code().value(),
                   e.what());
    }
    catch (std::exception &e)
    {
        fmt::print("Error >> reason: {}\n", e.what());
    }
    catch (...)
    {
        fmt::print("unknown error");
    }

    return 0;
}
