#include <random>
#include <vector>
#include <iostream>
#include <ctime>

// Входные данные
const int N = 5; 
std::vector<std::vector<int>> distance =
   {{ 0, 5, 8, 5, 3 },                     
    { 5, 0, 2, 4, 1 },
    { 8, 2, 0, 6, 7 },
    { 5, 4, 6, 0, 9 },
    { 3, 1, 7, 9, 0 }}; // Оптимальное решение для этой задачи коммивояжёра: 5 -> 1 -> 2 -> 4 -> 3 : расстояние 8
// ...

// Функции для вычисления точного оптимального значения
void print_optimal();
void optimal_internal(std::vector<bool> used, std::vector<int> trace, int overall_distance);
bool is_optimal(int input);
// ...

// Разное
std::string to_string(std::vector<int> input);
int randomnumber(int included_min, int included_max);
void print_step(int step, std::vector<int> trace, int selected_town, int overall_distance);
// ...

int main()
{
    std::vector<bool> X = std::vector<bool>(N, false); // Если мы уже входили в город, пишем 1
    std::vector<int> trace;
    int overall_distance = 0;
    int x = randomnumber(0, 4);
    X[x] = true;
    trace.push_back(x);
    std::cout << 1 << ") Trace " << to_string(trace) << " Select " << x << "\n";

    for (int i = 1; i < N; i++)
    {
        int current_town = x;
        int min_current_distance = -1;
        int min_current_town = -1;
        for (int j = 0; j < N; j++)
        {
            if (X[j]) continue;
            if (min_current_town == -1 || distance[current_town][j] < min_current_distance)
            {
                min_current_distance = distance[current_town][j];
                min_current_town = j;
            }
        }
        x = min_current_town;
        X[x] = true;
        overall_distance += min_current_distance;
        trace.push_back(x);
        print_step(i + 1, trace, x, overall_distance);
    }
    overall_distance += distance[trace[0]][trace[N-1]];

    std::cout << "Final: Trace " << to_string(trace) << " Distance " << overall_distance << "\n";

    std::cout << "Calculating best possible result:\n";
    print_optimal();
}

// Код функций для вычисления точного оптимального значения
void print_optimal()
{
    optimal_internal({ 1, 0, 0, 0, 0}, { 0 }, 0);
    optimal_internal({ 0, 1, 0, 0, 0}, { 1 }, 0);
    optimal_internal({ 0, 0, 1, 0, 0}, { 2 }, 0);
    optimal_internal({ 0, 0, 0, 1, 0}, { 3 }, 0);
    optimal_internal({ 0, 0, 0, 0, 1}, { 4 }, 0);
}
bool is_optimal(int input)
{
    static int current_optimal = __INT_MAX__;
    if (input <= current_optimal) 
    {
        current_optimal = input;
        return true;
    }
    return false;
}
void optimal_internal(std::vector<bool> used, std::vector<int> trace, int overall_distance)
{
    bool is_done = true;
    for (int i = 0; i < N; i++)
    {
        if (used[i]) continue;
        std::vector<bool> new_used = used;
        new_used[i].flip();
        std::vector<int> new_trace = trace;
        new_trace.push_back(i);
        is_done = false;
        optimal_internal(new_used, new_trace, overall_distance + distance[trace[trace.size() - 1]][i]);
    }
    if (is_done && is_optimal(overall_distance))
    {
        std::cout << to_string(trace) << " " << overall_distance << "\n";
    }
}
// ...

// Разное
std::string to_string(std::vector<int> input)
{
    std::string output = "[ ";
    for (int i = 0; i < input.size(); i++)
    {
        output.append(std::to_string(input[i]) + " ");    
    }
    output.append("]");
    return output;
}
int randomnumber(int included_min, int included_max)
{
    static std::default_random_engine rng(time(NULL));
    std::uniform_int_distribution<int> dist(included_min, included_max); 
    dist(rng);
    return dist(rng); 
}
void print_step(int step, std::vector<int> trace, int selected_town, int overall_distance)
{
    std::cout << step << ") Trace " << to_string(trace) << " Select " << selected_town 
    << " Distance " << distance[trace[trace.size()-2]][trace[trace.size()-1]] << " Overall Distance " << overall_distance << "\n";
    return;
}
// ...