inherit SKILL;
#include <ansi.h>
string *dodge_msg = ({
     "$nһ��"+BLINK""+HIG"����ˮ�ر����¡�"NOR+"��$Nֻ����ǰһ����������$n����Ӱ��\n",
     "$nһ��"+HIG"�����������һ���"NOR+"������΢�Σ��о����յرܿ���$N��һ�С�\n",
     "ֻ��$n�������һ����һ��"+BLINK""+HIG"������һ���ζ��"NOR+"���󵴶�������һ�ԡ�\n",
     "$n����$nһ��"+BLINK""+HIG"����ռ�Ƭ��ϼ��"NOR+"�����䷭�ɣ����$N��һ�С�\n",
});
int valid_enable(string usage) { return (usage=="dodge"); }
int valid_learn(object me)
{
        if( (int)me->query("spi") < 10 )
                return notify_fail("������Բ�����û�а취�����Ʋ���\n");
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int practice_skill(object me)
{
        if( (int)me->query("sen") < 30 )
                return notify_fail("��ľ���̫���ˣ����������Ʋ���\n");
        me->receive_damage("sen", 30);
        return 1;
}
