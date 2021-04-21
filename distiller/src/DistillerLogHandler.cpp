#include <Arduino.h>

#include "DistillerLogHandler.h"

/** description of the @ref ERROR base level */
const char rf24logLevelError[] = "ERROR";
/** description of the @ref WARN base level */
const char rf24logLevelWarn[] = " WARN";
/** description of the @ref INFO base level */
const char rf24logLevelInfo[] = " INFO";
/** description of the @ref DEBUG base level */
const char rf24logLevelDebug[] = "DEBUG";
/** collection of the base level descriptions */
const char *const rf24LogLevels[] =
{ rf24logLevelError, rf24logLevelWarn, rf24logLevelInfo, rf24logLevelDebug };

DistillerLogHandler::DistillerLogHandler(Print *stream)
{
    this->stream = stream;
}

void DistillerLogHandler::write(uint8_t logLevel, const char *vendorId,
        const char *message, va_list *args)
{
    appendTimestamp();
    stream->print(" ");

    appendLogLevel(logLevel);
    stream->print(" ");

    appendVendorId(vendorId);
    stream->print(" ");

    // print formatted message
    appendFormattedMessage(message, args);
    stream->println("");
}

void DistillerLogHandler::appendTimestamp()
{
    char c[12];
    sprintf(c, "%10lu", millis());
    stream->print(c);
}

void DistillerLogHandler::appendLogLevel(uint8_t logLevel)
{
    if (logLevel >= RF24LogLevel::ERROR && logLevel <= RF24LogLevel::DEBUG + 7)
    {
        uint8_t logIndex = ((logLevel & 0x38) >> 3) - 1;
        stream->print(rf24LogLevels[logIndex]);

        return;
    }

    stream->print("     ");
}

void DistillerLogHandler::appendVendorId(const char *vendorId)
{
    stream->print('[');
    stream->print(vendorId);
    stream->print(']');
}

void DistillerLogHandler::appendFormattedMessage(const char *format, va_list *args)
{
    for (; *format != 0; ++format)
    {
        if (*format == '%')
        {
            ++format;
            appendFormat(*format, args);
        }
        else
        {
            stream->print(*format);
        }
    }
}

void DistillerLogHandler::appendFormat(const char format, va_list *args)
{
    if (format == 's')
    {
        // print text from RAM
        register char *s = (char*) va_arg(*args, int);
        stream->print(s);

        return;
    }

    if (format == 'D' || format == 'F')
    {
        // print as double
        stream->print(va_arg(*args, double));

        return;
    }

    if (format == 'd' || format == 'i')
    {
        // print as integer
        stream->print(va_arg(*args, int), DEC);

        return;
    }

    stream->print(format);
}
