#include <iostream>
#include <math.h>
#include <string>
using namespace std;

enum enActivityScale { Little = 1, Light = 2, Moderate = 3, Heavy = 4, Extreme = 5};
enum enCaloriesGoal { Loose = 1, Maintain = 2, Gain = 3};
enum enGender {Male = 1, Female = 2};

struct strNutritionAttr
{
    // TC = Total Calories
    float protienG, protienCAL, protienPercentOfTC;
    float fatG, fatCAL, fatPercentOfTC;
    float carbG, carbCAL, carbPercentOfTC;
    float maintainCAL, looseCAL, gainCAL;
    enCaloriesGoal goalCalories;
};

struct strPhysicalAttr
{
    string name;
    float weightKILO, heightCM, weightLBS;
    int age;
    enActivityScale scale;
    enGender gender;
};

struct strAthleteInformation
{
    strPhysicalAttr MyPhysicalAttr;
    strNutritionAttr MyNutritionAttr;
};

// Reading Functions
float readNum(string msg) {
    float num;

    do
    {
    cout << msg;
    cin >> num;
    } while (num < 1);
    
    return num;
}

string readName(string msg) {
    string name;

    cout << msg;
    getline(cin, name);

    return name;
}

// All the function should return [calories], then I will convert it to grams.
// Calculation functions
int KgToLbs(int weight) {
    return weight * 2.20462;
}

float calcProtien(float weight) {
    // Convert your weight from kg to lb.
    return KgToLbs(weight) * 4;
}

float calcFat(float cals) {
    // 0.25 of the hole calories.
    return 0.25 * cals;
}

float calcCarb(float protienCals, float fatCals, float cals) {
    // is the result of subtracting the two previous functions.
    return cals - (protienCals + fatCals);
}

float calcPercentFromGoal(float cals, float goalCals) {
    return round((cals / goalCals) * 100);
}

// Enums Handlers
enCaloriesGoal goalHandler(string msg) {
        int enteredScale = readNum(msg);
    
    switch (enteredScale)
    {
    case enCaloriesGoal::Loose :
        return enCaloriesGoal::Loose;
    case enCaloriesGoal::Maintain :
        return enCaloriesGoal::Maintain;
    case enCaloriesGoal::Gain :
        return enCaloriesGoal::Gain;
    default:
        return enCaloriesGoal::Maintain;
    }
}

enActivityScale scaleHandler(string msg) {

    int enteredScale = readNum(msg);

    switch (enteredScale)
    {
    case enActivityScale::Little :
        return enActivityScale::Little;
    case enActivityScale::Light :
        return enActivityScale::Light;
    case enActivityScale::Moderate :
        return enActivityScale::Moderate;
    case enActivityScale::Heavy :
        return enActivityScale::Heavy;
    case enActivityScale::Extreme :
        return enActivityScale::Extreme;
    default:
        return enActivityScale::Light;
    }

}

enGender genderHandler(string msg) {
    int enteredScale = readNum(msg);

    switch (enteredScale)
    {
    case enGender::Male :
        return enGender::Male;
    case enGender::Female :
        return enGender::Female;
    default:
        return enGender::Male;
    }
}

float calcBMR(strAthleteInformation myAthlete) {
    switch (myAthlete.MyPhysicalAttr.gender)
    {
    case enGender::Male :
        return (10 * myAthlete.MyPhysicalAttr.weightKILO) + (6.25 * myAthlete.MyPhysicalAttr.heightCM) - (5 * myAthlete.MyPhysicalAttr.age) + 5;
    case enGender::Female :
        return (10 * myAthlete.MyPhysicalAttr.weightKILO) + (6.25 * myAthlete.MyPhysicalAttr.heightCM) - (5 * myAthlete.MyPhysicalAttr.age) - 161;
    default:
        break;
    }
}

float calcTDEE(strAthleteInformation myAthlete) {
    switch (myAthlete.MyPhysicalAttr.scale)
    {
    case enActivityScale::Little :
        return myAthlete.MyNutritionAttr.maintainCAL * 1.2;
    case enActivityScale::Light :
        return myAthlete.MyNutritionAttr.maintainCAL * 1.37;
    case enActivityScale::Moderate :
        return myAthlete.MyNutritionAttr.maintainCAL * 1.55;
    case enActivityScale::Heavy :
        return myAthlete.MyNutritionAttr.maintainCAL * 1.75;
    case enActivityScale::Extreme :
        return myAthlete.MyNutritionAttr.maintainCAL * 1.9;
    default:
        break;
    }
}



strAthleteInformation fillingPhysicalAttrData(strAthleteInformation &MyAthlete) {

    MyAthlete.MyPhysicalAttr.name = readName("Please Enter your Name : ");
    MyAthlete.MyPhysicalAttr.age = readNum("Please Enter your Age : ");
    MyAthlete.MyPhysicalAttr.gender = genderHandler("Please Enter your Gender [1 - 2] =>\n 1 - Male\n 2 - Female\n Please Enter the suited number : ");
    MyAthlete.MyPhysicalAttr.weightKILO = readNum("Please Enter your Weight (KG) : ");
    MyAthlete.MyPhysicalAttr.weightLBS = KgToLbs(MyAthlete.MyPhysicalAttr.weightKILO); 
    MyAthlete.MyPhysicalAttr.heightCM = readNum("Please Enter your Height (CM) : ");
    MyAthlete.MyPhysicalAttr.scale = scaleHandler("In Scale From [1 - 5] =>\n1 - Little\n2 - Light\n3 - Moderate\n4 - Heavy\n5 - Extreme\nEnter the most suited number to your case : ");

    // Static Data (Quick Test) :

    // MyAthlete.MyPhysicalAttr.name = "Abdullah Bander";
    // MyAthlete.MyPhysicalAttr.age = 23;
    // MyAthlete.MyPhysicalAttr.gender = enGender::Male;
    // MyAthlete.MyPhysicalAttr.weightKILO = 70;
    // MyAthlete.MyPhysicalAttr.weightLBS = 154.324; 
    // MyAthlete.MyPhysicalAttr.heightCM = 179;
    // MyAthlete.MyPhysicalAttr.scale = enActivityScale::Moderate;

    return MyAthlete;
}


strAthleteInformation fillingNutritionAttrData(strAthleteInformation &MyAthlete) {

    MyAthlete.MyNutritionAttr.goalCalories = goalHandler("\nIn Range From [1 - 3] =>\n1 - Loose weight\n2 - Maintain weight\n3 - Gain weight\nEnter the most suited goal number : ");

    switch (MyAthlete.MyNutritionAttr.goalCalories)
    {
    case enCaloriesGoal::Loose :
        MyAthlete.MyNutritionAttr.maintainCAL = calcBMR(MyAthlete);
        MyAthlete.MyNutritionAttr.maintainCAL = calcTDEE(MyAthlete);
        MyAthlete.MyNutritionAttr.looseCAL = MyAthlete.MyNutritionAttr.maintainCAL - 500;
        MyAthlete.MyNutritionAttr.gainCAL = MyAthlete.MyNutritionAttr.maintainCAL + 500;

        MyAthlete.MyNutritionAttr.protienCAL = MyAthlete.MyPhysicalAttr.weightLBS;
        MyAthlete.MyNutritionAttr.protienG = MyAthlete.MyNutritionAttr.protienCAL / 4;
        // MyAthlete.MyNutritionAttr.protienPercentOfTC = ;

        MyAthlete.MyNutritionAttr.fatCAL = calcFat(MyAthlete.MyNutritionAttr.looseCAL);
        MyAthlete.MyNutritionAttr.fatG = MyAthlete.MyNutritionAttr.fatCAL / 9;
        // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;

        MyAthlete.MyNutritionAttr.carbCAL = calcCarb(MyAthlete.MyNutritionAttr.protienCAL, MyAthlete.MyNutritionAttr.fatCAL, MyAthlete.MyNutritionAttr.looseCAL);
        MyAthlete.MyNutritionAttr.carbG = MyAthlete.MyNutritionAttr.carbCAL / 4;
        // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;
        break;
    case enCaloriesGoal::Maintain :
        MyAthlete.MyNutritionAttr.maintainCAL = calcBMR(MyAthlete);
        MyAthlete.MyNutritionAttr.maintainCAL = calcTDEE(MyAthlete);
        MyAthlete.MyNutritionAttr.looseCAL = MyAthlete.MyNutritionAttr.maintainCAL - 500;
        MyAthlete.MyNutritionAttr.gainCAL = MyAthlete.MyNutritionAttr.maintainCAL + 500;

        MyAthlete.MyNutritionAttr.protienCAL = MyAthlete.MyPhysicalAttr.weightLBS;
        MyAthlete.MyNutritionAttr.protienG = MyAthlete.MyNutritionAttr.protienCAL / 4;
        // MyAthlete.MyNutritionAttr.protienPercentOfTC = ;

        MyAthlete.MyNutritionAttr.fatCAL = calcFat(MyAthlete.MyNutritionAttr.maintainCAL);
        MyAthlete.MyNutritionAttr.fatG = MyAthlete.MyNutritionAttr.fatCAL / 9;
        // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;

        MyAthlete.MyNutritionAttr.carbCAL = calcCarb(MyAthlete.MyNutritionAttr.protienCAL, MyAthlete.MyNutritionAttr.fatCAL, MyAthlete.MyNutritionAttr.maintainCAL);
        MyAthlete.MyNutritionAttr.carbG = MyAthlete.MyNutritionAttr.carbCAL / 4;
        // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;
        break;
    case enCaloriesGoal::Gain :
        MyAthlete.MyNutritionAttr.maintainCAL = calcBMR(MyAthlete);
        MyAthlete.MyNutritionAttr.maintainCAL = calcTDEE(MyAthlete);
        MyAthlete.MyNutritionAttr.looseCAL = MyAthlete.MyNutritionAttr.maintainCAL - 500;
        MyAthlete.MyNutritionAttr.gainCAL = MyAthlete.MyNutritionAttr.maintainCAL + 500;

        MyAthlete.MyNutritionAttr.protienCAL = MyAthlete.MyPhysicalAttr.weightLBS;
        MyAthlete.MyNutritionAttr.protienG = MyAthlete.MyNutritionAttr.protienCAL / 4;
        // MyAthlete.MyNutritionAttr.protienPercentOfTC = ;

        MyAthlete.MyNutritionAttr.fatCAL = calcFat(MyAthlete.MyNutritionAttr.gainCAL);
        MyAthlete.MyNutritionAttr.fatG = MyAthlete.MyNutritionAttr.fatCAL / 9;
        // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;

        MyAthlete.MyNutritionAttr.carbCAL = calcCarb(MyAthlete.MyNutritionAttr.protienCAL, MyAthlete.MyNutritionAttr.fatCAL, MyAthlete.MyNutritionAttr.gainCAL);
        MyAthlete.MyNutritionAttr.carbG = MyAthlete.MyNutritionAttr.carbCAL / 4;
        // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;
        break;
    default:
        break;
    }
    // MyAthlete.MyNutritionAttr.maintainCAL = calcBMR(MyAthlete);
    // MyAthlete.MyNutritionAttr.maintainCAL = calcTDEE(MyAthlete);
    // MyAthlete.MyNutritionAttr.looseCAL = MyAthlete.MyNutritionAttr.maintainCAL - 500;
    // MyAthlete.MyNutritionAttr.gainCAL = MyAthlete.MyNutritionAttr.maintainCAL + 500;

    // MyAthlete.MyNutritionAttr.protienCAL = MyAthlete.MyPhysicalAttr.weightLBS;
    // MyAthlete.MyNutritionAttr.protienG = MyAthlete.MyNutritionAttr.protienCAL / 4;
    // // MyAthlete.MyNutritionAttr.protienPercentOfTC = ;

    // MyAthlete.MyNutritionAttr.fatCAL = calcFat(MyAthlete.MyNutritionAttr.maintainCAL);
    // MyAthlete.MyNutritionAttr.fatG = MyAthlete.MyNutritionAttr.fatCAL / 9;
    // // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;

    // MyAthlete.MyNutritionAttr.carbCAL = calcCarb(MyAthlete.MyNutritionAttr.protienCAL, MyAthlete.MyNutritionAttr.fatCAL, MyAthlete.MyNutritionAttr.maintainCAL);
    // MyAthlete.MyNutritionAttr.carbG = MyAthlete.MyNutritionAttr.carbCAL / 4;
    // // MyAthlete.MyNutritionAttr.fatPercentOfTC = ;


    return MyAthlete;
}

void printPhysicalData(strAthleteInformation athleteInfo) {
    
    cout << "************** PHYSICAL **************" << endl;
    cout << athleteInfo.MyPhysicalAttr.name << endl;
    cout << athleteInfo.MyPhysicalAttr.age << endl;
    cout << athleteInfo.MyPhysicalAttr.gender << endl;
    cout << athleteInfo.MyPhysicalAttr.weightKILO << endl;
    cout << athleteInfo.MyPhysicalAttr.weightLBS << endl;
    cout << athleteInfo.MyPhysicalAttr.heightCM << endl;
    cout << athleteInfo.MyPhysicalAttr.scale << endl;
}

void printNutritionData(strAthleteInformation athleteInfo) {

    cout << "************** NUTRITION **************" << endl;
    cout << "Maintain CAL : " << athleteInfo.MyNutritionAttr.maintainCAL << endl;
    cout << "Loose CAL : " << athleteInfo.MyNutritionAttr.looseCAL << endl;
    cout << "Gain CAL : " << athleteInfo.MyNutritionAttr.gainCAL << endl;
    cout << "\n";
    cout << "Protien : " << athleteInfo.MyNutritionAttr.protienCAL << "cal, " << athleteInfo.MyNutritionAttr.protienG << "g" << endl;
    cout << "\n";
    cout << "Fat : " << athleteInfo.MyNutritionAttr.fatCAL << "cal, " << athleteInfo.MyNutritionAttr.fatG << "g" << endl;
    cout << "\n";
    cout << "Carb : " << athleteInfo.MyNutritionAttr.carbCAL << "cal, " << athleteInfo.MyNutritionAttr.carbG << "g" << endl;
    cout << "\n";
}



int main () {
    strAthleteInformation MyAthlete;

    fillingPhysicalAttrData(MyAthlete);
    printNutritionData(fillingNutritionAttrData(MyAthlete));


    // string name = readName();
    // float weight = readNum("Enter Your Weight : ");
    // float calories = readNum("Enter Your Goal Calories : ");

    // float protien = calcProtien(weight);
    // float fat = calcFat(calories);
    // float carb = calcCarb(protien, fat, calories);

    // cout << "\n";
    // cout << "***********************************" << "\n";
    // cout << "Hi " << name << "." << endl;
    // cout << "\n";
    // cout << "Protien (Calories) = " << protien << endl;
    // cout << "Protien (Grams) = " << protien / 4 << endl;
    // cout << "Protien % Of the Goal Calories = %" << calcPercentFromGoal(protien, calories) << endl;
    // cout << "\n";
    // cout << "Fat (Calories) = " << fat << endl;
    // cout << "Fat (Grams) = " << fat / 9 << endl;
    // cout << "Fat Percent (%) From the Goal Calories = %" << calcPercentFromGoal(fat, calories) << endl;
    // cout << "\n";
    // cout << "Carb (Calories) = " << carb << endl;
    // cout << "Carb (Grams) = " << carb / 4 << endl;
    // cout << "Carb Percent (%) From the Goal Calories = %" << calcPercentFromGoal(carb, calories) << endl;
    // cout << "***********************************" << "\n";
    // cout << "Abdullah Ban..." << endl;




    return 0;
}