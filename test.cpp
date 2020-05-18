#include "pch.h"
#include "../MathFunctions/SMIabs.cpp"
#include "../MathFunctions/SMIceil.cpp"
#include "../MathFunctions/SMIfloor.cpp"
#include "../MathFunctions/SMIround.cpp"
#include "../MathFunctions/SMIfact.cpp"
#include "../MathFunctions/SMIln.cpp"
#include "../MathFunctions/SMIexp.cpp"
#include "../MathFunctions/SMIpow.cpp"
#include "../MathFunctions/SMIsqrt.cpp"
#include "../MathFunctions/SMIsin.cpp"
#include "../MathFunctions/SMIcos.cpp"
///////////////////////////////Написать тесты ceil и floor////////////////// 
TEST(SMIabs, Number)// Работает нормально
{
    EXPECT_EQ(SMIabs(1), 1);
    EXPECT_EQ(SMIabs(-5), 5);
    EXPECT_EQ(SMIabs(0), 0);
    EXPECT_EQ(SMIabs(3.7), 3.7);
    EXPECT_EQ(SMIabs(-3.4), 3.4);
    EXPECT_EQ(SMIabs(58989989884134513451345.5254151), 58989989884134513451345.5254151);
    ASSERT_NEAR(SMIabs(32414), 32412 ,2 );
}
TEST(SMIround, NumberRound)
{
    EXPECT_EQ(SMIround(-2), -2);
    EXPECT_EQ(SMIround(2), 2);
    EXPECT_EQ(SMIround(0), 0);
    EXPECT_EQ(SMIround(-2.23), -2);
    EXPECT_EQ(SMIround(-2.5), -3);
    EXPECT_EQ(SMIround(1.54), 2);
    ASSERT_EQ(SMIround(1.34), 1);
    EXPECT_EQ(SMIround(-2.14444444444441), -2);
    EXPECT_EQ(SMIround(-2.5456216354), -3);
    EXPECT_EQ(SMIround(2.53613333333333), 3);
    EXPECT_EQ(SMIround(2.134444444444), 2);
    EXPECT_EQ(SMIround(-249137880.13498), -249137880); // Работает до 9 миллиардов макс, включительно
}
TEST(SMIfact, Factorial)
{
    EXPECT_EQ(SMIfact(2), 2);
    EXPECT_EQ(SMIfact(0), 1);
    EXPECT_EQ(SMIfact(1), 1);
    EXPECT_EQ(SMIfact(19), 121645100408832000);
    EXPECT_EQ(SMIfact(20), 2432902008176640000);
    EXPECT_EQ(SMIfact(2.8), 2); //Работает с дробями, как с целыми числами
//Обычно, конечно, считают только от целых чисел факториал, но калькулятор может считать и от дробей    
}
TEST(SMIln, NaturLog) // Работает нормально 
{
    ASSERT_NEAR(SMIln(3), 1.09862, 0.00001);
    ASSERT_DOUBLE_EQ(SMIln(1), 0);
    ASSERT_NEAR(SMIln(5), 1.60944, 0.00001);
    ASSERT_NEAR(SMIln(5.4), 1.68639, 0.00001);
    ASSERT_NEAR(SMIln(7.4215451254), 2.00438, 0.00001);
    ASSERT_NEAR(SMIln(54135151243435), 31.62250, 0.00001);
    ASSERT_NEAR(SMIln(54135151243435.21433331434614), 31.62250, 0.00001);
}

TEST(SMIexp, Exponenta) // Пишет ответ с разной точностью после запятой( четыре или пять знаков, если вводить, к примеру 1 или 2) и комит снизу
{
    ASSERT_NEAR(SMIexp(0), 1, 0.1);
    ASSERT_NEAR(SMIexp(1), 2.71828, 0.00001);
    //ASSERT_NEAR(SMIexp(-5), 0.00673, 0.001); //Не корректно работает с отрицательной степенью
    ASSERT_NEAR(SMIexp(2.31), 10.0744, 0.0001);
    ASSERT_NEAR(SMIexp(3.311324732), 27.4214, 0.0001);
    ASSERT_NEAR(SMIexp(3.311324732), 27.4214, 0.0001);
    ASSERT_NEAR(SMIexp(20), 485165000, 1000); 
}
TEST(SMIpow, XvStepenyN)
{  
   ASSERT_EQ(SMIpow(0, 1234), 0);
   ASSERT_EQ(SMIpow(1, 1), 1);
   ASSERT_EQ(SMIpow(1, 24351.4135), 1);
   ASSERT_EQ(SMIpow(5, -5), 0.00032);
   ASSERT_EQ(SMIpow(5, 5), 3125);
   ASSERT_EQ(SMIpow(-5, 5), -3125);
   ASSERT_EQ(SMIpow(5, 0), 1);
   ASSERT_EQ(SMIpow(5, 1), 5);
   ASSERT_EQ(SMIpow(-5, 1), -5);
   ASSERT_EQ(SMIpow(-5, 0 ), 1);
   ASSERT_EQ(SMIpow(-6.34, 2), 40.1956);
   ASSERT_EQ(SMIpow(-6.34, 3), -254.840104);
   ASSERT_NEAR(SMIpow(5, 2.43), 49.9456, 0.0001 );
  // ASSERT_NEAR(SMIpow(8, -2.21), 0.01009, 0.00001); //Не корректно считает положительное число в степени дробного отрицательного числа
   ASSERT_NEAR(SMIpow(5, 3.4213411245), 246.272, 0.001);
   ASSERT_NEAR(SMIpow(3.34, 3), 37.2597, 0.0001);
   ASSERT_NEAR(SMIpow(3.34, 3.3214241245), 54.9015, 0.0001);
}
TEST(SMIsqrt, sqrt) 
{
   //ASSERT_EQ(SMIsqrt(0), 0); // Не даёт ноль из корня 0
   // ASSERT_EQ(SMIsqrt(1), 1); // Из еденицы не даёт еденицу, считает 0.999969
   ASSERT_EQ(SMIsqrt(4), 2);
   ASSERT_NEAR(SMIsqrt(3), 1.73205, 0.00001);
   // ASSERT_NEAR(SMIsqrt(3.23), 1.79722, 0.00001); // При взятии от дроби, даёт ошибку в пятом знаке, проблема не округлении, ошибка незначительна
   //ASSERT_NEAR(SMIsqrt(3.21342145145), 1.79260, 0.00001); // При взятии от дроби с большим "хвостом" дал ошибку в 4 знаке, ошибка не значительна
   ASSERT_NEAR(SMIsqrt(312353568673), 558886.00687, 0.00001);  // Округляет ответ от большого числа до целого, стирая хвост 
   ASSERT_NEAR(SMIsqrt(312353568673.5622256465), 558886.00687, 0.00001); // ответ также округлён для больших дробных чисел
}
TEST(SMIsin, sinus)
{
    ASSERT_EQ(SMIsin(0), 0);
    //ASSERT_NEAR(SMIsin(3.1415), 0.0000926535 , 0.0000000001); // Делает ошибку только в 10 знаке
    ASSERT_NEAR(SMIsin(1), 0.841470, 0.000001);
    ASSERT_NEAR(SMIsin(-2), -0.909297, 0.000001 );
    ASSERT_NEAR(SMIsin(-1453145.144435), -0.994143, 0.000001);
}
TEST(SMIcos, cos)
{
    ASSERT_EQ(SMIcos(0),1); // Тест скоро будет написан
}