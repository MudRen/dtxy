//zhuihun-sword
//lestat 2001 for hell

#include <ansi.h>
#include <combat.h>
inherit SKILL;

int yunwu(object me, object victim, object weapon, int damage);
mapping *action = ({
        ([      "name":                 "Ⱥħ����",
                "action":
"$N����$wһ����"+HIB"��Ⱥħ���衹"NOR"ʹ��������������������$n���Ƶ��ľ���ѣ����֪$N�������˶�����",
		"parry":		-10,
                "dodge":                -10,
                "damage":               25,
				"lvl" : 0,
                "damage_type":  "����"
        ]),
        ([      "name":                 "�������",
                "action":               
"$N$w������仯������һ��"+HIB"���������"NOR"����������֮���£������޶�������׽����$n����һ���ۻ����ң��ٸ����Ӧ��",
		"parry":		-10,
                "dodge":                -10,
                "damage":               25,
				"lvl" : 20,
                "damage_type":  "����"
        ]),
        ([      "name":                 "�ٹ�ҹ��",
                "action":
"$N�趯$w��һ��"+HIB"���ٹ�ҹ�С�"NOR",ͻȻһ�����壬$wЮ�������������$n��$l",
		"parry":		-20,
                "dodge":                -15,
                "damage":               20,
				"lvl" : 40,
                "damage_type":  "����"
        ]),
        ([      "name":                 "������·",
                "action":
"$N����$wһ�����ó��������⣬����һ��㱼䣬����"+HIB"��������·��"NOR"$w��бб�ص�����$n��$l",
		"parry":		-20,
                "dodge":                -20,
                "damage":               25,
				"lvl" : 60,
                "damage_type":  "����"
        ]),
        ([      "name":                 "��Ӱ����",
                "action":
"$N����$w���������ͻȻ���ڿ���һ����һ��"+HIB"����Ӱ������"NOR",���а�������֮����$w��·������ȣ���̼侹Ȼ���Ƶ���$n����",
		"parry":		-10,
                "dodge":                -20,
                "damage":               15,
				"lvl" : 80,
                "damage_type":  "����"
        ]),
        ([      "name":                 "��ع�",
                "action":
"$N��Ȼ������һչ��ʹ��"+HIB"����ع���"NOR"����$w�����Ȼ֮���������⻷��ת����ʱ֮���ѽ�$n����һ�Ž���֮��",
		"parry":		-20,
                "dodge":                -20,
                "damage":               20,
				"lvl" : 100,
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

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        string *msg1,*msg2;
        msg1 = ({
		HIB"$N����$w"+HIB"�������裬��������������ʵʵ�����˶�Ŀ���仯�Ź�֮����$n�������º�Ȼ��"NOR,
		HIB"$N����$w"+HIB"ԽʹԽ�죬һ��"+HIR"���������ޡ�"+HIB"�����ƾ���ӿ��$n���ɵ�ĿΪ֮ѣ��"NOR,
		HIB"ֻ��$N����$w"+HIB"���б�ã�������ȣ��廨���ţ�������$n������ǰ����һƬ���������ȥ��"NOR,
        });
        msg2 = ({
		HIR"����һ�����Ѫ��$w"+HIR"�½��˳�����$n��Ų��Ծ�������мܣ�ʼ���Ѳ���$N�Ľ������֣���Ѫ���������ܽ�����һ����Ȧ��$N���Ѵ̳�һ����"NOR,
		HIW"$Nһ����ռ�Ȼ����������������һ��$w"+HIW"�������ߣ�������������$n�Ĺ����д�����ȥ��ֻ�Ƶ�$n�������ˣ�"NOR,
		HIW"$n����һ������֮�£��������ˣ�$N����$w"+HIW"������������������������������䣬�仯�켫��"NOR,

        });
	if(me->query_temp("yunwu") && me->query_temp("yunwu_hit") ){
        me->add("force", -10);
	me->delete_temp("yunwu_hit");
        return ([
        "action":msg2[random(sizeof(msg2))] ,
        "dodge" : -50,
        "parry" : -50,
        "damage" : 70,
        "force" : 100,
        "damage_type":"����"]);
        }
        else if (me->query_temp("yunwu") ){
        me->add("force", -10);
        return ([
        "action":msg1[random(sizeof(msg1))] ,
        "dodge" : -60,
        "parry" : -60,
        "damage" : 80,
        "force" : 120,
	"post_action": (: yunwu :),	
        "damage_type":"����"]);
        }

/*
        level   = (int) me->query_skill("zhuihun-sword",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];*/
		return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 50
        ||      (int)me->query("force") < 50 )
                return notify_fail("�����������������û�а취��ϰ׷�꽣��\n");
        me->receive_damage("kee", 15);
        me->add("force", -5);
//        write("�㰴����ѧ����һ��׷�꽣����\n");
        return 1;
}


int yunwu(object me, object victim, object weapon, int damage)
{

string msg,str; 
        if(damage==RESULT_FORCE ||damage==RESULT_DODGE || damage==RESULT_PARRY) return 1;

	   else if ( (victim->query("eff_kee")<0 || !living(victim)) && victim->query_skill("force") > 100 ) {
        message_vision(HIR"\nֻ��$n�˿���һ��Ѫ����ӿȪ�����������ԭ��$p�н�������δ��������Ѫ�Ƶô��˿��м���������ȹ��죬�ֿɲ���\n" NOR, me,victim);
		me->delete_temp("yunwu");
str=victim->name()+HIM"��"+me->name()+"����ڤ��ѧ"NOR+HIB"���������ޡ�"+HIM"�����ˣ���˵"+victim->name()+"��ʬ�������ף�";
if( !random(5) ) message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
                return 1;
	   }
	else{
	me->set_temp("yunwu_hit", 1);
        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));

	}
}

void skill_improved(object me)
{
        if( (int)me->query_skill("zhuihun-sword", 1)  % 10 == 0 ) {
                tell_object(me,
                        RED "\n��ͻȻ����һ�ɶ���������ͷ��ֻ������ɱ��....\n\n" NOR);
                me->add("bellicosity", 100);
        } else
                me->add("bellicosity", 100);
}

string perform_action_file(string func)
{
return CLASS_D("ghost") + "/zhuihun-sword/" + func;
}



