#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#define PeopleNum 20
using namespace std;
struct Competitors{
    char Number[10];
    char Name[10];
    char Sex[10];
    char Major[20];
    char Class;
    char QQnumber[11];
    float AvgScore;
    float StuScore1[7];
    float StuScore2[7];
};
struct Referees{
    char Name[10];
    float Score[PeopleNum];
};
bool cmp1(int a, int b)
{
    return a > b;
}
bool cmp2(Competitors a, Competitors b)
{
    return a.AvgScore > b.AvgScore;
}
int main()
{
    float sum = 0;
    struct Competitors Competitors[PeopleNum];
    struct Referees Referees[7];
    ifstream Competitor("/Users/s20181106115/Desktop/Competitor.txt");
    ifstream Referee("/Users/s20181106115/Desktop/Referee.txt");
    ofstream Result("/Users/s20181106115/Desktop/Result.csv");
    if(Referee.is_open())
    {
        for(int i = 0; i < 7; i++)
        {
            Referee >> Referees[i].Name;
            for(int j = 0; j < PeopleNum; j++)
            {
                Referee >> Referees[i].Score[j];
            }
        }
        for(int i = 0; i < PeopleNum; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                Competitors[i].StuScore1[j] = Referees[j].Score[i];
                Competitors[i].StuScore2[j] = Referees[j].Score[i];
            }
            sort(Competitors[i].StuScore1, Competitors[i].StuScore1 + 7, cmp1);
            for(int k = 1; k < 6; k++)
            {
                sum += Competitors[i].StuScore1[k];
            }
            Competitors[i].AvgScore = sum / 5;
            sum = 0;
        }
        Referee.close();
    }
    if(Competitor.is_open())
    {
        for(int i = 0; i < PeopleNum; i++)
        {
            Competitor >> Competitors[i].Number
            >> Competitors[i].Name
            >> Competitors[i].Sex
            >> Competitors[i].Major
            >> Competitors[i].Class
            >> Competitors[i].QQnumber;
        }
        Competitor.close();
    }
    if(Result.is_open())
    {
        sort(Competitors, Competitors + PeopleNum, cmp2);
        Result << left << setw(5) << "Rank "
        << left << setw(5) << "Number "
        << left << setw(8) << "StuName "
        << left << setw(8) << "Sex "
        << left << setw(15) << "Major "
        << left << setw(3) << "Class "
        << left << setw(13) << "QQnumber ";
        for(int i = 0; i < 7; i++)
        {
            Result << left << setw(5) << Referees[i].Name << " ";
        }
        Result << left << setw(8) << "AvgScore ";
        Result << endl;
        for(int i = 0; i < PeopleNum; i++)
        {
            Result << left << setw(5) << i + 1
            << left << setw(5) << Competitors[i].Number << " "
            << left << setw(8) << Competitors[i].Name <<" "
            << left << setw(8) << Competitors[i].Sex <<" "
            << left << setw(15) << Competitors[i].Major <<" "
            << left << setw(3) << Competitors[i].Class <<" "
            << left << setw(13) << Competitors[i].QQnumber <<" ";
            for(int j = 0; j < 7; j++)
            {
                Result << left << setw(5)<< Competitors[i].StuScore2[j] << "    ";
            }
            Result << left << setw(8) << setprecision(2)<< fixed << Competitors[i].AvgScore <<" ";
            Result << endl;
        }
        Result.close();
    }
    return 0;
}
