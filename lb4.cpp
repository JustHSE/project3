#include <iostream>
#include <iomanip>

using namespace std;

int inputDaysCount()
{
    int d;
    cout << "=== Анализ многодневных данных сенсора ===" << endl;
    cout << "Введите количество дней: ";
    cin >> d;
    return d;
}

int inputHoursCount()
{
    int h;
    cout << "Введите количество измерений в дне: ";
    cin >> h;
    return h;
}

void inputData(float** p, int d, int h)
{
    for (int i = 0; i < d; i++)
    {
        cout << "День " << (i + 1) << ": ";
        for (int j = 0; j < h; j++)
        {
            cin >> *(*(p + i) + j);  
        }
    }
    cout << endl;
}

float dayAverage(float* row, int h)
{
    float sum = 0;
    for (int i = 0; i < h; i++)
    {
        sum += *(row + i);  
    }
    return sum / h;
}

float overallAverage(float** p, int d, int h)
{
    float totalSum = 0;
    for (int i = 0; i < d; i++)
    {
        float* currentDay = *(p + i);  
        for (int j = 0; j < h; j++) 
        {
            totalSum += *(currentDay + j);  
        }
    }
    return totalSum / (d * h);
}


void showHotDays(float** p, int d, int h)
{
    float overallAvg = overallAverage(p, d, h);
    
    cout << "Теплые дни:" << endl;
    bool foundHotDays = false;
    
    for (int i = 0; i < d; i++)
    {
        float* currentDay = *(p + i);  
        float dayAvg = dayAverage(currentDay, h);
        
        if (dayAvg > overallAvg)
        {
            foundHotDays = true;
            cout << "День " << (i + 1) << " (среднее = " << setprecision(1) << dayAvg << ")" << endl;
        }
    }
    
    if (!foundHotDays)
    {
        cout << "Нет дней с температурой выше общей средней." << endl;
    }
}

int main()
{
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
    
    int d = inputDaysCount();
    int h = inputHoursCount();
    
    if (d > 30)
    {
        cout << "Ошибка: количество дней не должно превышать 30!" << endl;
        return 1;
    }
    
    if (h > 24)
    {
        cout << "Ошибка: количество измерений не должно превышать 24!" << endl;
        return 1;
    }
    
    float** data = new float*[d];  
    
    for (int i = 0; i < d; i++)
    {
        *(data + i) = new float[h];  
    }
    
    inputData(data, d, h);
    
    float avg = overallAverage(data, d, h);
    
    cout << "\nОбщая средняя температура: " << fixed << setprecision(1) << avg << endl;
    cout << endl;
    
    showHotDays(data, d, h);
    
    for (int i = 0; i < d; i++)
    {
        delete[] *(data + i);  
    }
    delete[] data;  
    
    return 0;
}