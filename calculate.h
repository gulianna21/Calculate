#pragma once
#include <iostream>
#include <string>
#include <vector>


enum action
{
	ADD_TO_STACK = 1,
	GET_FROM_STACK,
	OUTPUT_BLOCK,
	END,
	ERROR
};

class Calculate
{
	std::string *npl;
public:
	Calculate()
	{
		npl = new std::string("");
	}

	~Calculate()
	{
		delete npl;
	}


	action getPrior(std::vector<char>& stack, char elem)
	{

		switch (elem)
		{
		case '+':
		case '-':
			if (stack.size() == 0 || stack.back() == '(')
				return ADD_TO_STACK;
			return GET_FROM_STACK;
				break;
		case '*':
		case '/':
		case '^':
			if (stack.size() == 0 || stack.back() == '(' || stack.back() == '+')
				return ADD_TO_STACK;
			return GET_FROM_STACK;
		case '(':
			return ADD_TO_STACK;
		case ')':
			if (stack.size() == 0)
				return ERROR;
			if (stack.back() == '(')
				return OUTPUT_BLOCK;
			return GET_FROM_STACK;
		default:
			return ERROR;
		}

	}


	//input = "124.2332 + 123.32423 / 123123 + (15.2323-16123)*25"
	std::string getNPL(std::string& input)
	{
		std::string digital = "";
		bool appendPointer = false;
		std::vector<char> *operators = new std::vector<char>;

		try
		{
			for (size_t i = 0; i < input.size(); i++)
			{
				switch (input[i])
				{
				case ' ':
					if (digital.size() == 0)
						break;
					npl->append(digital + " ");
					digital = "";
					appendPointer = false;
					break;
				case '.':
				case ',':
					if (appendPointer)
						throw 20;
					appendPointer = true;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					digital += input[i];
					break;

				default:
					throw 21;
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
				case ')':
				case '^':
					if (digital.size() != 0)
					{
						npl->append(digital + " ");
						digital = "";
						appendPointer = false;
					}
					bool exit = false;
					while (!exit) {
						action prior = getPrior(*operators, input[i]);
						switch (prior)
						{
						case ADD_TO_STACK:
							operators->push_back(input[i]);
							exit = true;
							break;
						case GET_FROM_STACK:
							*npl += operators->back();
							operators->pop_back();
							*npl += ' ';
							break;
						case OUTPUT_BLOCK:
							if (operators->back() != '(')
								throw 23;
							operators->pop_back();
							    exit = true;
							break;
						case END:
							exit = false;
							break;
						case ERROR:
							throw 22;
							break;
						}
					}

					break;
				}
			}
			if (digital.size() != 0)
			{
				npl->append(digital + " ");
			}
			while (operators->size())
			{
				*npl += operators->back();
				*npl += ' ';
				operators->pop_back();
			}

		}
		catch (int e)
		{
			std::cout << "error " << e;
		}

		return *npl;
	}


	double Counting(std::string& input)
	{
		std::string digital = "";
		bool appendPointer = false;
		std::vector<double> stack;
		double result = 0;

		for (int i = 0; i < input.size(); i++) //Для каждого символа в строке
		{
			switch (input[i])
			{
			case ' ':
				if (digital.size() == 0)
					break;
				stack.push_back(::atof(digital.c_str()));
				digital = "";
				appendPointer = false;
				break;
			case '.':
			case ',':
				if (appendPointer)
					throw 20;
				appendPointer = true;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				digital += input[i];
				break;

			default:
				throw 21;
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
			case '^':
				if (digital.size() != 0)
				{
					stack.push_back(::atof(digital.c_str()));
					digital = "";
					appendPointer = false;
				}
				if (stack.size() < 2)
					throw 24;
				double b = stack.back();
				stack.pop_back();
				double a = stack.back();
				stack.pop_back();
				double tmp = 0;
				switch (input[i])
				{
				case '+':tmp = a + b; break;
				case '-':tmp = a - b; break;
				case '*':tmp = a * b; break;
				case '/':tmp = a / b; break;
				case '^':tmp = pow((double)a, (double)b);
				}
				stack.push_back(tmp);
				break;
			}
		}
		return stack.back(); //Забираем результат всех вычислений из стека и возвращаем его
	}


};
