//�����β�����dragonfight.c
// by canoe 2000-11-23
// /daemon/skill/dragonfight.c
// �������Զ�����Ч��

#include <ansi.h>
inherit SKILL;

mapping *action = ({
	([	"action":
"$N����Ծ��һ�С��������졹��˫������ɽ����֮�ƻ���$n��$l",
		"dodge":		-10,
		"parry":		-10,
		"force":		150,
		"damage_type":		"����",
		"weapon" :		"˫��",
		"parry_msg":	"ֻ�������ϡ�һ������$N���ָ�",
	]),
	([	"action":
"$N���˷�����ͻȻ������ǰ����ָ�繳����׼$n��$lһ��ץ�˹�ȥ",
		"dodge":		10,
		"parry":		-20,
		"force":		100,
		"damage_type":		"ץ��",
		"weapon":		"������ָ",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
	]),
	([	"action":
"ֻ��$Nһ����˫��������һ��ɨ��$n����һ�С�������β�������Ƿ���ʤ��",
		"dodge":		-10,
		"parry":		-20,
		"force":		120,
		"damage_type":		"����",
		"weapon":		"˫��",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
	]),
	([	"action":
"$N����������ʹ��һ�С���ս��Ұ����Х���к�����ϣ���$nֱײ����",
		"dodge":		10,
		"parry":		-10,
		"force":		100,
		"damage_type":		"ײ��",
		"weapon":		"ȫ��",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
	]),
            ([	"action":
"ֻ��$Nһ������ڰ�գ�һ�С������ĺ�������δ��������ȫ��������$n",
		"dodge":		0,
		"parry":		-20,
		"force":		150,
		"damage_type":		"����",
		"weapon":		"����",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
	]),
            ([	"action":
"$N����һ������$n�������һȭ�����С������������������ף������ޱ�",
		"dodge":		10,
		"parry":		-30,
		"force":		180,
		"damage_type":		"����",
		"weapon":		"ȭͷ",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
	]),
});

int valid_learn(object me)
{
	if( (int)me->query_skill("dragonforce",1) < (int)me->query_skill("dragonfight",1)/2)
		return notify_fail("��������ķ���������տ���޷������������β�����\n");


	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("�����β���������֡�\n");
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
        if( (int)me->query_skill("dragonforce",1) < (int)me->query_skill("dragonfight",1)/2)
                return notify_fail("��������ķ���������տ���޷������������β�����\n");

	if( (int)me->query("sen") < 50)
		return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");

	if( (int)me->query("kee") < 50 )
		return notify_fail("����������������Ϣһ�������ɡ�\n");

	if( (int)me->query("force") < 20 )
		return notify_fail("������������ˡ�\n");

	me->receive_damage("kee", 30);
	me->add("force", -20);

	return 1;
}

string perform_action_file(string func)
{
return CLASS_D("dragon") + "/dragonfight/" + func;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
  string msg;
  int skills_extra=(int)me->query_skill("dragonfight", 1);       
       if( ( damage_bonus > 500 ) && (userp(me)))
          return 0;
         if ((string)me->query("family/family_name") != "��������" )
             return 0;
             
        if (!(me->query_temp("dragonfinger"))) return 0;
          
        if ((skills_extra/2) > random((int)victim->query_skill("parry", 1)))
             {
               victim->receive_wound("kee", (500-damage_bonus) );
            // victim->receive_wound("kee", (damage_bonus) );
              msg = HIW
                    "$Nһ��ŭ�����λó�������Ӱ����������$n������\n\n"NOR;
              message_vision(msg,me,victim);
             
             }
                switch(random(3)) {
                        case 0:{ victim->receive_damage("kee",damage_bonus/8);
                                 msg = HIG "$nһ�����飬��$N���������صػ����Ȳ���\n" NOR;
                                 break;};
                                
                        case 1:{  victim->receive_damage("kee",damage_bonus/4);
                                  msg =HIY "������Ӱ�У�$nͻȻ������ͷ������ð���ǣ�ˤ���ڵ�!\n" NOR;
                                 break;};
                                
                        case 2:{  victim->receive_damage("kee",damage_bonus*2/3);
                                 msg =HIR "��Ӱ�����������������棬$n��ʱ���յ����������\n" NOR;
                                 break;};
                                 
                        }
               
                             message_vision(msg,me,victim);
                return 0;
                          
}
