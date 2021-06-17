//��ȭ changquan.c
//menpai skill(can also be used by non-menpai NPCs)

inherit SKILL;
#include <ansi.h>
mapping *action = ({
        ([      "action":
"ֻ��$N����һ�����������һ��"+RED"�������ڡ�"NOR+"��׼$n�ı��Ӻ��������˹�ȥ",
                "dodge":                -45,
                "parry":                -25,
	    "force":		190,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����һ�֣���ȭ������һ��"+RED"���β�Ѱ�ߡ�"NOR+"����$n��$l�к���ȥ",
                "dodge":                -35,
                "parry":                -15,
	    "force":		160,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N��ȭ��$n����һ�Σ�����ʹ�˸�"+RED"��Ҷ��͵�ҡ�"NOR+"��$n��$l����һץ",
                "dodge":                -15,
                "parry":                -35,
	    "force":		160,
                "damage_type":  "ץ��"
        ]),
        ([      "action":
"$N����һ������ȭ��������ȭ���磬һ�С�"+RED"�ڻ����ġ�"NOR+"�Ʋ��ɵ��ػ���$n$l",
                "dodge":                -25,
                "parry":                -15,
	    "force":		180,
                "damage_type":  "����"
        ]),
        ([      "action":
"ֻ��$N������ʽ��һ��"+RED"��˫������"NOR+"ʹ�û����з硣����ȴ����һ������$n$l",
                "dodge":                -15,
                "parry":                -35,
	    "force":		170,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N������𣬴��һ������������"+RED"�������ཻ��"NOR+"��\n������$n���һ������ȭ����$n�������˹�ȥ",
                "dodge":                -25,
                "parry":                -35,
	    "force":		120,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N�����󹭲���˫��ʹ�˸�"+RED"������Ʊա�"NOR+"��$n��$lһ��",
                "dodge":                -45,
                "parry":                -35,
	    "force":		150,
                "damage_type":  "����"
        ]),
        ([      "action":
"ֻ��$N����������һ����ȭ����$n$l������һȭ�߹�һȭ��\n��һ�е����ֻ��൱���ţ�����"+RED"������������"NOR,
                "dodge":                -5,
                "parry":                -45,
	    "force":		180,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����һ�ݣ�����ʹ�˸�"+RED"�������̸���"NOR+"������ɨ��$n��$l",
                "dodge":                -35,
                "parry":                -15,
	    "force":		150,
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nһ��ת�����ƻ��أ����Ʒ���ʹ�˸�"+RED"��������ɽ��"NOR+"��$n��ͷһ��",
                "dodge":                -25,
                "parry":                -35,
	    "force":		190,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����Ծ�𣬰����һ������$n���ţ�ȴ�Ǹ����С�\n˵ʱ����ʱ�죬ֻ��$Nһ��������˫���ѵ���$n��$l",
                "dodge":                -25,
                "parry":                -35,
	    "force":		200,
                "damage_type":  "����"
        ]),
});

int valid_learn(object me)
{
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon")
)
                return notify_fail("����ȭ������֡�\n");
        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if( (int)me->query("sen") < 30)
		return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");
	if( (int)me->query("kee") < 30 )
		return notify_fail("����������������Ϣһ�������ɡ�\n");
	if( (int)me->query("force") < 10 )
		return notify_fail("������������ˡ�\n");

	me->receive_damage("kee", 30);
	me->add("force", -10);

	return 1;
}

string perform_action_file(string func)
{
 return CLASS_D("fighter") + "/changquan/"+func;
}
