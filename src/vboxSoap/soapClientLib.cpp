/* soapClientLib.cpp
   Generated by gSOAP 2.8.103 for vboxwebService.h

gSOAP XML Web services tools
Copyright (C) 2000-2020, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

/** Use this file in your project build instead of the two files soapC.cpp and soapClient.cpp. This hides the serializer functions by making them static, avoiding linking problems when linking multiple clients and servers. */

/* disable warnings for unused static functions defined in soapC.cpp */
#if defined(WIN32)
#pragma warning(disable:4505)
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"
#elif defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-function"
#endif
#define WITH_STATIC
#define SOAP_FMAC3 static
#include "soapC.cpp"
#include "soapClient.cpp"

/* End of soapClientLib.cpp */
