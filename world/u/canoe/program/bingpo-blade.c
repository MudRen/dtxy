#include <ansi.h>

inherit SKILL;


mapping *action = ({
        ([      "name":                 "��",
                "action":
"$N�ḧ���е�$w��ͻȻ��ֻ������һ������������һ����
�����̹ǵĺ�����ȻϮ����$n��$l",
     "dodge":     -15,
     "parry":     5,
     "damage":     15,
     "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
"ֻ��$N����$w�����μ��壬������$n����֮�ʣ�
ͻȻ����һ����$n����б������",
     "dodge":     -15,
     "parry":     5,
                   "damage":                  20,
                  "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
"$Nб����𣬴���һƬƥ��Ҳ�Ƶĵ������$n��$l",
                   "dodge":                   -15,
     "parry":     5,
                   "damage":                  15,
                   "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
"$NͻȻһ���߳������е�$w����һ�������Բ����
�����ĵ����ס��$n��ͷ�����ж���$n�ĺ���",
                   "dodge":                   -15,
     "parry":     5,
                   "damage":                  20,
                   "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
"ֻ��$N��ɫһ����һ�С�ǧ����⡹ʹ������ü�ݵ��Ÿ���
$n�����ѪҺ���Ʊ����޾��ĵ��ƶ�ס��������Ҳ�·�Ҫ�����ȥ",
                   "dodge":                   -15,
     "parry":     5,
                   "damage":                  30,
                   "damage_type":     "����"
        ]),   
        ([      "name":                 "��",
                "action":
"$N���ƽ�������$w�ϴ����ĺ���ȴԽ��ԽŨ��
������ʱ��$n����ͷһ����һ������⻹Ҫ�����ĺ����Ѵ�����$n$l",
                  "dodge":                   -15,
     "parry":     5,
                   "damage":                  20,
                   "damage_type":     "����"
        ]),   
        ([      "name":                 "��",
                "action":
"$NҲ�������߶�ʮһ���߾�$w�����ؾ���һ����$nӭ��ն�£�
��Ȼֻ��һ�������µĵ���ȴ����Ų����ĺ���������$n��һ����·",
                   "dodge":                   -15,
     "parry":     5,
                   "damage":                  20,
                   "damage_type":     "����"
        ]),   
});


int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 100 )
                return notify_fail("�������������û�а취�����Ǻ�����
����Щ���������ɡ�\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade"
        ||      (string)ob->query("material") != "ice" )
                return notify_fail("���������һ�ѱ����ĵ����������Ǻ�����\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="blade"; //note, should not be able to enable with parry...ice mah:D
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 5 )
                return notify_fail("�����������������û�а취��ϰ���Ǻ�����\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        write("�㰴����ѧ����һ����Ǻ�����\n");
        return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string action)
{
    return CLASS_D("yaomo")+"/xueshan/bingpo-blade/"+action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
  object weapon = me->query_temp("weapon");     
  string msg;
       
       if( ( damage_bonus > 250 ) && (userp(me)))
          return 0;
if(me->query("force")<200) return 0;
         if ((string)me->query("family/family_name") != "��ѩɽ" )
             return 0;
 if (me->query_temp("noauto")&&(random(15)!=1)) return 0;
          
        if ((!weapon) ||((string)weapon->query("material") != "ice" ))
                return 0; 
if(damage_bonus<150) damage_bonus= 150;
          
        if (((int)me->query_skill("blade", 1)/2) > random((int)victim->query_skill("force", 1)))
             {
              victim->receive_wound("kee", (300-damage_bonus) );
              msg = HIW
                    "$NĬ�������������Ǻ����к����Ƴ���$nһ�����죬�ѱ����ˣ�\n\n"NOR;
              message_vision(msg,me,victim);
             
             };
                switch(random(3)) {
                        case 0:{ victim->receive_damage("kee",damage_bonus/3*2);
                                 msg = "ֻ��һ˿����������Ϣ���굽$n���ڣ�\n";
                                 break;};
                                
                        case 1:{  victim->receive_damage("kee",damage_bonus/2);
                                  msg = "$N��ʹ��������$n���˿�������һ��ǳǳ�İ�ӡ��\n";
                                 break;};
                                
                        case 2:{  victim->receive_damage("kee",damage_bonus);
                                 msg ="$nͻȻ���������溮����...\n";
                                 break;};
                                 
                        }
               
                             message_vision(msg,me,victim);
                return 0;
 }
