//  butian-force�����ķ�
// /daemon/skill/butian-force.c
// writted by mind 2001/2

#include <ansi.h>
inherit FORCE;
int valid_enable(string usage) { return usage=="force"; }
int valid_learn(object me) { return 1; }
int practice_skill(object me)
{
        if( (string)me->query("family/family_name")!="����ɢ��")
                return notify_fail("���ɢ�ɣ������к����档\n");

        if( !environment(me)->query("butian-force_practice") )
                return notify_fail("�����ķ�ֻ��������ķ�̨�ϲſ�����\n");

        if( (int)me->query_skill("butian-force",1) >= 200 )
                return notify_fail("��Ĳ����ķ���������ˡ�\n");
        if( (int)me->query("kee") < 30 )
                return notify_fail("�����������\n");
        if( (int)me->query("sen") < 30 )
                return notify_fail("����񲻹���\n");
        if( (int)me->query("force") < 10 )
                return notify_fail("�����������");
        me->receive_damage("kee", 30);
        me->receive_damage("sen", 30);
        me->add("force", -10);

        return 1;
}

string exert_function_file(string func)
{
        return CLASS_D("sanxian") + "/butian-force/" + func;
}


