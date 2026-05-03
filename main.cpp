#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include <cpr/cpr.h>

void Trim(std::string& s)
{
	const auto NotSpace = [](unsigned char ch) { return !std::isspace(ch); };
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), NotSpace));
	s.erase(std::find_if(s.rbegin(), s.rend(), NotSpace).base(), s.end());
}

constexpr const char* kUrlsFilePath = R"(LocalDataSample\urls.txt)";

void TryReachUrl(std::string url)
{
	cpr::Response r = cpr::Get(cpr::Url{std::move(url)}, cpr::Timeout{15000});	

	if (!r.error && r.status_code >= 200 && r.status_code <= 299)
	{
		std::cout << "OK\n";
		return;
	}

	if (r.error.code != cpr::ErrorCode::OK)
	{
		std::cout << std::to_string(static_cast<long>(r.error.code)) << '\n';
		return;
	}

	std::cout << std::to_string(r.status_code) << '\n';	
}


int main()
{
	std::ifstream urlsFile(kUrlsFilePath);
	if (!urlsFile)
	{
		std::cerr << "Failed to open " << kUrlsFilePath << '\n';
		return 1;
	}

	std::string line;
	while (std::getline(urlsFile, line))
	{
		Trim(line);
		if (line.empty())
		{
			continue;
		}
		TryReachUrl(line);
	}

	return 0;
}
