#include "jforge/attributes/stack/reader.hpp"

#include "jforge/util/file.hpp"

auto jforge::attributes::stack::readVerificationTypeInfo(
    std::istream& stream) -> std::expected<VerificationTypeInfo, std::string>
{
    VerificationTypeInfo info{};
    auto tag = verificationTypeFromNum(util::read_bytes_be<uint8_t>(stream));
    if (!tag) return std::unexpected(tag.error());
    info.tag = *tag;
    if (tag.value() == VerificationType::Object ||
        tag.value() == VerificationType::UninitializedVariable)
    {
        info.data = util::read_bytes_be<uint16_t>(stream);
    }
    return info;
}

auto jforge::attributes::stack::readFrame(std::istream& stream) -> std::expected<StackMapFrame, std::string>
{
    StackMapFrame frame;
    frame.frameType = util::read_bytes_be<uint8_t>(stream);
    switch (frameTypeFromNum(frame.frameType))
    {
    case FrameType::SameFrame: {
            frame.data = SameFrame{};
        } break;
    case FrameType::SameLocals1StackItemFrame: {
            auto verificationTypeInfo = readVerificationTypeInfo(stream);
            if (!verificationTypeInfo) return std::unexpected(verificationTypeInfo.error());
            frame.data = SameLocals1StackItemFrame{
                .type = std::move(*verificationTypeInfo)
            };
        } break;
    case FrameType::SameLocals1StackItemFrameExtended:
        {
            const auto offsetDelta = util::read_bytes_be<uint16_t>(stream);
            auto verificationTypeInfo = readVerificationTypeInfo(stream);
            if (!verificationTypeInfo) return std::unexpected(verificationTypeInfo.error());
            frame.data = SameLocals1StackItemFrameExtended{
                .offsetDelta = offsetDelta,
                .type = std::move(*verificationTypeInfo)
            };
        } break;
    case FrameType::ChopFrame: {
            frame.data = ChopFrame{
                .offsetDelta = util::read_bytes_be<uint16_t>(stream),
            };
        } break;
    case FrameType::SameFrameExtended: {
            frame.data = SameFrameExtended{
                .offsetDelta = util::read_bytes_be<uint16_t>(stream),
            };
        } break;
    case FrameType::AppendFrame: {
            AppendFrame appendFrame;
            appendFrame.offsetDelta = util::read_bytes_be<uint16_t>(stream);
            for (int i = 0; i < frame.frameType - 251; i++) {
                auto verificationTypeInfo = readVerificationTypeInfo(stream);
                if (!verificationTypeInfo) return std::unexpected(verificationTypeInfo.error());
                appendFrame.locals.push_back(std::move(*verificationTypeInfo));
            }
            frame.data = std::move(appendFrame);
        } break;
    case FrameType::FullFrame: {
            FullFrame fullFrame;
            fullFrame.offsetDelta = util::read_bytes_be<uint16_t>(stream);

            const auto numLocals = util::read_bytes_be<uint16_t>(stream);
            for (int i = 0; i < numLocals; i++) {
                auto verificationTypeInfo = readVerificationTypeInfo(stream);
                if (!verificationTypeInfo) return std::unexpected(verificationTypeInfo.error());
                fullFrame.locals.push_back(std::move(*verificationTypeInfo));
            }

            const auto numStackItems = util::read_bytes_be<uint16_t>(stream);
            for (int i = 0; i < numStackItems; i++) {
                auto verificationTypeInfo = readVerificationTypeInfo(stream);
                if (!verificationTypeInfo) return std::unexpected(verificationTypeInfo.error());
                fullFrame.stack.push_back(std::move(*verificationTypeInfo));
            }
            frame.data = std::move(fullFrame);
        } break;
    case FrameType::Reserved:
        return std::unexpected(std::format("Encountered reserved frame type {}", frame.frameType));
    }
    return frame;
}
