#ifndef VECTORSINK_CXX
#define VECTORSINK_CXX

#include <algorithm>
#include <vector>

#include <fmt/format.h>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/synchronous_factory.h>
#include <iostream>

namespace car::system::logging
{
	template <typename Mutex>
	class VectorSink : public spdlog::sinks::base_sink<Mutex>
	{
	public:
		VectorSink(int max_lines) : max_lines(max_lines)
		{
		}

		void sink_it_(const spdlog::details::log_msg &msg) override
		{
			spdlog::memory_buf_t formatted;
			spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
			if (this->log_messages.size() < this->max_lines)
			{
				this->log_messages.push_back(std::string(formatted.data(), formatted.size()));
			}
			else
			{
				std::rotate(this->log_messages.begin(), this->log_messages.begin() + 1, this->log_messages.end());
				this->log_messages[this->log_messages.size() - 1] = std::string(formatted.data(), formatted.size());
			}
		};

		void flush_() override
		{
			this->log_messages.clear();
		};

		const std::vector<std::string> &get_log_messages() const
		{
			return this->log_messages;
		}

	private:
		const int max_lines;

		std::vector<std::string> log_messages;
	};
	using vector_sink_mt = VectorSink<std::mutex>;
}

#endif