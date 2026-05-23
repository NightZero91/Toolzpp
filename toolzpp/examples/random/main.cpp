#include <cstddef>
#include <thread>
#include <unordered_map>
#include <stdexcept>
#include <utility>
#include <vector>
#include <iostream>
#include <mutex>
#include "randompp.h"
//example

std::mutex mtx;

std::vector<int> random_fill_result(int min, int max, size_t cnt){
    tlz::random::Randomer rdm;
    std::vector<int> result;
    if (min > max) throw std::runtime_error("Min > Max.");
    result.reserve(cnt);
    for (size_t i = 0; i < cnt; i++){
        result.push_back(rdm.randint(min, max));
    }
    return result;
}

std::unordered_map<int, size_t> statistics(const std::vector<int> &result){
    std::unordered_map<int, size_t> result_frequency{};
    for (const auto i : result){
        if (result_frequency.find(i) == result_frequency.end()){
            result_frequency[i] = 1;
        }
        else{
            result_frequency[i]++;
        }
    }
    return result_frequency;
}

int get_highest(const std::unordered_map<int, size_t> &result_frequency){
    if (result_frequency.empty()) throw std::runtime_error("result_frequency empty.");
    std::pair<int, size_t> max{ 0,0 };
    for (const auto &i : result_frequency){
        if (i.second > max.second){
            max = i;
        }
    }
    return max.first;
}

void worker_helper(){
    auto res = random_fill_result(0, 1000, 1000000);
    auto res_fre = statistics(res);
    mtx.lock();
    std::cout << "highest:" << get_highest(res_fre) << std::endl;
    mtx.unlock();
}

void worker(size_t count){
    std::vector<std::thread> threads{};
    for (size_t i = 0; i < count; i++){
        threads.emplace_back(std::thread(worker_helper));
    }
    for (size_t i = 0; i < count; i++){
        threads[i].join();
    }
}

int main(){
    worker(32);
}