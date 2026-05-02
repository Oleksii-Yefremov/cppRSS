#include <iostream>
#include <string>

#include <cpr/cpr.h>

static constexpr const char Url[] = "https://example.com";

// Attempts a GET against a fixed URL and prints diagnostics to stderr on failure.
void TryReachHardcodedUrl()
{
	cpr::Response HttpResponse = cpr::Get(cpr::Url{Url}, cpr::Timeout{15000});

	if (HttpResponse.error)
	{
		std::cout << "Error reaching " << Url << ": " << HttpResponse.error.message << " ("<< std::to_string(HttpResponse.error.code) << ")\n";
		return;
	}

	if (HttpResponse.status_code < 200 || HttpResponse.status_code > 299)
	{
		std::cout << "Error reaching " << Url << ": HTTP " << HttpResponse.status_code;
		if (!HttpResponse.status_line.empty())
		{
			std::cout << " " << HttpResponse.status_line;
		}
		std::cout << '\n';
	}
	if (!HttpResponse.error)
	{
		std::cout << "Response: " << HttpResponse.text << std::endl;
	}	
}

int main()
{
	std::cout << "Program started" << std::endl;
	TryReachHardcodedUrl();
	std::cout << "Press any key to exit" << std::endl;
	std::cin.get();
	return 0;
}
