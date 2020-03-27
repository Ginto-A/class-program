#include<iostream>

int LocationOfSY(int year, int month, int day);

using namespace std;

class Datetime
{
public:
    //无参构造函数
    Datetime();
    //有参构造函数（函数重载）
    Datetime(int year, int month, int day, int hour, int minute, int second);
    //拷贝构造函数
    Datetime(const Datetime& dt);
    //缺省构造函数
    //构造函数初始值列表
    //Datetime(int y, int m, int d, int h, int min, int s) :year(y), month(m), day(d), hour(h), minute(min), second(s) { LunarLeap = false; };
    //析构函数
    ~Datetime();
    void setTime();//设定时间
    void showTime();//显示时间
    void showMoon();//转换成阴历

private:
    int year, month, day;
    int hour, minute, second;
    bool LunarLeap;//用于农历闰月判断
};

int main() {
    //Datetime* dt = new Datetime;//在堆区开辟空间，FIFO
    Datetime dt;//在栈区开辟，函数执行完会自动消亡，FILO
    Datetime dt1(2020, 3, 27, 10, 46, 30);
    Datetime dt2(dt1);
    Datetime& dt3 = dt;//引用，dt3是dt的别名
    Datetime* dt4 = &dt;//指针，dt4是指向dt的地址的指针

    //dt.setTime();
    dt.showTime();
    dt1.showTime();
    dt2.showTime();
    dt3.showTime();//引用的调用方法
    dt4->showTime();//指针的调用用法
    //dt1.showMoon();

    //delete dt;//与new配套，手动消亡
    return 0;
}

Datetime::Datetime()
{
    year = 0; month = 0; day = 0;
    hour = 0; minute = 0; second = 0;
    LunarLeap = false;
    cout << "构造" << this << endl;
}
Datetime::Datetime(int year, int month, int day, int hour, int minute, int second) {
    this->year = year; this->month = month; this->day = day;
    this->hour = hour; this->minute = minute; this->second = second;
    LunarLeap = false;//参数与成员变量同名时，可以用this指针解决
    cout << "构造" << this << endl;
}
Datetime::Datetime(const Datetime& dt) {
    year = dt.year; month = dt.month; day = dt.day;
    hour = dt.hour; minute = dt.minute; second = dt.second;
    LunarLeap = false;
    cout << "构造" << this << endl;
}

Datetime::~Datetime()
{
    cout << "析构" << this << endl;
}
void Datetime::showTime() {
    cout << "当前时间为：" << year << "/" << month << "/" << day << " "
        << hour << ":" << minute << ":" << second << endl;
}
void Datetime::setTime() {
    cout << "请按年月日输入日期（以空格间隔）" << endl;
    cin >> year >> month >> day;
    cout << "请按时分秒输入时间（以空格隔开）" << endl;
    cin >> hour >> minute >> second;
}
void Datetime::showMoon() {
    /**
     * 前提：网络的农历表
     * 1. 求得农历新年(农历表中的位数据得到)在公历年的位置和今天在公历年的位置
     *  =>今天在新年前，农历年-1，在后则农历年=公历年
     *  =>得到今天在农历年的位置
     * 2. 比对农历表的大小月位数据得到农历月份和日期，注意农历闰月
     */

     //使用比特位记录每年的情况
     //0~4 共5bit 春节日份
     //5~6 共2bit 春节月份
     //7~19 共13bit 13个月的大小月情况(如果无闰月，最后位无效)，大月为1,小月为0
     //20~23 共4bit 记录闰月的月份，如果没有闰月为0
     /***************************
      *  位操作不是很懂，先照搬了 *
      ***************************/
    static const int BEGIN_YEAR = 1901;
    static const int NUMBER_YEAR = 199;
    static const unsigned int LUNAR_YEARS[199] = {
         0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,
         0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A, //1901-1910
         0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,
         0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754, //1911-1920
         0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,
         0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E, //1921-1930
         0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,
         0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48, //1931-1940 
         0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,
         0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51, //1941-1950
         0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,
         0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x7AD53C, //1951-1960
         0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,
         0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46, //1961-1970
         0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,
         0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50, //1971-1980
         0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,
         0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB, //1981-1990
         0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,
         0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645, //1991-2000
         0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,
         0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E, //2001-2010
         0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,
         0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x4A9739, //2011-2020
         0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,
         0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43, //2021-2030
         0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,
         0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C, //2031-2040
         0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,
         0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37, //2041-2050
         0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,
         0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42, //2051-2060
         0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,
         0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B, //2061-2070
         0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,
         0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6, //2071-2080
         0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,
         0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E, //2081-2090
         0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,
         0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5 //2091-2099 
    };//数据来源于网络

    Datetime* Lunardt = new Datetime;
    Lunardt->year = year;
    Lunardt->month = 1;
    int year_index = year - BEGIN_YEAR;//下标，用于对照农历表

    if (year <= BEGIN_YEAR || year > BEGIN_YEAR + NUMBER_YEAR) {
        cout << "超出转换范围" << endl;
    }
    else {
        Datetime* SpringFestival = new Datetime;
        SpringFestival->year = year;
        SpringFestival->month = (LUNAR_YEARS[year_index] & 0x60) >> 5;//移位操作，根据农历表的第5~6位得到春节月份
        SpringFestival->day = (LUNAR_YEARS[year_index] & 0x1f);//根据0~4位得出日期

        int Locationdt = LocationOfSY(year, month, day);//今天在公历年的位置
        int LocationSF = LocationOfSY(SpringFestival->year, SpringFestival->month, SpringFestival->day);//春节在公历年的位置
        int LocationLunardt = Locationdt - LocationSF + 1;//今天在农历年的位置

        if (Locationdt < LocationSF) {
            year_index--;
            Lunardt->year--;
            if (year_index < 0) cout << "超出转换范围" << endl;
            SpringFestival->year--;
            SpringFestival->month = (LUNAR_YEARS[year_index] & 0x60) >> 5;
            SpringFestival->day = (LUNAR_YEARS[year_index] & 0x1f);
            LocationSF = LocationOfSY(SpringFestival->year, SpringFestival->month, SpringFestival->day);
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) LocationLunardt = 366 - LocationSF + Locationdt + 1;
            LocationLunardt = 365 - LocationSF + Locationdt + 1;
        }

        for (; Lunardt->month <= 13; Lunardt->month++) {
            int dayOfmonth = 29;//农历小月天数
            if ((LUNAR_YEARS[year_index] >> (6 + Lunardt->month)) & 0x1/*通过第7~19位数据判断大小月*/) dayOfmonth = 30; //农历大月天数
            if (LocationLunardt <= dayOfmonth) {//当位置比天数小退出循环
                break;
            }
            else {
                LocationLunardt -= dayOfmonth;
            }
        }
        Lunardt->day = LocationLunardt;
        delete SpringFestival;
    }

    int leapOfLunaryear = (LUNAR_YEARS[year_index] >> 20) & 0xf;//通过第20~23位数据得出这年有无闰月，是闰几月
    if (leapOfLunaryear > 0 && leapOfLunaryear < Lunardt->month) {
        Lunardt->month--;
        if (leapOfLunaryear == Lunardt->month) Lunardt->LunarLeap = true;
    }

    //输出结果
    int TianGan = 0, DiZhi = 0;
    TianGan = (Lunardt->year - 1864) % 10;//以1864年为基准计算天干地支
    DiZhi = (Lunardt->year - 1864) % 12;
    switch (TianGan) {
    case 0: cout << "甲"; break;
    case 1: cout << "乙"; break;
    case 2: cout << "丙"; break;
    case 3: cout << "丁"; break;
    case 4: cout << "戊"; break;
    case 5: cout << "己"; break;
    case 6: cout << "庚"; break;
    case 7: cout << "辛"; break;
    case 8: cout << "壬"; break;
    case 9: cout << "癸"; break;
    }
    switch (DiZhi) {
    case 0: cout << "子"; break;
    case 1: cout << "丑"; break;
    case 2: cout << "寅"; break;
    case 3: cout << "卯"; break;
    case 4: cout << "辰"; break;
    case 5: cout << "巳"; break;
    case 6: cout << "午"; break;
    case 7: cout << "未"; break;
    case 8: cout << "申"; break;
    case 9: cout << "酉"; break;
    case 10: cout << "戌"; break;
    case 11: cout << "亥"; break;
    }
    cout << "年";

    if (Lunardt->LunarLeap) cout << "闰";
    switch (Lunardt->month) {
    case 1: cout << "正"; break;
    case 2: cout << "二"; break;
    case 3: cout << "三"; break;
    case 4: cout << "四"; break;
    case 5: cout << "五"; break;
    case 6: cout << "六"; break;
    case 7: cout << "七"; break;
    case 8: cout << "八"; break;
    case 9: cout << "九"; break;
    case 10: cout << "十"; break;
    case 11: cout << "冬"; break;
    case 12: cout << "腊"; break;
    }
    cout << "月";

    switch (Lunardt->day) {
    case 1: cout << "初一" << endl; break;
    case 2: cout << "初二" << endl; break;
    case 3: cout << "初三" << endl; break;
    case 4: cout << "初四" << endl; break;
    case 5: cout << "初五" << endl; break;
    case 6: cout << "初六" << endl; break;
    case 7: cout << "初七" << endl; break;
    case 8: cout << "初八" << endl; break;
    case 9: cout << "初九" << endl; break;
    case 10: cout << "初十" << endl; break;
    case 11: cout << "十一" << endl; break;
    case 12: cout << "十二" << endl; break;
    case 13: cout << "十三" << endl; break;
    case 14: cout << "十四" << endl; break;
    case 15: cout << "十五" << endl; break;
    case 16: cout << "十六" << endl; break;
    case 17: cout << "十七" << endl; break;
    case 18: cout << "十八" << endl; break;
    case 19: cout << "十九" << endl; break;
    case 20: cout << "二十" << endl; break;
    case 21: cout << "廿一" << endl; break;
    case 22: cout << "廿二" << endl; break;
    case 23: cout << "廿三" << endl; break;
    case 24: cout << "廿四" << endl; break;
    case 25: cout << "廿五" << endl; break;
    case 26: cout << "廿六" << endl; break;
    case 27: cout << "廿七" << endl; break;
    case 28: cout << "廿八" << endl; break;
    case 29: cout << "廿九" << endl; break;
    case 30: cout << "三十" << endl; break;
    }//二十四节气对特定日期输出，不写了
    delete Lunardt;
}

int LocationOfSY(int year, int month, int day) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        switch (month) {
        case 1: return day; break;
        case 2: return 31 + day; break;
        case 3: return 60 + day; break;
        case 4: return 91 + day; break;
        case 5: return 121 + day; break;
        case 6: return 152 + day; break;
        case 7: return 182 + day; break;
        case 8: return 213 + day; break;
        case 9: return 244 + day; break;
        case 10: return 274 + day; break;
        case 11: return 305 + day; break;
        case 12: return 335 + day; break;
        }
    }
    switch (month) {
    case 1: return day; break;
    case 2: return 31 + day; break;
    case 3: return 59 + day; break;
    case 4: return 90 + day; break;
    case 5: return 120 + day; break;
    case 6: return 151 + day; break;
    case 7: return 181 + day; break;
    case 8: return 212 + day; break;
    case 9: return 243 + day; break;
    case 10: return 273 + day; break;
    case 11: return 304 + day; break;
    case 12: return 334 + day; break;
    }
}