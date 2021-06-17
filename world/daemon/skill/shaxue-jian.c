// By Canoe  12-12-2000
// Sigh, �Դ�������,��Ū������
#include <ansi.h>;
inherit SKILL;

mapping *action = ({
	([	"name":			"��ʬ����",
		"action":
"$N���ϸ��ֳ�һ˿�����Ц�ݣ�ͻȻʹ������ʬ���꡹��$wֱ��$n��$l",
		 "force" : 120,
        	"dodge" : -10,
        	"parry" : 5,
       	 	"damage" : 15,
        	"damage_type" : "����"
	]),
	([	"name":			"ħʬ����",
		"action":
"$N����$w�ó����콣Ӱ��һ�С�ħʬ���꡹��������Ϣ��ת��$n����",
		 "force" : 130,
        	"dodge" : -10,
        	"parry" : 10,
        	"damage" : 20,
        	"damage_type":		"����"
	]),
	([	"name":			"ʬɽѪ��",
		"action":
"$Nһ�С�ʬɽѪ���������������⣬ӳ��$n�ۻ����ң�ƽ��$n��$l",
		"force" : 140,
       		 "dodge" : -5,
        	"parry" : 5,
        	"damage" : 25,
		"damage_type":		"����"
	]),
	([	"name":			"�Ѫħ��",
		"action":
"$Nʹ��һ�С��Ѫħ�𡹣�����$w�����񿳣�����$n�ľ���ս",
		"force" : 160,
        	"dodge" : 5,
        	"parry" : 5,
        	"damage" : 30,
		"damage_type":		"����"
	]),
	([	"name":			"ħ���ʬ",
		"action":
"$N����һ����һ�С�ħ���ʬ���ó����콣Ӱ£��$n��$l��$n�����޴�",
		"force" : 180,
        	"dodge" : 10,
        	"parry" : 5,
        	"damage" : 40,
		"damage_type":		"����"
	]),
	([	"name":			"�ػ����",
		"action":
"$N��ʽһ�䣬ɱ���Ĳ���һ�С��ػ���졹���¶���,�Ƶ�$nû�л���֮��",
		"force" : 210,
        	"dodge" : 15,
        	"parry" : 15,
        	"damage" : 50,
		"damage_type":		"����"
	]),
	([	"name":			"ħ������",
		"action":
"$NԾ�����ɣ���ʽ���䣬��ħ�����졹�羪�κ��ˣ���ת�������",
		"force" : 240,
        	"dodge" : 15,
        	"parry" : 15,
        	"damage" : 60,
		"damage_type":		"����"
	]),
	
	([	"name":			"�����ħ",
		"action":
"$Nһ�С������ħ�������˺�һ����ɱ��ȥ��ͻȻ����һ��������$n��$l",
		"force" : 270,
       		 "dodge" : 25,
        	"parry" :  25,
		"damage":		70,
		"damage_type":		"����"
	]),
	([	"name":			"��ħһ��",
		"action":
"$N������������λ���һ��Ѫ��ʹ��"HIR"����ħһ����"NOR"����$n",
		"force" : 300,
        	"dodge" : 30,
        	"parry" : 15,
        	"damage": 80,
		"damage_type":		"����"
	]),
});
int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("���������Ϊ������׹��Ѫ��ѧ��Ҳû�á�\n");
	if (!(ob = me->query_temp("weapon"))
	   || (string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ����������ϰ������\n");
	return 1;
}

int practice_skill(object me)
{
	int dod=(int)me->query_skill("dodge");
	int swo=(int)me->query_skill("shaxue-jian");

	if (dod<swo/2)
		return notify_fail("����������Ͻ���������ȥ�ܿ��ܻ��˵��Լ���\n");
	if ((int)me->query("kee") < 30)
		return notify_fail("������Ƿ�ѣ�ǿ���׹��Ѫ���к����档\n");
	if ((int)me->query("force") < 5)
		return notify_fail("���������㣬ǿ���׹��Ѫ�����߻���ħ��Σ�ա�\n");
	me->receive_damage("kee", 30);
	me->add("force", -5);
	message_vision("$NĬĬ������һ�����Ȼ������һ��׹��Ѫ����\n", me);
	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword"||usage=="parry";
}

mapping query_action(object me, object weapon)
{
int zhaoshu, level;

zhaoshu = sizeof(action);
level   = (int) me->query_skill("shaxue-jian",1);

if (level < 300 )
zhaoshu--;
if (level < 270 )
zhaoshu--;
if (level < 240 )
zhaoshu--;
if (level < 210 )
zhaoshu--;
if (level < 180 )
zhaoshu--;
if (level < 150 )
zhaoshu--;
if (level < 120 )
zhaoshu--;
return action[random(zhaoshu)];
}

void skill_improved(object me)
{
        if( (int)me->query_skill("shaxue-jian", 1) > 30 
	 && (int)me->query_skill("shaxue-jian", 1)  % 10 == 0 ) {
                tell_object(me,
                        RED "\n��ͻȻ����һ�ɶ���������ͷ��ֻ������ɱ��....\n\n" NOR);
                me->add("bellicosity", 200);
	}
}

string perform_action_file(string func)
{
return ("/u/canoe/pfm") + func;
}

