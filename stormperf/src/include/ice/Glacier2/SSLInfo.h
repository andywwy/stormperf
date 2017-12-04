// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.5.0
//
// <auto-generated>
//
// Generated from file `SSLInfo.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Glacier2_SSLInfo_h__
#define __Glacier2_SSLInfo_h__

#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <IceUtil/ScopedArray.h>
#include <IceUtil/Optional.h>
#include <Ice/BuiltinSequences.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 305
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

#ifndef GLACIER2_API
#   ifdef GLACIER2_API_EXPORTS
#       define GLACIER2_API ICE_DECLSPEC_EXPORT
#   else
#       define GLACIER2_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace Glacier2
{

struct SSLInfo
{
    ::std::string remoteHost;
    ::Ice::Int remotePort;
    ::std::string localHost;
    ::Ice::Int localPort;
    ::std::string cipher;
    ::Ice::StringSeq certs;
};

}

namespace Ice
{
template<>
struct StreamableTraits< ::Glacier2::SSLInfo>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 12;
    static const bool fixedLength = false;
};

template<class S>
struct StreamWriter< ::Glacier2::SSLInfo, S>
{
    static void write(S* __os, const ::Glacier2::SSLInfo& v)
    {
        __os->write(v.remoteHost);
        __os->write(v.remotePort);
        __os->write(v.localHost);
        __os->write(v.localPort);
        __os->write(v.cipher);
        __os->write(v.certs);
    }
};

template<class S>
struct StreamReader< ::Glacier2::SSLInfo, S>
{
    static void read(S* __is, ::Glacier2::SSLInfo& v)
    {
        __is->read(v.remoteHost);
        __is->read(v.remotePort);
        __is->read(v.localHost);
        __is->read(v.localPort);
        __is->read(v.cipher);
        __is->read(v.certs);
    }
};

#if defined(ICE_HAS_DECLSPEC_IMPORT_EXPORT) && !defined(GLACIER2_API_EXPORTS)
template struct GLACIER2_API StreamWriter< ::Glacier2::SSLInfo, ::IceInternal::BasicStream>;
template struct GLACIER2_API StreamReader< ::Glacier2::SSLInfo, ::IceInternal::BasicStream>;
#endif

}

#endif
