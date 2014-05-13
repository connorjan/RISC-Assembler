#include "Exception.h"

ReadError::ReadError() : runtime_error("File read error."){}

AddressError::AddressError() : runtime_error("Invalid address."){}

ParamError::ParamError() : runtime_error("Invalid parameter."){}

InstError::InstError() : runtime_error("Invalid instruction."){}