// moneyd.c  Ǯ�Ĺ���
// Ronger 11/98
// by Xiang@XKX (95/12/22)

#include <ansi.h>

string money_str(int amount)
{
        // returns a chinese string of `amount` of money
        string output;

        if (amount / 10000) {
                output = chinese_number(amount / 10000) + "��"HIY"�ƽ�"NOR;
                amount %= 10000;
        }
        else
                output = "";
        if (amount / 100) {
                output = output + chinese_number(amount / 100) + "��"HIW"����"NOR;
                amount %= 100;
        }
        if (amount)
                return output + chinese_number(amount) + "��"YEL"ͭ��"NOR;
        return output;
}


