#pragma once

#include <iostream>

namespace COMMAND {
	void help(void) noexcept;
	void start_scan(const char* IP, int TARGET_PORT, int THREAD_NUMBER, int MAX_RANGE);
}
