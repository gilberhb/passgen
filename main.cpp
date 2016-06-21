#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;
using std::random_device;
using std::uniform_int_distribution;

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	po::options_description desc;
	desc.add_options()
		("help","produce help")
		("N", boost::program_options::value<int>()->default_value(4), "number of words")
		("dictionary", po::value<std::string>()->default_value("/usr/share/dict/words"), "dictionary file with one word per line");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}

	int N = vm["N"].as<int>();

	string dictionary_file = vm["dictionary"].as<string>();	

	ifstream words_file (dictionary_file);	
	
	if (!words_file.is_open()) {
		cerr << "Error: unable to open dictionary file" << endl;
		return 1;
	}

	string word;
	vector<string> words;
	while (!words_file.eof())
	{
		getline(words_file, word);
		if (word.length() > 0) {
			words.emplace_back(std::move(word));
		}	
	}

	cout << "Found " << words.size() << " words." << endl;

	random_device rand_dev;
	uniform_int_distribution<int>	distribution(0,words.size()-1);
	
	string password;
	for (int i = 0; i < N-1; ++i)
	{
		int index = distribution(rand_dev);
		password.append(words[index]);
		password.append(" ");
	}

	int index = distribution(rand_dev);
	password.append(words[index]);
	
	cout << "Generated Password: " << password << endl;
	
	return 0;
}
