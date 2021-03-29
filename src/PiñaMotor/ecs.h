#pragma once
#include <ctime>

namespace ecs {

	using CmpIdType = std::size_t;
	using HandlerIdType = std::size_t;

	enum CmpId : CmpIdType {
		Transform = 0,
		_LastCmptId_
	};

	constexpr std::size_t maxComponents = _LastCmptId_;
	constexpr std::size_t maxHandlers = _LastHndlrId_;
}
