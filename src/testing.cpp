#include <string>
#include <iostream>
#include <vector>

// number to character mapping for alphabet
std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

/**
 * Decode 1-26 to a-z
 */
std::string decode(int number) {
    if (number < 1) {
        std::cout << "Invalid number: " << number << std::endl;
        exit(1);
    }
    if (number > 26) {
        // treat as 2 digits (ex: if number is 27, treat as 2 and 7)
        return decode(number / 10) + decode(number % 10);
    }
    return std::string(1, alphabet[number - 1]);
}

std::vector<std::string> getDecodings(std::string input) {
    std::vector<std::string> decodings;
    std::string currentDecoding = "";

    // get decoding if we group by 1s
    for (int i = 0; i < input.length(); i++) {
        currentDecoding += decode(input[i] - '0');
    }
    decodings.push_back(currentDecoding);

    // get decoding if we group by 2s going forwards
    for (int i = 0; i < input.length() - 1; i++) {
        currentDecoding = "";
        for (int j = 0; j < input.length(); j++) {
            if (j == i) {
                currentDecoding += decode((input[j] - '0') * 10 + (input[j + 1] - '0'));
                j++;
            } else {
                currentDecoding += decode(input[j] - '0');
            }
        }
        decodings.push_back(currentDecoding);
    }

    // remove duplicates
    for (int i = 0; i < decodings.size(); i++) {
        for (int j = i + 1; j < decodings.size(); j++) {
            if (decodings[i] == decodings[j]) {
                decodings.erase(decodings.begin() + j);
                j--;
            }
        }
    }

    return decodings;
}

void runTest(std::string input) {
    std::vector<std::string> decodings = getDecodings(input);
    
    // print number of decodings
    std::cout << "Number of decodings: " << decodings.size() << std::endl;

    // print decodings
    for (int i = 0; i < decodings.size(); i++) {
        std::cout << decodings[i] << std::endl;
    }
}

int main() {
    // vector of inputs
    std::vector<std::string> inputs;
    inputs.push_back("111");
    inputs.push_back("1234");
    std::cout << "---------" << std::endl;
    for (int i = 0; i < inputs.size(); i++) {
        runTest(inputs[i]);
        std::cout << "---------" << std::endl;
    }
    return 0;
}