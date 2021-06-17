//������ָ�� jienan-zhi.c
// lestat...2001
//menpai skill

inherit SKILL;
#include <ansi.h>

mapping *action = ({
        ([      "action":               "��������������$n��ɫͻ�䣬$Nȴ�������ڣ����޶����ֵļ��󣬺�һ��"+HIY"��ƿ�����⡹"NOR"",
		"dodge":		-15,
		"parry":		-15,
		"force":		170,
		"damage_type":	"����",
                        "weapon":		"$N������ʳ��ָ",
	]),
	([	"action":		"$Nһʽ"+HIY"��٤Ҷ΢Ц��"NOR"��˫��ʳָ���棬ָ�����һ�����������$n��$l",
		"dodge":		-25,
		"parry":		-25,
		"force":		180,
		"damage_type":	"����",		
                        "weapon":		"$N������ʳָ",
	]),
	([	"action":		"$N����������ǰ��һʽ"+HIY"�������黨��"NOR"������ʳָ��סĴָ���������$nһ��",
		"dodge":		-15,
		"parry":		-15,
		"force":		160,
		"damage_type":	"����",
                        "weapon":		"$N������ʳָ",
	]),
	([	"action":		"$N���������ʮָ�濪��һʽ"+HIY"����������"NOR"��Сָ����$n��̫ԨѨ",
		"dodge":		-25,
		"parry":		-15,
		"force":		120,
		"damage_type":	"����",
                        "weapon":		"$N������ʳָ", 
	]),
            ([	"action":		"$N΢΢һЦ��һ��"+HIY"��ѩ�غ�����"NOR"���������ڣ�ָ�����������������ĥ��͸���޷����",
		"dodge":		-15,
		"parry":		-25,
		"force":		100,
		"damage_type":	"����",
                        "weapon":		"$N������ʳָ",
	]),
            ([	"action":		"$Nһ��"+HIY"����ɫ���ࡹ"NOR"��$n������ŵ�һ�ƿ�֮����ȴ��$P΢Ц��ͷ��ȴ�����κζ���",
		"dodge":		-55,
		"parry":		-35,
		"force":		150,
		"damage_type":	"����",
                        "weapon":		"$N������Ĵָ��ʳָ",
	]),
});

int valid_learn(object me)
{
	
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("������ָ������֡�\n");
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

	me->receive_damage("sen", 20);
	me->receive_damage("kee", 20);
	me->add("force", -10);

	return 1;
}

string perform_action_file(string func)
{
return CLASS_D("bonze") + "/jienan-zhi/" + func;
}


