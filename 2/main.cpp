#include <iostream>
#include <stack>
#include <vector>
#include <math.h>

#define PI 3.14159265

using namespace std;

double DegreesToRadians(double degrees)
{
    return degrees * PI / 180;
}

void ConvertDhTableDegreesToRadians(vector<vector<double>> DhTable)
{
    for (auto i = 0; i < DhTable.size(); i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            DhTable[i][j] = DegreesToRadians(DhTable[i][j]);
        }
    }
}

vector<vector<double>> DhRowToMatrix(vector<double> DhRow)
{
    vector<vector<double>> resultingMatrix{
        {cos(DhRow[0]), -sin(DhRow[0]) * cos(DhRow[1]), sin(DhRow[0]) * sin(DhRow[1]), DhRow[2] * cos(DhRow[0])},
        {sin(DhRow[0]), cos(DhRow[0]) * cos(DhRow[1]), -cos(DhRow[0]) * sin(DhRow[1]), DhRow[2] * sin(DhRow[0])},
        {0, sin(DhRow[1]), cos(DhRow[1]), DhRow[3]},
        {0, 0, 0, 1}};

    return resultingMatrix;
}

vector<vector<double>> MultiplyTwoMatrices(vector<vector<double>> matrix1, vector<vector<double>> matrix2)
{
    vector<vector<double>> resultingMatrix(4, vector<double>(4));

    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                resultingMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return resultingMatrix;
}

double GetVectorLengthFromDhMatrix(vector<vector<double>> dhMatrix)
{
    double x = dhMatrix[0][3];
    double y = dhMatrix[1][3];
    double z = dhMatrix[2][3];

    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

int main()
{
    double Joint1Displacement = 10;
    double Joint2Displacement = 10;
    double Joint3Displacement = 10;
    double Joint4Displacement = -2;
    double Joint5Displacement = 1;
    double distanceToTarget = 20;

    vector<vector<double>> DhTable{
        {0, 90, 0, Joint1Displacement},
        {0, 0, Joint2Displacement, 0},
        {0, 0, Joint3Displacement, 0},
        {0, 90, 0, Joint4Displacement},
        {0, 90, 0, Joint5Displacement},
        {0, 0, 0, distanceToTarget}};

    ConvertDhTableDegreesToRadians(DhTable);

    stack<vector<vector<double>>> DhMatricesStack;

    for (auto i = 0; i < DhTable.size(); i++)
    {
        DhMatricesStack.push(DhRowToMatrix(DhTable[i]));
    }

    vector<vector<double>> transformationMatrix = DhMatricesStack.top();
    DhMatricesStack.pop();

    auto DhMatricesCount = DhMatricesStack.size();

    for (auto i = 0; i < DhMatricesCount; i++)
    {
        transformationMatrix = MultiplyTwoMatrices(transformationMatrix, DhMatricesStack.top());
        DhMatricesStack.pop();
    }

    cout << "Distance to target: " << GetVectorLengthFromDhMatrix(transformationMatrix);
}