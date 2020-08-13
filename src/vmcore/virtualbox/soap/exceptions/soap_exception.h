#ifndef SOAP_EXCEPTION_H
#define SOAP_EXCEPTION_H

#include "soapH.h"
#include "connection_exception.h"
#include "logon_exception.h"
#include <exception>
#include <stdexcept>

class exception_util{
public:
	static void  resolve_throw(int result, struct soap *obj){
		if(result == SOAP_OK) return;
		if(!obj) return;

		switch(result){
		case SOAP_TCP_ERROR:
			throw connection_exception(obj->fault->faultstring);
		break;
		}
	}
};

/* void resolve_soap_exception(int result, struct soap *obj){
	if(result == SOAP_OK) return;
	if(!obj) return;
	
	switch(result){
		case SOAP_TCP_ERROR:
			throw new connection_exception(obj->fault->faultstring);
		break;
	}
} */

#endif