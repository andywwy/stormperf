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
// Generated from file `BackgroundSaveEvictor.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Freeze_BackgroundSaveEvictor_h__
#define __Freeze_BackgroundSaveEvictor_h__

#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <IceUtil/ScopedArray.h>
#include <IceUtil/Optional.h>
#include <Freeze/Evictor.h>
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

#ifndef FREEZE_API
#   ifdef FREEZE_API_EXPORTS
#       define FREEZE_API ICE_DECLSPEC_EXPORT
#   else
#       define FREEZE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace Freeze
{

class BackgroundSaveEvictor;
bool operator==(const BackgroundSaveEvictor&, const BackgroundSaveEvictor&);
bool operator<(const BackgroundSaveEvictor&, const BackgroundSaveEvictor&);
FREEZE_API ::Ice::LocalObject* upCast(::Freeze::BackgroundSaveEvictor*);
typedef ::IceInternal::Handle< ::Freeze::BackgroundSaveEvictor> BackgroundSaveEvictorPtr;

}

namespace Freeze
{

class FREEZE_API BackgroundSaveEvictor : virtual public ::Freeze::Evictor
{
public:

    typedef BackgroundSaveEvictorPtr PointerType;

    virtual void keep(const ::Ice::Identity&) = 0;

    virtual void keepFacet(const ::Ice::Identity&, const ::std::string&) = 0;

    virtual void release(const ::Ice::Identity&) = 0;

    virtual void releaseFacet(const ::Ice::Identity&, const ::std::string&) = 0;
};

inline bool operator==(const BackgroundSaveEvictor& l, const BackgroundSaveEvictor& r)
{
    return static_cast<const ::Ice::LocalObject&>(l) == static_cast<const ::Ice::LocalObject&>(r);
}

inline bool operator<(const BackgroundSaveEvictor& l, const BackgroundSaveEvictor& r)
{
    return static_cast<const ::Ice::LocalObject&>(l) < static_cast<const ::Ice::LocalObject&>(r);
}

}

#endif