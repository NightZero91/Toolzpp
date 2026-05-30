/**
 * @file main.cpp
 * @brief Multi-threaded random number statistics example
 * @copyright MIT License
 *
 * This example demonstrates:
 * - Random number generation using tlz::random::Randomer
 * - Multi-threaded data processing
 * - Statistical analysis (frequency counting)
 * - Thread-safe console output
 *
 * NightZero91/Toolzpp
 */

#include "randompp.h"
#include <cstddef>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

// ============ Global Synchronization ============

/**
 * @brief Mutex for thread-safe console output
 *
 * Protects std::cout from concurrent access by multiple threads.
 * Without this, output from different threads would interleave unpredictably.
 */
std::mutex mtx;

// ============ Random Number Generation ============

/**
 * @brief Generate a vector of random integers
 *
 * Creates a new Randomer instance for each call (thread-safe).
 * Each thread gets its own random number generator to avoid contention.
 *
 * @param min Minimum value (inclusive)
 * @param max Maximum value (inclusive)
 * @param cnt Number of random numbers to generate
 * @return std::vector<int> Vector filled with random numbers
 * @throws std::runtime_error if min > max
 *
 * @note Each call creates a new Randomer, ensuring thread safety
 * @note The vector is pre-allocated with reserve() for performance
 */
std::vector<int> random_fill_result(int min, int max, size_t cnt) {
  // Validate input parameters
  if (min > max) {
    throw std::runtime_error("Min > Max.");
  }

  // Create a new random number generator for this call
  // This is thread-safe because each thread gets its own instance
  tlz::random::Randomer rdm;

  // Pre-allocate memory to avoid reallocation during push_back
  std::vector<int> result;
  result.reserve(cnt);

  // Generate random numbers
  for (size_t i = 0; i < cnt; i++) {
    result.push_back(rdm.randint(min, max));
  }

  return result;
}

// ============ Statistical Analysis ============

/**
 * @brief Count frequency of each integer in a vector
 *
 * Uses unordered_map for O(1) average lookup and insertion.
 *
 * @param result Vector of integers to analyze
 * @return std::unordered_map<int, size_t> Map from value to frequency count
 *
 * @note Complexity: O(n) time, O(k) space where k is number of unique values
 */
std::unordered_map<int, size_t> statistics(const std::vector<int> &result) {
  std::unordered_map<int, size_t> result_frequency{};

  // Count occurrences of each value
  for (const auto i : result) {
    // find() returns end() if key doesn't exist
    if (result_frequency.find(i) == result_frequency.end()) {
      result_frequency[i] = 1; // First occurrence
    } else {
      result_frequency[i]++; // Subsequent occurrence
    }
  }

  return result_frequency;
}

// ============ Finding Maximum Frequency ============

/**
 * @brief Find the value with the highest frequency
 *
 * Iterates through the frequency map to find the maximum count.
 * If multiple values have the same maximum count, returns the first
 * encountered.
 *
 * @param result_frequency Frequency map from statistics()
 * @return int The value that appears most frequently
 * @throws std::runtime_error if the map is empty
 *
 * @note For mode calculation, this returns the smallest value with max count
 * @note Complexity: O(n) where n is number of unique values
 */
int get_highest(const std::unordered_map<int, size_t> &result_frequency) {
  if (result_frequency.empty()) {
    throw std::runtime_error("result_frequency empty.");
  }

  // Initialize with first element's value and count 0
  // The pair stores: first = value, second = frequency
  std::pair<int, size_t> max{0, 0};

  // Find entry with maximum frequency
  for (const auto &i : result_frequency) {
    if (i.second > max.second) {
      max = i; // Update both value and frequency
    }
  }

  return max.first; // Return the value (not the frequency)
}

// ============ Worker Thread Function ============

/**
 * @brief Worker function executed by each thread
 *
 * Each worker independently:
 * 1. Generates 1,000,000 random numbers between 0 and 1000
 * 2. Calculates frequency statistics
 * 3. Finds the most frequent number (mode)
 * 4. Prints the result using a mutex for thread safety
 *
 * @note Each thread has its own Randomer instance (no contention)
 * @note Mutex ensures output lines don't interleave
 */
void worker_helper() {
  // Step 1: Generate random numbers (thread-local, no lock needed)
  auto res = random_fill_result(0, 1000, 1000000);

  // Step 2: Calculate frequency statistics
  auto res_fre = statistics(res);

  // Step 3: Get the mode (most frequent number)
  int mode = get_highest(res_fre);

  // Step 4: Print result with mutex protection
  // Lock the mutex before accessing std::cout
  mtx.lock();
  std::cout << "highest:" << mode << std::endl;
  mtx.unlock();
}

// ============ Thread Management ============

/**
 * @brief Create and manage multiple worker threads
 *
 * Spawns 'count' threads, each running worker_helper().
 * Waits for all threads to complete before returning.
 *
 * @param count Number of worker threads to create
 *
 * @note Threads are stored in a vector and joined in order
 * @note Each thread runs independently and may finish in any order
 *
 * @warning Creating too many threads may cause resource contention
 * @recommended Keep count <= number of CPU cores for optimal performance
 */
void worker(size_t count) {
  // Container to hold all thread objects
  std::vector<std::thread> threads{};

  // Reserve memory to avoid reallocation
  threads.reserve(count);

  // Create and start all worker threads
  for (size_t i = 0; i < count; i++) {
    // emplace_back constructs thread in-place
    // Pass worker_helper function to thread constructor
    threads.emplace_back(std::thread(worker_helper));
  }

  // Wait for all threads to complete
  for (size_t i = 0; i < count; i++) {
    threads[i].join(); // Blocks until thread i finishes
  }
}

// ============ Main Entry Point ============

/**
 * @brief Main function - entry point of the program
 *
 * Launches 32 worker threads, each analyzing 1 million random numbers.
 * Total numbers generated: 32 * 1,000,000 = 32,000,000
 *
 * Expected behavior:
 * - Each thread prints its most frequent number
 * - Output order may vary due to thread scheduling
 * - All threads complete before program exits
 *
 * @return int Exit code (0 on success)
 *
 * @note For uniform random distribution, the mode is likely around 500
 * @note Execution time depends on CPU cores (parallel execution)
 *
 * Example output (order may vary):
 *   highest:498
 *   highest:512
 *   highest:487
 *   ...
 *   highest:503
 */
int main() {
  // Launch 32 worker threads
  // Each thread processes 1,000,000 random numbers
  worker(32);

  return 0;
}

// ============ Key Takeaways ============
/**
 * This example demonstrates:
 *
 * 1. Thread Safety:
 *    - Each thread gets its own Randomer instance
 *    - Mutex protects shared resources (std::cout)
 *
 * 2. Performance Optimizations:
 *    - reserve() to avoid reallocation
 *    - O(n) algorithms for counting and searching
 *    - Parallel execution across CPU cores
 *
 * 3. Statistical Concepts:
 *    - Frequency counting using hash maps
 *    - Finding mode (most frequent value)
 *    - Law of large numbers demonstration
 *
 * 4. RAII Principles:
 *    - Mutex is manually locked/unlocked
 *    - Consider std::lock_guard for exception safety
 *
 * @warning Current mutex usage lacks exception safety
 * @improvement Use std::lock_guard<std::mutex> lock(mtx) instead
 */