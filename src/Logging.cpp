// GPLv3
// Copyright (c) 2019 Danny Angelo Carminati Grein

#include "Logging.h"

#if !defined(DISABLE_LOG)

#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <cstdarg>
#include <external/loguru.h>

eLogSystem g_LogEnabled = LogSystemAll;

#define LOG_SYSTEM(id, name) LOG_DECLARE_SYSTEM(name)
#include "Loggers.h"
#undef LOG_SYSTEM

void uo_log(int type, const char *sys, const char *fmt, ...)
{
    char msg[512] = {};
    va_list vargs;
    va_start(vargs, fmt);
    vsnprintf(msg, 512, fmt, vargs);
    va_end(vargs);
    switch (type)
    {
        case 1:
            TRACE(XUOCore, "%s: %s", sys, msg);
            break;
        case 2:
            DEBUG(XUOCore, "%s: %s", sys, msg);
            break;
        case 3:
            Info(XUOCore, "%s: %s", sys, msg);
            break;
        case 4:
            Warning(XUOCore, "%s: %s", sys, msg);
            break;
        case 5:
            Error(XUOCore, "%s: %s", sys, msg);
            break;
    }
}

const char *log_system_name(int sys)
{
    switch (sys)
    {
#define LOG_SYSTEM(id, name)                                                                       \
    case eLogSystem::LogSystem##name:                                                              \
        return TOSTRING(name);
#include "Loggers.h"
#undef LOG_SYSTEM
        default:
            break;
    }
    return "Unknown";
}

void LogInit(int argc, char *argv[], const char *filename)
{
    loguru::g_stderr_verbosity = 1;
    loguru::init(argc, argv);
    loguru::add_file(filename, loguru::Truncate, loguru::Verbosity_INFO);
    loguru::g_preamble_date = false;
    loguru::g_preamble_time = false;

#define LOG_SYSTEM(id, name) LOG_DEFINE_SYSTEM(name)
#include "Loggers.h"
#undef LOG_SYSTEM
}

void LogHexBuffer(eLogSystem sys, int level, const char *title, uint8_t *buf, int size)
{
    auto logger = g_logClient;
    switch (sys)
    {
#define LOG_SYSTEM(id, name)                                                                       \
    case eLogSystem::LogSystem##name:                                                              \
        logger = g_log##name;                                                                      \
        break;
#include "Loggers.h"
#undef LOG_SYSTEM
        default:
            break;
    }

    if (title && title[0] != '\0')
    {
        VLOG_F(sys, level, "%s", title);
    }
    int num_lines = size / 16;
    if (size % 16 != 0)
    {
        num_lines++;
    }

    for (int line = 0; line < num_lines; line++)
    {
        char out[128];
        char *cur = out;
        char *end = cur + sizeof(out);
        int row = 0;
        int r = 0;
        r = snprintf(cur, end - cur, "%04X: ", line * 16);
        assert(r >= 0 && r < end - cur && end - cur >= 0);
        cur += r;
        for (row = 0; row < 16; row++)
        {
            if (line * 16 + row < size)
            {
                r = snprintf(cur, end - cur, "%02X ", buf[line * 16 + row]);
                assert(r >= 0 && r < end - cur && end - cur >= 0);
                cur += r;
            }
            else
            {
                r = snprintf(cur, end - cur, "-- ");
                assert(r >= 0 && r < end - cur && end - cur >= 0);
                cur += r;
            }
        }
        r = snprintf(cur, end - cur, ": ");
        assert(r >= 0 && r < end - cur && end - cur >= 0);
        cur += r;
        for (row = 0; row < 16; row++)
        {
            if (line * 16 + row < size)
            {
                const char ch = isprint(buf[line * 16 + row]) != 0 ? buf[line * 16 + row] : '.';
                r = snprintf(cur, end - cur, ch == '%' ? "%c%%" : "%c", ch);
                assert(r >= 0);
                assert(r < end - cur);
                assert(end - cur >= 0);
                cur += r;
            }
        }
        VLOG_F(sys, level, "%s", out);
    }
}

#else

void LogInit(const char *filename)
{
}
void LogHexBuffer(eLogSystem sys, int level, const char *title, uint8_t *buf, int size)
{
}
void uo_log(int type, const char *sys, const char *fmt, ...)
{
}
#endif
