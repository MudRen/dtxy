//Cracked by Roath

#include <ansi.h>

inherit SKILL;

mapping *action = ({
    ([  "action":       "$Nʹһ�С���Ӣ�ͷס�����������Ʈ������$w����ʵʵ�ó���㽣���׷���������$n$l",
        "dodge":     -5,
        "parry":                -10,
        "damage":        50,
        "damage_type":  "����"
        ]),
    ([  "action":       "$N�趯$w��һʽ�������һ�����������$n����һ�Σ�����$w�������佣��Ю�Ż�����������$n��$l",
        "dodge":     -35,
        "parry":                -5,        
        "damage":        55,
        "damage_type":  "����"
    ]),
    ([ "action":        "$N������$nһת������$w����һָ��һʽ���������꡹�ó����콣Ӱ����$n$l�����ӳ�����",
     "dodge":     -10,
     "parry":                -15,

        "damage":        60,
                "damage_type":  "����"
        ]),
    ([  "action":       "$N����ƮȻ�����ڰ��������һ������Ȼһʽ�����Ƿɻ�������$w�������޵�������$n��$l",
     "dodge":     -10,
     "parry":                -15,

        "damage":       65,
                "damage_type":  "����"
        ]),
    ([  "action":       "$N�������࣬һʽ��ϸ���ɷ��ء�ͷ�½��ϣ�һ�С������䡹����$w���һ����������$n��$l",
     "dodge":     -30,
     "parry":                -5,

        "damage":       70,
        "damage_type":  "����"
    ]),
    ([  "action":       "$Nһ�����ʹ�������컨�꡹������$w�ó����컨�꣬Ѹ����������$n��$l",
     "dodge":     -30,
     "parry":                -5,

        "damage":       75,
        "damage_type":  "����"
    ]),
    ([  "action":    "$N��̾һ��������$w����һ����һʱ���仨���⡹��$w��ȻԾ��ٿ�Ļ��������¶���һ���ƮȻ����$n��$l",
       "dodge":     -20,
       "parry":                -20,
        "damage":       70,
        "damage_type":  "����"
    ]),

});

int valid_learn(object me)
{
        object ob;

    if( (int)me->query_skill("zixia-shengong",1) < 50)
        return notify_fail("�����ϼ�񹦻�򻹲�����\n");

if( (int)me->query_skill("yujianshu",1) < 50)
return notify_fail("�����������򻹲�����\n");

    if( (int)me->query("max_force") < 300 )
        return notify_fail("��������������������Ľ���\n");

        if (!objectp(ob = me->query_temp("weapon"))
        || (string)ob->query("skill_type") != "sword")
                return notify_fail("���������һ�ѽ�����ѧϰ������\n");

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
        object ob;

    if( (int)me->query("kee") < 30
    ||  (int)me->query("force") < 5 )
        return notify_fail("�����������������û�а취��ϰ�Ľ���\n");

        if (!objectp(ob = me->query_temp("weapon"))
        || (string)ob->query("skill_type") != "sword")
                return notify_fail("���������һ�ѽ�����ϰ��������\n");

    me->receive_damage("kee", 30);
        me->add("force", -5);
    write("�㰴����ѧ����һ���Ľ���\n");
        return 1;
}

string perform_action_file(string action)
{
        return CLASS_D("shushan") + "/mindsword/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if(userp(me)){
        if( random(me->query_skill("mindsword")) < 50) {
         
           victim->receive_damage("kee",random(me->query_skill("mindsword"))+200);
           return HIM"�ۼ�$n��������������ԭ��$N�����������У������ת$n��Ȼ���� \n"NOR;
         
          }
       }
}

int ob_hit(object ob,object me,int damage)
{
  message_vision(HIY"�ۿ�$N��һ����Ҫ����$n,����$n�����н��ʵ�ס�ˣ�\n"NOR,ob,me);
  return -damage/2;
}

