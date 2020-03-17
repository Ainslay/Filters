#pragma once
#include <iostream>
#include <string>

class Exception
{
private:
	int m_ErrorCode;
	std::string m_ErrorMessage;

public:
	Exception() = delete;

	Exception(int errorCode, std::string errorMessage)
	{
		m_ErrorCode = errorCode;
		m_ErrorMessage = errorMessage;
	}

	void PrintInfo()
	{
		std::cout << "ERROR " << m_ErrorCode << ": " << m_ErrorMessage << std::endl;
	}

	const int& GetErrorCode() { return m_ErrorCode; }
	const int& GetErrorMessage() { return m_ErrorCode; }
};

