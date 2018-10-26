﻿// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/***********************************************************************************
**
** GUIShader.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/

#include "stdafx.h"

CGUIShader::CGUIShader(CGLShader *shader, bool enabled)
    : CBaseGUI(GOT_SHADER, 0, 0, 0, 0, 0)
    , m_Shader(shader)
{
    Enabled = enabled;
}

CGUIShader::~CGUIShader()
{
}

void CGUIShader::Draw(bool checktrans)
{
    DEBUG_TRACE_FUNCTION;
    if (Enabled && m_Shader != nullptr)
        m_Shader->Use();
    else
        UnuseShader();
}

