/**
 * @file main_example.cpp
 * @brief Complete demonstration of toolzpp library
 * @copyright MIT License
 *
 * This example showcases the key features of the toolzpp library:
 * - String processing (split, format, case conversion)
 * - Random number generation
 * - Mathematical operations (average, median, mode)
 * - Container algorithms (map, filter, slice)
 * - Command-line progress bar
 * - C-style array utilities
 * - Multi-threading with random numbers
 *
 */

#include "toolzpp.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>


using tlz::operator<<;
// ============ Forward Declarations ============

void demo_string_processing();
void demo_random_numbers();
void demo_mathematics();
void demo_container_algorithms();
void demo_progress_bar();
void demo_carray_utilities();
void demo_multi_threading();

// ============ Main Entry Point ============

int main() {
  std::cout << "\n";
  std::cout
      << "╔══════════════════════════════════════════════════════════════╗\n";
  std::cout
      << "║                 toolzpp Library Demonstration                ║\n";
  std::cout
      << "║                   A Modern C++ Utility Library               ║\n";
  std::cout
      << "╚══════════════════════════════════════════════════════════════╝\n";
  std::cout << "\n";

  demo_string_processing();
  demo_random_numbers();
  demo_mathematics();
  demo_container_algorithms();
  demo_progress_bar();
  demo_carray_utilities();
  demo_multi_threading();

  std::cout << "\n";
  std::cout
      << "╔══════════════════════════════════════════════════════════════╗\n";
  std::cout
      << "║                    Demonstration Complete!                   ║\n";
  std::cout
      << "║                      Thank you for using toolzpp             ║\n";
  std::cout
      << "╚══════════════════════════════════════════════════════════════╝\n";
  std::cout << "\n";

  return 0;
}

// ============ 1. String Processing ============

/**
 * @brief Demonstrates string utilities
 *
 * Features shown:
 * - String splitting and joining
 * - Case conversion (upper/lower)
 * - Whitespace stripping
 * - Character replacement
 * - Substring search
 */
void demo_string_processing() {
  std::cout
      << "┌─────────────────────────────────────────────────────────────┐\n";
  std::cout
      << "│ 1. String Processing                                        │\n";
  std::cout
      << "└─────────────────────────────────────────────────────────────┘\n\n";

  using namespace tlz::str;

  // Split a comma-separated string
  std::string csv = "apple,banana,cherry,date";
  std::cout << "  Original: \"" << csv << "\"\n";

  auto fruits = split(csv, ',');
  std::cout << "  Split:    [";
  for (size_t i = 0; i < fruits.size(); ++i) {
    std::cout << fruits[i];
    if (i < fruits.size() - 1)
      std::cout << ", ";
  }
  std::cout << "]\n";

  // Join back with different separator
  std::string joined = join(fruits, ';');
  std::cout << "  Joined:   \"" << joined << "\"\n";

  // Case conversion
  std::string text = "Hello World!";
  std::cout << "  Original: \"" << text << "\"\n";
  std::cout << "  Upper:    \"" << upper(text) << "\"\n";
  std::cout << "  Lower:    \"" << lower(text) << "\"\n";

  // Partial case conversion (range-based)
  std::string mixed = "HeLLo WoRLd";
  auto partial = upper(mixed, {0, 3});
  std::cout << "  Partial upper (0-3): \"" << partial << "\"\n";

  // Whitespace trimming
  std::string spaced = "   trim me   ";
  std::cout << "  Original: \"" << spaced << "\"\n";
  std::cout << "  Stripped: \"" << trim(spaced) << "\"\n";

  // Character replacement
  std::string with_spaces = "a b c d e";
  auto replaced = replace(with_spaces, ' ', '_');
  std::cout << "  Replace spaces: \"" << replaced << "\"\n";

  // Contains check
  bool has_world = contains(text, "World");
  std::cout << "  Contains 'World': " << std::boolalpha << has_world << "\n\n";
}

// ============ 2. Random Number Generation ============

/**
 * @brief Demonstrates random number utilities
 *
 * Features shown:
 * - Integer random numbers
 * - Floating-point random numbers
 * - Random choice from container
 */
void demo_random_numbers() {
  std::cout
      << "┌─────────────────────────────────────────────────────────────┐\n";
  std::cout
      << "│ 2. Random Number Generation                                 │\n";
  std::cout
      << "└─────────────────────────────────────────────────────────────┘\n\n";

  using namespace tlz::random;

  Randomer rng;

  // Generate random integers
  std::cout << "  Random integers (1-100): ";
  for (int i = 0; i < 10; ++i) {
    std::cout << rng.randint(1, 100) << " ";
  }
  std::cout << "\n";

  // Generate random floating-point numbers
  std::cout << "  Random doubles (0.0-1.0): ";
  for (int i = 0; i < 5; ++i) {
    std::cout << std::fixed << std::setprecision(3) << rng.randreal(0.0, 1.0)
              << " ";
  }
  std::cout << "\n";

  // Random choice from container
  std::vector<std::string> colors = {"Red", "Green", "Blue", "Yellow",
                                     "Purple"};
  std::cout << "  Colors: ";
  for (const auto &c : colors)
    std::cout << c << " ";
  std::cout << "\n";
  std::cout << "  Random choice: " << rng.choice(colors) << "\n\n";
}

// ============ 3. Mathematical Operations ============

/**
 * @brief Demonstrates mathematical utilities
 *
 * Features shown:
 * - Sum, average, median, mode
 * - Weighted average
 * - Vector statistics
 */
void demo_mathematics() {
  std::cout
      << "┌─────────────────────────────────────────────────────────────┐\n";
  std::cout
      << "│ 3. Mathematical Operations                                  │\n";
  std::cout
      << "└─────────────────────────────────────────────────────────────┘\n\n";

  using namespace tlz::math;

  // Sample data
  std::vector<int> data = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  std::vector<int> repeated = {5, 5, 5, 10, 10, 15, 20, 20, 20, 20};

  std::cout << "  Data: ";
  for (int v : data)
    std::cout << v << " ";
  std::cout << "\n";

  // Basic statistics
  std::cout << "  Average: " << average(data) << "\n";
  std::cout << "  Median:  " << median(data) << "\n";

  // Mode (most frequent value)
  std::cout << "  Repeated data: ";
  for (int v : repeated)
    std::cout << v << " ";
  std::cout << "\n";
  std::cout << "  Mode:    " << mode(repeated) << "\n";

  // Weighted average
  std::vector<double> values = {70, 80, 90};
  std::vector<double> weights = {0.2, 0.3, 0.5};
  std::cout << "  Weighted average: " << average(values, weights) << "\n\n";
}

// ============ 4. Container Algorithms ============

/**
 * @brief Demonstrates container algorithms
 *
 * Features shown:
 * - Map (transform each element)
 * - Filter (remove elements by predicate)
 * - Slice (extract sub-range)
 * - Vector concatenation and repetition
 */
void demo_container_algorithms() {
  std::cout
      << "┌─────────────────────────────────────────────────────────────┐\n";
  std::cout
      << "│ 4. Container Algorithms                                     │\n";
  std::cout
      << "└─────────────────────────────────────────────────────────────┘\n\n";

  using namespace tlz::algo;
  using namespace tlz;

  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << "  Original: ";
  for (int v : numbers)
    std::cout << v << " ";
  std::cout << "\n";

  // Map: square each number
  auto squared = numbers;
  vector_map(squared, [](int x) { return x * x; });
  std::cout << "  Squared:  ";
  for (int v : squared)
    std::cout << v << " ";
  std::cout << "\n";

  // Filter: keep only even numbers
  auto even = numbers;
  vector_filter(even, [](int x) { return x % 2 == 0; });
  std::cout << "  Even:     ";
  for (int v : even)
    std::cout << v << " ";
  std::cout << "\n";

  // Slice: extract sub-range
  auto slice = vector_slice(numbers, 2, 6);
  std::cout << "  Slice (2-6): ";
  for (int v : slice)
    std::cout << v << " ";
  std::cout << "\n";

  // Vector concatenation
  std::vector<int> first = {1, 2, 3};
  std::vector<int> second = {4, 5, 6};
  auto concatenated = first + second;
  std::cout << "  Concatenated: ";
  for (int v : concatenated)
    std::cout << v << " ";
  std::cout << "\n";

  // Vector repetition
  std::vector<int> base = {1, 2};
  auto repeated_3x = base * 3;
  std::cout << "  Repeated 3x: ";
  for (int v : repeated_3x)
    std::cout << v << " ";
  std::cout << "\n\n";
}

// ============ 5. Progress Bar ============

/**
 * @brief Demonstrates command-line progress bar
 *
 * Features shown:
 * - Visual progress indication
 * - Percentage display
 * - Customizable appearance
 * - In-place update using carriage return
 */
void demo_progress_bar() {
  std::cout
      << "┌─────────────────────────────────────────────────────────────┐\n";
  std::cout
      << "│ 5. Command-Line Progress Bar                                │\n";
  std::cout
      << "└─────────────────────────────────────────────────────────────┘\n\n";

  using namespace tlz::cmdui;

  ProgressBar bar(0, 40, 0, 100, '=', "Processing");

  std::cout << "  Simulating progress...\n  ";

  for (int i = 0; i <= 100; i += 5) {
    bar.set_value(i);
    bar.print();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  std::cout << "\n\n  Complete!\n\n";
}

// ============ 6. C-Style Array Utilities ============

/**
 * @brief Demonstrates C-style array utilities
 *
 * Features shown:
 * - Convert C array to vector/array
 * - Convert parallel arrays to map
 * - Array operations (max, min, contains, reverse)
 * - Array printing
 */
void demo_carray_utilities() {
  std::cout
      << "┌─────────────────────────────────────────────────────────────┐\n";
  std::cout
      << "│ 6. C-Style Array Utilities                                  │\n";
  std::cout
      << "└─────────────────────────────────────────────────────────────┘\n\n";

  using namespace tlz::carraypp;

  // C-style arrays
  int arr[] = {42, 17, 93, 8, 55, 23, 67, 34};
  constexpr size_t size = sizeof(arr) / sizeof(arr[0]);

  // Print original
  std::cout << "  Original: ";
  carray_print<int, size>(arr);
  std::cout << "\n";

  // Find max and min
  std::cout << "  Maximum: " << find_maxv<int, size>(arr) << "\n";
  std::cout << "  Minimum: " << find_minv<int, size>(arr) << "\n";

  // Check contains
  std::cout << "  Contains 55: " << std::boolalpha
            << carray_contains<int, size>(arr, 55) << "\n";
  std::cout << "  Contains 99: " << carray_contains<int, size>(arr, 99) << "\n";

  // Reverse array
  carray_reverse<int, size>(arr);
  std::cout << "  Reversed: ";
  carray_print<int, size>(arr);
  std::cout << "\n";

  // Reset all values
  reset_all<int, size>(arr, 0);
  std::cout << "  Reset to zeros: ";
  carray_print<int, size>(arr);
  std::cout << "\n";

  // Convert to vector
  int original[] = {10, 20, 30};
  auto vec = carray_to_vector<int, 3>(original);
  std::cout << "  C array to vector: " << vec << "\n";

  // Convert to map from parallel arrays
  const char *keys[] = {"name", "age", "city"};
  const char *values[] = {"Alice", "25", "New York"};
  auto map =
      carray_to_unordered_map<const char *, const char *, 3>(keys, values);
  std::cout << "  Parallel arrays to map: { ";
  for (const auto &[k, v] : map) {
    std::cout << k << ": " << v << " ";
  }
  std::cout << "}\n\n";
}

// ============ 7. Multi-Threading with Random Numbers ============

/**
 * @brief Worker function for multi-threading demo
 *
 * Each thread independently:
 * 1. Generates random numbers
 * 2. Calculates frequency statistics
 * 3. Finds the mode
 *
 * @param id Thread identifier for output
 * @param count Number of random numbers to generate
 */
void worker_demo(int id, int count) {
  tlz::random::Randomer rng;
  std::unordered_map<int, int> freq;

  // Generate random numbers and count frequencies
  for (int i = 0; i < count; ++i) {
    int num = rng.randint(1, 100);
    freq[num]++;
  }

  // Find the mode
  int mode = 0;
  int max_count = 0;
  for (const auto &[num, cnt] : freq) {
    if (cnt > max_count) {
      max_count = cnt;
      mode = num;
    }
  }

  std::mutex mtx;
  mtx.lock();
  std::cout << "  Thread " << id << ": mode = " << mode
            << " (frequency: " << max_count << "/" << count << ")\n";
  mtx.unlock();
}

/**
 * @brief Demonstrates multi-threading with random numbers
 *
 * Launches multiple threads, each generating random numbers
 * and calculating statistical mode independently.
 */
void demo_multi_threading() {
  std::cout
      << "┌─────────────────────────────────────────────────────────────┐\n";
  std::cout
      << "│ 7. Multi-Threading with Random Numbers                      │\n";
  std::cout
      << "└─────────────────────────────────────────────────────────────┘\n\n";

  constexpr int NUM_THREADS = 4;
  constexpr int NUM_SAMPLES = 100000;

  std::cout << "  Launching " << NUM_THREADS << " threads...\n";
  std::cout << "  Each thread generates " << NUM_SAMPLES
            << " random numbers (1-100)\n";
  std::cout << "  and calculates the mode.\n\n";

  std::vector<std::thread> threads;
  threads.reserve(NUM_THREADS);

  // Create and start threads
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.emplace_back(worker_demo, i + 1, NUM_SAMPLES);
  }

  // Wait for all threads to complete
  for (auto &t : threads) {
    t.join();
  }

  std::cout << "\n  All threads completed.\n\n";
}

// ============ End of Example ============

/**
 * ============================================================================
 * Additional Notes:
 * ============================================================================
 *
 * This example covers the major features of the toolzpp library:
 *
 * 1. String Processing (tlz::str)
 *    - split, join, upper, lower, strip, replace, contains
 *
 * 2. Random Numbers (tlz::random)
 *    - randint, randreal, choice
 *
 * 3. Mathematics (tlz::math)
 *    - vector_sum, average, median, mode, weighted average
 *
 * 4. Container Algorithms (tlz::algo)
 *    - vector_map, vector_filter, vector_slice, contains
 *
 * 5. Progress Bar (tlz::cmdui)
 *    - ProgressBar class with real-time updates
 *
 * 6. C-Array Utilities (tlz::carraypp)
 *    - Conversion, searching, reversing, printing
 *
 * 7. Multi-Threading
 *    - Thread-safe random number generation
 *
 * For more examples and detailed documentation, please refer to:
 * - GitHub: https://github.com/yourusername/toolzpp
 * - Each module's header file contains inline documentation
 *
 * ============================================================================
 */