﻿// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/***********************************************************************************
**
** TextData.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/

#include "stdafx.h"

CTextData::CTextData()
    : CRenderTextObject()
{
    DEBUG_TRACE_FUNCTION;
}

CTextData::CTextData(CTextData *obj)
    : Unicode(obj->Unicode)
    , Type(obj->Type)
    , Font(obj->Font)
    , Timer(obj->Timer)
    , Alpha(obj->Alpha)
{
    DEBUG_TRACE_FUNCTION;
    RealDrawX = obj->RealDrawX;
    RealDrawY = obj->RealDrawY;
    Color = obj->Color;
    Text = obj->Text;
    UnicodeText = obj->UnicodeText;
}

CTextData::~CTextData()
{
    DEBUG_TRACE_FUNCTION;
    m_Texture.Clear();
    Owner = nullptr;
}

bool CTextData::CanBeDrawedInJournalGump()
{
    DEBUG_TRACE_FUNCTION;
    bool result = true;

    switch (Type)
    {
        case TT_SYSTEM:
            result = g_JournalShowSystem;
            break;
        case TT_OBJECT:
            result = g_JournalShowObjects;
            break;
        case TT_CLIENT:
            result = g_JournalShowClient;
            break;
        default:
            break;
    }

    return result;
}

void CTextData::GenerateTexture(
    int maxWidth, ushort flags, TEXT_ALIGN_TYPE align, uchar cell, int font)
{
    DEBUG_TRACE_FUNCTION;
    if (Unicode)
    {
        if (font == -1)
            font = Font;

        g_FontManager.GenerateW(
            (uchar)font, m_Texture, UnicodeText, Color, cell, maxWidth, align, flags);
    }
    else
        g_FontManager.GenerateA((uchar)Font, m_Texture, Text, Color, maxWidth, align, flags);

    if (!m_Texture.Empty())
    {
        if (g_ConfigManager.ScaleSpeechDelay)
            Timer += (((4000 * m_Texture.LinesCount) * g_ConfigManager.SpeechDelay) / 100);
        else
        {
            uint delay =
                ((int64_t)((int64_t)5497558140000 * g_ConfigManager.SpeechDelay) >> 32) >> 5;
            Timer += (uint)((delay >> 31) + delay);
        }
    }
}

