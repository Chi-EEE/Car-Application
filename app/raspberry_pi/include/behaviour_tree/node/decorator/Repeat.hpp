#ifndef BEHAVIOUR_TREE_REPEAT_HPP
#define BEHAVIOUR_TREE_REPEAT_HPP

#pragma once

#include "Decorator.hpp"

namespace behaviour_tree::node::decorator
{
	class Repeat : public Decorator
	{
	public:
		Repeat(const std::string& name, std::unique_ptr<Node> child, const int& count, const bool& break_on_fail) : Decorator(name, std::move(child)), count(count), break_on_fail(break_on_fail)
		{
		}

		const DecoratorType type() const override { return DecoratorType::Repeat; }

		const Status run(Context& context) override
		{
			spdlog::info("Running Repeat node {} times", this->getCount());
			for (int i = 0; i < this->count; i++)
			{
				auto status = this->child->run(context);
				switch (status)
				{
				case Status::Success:
					continue;
				case Status::Failure:
					if (this->break_on_fail)
					{
						return Status::Failure;
					}
					continue;
				}
			}
		}

		const std::string toString() const override {
			const std::string& name = this->getName();
			if (name != "")
				return fmt::format(R"(<Repeat name="{}" count="{}" break_on_fail="{}">{}</Repeat>)", name, this->getCount(), this->getBreakOnFail() ? "true" : "false", this->child->toString());
			else
				return fmt::format(R"(<Repeat count="{}" break_on_fail="{}">{}</Repeat>)", this->getCount(), this->getBreakOnFail() ? "true" : "false", this->child->toString());
		}

		const int& getCount() const {
			return this->count;
		}

		const bool& getBreakOnFail() const {
			return this->break_on_fail;
		}

	private:
		const int count;
		const bool break_on_fail;
	};
}

#endif