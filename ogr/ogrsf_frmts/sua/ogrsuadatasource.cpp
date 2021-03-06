/******************************************************************************
 *
 * Project:  SUA Translator
 * Purpose:  Implements OGRSUADataSource class
 * Author:   Even Rouault, even dot rouault at spatialys.com
 *
 ******************************************************************************
 * Copyright (c) 2010, Even Rouault <even dot rouault at spatialys.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#include "ogr_sua.h"
#include "cpl_conv.h"
#include "cpl_string.h"

CPL_CVSID("$Id: ogrsuadatasource.cpp 355b41831cd2685c85d1aabe5b95665a2c6e99b7 2019-06-19 17:07:04 +0200 Even Rouault $")

/************************************************************************/
/*                          OGRSUADataSource()                          */
/************************************************************************/

OGRSUADataSource::OGRSUADataSource() :
    pszName(nullptr),
    papoLayers(nullptr),
    nLayers(0)
{}

/************************************************************************/
/*                         ~OGRSUADataSource()                          */
/************************************************************************/

OGRSUADataSource::~OGRSUADataSource()

{
    for( int i = 0; i < nLayers; i++ )
        delete papoLayers[i];
    CPLFree( papoLayers );

    CPLFree( pszName );
}

/************************************************************************/
/*                           TestCapability()                           */
/************************************************************************/

int OGRSUADataSource::TestCapability( CPL_UNUSED const char * pszCap )
{
    return FALSE;
}

/************************************************************************/
/*                              GetLayer()                              */
/************************************************************************/

OGRLayer *OGRSUADataSource::GetLayer( int iLayer )

{
    if( iLayer < 0 || iLayer >= nLayers )
        return nullptr;
    else
        return papoLayers[iLayer];
}

/************************************************************************/
/*                                Open()                                */
/************************************************************************/

int OGRSUADataSource::Open( const char * pszFilename )

{
    pszName = CPLStrdup( pszFilename );

    VSILFILE* fp = VSIFOpenL(pszFilename, "rb");
    if (fp == nullptr)
        return FALSE;

    nLayers = 1;
    papoLayers = (OGRLayer**) CPLMalloc(sizeof(OGRLayer*));
    papoLayers[0] = new OGRSUALayer(fp);

    return TRUE;
}
