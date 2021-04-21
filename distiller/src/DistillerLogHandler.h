#ifndef SRC_DISTILLERLOGHANDLER_H_
#define SRC_DISTILLERLOGHANDLER_H_

#include <handlers/RF24AbstractLogHandler.h>
#include <Print.h>

/**
 * A log handler implementation which outputs log messages to a stream.
 */
class DistillerLogHandler : public RF24AbstractLogHandler
{
protected:

    /** The output stream */
    Print *stream;

public:

    /**
     * @brief instance constructor
     * @param stream The output stream to which logging messages are directed.
     */
    DistillerLogHandler(Print *stream);

protected:
    void write(uint8_t logLevel, const char *vendorId, const char *message,
            va_list *args);

    /** @brief output a timestamp */
    void appendTimestamp();

    /**
     * @brief output a description of the log level
     * @param logLevel The level to describe.
     */
    void appendLogLevel(uint8_t logLevel);

    /**
     * @brief output a origin of the message
     * @param vendorId The origin name.
     */
    void appendVendorId(const char *vendorId);

    /**
     * @brief output a message with the specifiers replaced with values from the sequence of @p args
     * @param format The format of the message
     * @param args The sequence of args
     */
    void appendFormattedMessage(const char *format, va_list *args);

    /**
     * @brief output a message with the specifiers replaced with values from the sequence of @p args
     * @param format The format of the message
     * @param args The sequence of args
     */
    void appendFormat(const char format, va_list *args);
};

#endif /* SRC_DISTILLERLOGHANDLER_H_ */
