#ifndef STREXCEPTION_HPP
#define STREXCEPTION_HPP

#include <sstream>
#include <comdef.h>
#include <d3dcompiler.h>

class StrException : public std::exception
{
private:
	std::string msg;

	void hresult_handle(const std::string &msg, HRESULT &hr)
	{
		std::ostringstream stream;
		_com_error err(hr);
		stream << msg << std::endl << err.ErrorMessage();
		this->msg = stream.str();
		exception(this->msg.c_str());
	}

	void blob_handle(const std::string &msg, ID3DBlob *err_blob)
	{
		std::ostringstream stream;
		stream << msg << std::endl << static_cast<char*>(err_blob->GetBufferPointer());
		this->msg = stream.str();
		exception(this->msg.c_str());
	}
public:
	StrException(const std::string &msg)
	{
		this->msg = msg;
		exception(this->msg.c_str());
	}
	StrException(const std::string &msg, HRESULT &hr)
	{
		this->hresult_handle(msg, hr);
	}
	StrException(const std::string &msg, ID3DBlob *err_blob)
	{
		this->blob_handle(msg, err_blob);
	}
	StrException(const std::string &msg, HRESULT &hr, ID3DBlob *err_blob)
	{
		if(err_blob)
			this->blob_handle(msg, err_blob);
		else
			this->hresult_handle(msg, hr);
	}
	virtual ~StrException()	{}

	const char *toCharStr()
	{
		return msg.c_str();
	}
};

#endif