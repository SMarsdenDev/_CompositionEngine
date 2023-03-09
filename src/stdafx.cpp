#include "stdafx.h"

namespace _CompositionEngine
{

    void PrintOpenGLError(int err_code)
    {
        switch (err_code)
        {
        case(GL_INVALID_ENUM):
        {
            LOG_ERROR(R"(An unacceptable value is specified 
    		for an enumerated argument. The offending command 
    		is ignored and has no other side effect than to 
    		set the error flag.)");
            break;
        }
        case(GL_INVALID_VALUE):
        {
            LOG_ERROR(R"(A numeric argument is out of range. 
    		The offending command is ignored and has no 
    		other side effect than to set the error flag.)");
            break;
        }
        case(GL_INVALID_OPERATION):
        {
            LOG_ERROR(R"(The specified operation is not allowed 
    		in the current state. The offending command is 
    		ignored and has no other side effect than to set 
    		the error flag.)");
            break;
        }
        case(GL_OUT_OF_MEMORY):
        {
            LOG_ERROR(R"(There is not enough memory left to 
    		execute the command. The state of the GL is 
    		undefined, except for the state of the error 
    		flags, after this error is recorded.)");
            break;
        }
        case(GL_STACK_UNDERFLOW):
        {
            LOG_ERROR(R"(An attempt has been made to perform an 
    		operation that would cause an internal stack to 
    		underflow.)");
            break;
        }
        case(GL_STACK_OVERFLOW):
        {
            LOG_ERROR(R"(An attempt has been made to perform an 
    		operation that would cause an internal stack to 
    		overflow.)");
            break;
        }
        }
    }
    void CheckOpenGLErrors()
    {
        int err = glGetError();
        while (err != GL_NO_ERROR)
        {
            PrintOpenGLError(err);
            err = glGetError();
        }
    }
}