#include <regex>
#include <iomanip>
#include "CalculatorController.h"
#include "boost/format.hpp"

namespace
{
	const std::string REGEX_COMMAND = R"((var|let|fn|printvars|printfns|print))";
	const std::string REGEX_IDENTIFIER_OR_DOUBLE = R"(([0-9\.]+|[\w]+)?)";
	const std::string REGEX_IDENTIFIER = R"(([\w]+)?)";
	const std::string REGEX_OPERATION = R"((\+|-|\*|\/)?)";
	const std::string REGEX_SPACE = R"( ?)";

	ÑFunction::Operation ToOperation(std::string const& operation)
	{
		if (operation == "+") return ÑFunction::Operation::Add;
		if (operation == "-") return ÑFunction::Operation::Sub;
		if (operation == "*") return ÑFunction::Operation::Mult;
		if (operation == "/") return ÑFunction::Operation::Div;
		return ÑFunction::Operation::None;
	}

	bool ParseCommand(std::string commandFromUser, Arguments& arguments)
	{
		std::string regexStr;

		try
		{
			regexStr = (boost::format("^%s%s%s%s%s%s%s%s%s$") % REGEX_COMMAND % REGEX_SPACE % REGEX_IDENTIFIER % R"( ?=? ?)" % REGEX_IDENTIFIER_OR_DOUBLE % REGEX_SPACE % REGEX_OPERATION % REGEX_SPACE % REGEX_IDENTIFIER).str();
		}
		catch (boost::io::format_error&)
		{
			return false;
		}

		std::regex regex(regexStr, std::regex_constants::icase);
		std::smatch match;

		if (!std::regex_match(commandFromUser, match, regex)) return false;
		
		try
		{
			arguments.command = std::string(match[1]);

			if (!arguments.command.has_value()) return false;

			arguments.identifier1 = std::string(match[2]);
			arguments.identifier2 = std::string(match[3]);
			arguments.operation = ToOperation(std::string(match[4]));
			arguments.identifier3 = std::string(match[5]);
			return true;
		}
		catch (std::exception const&)
		{
			return false;
		}
	}
}

CCalculatorController::CCalculatorController(CCalculator& calc, std::istream& input, std::ostream& output)
	:m_calc(calc), m_input(input), m_output(output),
	m_actionMap(
	{
		{ "var", bind(&CCalculatorController::Var, this, std::placeholders::_1) },
		{ "let", bind(&CCalculatorController::Let, this, std::placeholders::_1) },
		{ "fn", bind(&CCalculatorController::Fn, this, std::placeholders::_1) },
		{ "print", bind(&CCalculatorController::Print, this, std::placeholders::_1) },
		{ "printvars", bind(&CCalculatorController::Printvars, this, std::placeholders::_1) },
		{ "printfns", bind(&CCalculatorController::Printfns, this, std::placeholders::_1) }
	})
{
}

bool CCalculatorController::HandleCommand()
{
	std::string commandFromUser;
	std::getline(m_input, commandFromUser);

	Arguments argv;
	if (!ParseCommand(commandFromUser, argv)) return false;

	if (auto const& it = m_actionMap.find(argv.command.value()); it != m_actionMap.end())
	{
		try
		{
			it->second(argv);
			return true;
		}
		catch (std::exception const& error)
		{
			m_output << termcolor::red << "Error: " << error.what() << termcolor::reset << std::endl;
			return true;
		}
	}

	return false;
}

void CCalculatorController::Var(Arguments const& commandFromUser)
{
	m_calc.SetVariable(commandFromUser.identifier1.value());
}

void CCalculatorController::Let(Arguments const& commandFromUser)
{
	std::string identifier1 = commandFromUser.identifier1.value();
	std::string identifier2 = commandFromUser.identifier2.value();
	std::istringstream sstream(identifier2);

	double value;
	if (sstream >> value and sstream.eof())
	{
		m_calc.SetValueToVariable(identifier1, value);
	}
	else
	{
		m_calc.SetValueToVariable(identifier1, identifier2);
	}
}

void CCalculatorController::Fn(Arguments const& commandFromUser)
{
	std::string identifier1 = commandFromUser.identifier1.value();
	std::string identifier2 = commandFromUser.identifier2.value();
	ÑFunction::Operation operation = commandFromUser.operation;
	std::string identifier3 = commandFromUser.identifier3.value();

	if (operation != ÑFunction::Operation::None)
	{
		m_calc.SetFunction(identifier1, identifier2, operation, identifier3);
	}
	else
	{
		m_calc.SetFunction(identifier1, identifier2);
	}
}

void CCalculatorController::PrintOptionalValue(std::optional<double> value)
{
	if (value.has_value())
	{
		m_output << std::fixed << std::setprecision(2) << value.value() << std::endl;
	}
	else
	{
		m_output << "nan" << std::endl;
	}
}

void CCalculatorController::PrintValues(CCalculator::Values const& values)
{
	for (auto const& [identifier, value] : values)
	{
		m_output << identifier << ":";
		PrintOptionalValue(value);
	}
}

void CCalculatorController::Print(Arguments const& commandFromUser)
{
	PrintOptionalValue(m_calc.GetValue(commandFromUser.identifier1.value()));
}

void CCalculatorController::Printvars(Arguments const& commandFromUser)
{
	PrintValues(m_calc.GetValuesOfVariables());
}

void CCalculatorController::Printfns(Arguments const& commandFromUser)
{
	PrintValues(m_calc.GetValuesOfFunctions());
}
