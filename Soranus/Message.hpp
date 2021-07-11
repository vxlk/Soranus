
#include <stdexcept>

namespace Message {

enum class ReturnCode {
	Okay = 0,
	ExceptionError = 1
};

struct ReturnCodeException {
	void operator()(ReturnCode ret) {
		std::string message;
		switch (ret) {
			case ReturnCode::ExceptionError: message = "Generic Exception Thrown";
		}
		throw std::runtime_error(message.c_str());
	}
};

} // Message