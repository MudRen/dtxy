//Ʈѩ��ɡ�Ʈѩ������Ʈѩ���䡢Ʈѩ����
//Ʈѩ���Ʈѩ���졢Ʈѩ���衢Ʈѩ���⡢Ʈѩ����
#include <ansi.h>

inherit SKILL;


mapping *action = ({
        ([      "name":                 "��",
                "action":
"$N�ḧ���е�$w��ͻȻ��ֻ������һ������������һ����
�����̹ǵĺ�����ȻϮ����$n��$l",
     "dodge":     -15,
     "parry":     -15,
     "damage":     15,
     "damage_type":     "����",
        ]),
        ([      "name":                 "��",
                "action":
"ֻ��$N����$w�����μ��壬������$n����֮�ʣ�
ͻȻ����һ����$n����б������",
     "dodge":     -15,
     "parry":     -15,
                   "damage":                  20,
                  "damage_type":     "����",
        ]),
        ([      "name":                 "��",
                "action":
"$Nб����𣬴���һƬƥ��Ҳ�Ƶĵ������$n��$l",
                   "dodge":                   -15,
     "parry":     -25,
                   "damage":                  15,
                   "damage_type":     "����",
        ]),
        ([      "name":                 "��",
                "action":
"$NͻȻһ���߳������е�$w����һ�������Բ����
�����ĵ����ס��$n��ͷ�����ж���$n�ĺ���",
                   "dodge":                   -15,
     "parry":     -35,
                   "damage":                  20,
                   "damage_type":     "����",
        ]),
        ([      "name":                 "��",
                "action":
"ֻ��$N��ɫһ����һ�С�ǧ����⡹ʹ������ü�ݵ��Ÿ���
$n�����ѪҺ���Ʊ����޾��ĵ��ƶ�ס��������Ҳ�·�Ҫ�����ȥ",
                   "dodge":                   -15,
     "parry":     -25,
                   "damage":                  30,
                   "damage_type":     "����",
        ]),   
        ([      "name":                 "��",
                "action":
"$N���ƽ�������$w�ϴ����ĺ���ȴԽ��ԽŨ��
������ʱ��$n����ͷһ����һ������⻹Ҫ�����ĺ����Ѵ�����$n$l",
                  "dodge":                   -15,
     "parry":     -25,
                   "damage":                  20,
                   "damage_type":     "����",
        ]),   
        ([      "name":                 "��",
                "action":
"$NҲ�������߶�ʮһ���߾�$w�����ؾ���һ����$nӭ��ն�£�
��Ȼֻ��һ�������µĵ���ȴ����Ų����ĺ���������$n��һ����·",
                   "dodge":                   -15,
     "parry":     -45,
                   "damage":                  20,
                   "damage_type":     "����",
        ]),   
});

mapping *action_piaoxue = ({
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ���\n"+NOR"$N�ḧ���е�$w��̧�����죬ͻȻһ����Ȼ��ɵĵ���Ϯ����$n��$l",
     "dodge":     -20,
     "parry":     -20,
     "force":     20,
     "damage":     20,
     "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$Nб����𣬴���һƬƥ��Ҳ�Ƶĵ������$n��$l",
     "dodge":     -30,
     "parry":     -30,
     "force":     30,
     "damage":     30,
                  "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$N�߾�$w��$nӭ����ն����",
     "dodge":     -40,
     "parry":     -40,
     "force":     40,
     "damage":     40,
                   "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$N����$w��˲������$n�����ŵ�֮�࣬$n������ϯ��",
     "dodge":     -50,
     "parry":     -50,
     "force":     50,
     "damage":     50,
                   "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$N�ᵶԶ�ݣ�$n����ͷһ����һ������⻹Ҫ�����ĺ����Ѵ�����$n$l",
     "dodge":     -60,
     "parry":     -60,
     "force":     60,
     "damage":     60,
                   "damage_type":     "����"
        ]),   
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$N���ܲ��ˣ�$w��������쵶�⣬��ס��$n��ͷ�����ж���$n�ĺ���",
     "dodge":     -60,
     "parry":     -60,
     "force":     70,
     "damage":     70,
                   "damage_type":     "����"
        ]),   
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$N��ɫ������$w������ʢ��$n�����ѪҺ���Ʊ����޾��ĺ�����ס��������Ҳ�·�Ҫ�����ȥ",
     "dodge":     -60,
     "parry":     -60,
     "force":     80,
     "damage":     80,
                   "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$N��������������ע��$w��$w������Ų����ĺ���������$n��һ����·",
     "dodge":     -70,
     "parry":     -70,
     "force":     90,
     "damage":     90,
                   "damage_type":     "����"
        ]),
        ([      "name":                 "��",
                "action":
BLINK+HIW"Ʈѩ����\n"+NOR"$N��$w�߸����������ѩ��$wΪ���Ŀ�ʼ���ۣ�������ؼ�������$w�Ը߿շ�׹����$n",
     "dodge":     -80,
     "parry":     -80,
     "force":     100,
     "damage":     100,
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
        int i = me->query_temp("piaoxue");
        if( i ) return action_piaoxue[i-1];
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
       
       // emotion: why restrict human player? // if( ( damage_bonus > 250 ) && (userp(me)))
       // emotion:  return 0;
if(me->query("force")<200) return 0;
         if ((string)me->query("family/family_name") != "��ѩɽ" )
             return 0;
// if (me->query_temp("noauto")&&(random(15)!=1)) return 0;
          
        if ((!weapon) ||((string)weapon->query("material") != "ice" ))
                return 0; 
        // emotion: // if(damage_bonus<150) damage_bonus= 150;
          
        if (((int)me->query_skill("blade")/2) > random((int)victim->query_skill("force")))
             {
              // emotion: bug what if damage_bonus is greater than 300?? // victim->receive_wound("kee", (300-damage_bonus) );
              victim->receive_wound("kee", damage_bonus/3 );  // emotion
              msg = HIW"\n$N"HIW+"Ĭ�������������Ǻ����к����Ƴ���$n"+HIW"һ�����죬�ѱ����ˣ�"NOR;
              message_vision(msg,me,victim);
             
             };
             if( random(damage_bonus/2) > victim->query_str()/5) {
                switch(random(3)) {
                        case 0:{ victim->receive_damage("kee",damage_bonus/3*2);
                                 //msg = WHT"ֻ��һ˿����������Ϣ���굽$n"+WHT"���ڣ�\n"NOR;
                                 return WHT"ֻ��һ˿����������Ϣ���굽$n"+WHT"���ڣ�\n"NOR;
                                 break;};
                                
                        case 1:{  victim->receive_damage("kee",damage_bonus/2);
                                  return WHT"$N"+WHT"��ʹ��������$n"WHT"���˿�������һ��ǳǳ�İ�ӡ��\n"NOR;
                                 break;};
                                
                        case 2:{  victim->receive_damage("kee",damage_bonus);
                                  return WHT"$n"+WHT"ͻȻ���������溮����...\n"NOR;
                                 break;};
                                 
                        }
               
                             //message_vision(msg,me,victim);
           }
                return 0;
 }
