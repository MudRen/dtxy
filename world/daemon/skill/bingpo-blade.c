//飘雪天成、飘雪初降、飘雪零落、飘雪飞舞
//飘雪万里、飘雪漫天、飘雪冰凌、飘雪冰封、飘雪穿云
#include <ansi.h>

inherit SKILL;


mapping *action = ({
        ([      "name":                 "无",
                "action":
"$N轻抚手中的$w，突然间只见刀光一闪，再闪，又一闪！
三道刺骨的寒气已然袭上了$n的$l",
     "dodge":     -15,
     "parry":     -15,
     "damage":     15,
     "damage_type":     "割伤",
        ]),
        ([      "name":                 "无",
                "action":
"只见$N倒提$w，身形急冲，就在与$n错身之际，
突然反手一刀从$n后脑斜劈而下",
     "dodge":     -15,
     "parry":     -15,
                   "damage":                  20,
                  "damage_type":     "劈伤",
        ]),
        ([      "name":                 "无",
                "action":
"$N斜身飞起，带出一片匹练也似的刀光卷向$n的$l",
                   "dodge":                   -15,
     "parry":     -25,
                   "damage":                  15,
                   "damage_type":     "劈伤",
        ]),
        ([      "name":                 "无",
                "action":
"$N突然一脚踢出，手中的$w划出一道轻妙的圆弧，
淡淡的刀光封住了$n的头脸，切断了$n的呼吸",
                   "dodge":                   -15,
     "parry":     -35,
                   "damage":                  20,
                   "damage_type":     "割伤",
        ]),
        ([      "name":                 "无",
                "action":
"只见$N脸色一寒，一招「千里冰封」使出，从眉捷到脚跟，
$n周身的血液都似被这无尽的刀势冻住，而生命也仿佛要离体而去",
                   "dodge":                   -15,
     "parry":     -25,
                   "damage":                  30,
                   "damage_type":     "劈伤",
        ]),   
        ([      "name":                 "无",
                "action":
"$N刀势渐慢，而$w上带出的寒气却越来越浓。
就在这时，$n的心头一紧，一道比针尖还要锐利的寒气已刺上了$n$l",
                  "dodge":                   -15,
     "parry":     -25,
                   "damage":                  20,
                   "damage_type":     "刺伤",
        ]),   
        ([      "name":                 "无",
                "action":
"$N也不管三七二十一，高举$w呼！地就是一刀向$n迎面斩下！
虽然只有一刀，可怕的刀势却似万古不化的寒冰封死了$n的一切退路",
                   "dodge":                   -15,
     "parry":     -45,
                   "damage":                  20,
                   "damage_type":     "劈伤",
        ]),   
});

mapping *action_piaoxue = ({
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪天成\n"+NOR"$N轻抚手中的$w，抬首望天，突然一道浑然天成的刀光袭上了$n的$l",
     "dodge":     -20,
     "parry":     -20,
     "force":     20,
     "damage":     20,
     "damage_type":     "劈伤"
        ]),
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪初降\n"+NOR"$N斜身飞起，带出一片匹练也似的刀光卷向$n的$l",
     "dodge":     -30,
     "parry":     -30,
     "force":     30,
     "damage":     30,
                  "damage_type":     "劈伤"
        ]),
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪零落\n"+NOR"$N高举$w向$n迎面连斩数刀",
     "dodge":     -40,
     "parry":     -40,
     "force":     40,
     "damage":     40,
                   "damage_type":     "劈伤"
        ]),
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪飞舞\n"+NOR"$N挥舞$w，瞬间向着$n劈出九刀之多，$n被刀光席卷",
     "dodge":     -50,
     "parry":     -50,
     "force":     50,
     "damage":     50,
                   "damage_type":     "劈伤"
        ]),
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪万里\n"+NOR"$N提刀远遁，$n的心头一紧，一道比针尖还要锐利的寒气已刺上了$n$l",
     "dodge":     -60,
     "parry":     -60,
     "force":     60,
     "damage":     60,
                   "damage_type":     "劈伤"
        ]),   
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪漫天\n"+NOR"$N不管不顾，$w狂舞出漫天刀光，封住了$n的头脸，切断了$n的呼吸",
     "dodge":     -60,
     "parry":     -60,
     "force":     70,
     "damage":     70,
                   "damage_type":     "劈伤"
        ]),   
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪冰凌\n"+NOR"$N脸色冰寒，$w寒气更盛，$n周身的血液都似被这无尽的寒气冻住，而生命也仿佛要离体而去",
     "dodge":     -60,
     "parry":     -60,
     "force":     80,
     "damage":     80,
                   "damage_type":     "劈伤"
        ]),
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪冰封\n"+NOR"$N将寒冰真气缓缓注入$w，$w化作万古不化的寒冰封死了$n的一切退路",
     "dodge":     -70,
     "parry":     -70,
     "force":     90,
     "damage":     90,
                   "damage_type":     "劈伤"
        ]),
        ([      "name":                 "无",
                "action":
BLINK+HIW"飘雪穿云\n"+NOR"$N将$w高高抛起，漫天飞雪以$w为中心开始凝聚，当天空重见清明，$w自高空飞坠劈向$n",
     "dodge":     -80,
     "parry":     -80,
     "force":     100,
     "damage":     100,
                   "damage_type":     "劈伤"
        ]),   
});

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 100 )
                return notify_fail("你的内力不够，没有办法练冰魄寒刀，
多练些内力再来吧。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade"
        ||      (string)ob->query("material") != "ice" )
                return notify_fail("你必须先找一把冰做的刀才能练冰魄寒刀。\n");

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
                return notify_fail("你的内力或气不够，没有办法练习冰魄寒刀。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        write("你按着所学练了一遍冰魄寒刀。\n");
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
         if ((string)me->query("family/family_name") != "大雪山" )
             return 0;
// if (me->query_temp("noauto")&&(random(15)!=1)) return 0;
          
        if ((!weapon) ||((string)weapon->query("material") != "ice" ))
                return 0; 
        // emotion: // if(damage_bonus<150) damage_bonus= 150;
          
        if (((int)me->query_skill("blade")/2) > random((int)victim->query_skill("force")))
             {
              // emotion: bug what if damage_bonus is greater than 300?? // victim->receive_wound("kee", (300-damage_bonus) );
              victim->receive_wound("kee", damage_bonus/3 );  // emotion
              msg = HIW"\n$N"HIW+"默运真气，将冰魄寒刀中寒气逼出，$n"+HIW"一个不察，已被冻伤！"NOR;
              message_vision(msg,me,victim);
             
             };
             if( random(damage_bonus/2) > victim->query_str()/5) {
                switch(random(3)) {
                        case 0:{ victim->receive_damage("kee",damage_bonus/3*2);
                                 //msg = WHT"只见一丝寒气无声无息地钻到$n"+WHT"体内！\n"NOR;
                                 return WHT"只见一丝寒气无声无息地钻到$n"+WHT"体内！\n"NOR;
                                 break;};
                                
                        case 1:{  victim->receive_damage("kee",damage_bonus/2);
                                  return WHT"$N"+WHT"暗使巧力，在$n"WHT"的伤口上留下一道浅浅的白印！\n"NOR;
                                 break;};
                                
                        case 2:{  victim->receive_damage("kee",damage_bonus);
                                  return WHT"$n"+WHT"突然觉得体内奇寒难忍...\n"NOR;
                                 break;};
                                 
                        }
               
                             //message_vision(msg,me,victim);
           }
                return 0;
 }
