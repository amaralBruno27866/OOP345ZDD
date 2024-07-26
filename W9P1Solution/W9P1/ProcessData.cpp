// Workshop 9 - Multi-Threading, Thread Class

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include "ProcessData.h"

namespace seneca
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++)
		{
			avg += arr[i];
		}
		avg /= divisor;
	}
	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++)
		{
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr;
	}

	// The following constructor of the functor receives name of the data file, opens it in
	//   binary mode for reading, reads first int data as total_items, allocate memory space
	//   to hold the data items, and reads the data items into the allocated memory space.
	//   It prints first five data items and the last three data items as data samples.
	ProcessData::ProcessData(const std::string& filename) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::ifstream file(filename, std::ios::binary);

		if(!file) {
			std::cerr << "Error: Cannot open file '" << filename << "'\n";
			return;
		}

		// Read the total number od items
		file.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		if (!file) {
			std::cerr << "Error: Cannot read total_items from file " << filename << std::endl;
		}

		// Allocate memory for data
		data = new int[total_items];

		// Read the data items
		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));
		if (!file) {
			std::cerr << "Error: Cannot read data from items from file " << filename << std::endl;
			delete[] data;
			data = nullptr;
			total_items = 0;
			return;
		}

		file.close();

		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [";
		for (int i = 0; i < 5 && i < total_items; ++i) {
			std::cout << data[i] << (i < 4 && i < total_items - 1 ? ", " : "");
		}
		std::cout << ", ... , ";
		for (int i = total_items - 3; i < total_items; ++i) {
			if (i >= 0) {
				std::cout << data[i] << (i < total_items - 1 ? ", " : "");
			}
		}
		std::cout << "]\n";
	}

	ProcessData::~ProcessData()
	{
		delete[] data;
	}


	// TODO Implement operator(). See workshop instructions for details.
	int ProcessData::operator()(const std::string& target_filename, double& avg, double& var) {
		// Compute average
		computeAvgFactor(data, total_items, total_items, avg);

		// Compute variance
		computeVarFactor(data, total_items, total_items, avg, var);

		// Open the target file in binary mode
		std::ofstream target_file(target_filename, std::ios::binary);
		if (!target_file) {
			std::cerr << "Error: Cannot open target file " << target_filename << std::endl;
			return -1;
		}

		// Write the total number of items
		target_file.write(reinterpret_cast<const char*>(&total_items), sizeof(total_items));
		if (!target_file) {
			std::cerr << "Error: Cannot write total_items to target file " << target_filename << std::endl;
			return -1;
		}

		// Write the data items
		target_file.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));
		if (!target_file) {
			std::cerr << "Error: Cannot write data items to target file " << target_filename << std::endl;
			return -1;
		}

		return 0;

	}
}
