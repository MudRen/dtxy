//Ħ����
//lestat modi for dtxy 2001
#include <ansi.h>

inherit SKILL;

mapping *action = ({
	([	"action":		"$Nһ��"+HIY"����벶��ʽ��"NOR"������ץ��$n�ĵ������$n�����Է���һ˲�䣬����ȴ��������$n��$l",
		"dodge":		-10,
		"parry":		-10,
		"force":		160,
		"damage_type":	"����",
                        "weapon":		"����ʳָ",
	]),
	([	"action": "$N˫��һ������"+HIM"��÷����䡹"NOR"��˫���紩������һ�����·��ɡ�\n$n�������ۣ�ɲ�Ǽ�$N����������ǰ",
		"dodge":		-25,
		"parry":		-15,
		"force":		180,
		"damage_type":	"����",
                        "weapon":		"����",
	]),
	([	"action":		"ֻ��$Nһת��һָ��в�´���������$n��$l��ȴ����һ��"+HIC"���������ߡ�"NOR,
		"dodge":		-25,
		"parry":		-10,
		"force":		200,
		"damage_type":	"����",
                        "weapon":		"����ʳָ",
	]),
	([	"action":		"$N˫��һ������������ƶ�������һ��"+YEL"����ʿ��ɽ��"NOR"����һ�������$n��$l",
		"dodge":		-20,
		"parry":		-20,
		"force":		140,
		"damage_type":	"����",
                        "weapon":		"����", 
	]),
            ([	"action":		"$Nһ��"+WHT"������������"NOR"�������ڿ����黮�˸��뻡������$n��$l",
		"dodge":		-30,
		"parry":		-10,
		"force":		170,
		"damage_type":	"����",
                        "weapon":		"����",
	]),
            ([	"action":		"����$Nһ��ŭ�����ָ߸߾���һʽ"+HIG"��������ɽ��"NOR"������$n��$l",
		"dodge":		-10,
		"parry":		-10,
		"force":		220,
		"damage_type":	"����",
                        "weapon":		"����",
	]),
	([  "action": 	HIC"$N˫��һ��������ͻ�����֮�⣬����һ�������������ɫ�������������$n"NOR,
                "dodge":                -70,
                "parry":                -80,
                "force":                400,
                "damage_type":  "����",
	 ]),
});

int valid_learn(object me)
{
	
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("��Ħ���ֱ�����֡�\n");
	return 1;
}

int valid_enable(string usage)
{
	return usage=="unarmed";
}

mapping query_action(object me, object weapon)
{
        int i;
        i=me->query_temp("moyunshou_per");
        if( !me->query_temp("moyunshou_per") ) {
        return action[random(6)];
        }else {
        return action[i];
        }
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 5 )
                return notify_fail("�����������������û�а취��ϰĦ���֡�\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        write("�㰴����ѧ����һ��Ħ���֡�\n");
        return 1;

}

string perform_action_file(string func)
{
return CLASS_D("yaomo") + "/kusong/moyun-shou/" + func;
}


