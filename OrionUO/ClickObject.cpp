﻿// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/***********************************************************************************
**
** ClickObject.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/

#include "stdafx.h"

CClickObject g_ClickObject;

void CClickObject::Clear(CRenderObject *obj)
{
    DEBUG_TRACE_FUNCTION;
    if (obj == Object)
    {
        Object = nullptr;
        Gump = nullptr;
        Timer = 0;
        X = 0;
        Y = 0;
        Enabled = false;
        Page = 0;
    }
}

void CClickObject::Clear()
{
    DEBUG_TRACE_FUNCTION;
    Object = nullptr;
    Gump = nullptr;
    Timer = 0;
    //m_X = 0;
    //m_Y = 0;
    Enabled = false;
    Page = 0;
}

void CClickObject::Init(CRenderObject *obj, CGump *gump)
{
    DEBUG_TRACE_FUNCTION;
    Enabled = true;
    Object = obj;
    Gump = gump;
    Timer = 0;
    X = 0;
    Y = 0;
    Page = 0;
}

