// spysword. 【刺客剑法】
// /daemon/skill/spysword.c
// writted by mind 2001/2

#include <ansi.h>
inherit SKILL;
string* skill_head =({
        "$N怔怔而望，若有所思,忽然招变",
        "$N斜倚长剑，轻啸而歌却充满了枯涩的意味，一招",
        "$N衣袂飞舞，身形舒缓如舞，使出",
        "$N微闭双目，一股落寞的神情布于脸上，一式",
        "$N仰天不语，脸上掠过一丝忧愁，使出",
});
string* skill_tail =({
        "，手中$w化为一道疾光刺向$n的$l",
        "，手中$w遥遥刺向$n的$l",
        "，手中$w飞刺$n的$l",
        "，手中$w如飞，发出点点寒光",
        "，顿时一阵幽香飘向$n",
});
mapping *action = ({
      ([        "action":
"$N一声长叹，$w轻点一招"+HIG"「醉拍春衫惜旧香」"NOR+"向着$n的$l疾刺而去",

                 "dodge": -35,
                 "parry": -5,
                 "damage": 60,
                 "damage_type": "刺伤"
       ]),
        ([      "action":
"$N紧缩眉头，心中似有很深的怨气$w一闪而隐，一招"+MAG"「天将离恨恼梳狂」"NOR+"刺向$n的$l",
 
                 "dodge": 0,
                "parry" : -10,
                 "damage": 55,
                "damage_type": "刺伤"
         ]),
         ([      "action":
"$N仰天不语，脸上掠过一丝忧愁，$w暂缓，一招"+HIC"「有所思」"NOR+
"遥遥刺向$n的$l",

                "dodge": 0,
                "parry": -5,
                "damage": 70,
                "damage_type": "刺伤"
          ]),
          ([      "action":
"$N怔怔而望，若有所思,忽然变招，\n"
"蓦然有骤风席卷，剑招凌烈撒向$n的$l,好一招"+RED"「怒剑狂花」"NOR,

                "dodge": 0,
                "parry": -30,
                "damage": 50,
                 "damage_type": "刺伤"
           ]),
           ([      "action":
"$N衣袂飞舞，身形舒缓如舞，轻歌曼妙\n"
"一招"+MAG"「云渺渺，水茫茫」"NOR+"，$w划向$n的$l",
 
                  "damage": 80,
                 "dodge": -40,
                "parry": 0,
                 "damage_type": "割伤"
           ]),
           ([      "action":
"$N微闭双目，一股落寞的神情布于脸上，剑意凝重,空气顿时压力大增\n"
"一招"+BLU"「寂寞浪子青衫湿」"NOR+"飞刺$n的$l",
                  "dodge": 0,
                "parry": -50,
                  "damage": 60,
                  "damage_type": "刺伤"
           ]),
           ([      "action":
"$N斜倚长剑，轻啸而歌却充满了枯涩的意味，$w自肋下翻刺而出\n"
"一招"+HIM"「相思本是无凭语」"NOR+"刺向$n的$l",
                   "dodge": 0,
                "parry": -15,
                   "damage": 65,
                   "damage_type": "刺伤"
             ]),
             ([      "action":
"$N缓缓摇头，双目中似有泪光闪动$w辉映着苍白的光芒\n"
"若隐若现的闪现而出,一招"+YEL"「莫向花笺费泪行」"NOR+"刺向$n的$l",
                  "dodge": 0,
                "parry": -5,
                  "damage": 80,
                  "damage_type": "刺伤"
              ]),
              (["action":               HIW"$N手中的$w"+HIW"在一弹指间已向$n"+HIW"的$l连刺数剑"NOR,
                "dodge":                -10,
                "parry" :               -50,
                "damage" :              50,
                "damage_type":  "刺伤"
                ]),
                (["action":             HIW"$N身形一转，手中的$w"+HIW"从左肋下向$n"+HIW"的$l戳了过去"NOR,
                "dodge":                -10,
                "parry" :               -60,
                "damage":               60,
                "damage_type":  "刺伤"
                ]),
                (["action":             HIW"$N手腕一抖，$w"+HIW"挟著闪闪剑光逼向$n"+HIW"的$l"NOR,
                "dodge":                -10,
                "parry" :               -70,
                "damage" :              70,
                "damage_type":  "刺伤"
                ]),
                (["action":             HIW"$N身形一矮，手中的$w"+HIW"由下往上刺向$n"+HIW"的$l"NOR,
                "dodge":                -10,
                "parry" :               -80,
                "damage":               80,
                "damage_type":  "刺伤"
                ]),
                (["action":             HIW"$N手中$w"+HIW"剑光暴长，如千年蛇蝎往$n"+HIW"$l咬去"NOR,
                "dodge":                -10,
                "parry" :               -90,
                "damage":               90,
                "damage_type":  "刺伤"
                ]),
                (["action":             HIW"$N手中的$w"+HIW"以无法形容的速度直射$n"+HIW"的$l"NOR,
                "dodge":                -10,
                "parry" :               -100,
                "damage":               100,
                "damage_type":  "刺伤"
                ]),
});

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 200 )
        return notify_fail("你的内力不够，没有办法练刺客剑法。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
     int i;
     mapping* m_actions;
     m_actions=me->query("skill_spysword");
     i=me->query("dunnoname");
     if( !me->query("dunnoname") ) 
     {
     	if(me->query("skill_spysword")==0 )
     		return action[random(8)];
     	if( random(3) == 1 )
     		return m_actions[random(sizeof(m_actions))];
     	else
        	return action[random(8)];
      }
      else 
      {
        	return action[i];
      }
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 3 )
                return 
notify_fail("你的内力或气不够，没有办法练习刺客剑法。\n");
        me->receive_damage("kee", 30);
        me->add("force", -3);
          write("你按著所学练了一遍刺客剑法。\n");
        return 1;
}

string perform_action_file(string func)
{
return CLASS_D("sanxian") + "/spysword/" + func;
}
void skill_improved(object me)
{
   int m_skill=me->query_skill("spysword",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"你对刺客剑法的领悟加深了，你的刺客剑法进入了一个新的境界！\n"NOR);
     if(me->query("zichuang/times")>7){
        tell_object(me,HIW"然而你的功夫已经练至顶峰，不能再创出新招了。\n"NOR);
        return;
     }
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"然而你的心中居然产生了一种失落感！\n"NOR);
        return;
     }
     if((random(me->query("int")/2)+(int)me->query_skill("literate")/50)<10){
       tell_object(me,HIW"然而你的心中升起一种惆怅的感觉，仿佛有一丝重要的东西没有抓住。\n"NOR);
       return;
     }
     tell_object(me,HIW"你突然福至心灵，对刺客剑法领悟出了一招新的用法！\n"NOR);
     tell_object(me,"请为这招取一个名字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
   }
   return;
}

void name_skill(object me, string arg)
{
	string *banned_name = ({
                "你", "你", "我", "他", "她", "它", "爸", "妈",
                "爷", "奶", "巫师", "天神", "神仙",
        });
   mapping* m_actions;
   mapping m_act=([]);
   int content, i=strlen(arg);
   string msg;

   m_actions=me->query("skill_spysword");
   if(!pointerp(m_actions))m_actions=({});

   content=me->query("str")+2*me->query_skill("unarmed",1)/10;
   m_act+=(["damage":content]);
   content=-me->query("spi");
   m_act+=(["dodge" :content]);
   content=-me->query("cps");
   m_act+=(["parry" :content]);
   content=me->query("con")+2*me->query_skill("force",1)/10;
   m_act+=(["force" :content]);
   m_act+=(["damage_type":"刺伤"]);
if (!arg || arg=="") 
     {
          tell_object(me,"请为你的新招式取一个名字：");
          input_to( (: call_other, __FILE__, "name_skill", me:));
          return;
     }
     else while(i--) 
     {
                if( arg[i]<=' ' ) 
                {
                        tell_object(me,"招式名字不能使用控制字元，请重新设定一个名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if(strsrch(arg, "　") >= 0) 
                {
                        tell_object(me,"招式名字不能有空格，请重新设定一个名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) ) 
                {
                        tell_object(me,"请您用「中文」为你的新招式取名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
     }
     if( member_array(arg, banned_name)!=-1 ) 
     {
     tell_object(me,"对不起，这种名字会造成其他人的困扰。请重新设定一个名字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
     if( (strlen(arg) < 8) || (strlen(arg) > 16 ) ) 
     {
     tell_object(me,"对不起，招式名字必须是 ４ 到 ８ 个中文字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIM"「"+arg+"」"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_spysword",m_actions);
    me->add("zichuang/times",1);
}


