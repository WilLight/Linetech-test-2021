#include <iostream>
#include <future>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

float arithmeticAverage(vector<int> parsedData)
{
    int sum = 0;
    int vectorSize = parsedData.size();

    for (int i = 0; i < vectorSize; i++)
    {
        sum += parsedData[i];
    }

    return (float)sum / vectorSize;
}

float medianValue(vector<int> parsedData)
{
    auto sortedData = parsedData;
    sort(sortedData.begin(), sortedData.end());
    int vectorSize = sortedData.size();

    if (vectorSize % 2)
    {
        return (float)(sortedData[vectorSize / 2 - 1] + sortedData[vectorSize / 2]) / 2;
    }
    else
    {
        return (float)sortedData[vectorSize / 2];
    }
}

int main()
{
    vector<int> data;

    float task1Result;
    float task2Result;

    string line;
    ifstream dataset;
    dataset.open("data.txt");
    if (dataset.is_open())
    {
        while (getline(dataset, line))
        {
            data.push_back(stoi(line, nullptr));
        }
        dataset.close();
    }
    else
    {
        cout << "File not found" << endl;
    }

    future<float> future1 = async(arithmeticAverage, data);
    future<float> future2 = async(medianValue, data);
    task1Result = future1.get();
    cout << "Task1 Finished: " << task1Result << endl;
    task2Result = future2.get();
    cout << "Task2 Finished: " << task2Result << endl;
}