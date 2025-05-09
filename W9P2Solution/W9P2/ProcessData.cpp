/*/////////////////////////////////////////////////////////////////////////
				  Workshop - #9 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// Workshop 9 - Multi-Threading, Thread Class

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <thread>
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
			// std::this_thread::sleep_for(std::chrono::nanoseconds(1)); // This part was used just to make the reflection of the multi-threading
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
			// std::this_thread::sleep_for(std::chrono::nanoseconds(1)); // This part was used just to make the reflection of the multi-threading
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr && num_threads>0 && averages && variances && p_indices;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples.
	ProcessData::ProcessData(const std::string& filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.

		std::ifstream file(filename, std::ios::binary);

		if (!file) {
			std::cerr << "Error: Cannot open file '" << filename << "'\n";
			return;
		}

		// Read the total number of items
		file.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		if (!file) {
			std::cerr << "Error: Cannot read total_items from file " << filename << std::endl;
			return;
		}

		// Allocate memory for data
		data = new (std::nothrow) int[total_items];
		if (!data) {
			std::cerr << "Error: Memory allocation failed for data\n";
			total_items = 0;
			return;
		}

		// Read the data items
		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));
		if (!file) {
			std::cerr << "Error: Cannot read data items from file " << filename << std::endl;
			delete[] data;
			data = nullptr;
			total_items = 0;
			return;
		}

		file.close();

		// Print the first three and the last three data items as samples
		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [";
		for (int i = 0; i < 3 && i < total_items; ++i) {
			std::cout << data[i] << (i < 2 && i < total_items - 1 ? ", " : "");
		}
		std::cout << ", ... , ";
		for (int i = total_items - 3; i < total_items; ++i) {
			if (i >= 0) {
				std::cout << data[i] << (i < total_items - 1 ? ", " : "");
			}
		}
		std::cout << "]\n";

		// Initialize variables for multi-threaded computation
		num_threads = n_threads;
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads + 1] {};
		for (int i = 0; i < num_threads + 1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}

	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the
	//   function logic for the computation of average and variance by running the
	//   functions `computeAvgFactor` and `computeVarFactor` in multiple threads.
	// The function divides the data into a number of parts, where the number of parts is
	//   equal to the number of threads. Use multi-threading to compute average-factor for
	//   each part of the data by calling the function `computeAvgFactor`. Add the obtained
	//   average-factors to compute total average. Use the resulting total average as the
	//   average value argument for the function computeVarFactor, to compute variance-factors
	//   for each part of the data. Use multi-threading to compute variance-factor for each
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument `target_file`.
	// Also, read the workshop instruction.
	int ProcessData::operator()(const std::string& target_file, double& avg, double& var) {

		// Partition the data
		size_t partition_size = total_items / num_threads;
		std::vector<std::thread> threads;

		/// Compute average using multi-threading
		for (size_t i = 0; i < static_cast<size_t>(num_threads); i++) {
			size_t start_index = i * partition_size;
			size_t end_index = (i == static_cast<size_t>(num_threads) - 1) ? total_items : static_cast<size_t>(start_index + partition_size);
			size_t size = end_index - start_index;
			threads.emplace_back(std::bind(computeAvgFactor, data + start_index, size, total_items, std::ref(averages[i])));
		}

		for (auto& thread : threads) {
			thread.join();
		}

		avg = 0.0;
		for (size_t i = 0; i < static_cast<size_t>(num_threads); ++i) {
			avg += averages[i];
		}

		// Clear threads for reuse
		threads.clear();

		// Compute variance using multi-threading
		for (size_t i = 0; i < static_cast<size_t>(num_threads); ++i) {
			size_t start_index = i * partition_size;
			size_t end_index = (i == static_cast<size_t>(num_threads) - 1) ? total_items : static_cast<size_t>(start_index + partition_size);
			size_t size = end_index - start_index;

			threads.emplace_back(std::bind(computeVarFactor, data + start_index, size, total_items, avg, std::ref(variances[i])));
		}

		for (auto& thread : threads) {
			thread.join();
		}

		var = 0.0;
		for (size_t i = 0; i < static_cast<size_t>(num_threads); ++i) {
			var += variances[i];
		}

		// Write data to target file
		std::ofstream ofs(target_file, std::ios::binary);
		if (ofs) {
			ofs.write(reinterpret_cast<char*>(&total_items), sizeof(total_items));
			ofs.write(reinterpret_cast<char*>(data), total_items * sizeof(int));
		}

		return 0;
	}
}
