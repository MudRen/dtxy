// ice_fire_zhang.c ����������
// /daemon/skill/ice_fire_zhang.c
// writted by mind 2001/2
#include <ansi.h>
inherit SKILL;



mapping *action = ({
([      "action" : "$Nһʽ"+HIC"������ǧ��ѩ��"NOR+"��˫�ƴ󿪴�ϣ�ֱ��$n��$l��ȥ",
        "dodge": -10,
        "parry": -10,
        "force": 100,
        "damage_type" : "����",
        "weapon" : "˫��",
]),
([      "action" : "$N����һ�䣬һʽ"+HIC"����������ѩ��"NOR+"��˫��������ֱ������$n��$l",
        "dodge": 0,
        "parry": -20,
        "force": 150,
        "damage_type" : "����",
        "weapon" : "˫��",
]),
([      "action" : "$Nʹһʽ"+HIC"����ѩ������������"NOR+"��������΢����棬������ϸ�����ֱȡ$n��$l",
        "dodge": 10,
        "parry": -30,
        "force": 200,
        "damage_type": "����",
        "weapon": "������",
]),
([      "action" : "$Nʹһʽ"+HIC"����ѩƾ�ٽ�ɽ����"NOR+"��˫��Ю��籩ѩ֮�ƣ��͵�����$n��$l",
        "dodge": 0,
        "parry": -10,
        "force": 250,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIC"����˪��÷����ɺ��"NOR+"��˫�ƴ�����ɪ�ĺ���������$n��$l",
        "dodge": 10,
        "parry": -50,
        "force": 300,
        "damage_type" : "����",
]),
([      "action" : "$N����һ�֣�һʽ"+HIR"�����������ղ׺���"NOR+"������������������$n�����ȥ",
        "dodge": -10,
        "parry": -20,
        "force": 120,
        "damage_type" : "����",
        "weapon" : "˫��",
]),
([      "action" : "$N����һת��ʹ��һʽ"+HIR"���������졹"NOR+"��ֻ��������Ӱ��ס��$n��ȫ��",
        "dodge": 10,
        "parry": -30,
        "force": 170,
        "damage_type" : "����",
]),
([      "action" : "$N����Ȼһ�䣬ʹ��һʽ"+HIR"��������͡�"NOR+"����Ӱǧ����ã���$n�޷�����",
        "dodge": 10,
        "parry": -60,
        "force": 300,
        "damage_type" : "����",
]),
([      "action" : "$NͻȻ����һ����ʹ��һʽ"+HIR"���ǿݷ��١�"NOR+"���������أ�������ӯ������$n��$l",
        "dodge": 10,
        "parry": -40,
        "force": 250,
        "damage_type": "����",
        "weapon": "������",
]),
([      "action" : "$N��Хһ��������һʽ"+HIC"�����ǵ���"NOR+"��������չ"+HIR"�����浶��"NOR+"�����ɽ�Ȼ��ͬ����������$n��$l",
        "dodge": 0,
        "parry": 0,
        "force": 500,
        "damage_type" : "����",
])
});

mapping *action1 = ({        
([      "action": "$N����Ԫ������͸��������"+BLINK+HIW"���ǵ�"+NOR"һʽ"+HIW"������˪�꡻"NOR+"�������ޱȵػ���$n",
        	"force":               400,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),
([      "action": "$N����ȫ��֮��������"+BLINK+HIR"���浶"+NOR"һ��"+HIR"�������Ի�"NOR+"�������ޱȵػ���$n",
                "force":               400,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),
([      "action" : "$N��Хһ��������"+BLINK+HIW"�����ǵ���"NOR+"������"+BLINK+HIR"�����浶��"NOR+"�����ɽ�Ȼ��ͬ����������$n",
                "force":               500,
                "dodge":                -80,
                "parry":                -80,
                "damage_type":  "����"
        ]),
});

int valid_enable(string usage)
{
        return usage=="unarmed" || usage=="parry" ;
}

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
   return notify_fail("�����������Ʊ�����֡�\n");
    
    if ((int)me->query("max_force") < 400)
   return notify_fail("�������̫�����޷�������������");
        if( (string)me->query_skill_mapped("force")!= "butian-force")
                return notify_fail("����ڹ��ķ������޷���ϰ��\n");
    return 1;
}


mapping query_action(object me, object weapon)
{
	int i;
	i = me->query_temp("icefire");
	if( i )
		return action1[i-1];
	else
	{
		i = random(sizeof(action));
		me->set_temp("sanxian/icefire",i);
		return action[i];
	}
}

int practice_skill(object me)
{
        if ((int)me->query("kee")<30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("force") < 40)
                return notify_fail("����������������������ơ�\n");
        me->receive_damage("kee",30);
        me->add("force",-30);
        write(HIW"���������죬��˸��ͣ��\n"NOR);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int force;
        int i;
        int k;
        if( damage_bonus < 100 ) return 0;
	i = me->query_temp("icefire");
	if( !i ) 
	{
		k = me->query_temp("sanxian/icefire");
		if( k < 5 ) i = 1;
		if( k >= 5 && k < 8 ) i = 2;
		if( k >= 8 ) i =3;
	}
	if( wizardp(me) ) tell_object(me,"");
        if( random(me->query_skill("ice_fire_zhang",1)) > 60 )
        victim->apply_condition("ice_fire_poison", random(me->query_skill("ice_fire_zhang")/10) + 1 + victim->query_condition("ice_fire_poison"));
        if( random(damage_bonus) > victim->query_str()/4 ) 
        {
               	victim->receive_wound("kee", (damage_bonus - 60) / 4 );
               	if( i == 1 )
               		return HIC"$N����һ�ߣ�һ��������������$n��$l��\n"NOR;
               	if( i == 2 )
               		return HIR"$n��$l��$N�߶��Ļ��浶�յ�Ѫ��ģ����\n"NOR;
               	if( i == 3 )
               		return HIG"$N���ֱ��ǵ������ֻ��浶��������Ȼ��ͬ���ھ�ȫ��$n���ڱ�����\n"NOR;
               	switch(random(3)) 
               	{
                       	case 0: return HIR"$n��$l��$N�߶��Ļ��浶�յ�Ѫ��ģ����\n"NOR;
                       	case 1: return HIC"$N����һ�ߣ�һ��������������$n��$l��\n"NOR;
                       	case 2: return HIG"$N���ֱ��ǵ������ֻ��浶��������Ȼ��ͬ���ھ�ȫ��$n���ڱ�����\n"NOR;
               	}
        }
        if( random(3*me->query_skill("ice_fire_zhang",1)) > random(2*damage_bonus) )
        {
                        victim->receive_wound("kee", damage_bonus);
                        victim->receive_wound("sen", damage_bonus);
                        victim->add("force", -damage_bonus);
                        victim->set("force_factor", 0);
                        return
HIB"$n���û���յ����ģ�Ԫ���ɢ������������Ȼ�޹⣡\n"NOR;
        }
}

string perform_action_file(string func)
{
return CLASS_D("sanxian") + "/ice_fire_zhang/" + func;
}

void skill_improved(object me)
{
        if( (string)me->query("family/family_name")!="����ɢ��")
        {
                tell_object(me,
                        HIW "\n����Ʋ�ס���ڵĺ�����ҵ����Ϣһ���߻���ħ�ˣ���....\n\n" NOR);
                me->skill_death_penalty();
                me->delete_skill("ice_fire_zhang");
                me->unconcious();
        } 
}

