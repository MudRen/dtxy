// six-chaos-sword.c
//not used, set to default first.

#include <ansi.h>

inherit SKILL;

mapping *action = ({
        ([      "name":                 "Ⱥħ����",
                "action":
"$N����$wһ�����γ�������Ӱ�������������$n��$l��������",
		"parry":		0,
                "dodge":                0,
                "damage":               20,
                "damage_type":  "����"
        ]),
        ([      "name":                 "�������",
                "action":               "$N����һת������һ��������$w��һ�����߰����$n��$l",
		"parry":		-10,
                "dodge":                0,
                "damage":               25,
                "damage_type":  "����"
        ]),
        ([      "name":                 "�ٹ�ҹ��",
                "action":
"$N�趯$w��ͻȻһ�����壬$wЮ�������������$n��$l",
		"parry":		5,
                "dodge":                0,
                "damage":               20,
                "damage_type":  "����"
        ]),
        ([      "name":                 "������·",
                "action":
"$N����$wһ�����ó��������⣬����һ��㱼䣬$w��бб�ص�����$n��$l",
		"parry":		-10,
                "dodge":                0,
                "damage":               30,
                "damage_type":  "����"
        ]),
        ([      "name":                 "��Ӱ����",
                "action":
"$N����$w���Ⱪ�����ּ��ֿ����$n$l��ȥ",
		"parry":		10,
                "dodge":                0,
                "damage":               25,
                "damage_type":  "����"
        ]),
        ([      "name":                 "��ع�",
                "action":
"$N��Ȼ������һչ������$wͻ�����߽�â��৵ش�����$n��$l",
		"parry":		0,
                "dodge":                -10,
                "damage":               30,
                "damage_type":  "����"
        ]),
});

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 100 )
                return notify_fail("�������������û�а취��׷�꽣��\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 5 )
                return notify_fail("�����������������û�а취��ϰ׷�꽣��\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        write("�㰴����ѧ����һ��׷�꽣����\n");
        return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

void skill_improved(object me)
{
        if( (int)me->query_skill("six-chaos-sword", 1)  % 10 == 0 ) {
                tell_object(me,
                        RED "\n��ͻȻ����һ�ɶ���������ͷ��ֻ������ɱ��....\n\n" NOR);
                me->add("bellicosity", 100);
        } else
                me->add("bellicosity", 10);
}

