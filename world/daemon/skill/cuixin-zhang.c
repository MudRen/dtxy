//�������ơ� jinhun-zhang.c
//menpai skill
//lestat �޸���2001 for��ѩɽ
#include <ansi.h>

inherit SKILL;

mapping *action = ({
        ([      "action":
"ֻ��$N�������������ֻ��أ��������ĳʰ��죬һ��"+RED"������Σ¥��ϸϸ��"NOR"����һ������֮������$n$l",
                "dodge":                -35,
                "parry":                -45,
	        "force":		120,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N��������������λ��˫��һ��ʹһ��"+RED"����ɫ�̹�����"NOR"������ͻȻ����������$n$lһ��һ��",
                "dodge":                -25,
                "parry":                -25,
	        "force":		120,
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nһ��"+RED"������˭��ƾ���⡹"NOR"���ֱ۾���û����ͷ�Ƶ�����һ������������ػ�����$n$l",
                "dodge":                -45,
                "parry":                -35,
	        "force":		120,
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nһʽ"+RED"��������ͼһ��"NOR"��˫���ڿ����л����������죡�����ݺ���ͻȻ�ɳ�һ�ƣ�������Ϣ������$n$l",
                "dodge":                -45,
                "parry":                -5,
	        "force":		100,
                "damage_type":  "����"
        ]),
        ([      "action":
"ֻ��$Nһ����Х����һ��"+RED"��Ϊ���������㲡�"NOR"����������ˮ�����������ƣ�������ת�����಻��������$nl����Ҫ��",
                "dodge":                -25,
                "parry":                -50,
	        "force":		120,
                "damage_type":  "����"
        ]),
        ([      "action":
HIW"$N����������ת�����������ݰ���$n"NOR+HIW"��ȥ��תһȦ��һ�ƣ����Ʋ���$n"NOR+HIW"��$l"NOR,
                "dodge":                -60,
                "parry":                -80,
	        "force":		360,
                "damage_type":  "����"
        ]),

});

int valid_learn(object me)
{
	if( (string)me->query_skill_mapped("force")!= "ningxie-force")
     return notify_fail("�����Ʊ�����ϱ�����Ѫ����������\n");
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("�������Ʊ�����֡�\n");
	return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
        int i;
        i=me->query_temp("cuixin_per");
        if( !me->query_temp("cuixin_per") ) {
        return action[random(5)];
        }else {
        return action[i];
        }
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
return CLASS_D("yaomo") + "/xueshan/cuixin-zhang/"+func;
}

