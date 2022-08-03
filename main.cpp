#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <stack>


struct Token {
	int number = 0;
	char operation = {};
	bool is_number = false;
};

bool is_numeric(const char ch) {
	return ch >= '0' && ch <= '9';
}

int convert_to_int(const char ch) {
	return ch - '0';
}

std::vector<Token> tokenize(const std::vector<std::string>& inputs) {
	std::vector<Token> tokens;
	
	for (const auto& input : inputs) {
		Token token;
		if (is_numeric(input[0])) {
			token.number = std::stoi(input);
			token.is_number = true;
			tokens.push_back(token);
		}
		else {
			token.operation = input[0];
			tokens.push_back(token);
		}
	}
	return tokens;
}

std::vector<std::string> split(const std::string &str) {
	std::vector<std::string> temp;
	std::string curr_string = "";


	for (auto ch : str) {
		if (ch != ' ') {
			curr_string += ch;
		}
		else {
			if (!curr_string.empty()) {
				temp.push_back(curr_string);
				curr_string = "";
			}

		}
	}
	if (!curr_string.empty()) {
		temp.push_back(curr_string);
	}
	return temp;
}


int operate(int num1, int num2, char operation) {
	if (operation == '+') {
		return num1 + num2;
	}
	else if (operation == '-') {
		return num1 - num2;
	}
	else if (operation == '*') {
		return num1 * num2;
	}
	else if (operation == '/') {
		return num1 / num2;
	}
	return 0;
}


int do_math(std::vector<Token> tokens) {
	std::stack<int> stk;
	for (auto token : tokens) {
		if (token.is_number == true) {
			stk.push(token.number);
		}
		else {
			int temp1 = stk.top();
			stk.pop();
			int temp2 = stk.top();
			stk.pop();
			stk.push(operate(temp2, temp1, token.operation));
		}
	}
	return stk.top();
	
}

void print_token(const std::vector<Token> tokens) {
	for (auto token : tokens) {
		if (token.is_number) {
			std::cout << token.number;
		}
		else {
			std::cout << token.operation;
		}
	}

}

int main() {
	
	std::vector<std::string> temp = split("54 43 + 54 *");
	std::cout << do_math(tokenize(temp));
	
    return 0;
}
