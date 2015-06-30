#include "sdfloader.hpp"

void loadSDF(std::string const& file)
{
	std::ifstream sdf; //sdf datei, die geöffnet wird und in stream objekt gespeichert wird
	std::vector<std::string> lines; //vec in dem einzelne zeilen d datei gespeichert
	sdf.open(file);
	if(sdf.is_open())
	{
		std::string line;
		while(getline(sdf, line))
		{
			lines.push_back(line);
		}
		sdf.close(); //dateisystem sonst weiß nicht, dass die wieder freigegeben ist, die datei
	}
	else
	{
		std::cout << "ERROR! File could not be opened. ERROR!" << std::endl;
		return;
	}
	std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

}

