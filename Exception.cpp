#include "Exception.h"

ReadError::ReadError() : runtime_error("File read error."){}

AddressError::AddressError() : runtime_error("Invalid address."){}

ParamError::ParamError() : runtime_error("Invalid parameter."){}

InstError::InstError() : runtime_error("Invalid instruction."){}

UndefLabel::UndefLabel() : runtime_error("Undefined Label."){}

VonError::VonError() : runtime_error("Von Neumann error."){}

JmpError::JmpError() : runtime_error("Jump error."){}

DepthError::DepthError() : runtime_error("Jump error."){}