#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

int GetPrimeAt(char c)
{
	int n = c - 'a';
	int counter = 0;
	bool isPrime = true;
	int nthPrime = 0;

	for (int i = 2; counter != n + 1; ++i)
	{
		for (int j = 2; j <= sqrt(i); ++j)
		{
			if (i % j == 0)
			{
				isPrime = false;
				break;
			}
			isPrime = true;
		}
		if (isPrime == true)
		{
			// char alphabet = 'a' + counter++;
			// std::cout << alphabet << i << '\t';
			nthPrime = i;
			++counter;
		}
	}
	return nthPrime;
}

char GetCharAt(int x)
{
	int counter = 0;
	bool isPrime = true;
	int nthPrime = 0;

	for (int i = 2; i != x; ++i)
	{
		for (int j = 2; j <= sqrt(i); ++j)
		{
			if (i % j == 0)
			{
				isPrime = false;
				break;
			}
			isPrime = true;
		}
		if (isPrime == true)
		{
			// char alphabet = 'a' + counter++;
			// std::cout << alphabet << i << '\t';
			++counter;
		}
	}
	char result = 'a' + counter;
	return result;
}

void SearchInVec(const char c, const std::string& str, std::vector<int>& indexOfResult)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == c)
			indexOfResult.emplace_back(i);
	}
}

void BlackListFilter(const std::vector<std::string>& dic,
	const std::string& blackList,
	std::vector<std::string>& result)
{
	for (int i = 0; i < dic.size(); ++i)
	{
		bool isDeleted = false;
		for (const char& e : blackList)
		{
			if (dic[i].find(e) != std::string::npos)
			{
				isDeleted = true;
				break;
			}
		}
		if (isDeleted)
			continue;
		else
			result.push_back(dic[i]);
	}
}

void ColorFilter(const std::vector<std::string>& dic,
	const std::vector<std::pair<int, char>>& filter,
	std::vector<std::string>& results)
{
	for (int i = 0; i < dic.size(); ++i)
	{
		bool isGreen = true;
		bool isGold = true;
		for (auto& e : filter)
		{
			int pos = std::get<int>(e);
			char c = std::get<char>(e);
			std::vector<int> indexes;
			SearchInVec(c, dic[i], indexes);
			if (c == '\0')
				continue;
			else if (pos % 10 == 0)
			{
				pos /= 10;
				pos -= 1;
				bool hasChar = false;
				for (int& idx : indexes)
				{
					hasChar = true;
					if (idx != pos)
					{
						isGreen = false;
					}
					else
					{
						isGreen = true;
						break;
					}
				}
				if (!hasChar)
				{
					isGreen = false;
					break;
				}
			}
			else
			{
				pos -= 1;
				bool isIdx = false;
				bool hasChar = false;
				for (int& idx : indexes)
				{
					hasChar = true;
					if (idx == pos)
					{
						isIdx = true;
						break;
					}
				}
				if (isIdx || !hasChar)
				{
					isGold = false;
					break;
				}
			}
			if (!isGold || !isGreen)
				break;
		}
		if (isGreen && isGold)
			results.emplace_back(dic[i]);
	}
}

int main()
{
	std::ifstream in("Dictionary.txt");
	std::vector<std::string> dictionary;
	std::vector<char> vowels = { 'a', 'e', 'i', 'o', 'u' };
	// lcumw
	std::string frqntLttrs = "etaoinshrd";
	std::vector<std::pair<std::string, int>> foundWords;
	std::vector<std::string> virtualdictionary;

	for (int i = 0; in.good(); ++i)
	{
		dictionary.emplace_back();
		std::getline(in, dictionary[i]);
	}

	virtualdictionary = dictionary;

	int wordCnt = 0;
	for (int i = 0; i < dictionary.size(); ++i)
	{
		std::string temp;
		temp = dictionary[i];
		std::string lettersInuse;
		int letterCnt = 0;
		int wordScore = 1;
		for (int j = 0; j < frqntLttrs.size(); ++j)
		{
			auto const idx = temp.find_last_of(temp[j]);
			if (idx != j)
				break;

			auto const letterIdx = frqntLttrs.find(temp[j]);
			if (letterIdx != std::string::npos)
			{
				int chans = letterIdx + 1;
				wordScore /= chans * std::pow(10, 5);
				++letterCnt;
				lettersInuse += temp[j];
				continue;
			}
			break;
		}
		if (letterCnt == 5)
		{
			// int nDelLttrs = 0;
			// for (int i = 0; i < frqntLttrs.size(); ++i)
			// {
			// 	if (lettersInuse.find(frqntLttrs[i]) != std::string::npos)
			// 	{
			// 		// std::cout << frqntLttrs[i] << '\n';
			// 		frqntLttrs.erase(frqntLttrs.begin() + i);
			// 		++nDelLttrs;
			// 		--i;
			// 	}
			// }

			foundWords.push_back(std::make_pair(temp, wordScore));

			// foundWords.push_back(temp);
			// foundWordsScores.push_back(wordScore);
			// std::cout << foundWords[wordCnt++] << '\n';
		}
	}

	std::cout << "Best Opening Moves...\n\n";
	std::sort(foundWords.rbegin(), foundWords.rend());
	for (auto& e : foundWords)
	{
		std::cout << std::get<std::string>(e) << '\t';
	}

	bool isRunning = true;

	while (isRunning)
	{
		std::string word;

		std::cout << "\n\nWhat's your move? (press q to quit)\n";
		std::cin >> word;

		if (word == "q")
		{
			isRunning = false;
			break;
		}

		int result = 0;
		std::string blackList;
		// std::vector<int> resultVec;
		// resultVec.resize(5, 1);
		std::vector<std::pair<int, char>> resultVec(5);
		std::cout << "\nWht's the result?\n";
		for (int i = 0; i < 5; ++i)
		{
			std::cin >> result;
			if (result == 0)
			{
				blackList += word[i];
			}
			if (result == 1)
			{
				resultVec[i] = { i + 1, word[i] };
				// resultVec[i] *= GetPrimeAt(word[i]);
			}
			if (result == 2)
			{
				resultVec[i] = { (i + 1) * 10, word[i] };
				// resultVec[i] *= GetPrimeAt(word[i]) * 2;
			}
		}

		std::vector<std::string> blackListFiltered;
		std::vector<std::string> finalResults;

		BlackListFilter(virtualdictionary, blackList, blackListFiltered);

		ColorFilter(blackListFiltered, resultVec, finalResults);

		virtualdictionary = finalResults;

		for (const auto& e : finalResults)
		{
			std::cout << e << '\t';
		}
	}

	//for (int t = 0; t < dictionary.size(); ++t)
	//{
	//	bool isDeleted = false;
	//	for (char& e : blackList)
	//	{
	//		if (dictionary[t].find(e) != std::string::npos)
	//		{
	//			isDeleted = true;
	//			break;
	//		}
	//	}
	//	if (isDeleted)
	//		continue;

	//	for (int i = 0; i < resultVec.size(); ++i)
	//	{
	//		if (resultVec[i] == 0)
	//			continue;

	//		char c;
	//		// if it is Green
	//		if (resultVec[i] % 2 == 0)
	//		{
	//			c = GetCharAt(resultVec[i] / 2);
	//			std::vector<int> indexes;
	//			SearchInVec(c, dictionary[t], indexes);
	//			for (int& e : indexes)
	//			{
	//				if (e == i)

	//			}
	//		}
	//	}
	//}

	/*int wordIdx = 0;
	for (int i = 0; i < 100; ++i)
	{
		std::string temp;
		std::getline(in, temp);
		if (temp[0] == 'y')
			continue;

		bool hasVowels = false;
		for (int i = 0; i < vowels.size(); ++i)
		{
			if (temp.find(vowels[i]) != std::string::npos)
			{
				hasVowels = true;
				break;
			}
		}
		if (!hasVowels)
		{
			words.push_back(temp);
			std::cout << words[wordIdx++] << '\n';
		}
	}*/

	//int n;
	//std::cin >> n;

	//int counter = 0;
	//bool isPrime = true;
	//for (int i = 2; counter != n; ++i)
	//{
	//	for (int j = 2; j <= sqrt(i); ++j)
	//	{
	//		if (i % j == 0)
	//		{
	//			isPrime = false;
	//			break;
	//		}
	//		isPrime = true;
	//	}
	//	if (isPrime == true)
	//	{
	//		char alphabet = 'a' + counter++;
	//		std::cout << alphabet << i << '\t';
	//		//counter++;
	//	}
	//}

	return 0;
}