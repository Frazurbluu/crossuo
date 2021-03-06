﻿// MIT License
// Copyright (C) August 2016 Hotride

#ifndef NEW_RENDERER_ENABLED

#include "GUIBlending.h"
#include "../Utility/PerfMarker.h"

CGUIBlending::CGUIBlending(bool enabled, uint32_t sFactor, uint32_t dFactor)
    : CBaseGUI(GOT_BLENDING, 0, 0, 0, 0, 0)
    , SFactor(sFactor)
    , DFactor(dFactor)
{
    Enabled = enabled;
}

CGUIBlending::~CGUIBlending()
{
}

void CGUIBlending::Draw(bool checktrans)
{
    ScopedPerfMarker(__FUNCTION__);
    if (Enabled)
    {
        glEnable(GL_BLEND);
        glBlendFunc(SFactor, DFactor);
    }
    else
    {
        glDisable(GL_BLEND);
    }
}

#endif // #ifndef NEW_RENDERER_ENABLED
