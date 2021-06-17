//���ڴ���ӡ dashouyin.c
#include <ansi.h>

inherit SKILL;

mapping *action = ({
        ([     "action":
"$N�ֽ�"+HIY"����������ӡ��"NOR",�����Ķ�,����$n��$1",
               "dodge":     20,
               "parry":     20,
               "force":     200,
               "damage_type":  "����"
        ]),
        ([     "action":
"$N�ֽᡸʩ��ηӡ��,�������������߾�����,Ȼ����ȭӿ��,����$n��$1",
               "parry":     15,
               "dodge":     15,
               "force":     150,
               "damage_type":  "����"
        ]),
        ([     "action":
"$N��������,Ȼ�������ڸ�ӡ��,��������,����$n��$1",
               "dodge":     10,
               "parry":     10,
               "force":     200,
               "damage_type":  "����"
        ]),
        ([     "action":
"$N��$n�Ĺ�����Ư���ض���,���н�����⸿ӡ��,��͸ָ��,����$n��$1",
               "dodge":     25,
               "parry":     20,
               "force":     120,
               "damage_type":  "����"
        ]),
        ([     "action":
"$N�ֽᡸ������ӡ��,���������ſ�����$n",
               "dodge":     -5,
               "parry":     10,
               "force":     200,
               "damage_type":  "����"
        ]),
        ([     "action":
"$Nһ�������ü�ۼ䣬ʹ��Ĵָ����ü�ġ����ǡ���ƿӡ��,ͻȻȡ��$N��$1",
               "dodge":     10,
               "parry":     10,
               "force":     100,
               "damage_type":  "����"
        ]),
        ([     "action":
"$Nٿ������ȴ�Ա�����ϥ������������̬��˫��ȴ��������ӡ�ᣬ�仯�޷�����Ȼ���һ��,��������ӡ�����籩��㹥��",
               "dodge":     25,
               "parry":     20,
               "force":     220,
               "damage_type":  "����"
        ]),
        ([     "action":
"$N�������ʨ��ӡ��,���޻��ɵ�һ������.",
               "dodge":     -5,
               "parry":     10,
               "force":     180,
               "damage_type":  "����"
        ]),
        ([     "action":
"$N���ŵض��$n�Ĺ���,���ᡸ��ʨ��ӡ��,����������ˮ�㹥��$n",
               "dodge":     25,
               "parry":     20,
               "force":     200,
               "damage_type":  "����"
        ]),
});

int valid_learn(object me)
{
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon")
)
                return notify_fail("�����ڴ���ӡ������֡�\n");
        if( (int)me->query("max_force") < 50 )
                return notify_fail("�������̫�����޷������ڴ���ӡ��\n");
        return 1;
}
int valid_enable(string usage) { return usage=="unarmed"; }

int practice_skill(object me)
{
        if( (int)me->query("sen") < 40)
                return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");
        if( (int)me->query("kee") < 40 )
                return notify_fail("����������������Ϣһ�������ɡ�\n");
        if( (int)me->query("force") < 10 )
                return notify_fail("������������ˡ�\n");

        me->receive_damage("kee", 10);
        me->receive_damage("sen", 10);
        me->add("force", -10);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/2) > victim->query_str() ) {
                victim->receive_wound("kee", (damage_bonus - 100) / 2 );
                switch(random(3)) {
                        case 0: return "��������������һ�����죬�����ǹ����������\n";
                        case 1: return "$N����һ�£�$n��$l������������һ�����죡\n";
                        case 2: return "ֻ����$n��$l��������һ�� ...\n";
                }
        }
}

string perform_action_file(string func)

{
//return CLASS_D("ghost") + "/jinghun-zhang/" + func;
}
