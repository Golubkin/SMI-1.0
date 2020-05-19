#include "pch.h"
#include "../MathFunctions/SMIabs.cpp"
#include "../MathFunctions/SMIfloor.cpp"
#include "../MathFunctions/SMIceil.cpp"
#include "../MathFunctions/SMIround.cpp"
#include "../MathFunctions/SMIfact.cpp"
#include "../MathFunctions/SMIln.cpp"
#include "../MathFunctions/SMIexp.cpp"
#include "../MathFunctions/SMIpow.cpp"
#include "../MathFunctions/SMIsqrt.cpp"
#include "../MathFunctions/SMIsin.cpp"
#include "../MathFunctions/SMIcos.cpp"
#include "../MathFunctions/SMItg.cpp"
#include "../MathFunctions/SMIctg.cpp"
#include "../MathFunctions/SMIlog.cpp"
TEST(SMIceil, Vbolst) // Работает нормально
{
    ASSERT_EQ(SMIceil(14.9), 15);
    ASSERT_EQ(SMIceil(1134513514), 1134513514);
    ASSERT_EQ(SMIceil(-14.9), -14);
    ASSERT_EQ(SMIceil(-1134513514), -1134513514);
}
TEST(SMIfloor, Vmenst) // Работает нормально
{
    ASSERT_EQ(SMIfloor(14.9), 14);
    ASSERT_EQ(SMIfloor(1134513514.9), 1134513514);
    ASSERT_EQ(SMIfloor(-14.9), -15);
    ASSERT_EQ(SMIfloor(-1134513514), -1134513514);
}
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
TEST(SMIround, NumberRound) // Работает нормально
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
    EXPECT_EQ(SMIround(-249137880.13498), -249137880); 
}
TEST(SMIfact, Factorial) // Работает нормально
{
    EXPECT_EQ(SMIfact(2), 2);
    EXPECT_EQ(SMIfact(0), 1);
    EXPECT_EQ(SMIfact(1), 1);
    EXPECT_EQ(SMIfact(19), 121645100408832000);
    EXPECT_EQ(SMIfact(20), 2432902008176640000);
    EXPECT_EQ(SMIfact(2.8), 2);     
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

TEST(SMIexp, Exponenta) // Работает нормально
{
    ASSERT_NEAR(SMIexp(0), 1, 0.1);
    ASSERT_NEAR(SMIexp(1), 2.71828, 0.00001);
    ASSERT_NEAR(SMIexp(-5), 0.00673, 0.00001); 
    ASSERT_NEAR(SMIexp(-5.546536566444), 0.0039, 0.0001);
    ASSERT_NEAR(SMIexp(2.31), 10.0744, 0.0001);
    ASSERT_NEAR(SMIexp(3.311324732), 27.4214, 0.0001);
    ASSERT_NEAR(SMIexp(3.311324732), 27.4214, 0.0001);
    ASSERT_NEAR(SMIexp(20), 485165000, 1000); 
}
TEST(SMIpow, XvStepenyN) // Работает нормально
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
   ASSERT_NEAR(SMIpow(8, -2.21), 0.0100965, 0.000001); 
   ASSERT_NEAR(SMIpow(8, -5.2145134513), 0.0000195355, 0.0000000001);
   ASSERT_NEAR(SMIpow(5, 3.4213411245), 246.272, 0.001);
   ASSERT_NEAR(SMIpow(3.34, 3), 37.2597, 0.0001);
   ASSERT_NEAR(SMIpow(3.34, 3.3214241245), 54.9015, 0.0001);
}
TEST(SMIsqrt, sqrt) // Работает нормально 
{
   ASSERT_NEAR(SMIsqrt(0), 0, 0.01); 
   ASSERT_NEAR(SMIsqrt(1), 1, 0.01); 
   ASSERT_EQ(SMIsqrt(4), 2);
   ASSERT_NEAR(SMIsqrt(3), 1.73205, 0.00001);
   ASSERT_NEAR(SMIsqrt(3.23), 1.79722, 0.0001); 
   ASSERT_NEAR(SMIsqrt(3.21342145145), 1.79260, 0.00001); 
   ASSERT_NEAR(SMIsqrt(312353568673), 558886.00687, 0.00001);  
   ASSERT_NEAR(SMIsqrt(312353568673.5622256465), 558886.00687, 0.00001); 
}
TEST(SMIsin, sinus) // Работает нормально
{
    ASSERT_EQ(SMIsin(0), 0);
    ASSERT_NEAR(SMIsin(3.1415), 0.0000926535 , 0.000000001); 
    ASSERT_NEAR(SMIsin(1), 0.841470, 0.000001);
    ASSERT_NEAR(SMIsin(-2), -0.909297, 0.000001 );
    ASSERT_NEAR(SMIsin(-1453145.144435), -0.994143, 0.000001);
}
TEST(SMIcos, cosinus) // Работает нормально
{
    ASSERT_NEAR(SMIcos(0), 1, 0.00000001);
    ASSERT_NEAR(SMIcos(1), 0.540302, 0.000001);
    ASSERT_NEAR(SMIcos(-2), -0.416146, 0.000001);
    ASSERT_NEAR(SMIcos(-1453145.144435), 0.108067, 0.00001); 
}
TEST(SMItg, tangens) // Работает нормально
{
    ASSERT_EQ(SMItg(0), 0);
    ASSERT_NEAR(SMItg(1), 1.55740, 0.00001);
    ASSERT_NEAR(SMItg(-2), 2.18503, 0.00001);
    ASSERT_NEAR(SMItg(12345.12345), -4.17452, 0.0001);
}
TEST(SMIctg, catanges) // Работает нормально
{
    ASSERT_NEAR(SMIctg(1), 0.64209, 0.00001);
    ASSERT_NEAR(SMIctg(-2), 0.45765, 0.00001);
    ASSERT_NEAR(SMIctg(12345.12345), -0.23954, 0.0001);
}
TEST(SMIlog, logorifm)
{
    ASSERT_EQ(SMIlog(2, 1), 0);
    ASSERT_EQ(SMIlog(2, 2), 1);
    ASSERT_EQ(SMIlog(2.2, 2.2), 1);
    ASSERT_EQ(SMIlog(2132421341234, 1), 0);
    ASSERT_EQ(SMIlog(2434.3242341234123, 1), 0);
    ASSERT_NEAR(SMIlog(5,3), 0.683, 0.001);
    ASSERT_NEAR(SMIlog(3.2134, 5.15145), 1.404, 0.001);
    ASSERT_NEAR(SMIlog(3562264256.2134, 513444444444444444444444.15145), 2.482, 0.001);
}