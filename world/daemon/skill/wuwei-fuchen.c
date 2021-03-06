// wuwei-fuchen无为拂尘
// /daemon/skill/wuwei-fuchen.c
// writted by mind 2001/2
//lestat modi for dtxy 2001

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([ "action": "$N身形若被狂风吹送，飘然而至。一招"+HIM"「玉带围腰」"NOR+"，手中$w变出一个个圆圈，卷向$n的腰间。",
   "dodge": -5,
   "damage":30,
   "parry": -5,
   "skill_name" : "玉带围腰",
   "damage_type":  "刺伤"
]),
([ "action": "$N伸指在$w上一弹，趁$w轻响之际一招"+HIG"「庸人自扰」"NOR+"，象残照般洒向$n的$l",
   "dodge": -10,
   "damage":50,
   "parry": -10,
   "skill_name" : "庸人自扰",
   "damage_type":  "割伤"
]),
([ "action": "$N将内力注入$w，蓦地使出一式"+HIY"「龙行乾象」"NOR+"，$w矫夭飞舞，直如神龙破空一般抽向$n",
   "dodge": -40,
   "damage":40,
   "parry": 0,
   "skill_name" : "龙行乾象",
   "damage_type":  "抽伤"
]),
([ "action": "$N一声高喝，吸气催力，一式"+HIC"「有所为」"NOR+"，$w急速转动，鞭影纵横，直中有圆，圆中有直，似真似幻，绞向$n",
   "dodge": -10,
   "damage":40,
   "parry": -50,
   "skill_name" : "有所为",
   "damage_type":  "割伤"
]),
([ "action": "$N面露微笑跨前一步，右手$w轻扬，缓缓使出一式"+HIW"「静止观止」"NOR+"，鞭势平和中正，不带丝毫霸气",
   "dodge": -20,
   "damage":30,
   "parry": -30,
   "skill_name" : "静止观止",
   "damage_type":  "鞭伤"
]),
});
int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_force") < 100 )
               return notify_fail("你的内力不足。\n");

       if ((int)me->query_skill("force") < 30)
               return notify_fail("你的内功火候太浅。\n");

       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("你必须先找一条鞭子才能练无为拂尘。\n");

       return 1;
}


mapping query_action(object me)
{   
	mapping* m_actions;
     m_actions=me->query("skill_wuwei-fuchen"); 
        if (random(me->query_str()) >= 30 && me->query_skill("wuwei-fuchen",1) > 100 &&
             me->query_skill("parry",1) > 100 &&
             me->query("force") > 1000 &&
             me->query("kee")>300 &&
             (string)me->query("family/family_name")=="三界散仙") {
                me->add("kee",-10);           
                me->add("force", -30);
                return ([
                "action": HIR "$N手腕一抖，但见飞舞的$w"+HIR"从天而下和$n"+HIR"缠在一起，一股排山倒海的内劲无声息的向$n"+HIR"胸口撞去"NOR,
                "force": 80,
                "dodge": -85,
                "parry": -85,
                "damage" : 80,
                "damage_type": "内伤"]);
        }
           if (random(me->query_str()) >= 40 && me->query_skill("wuwei-fuchen",1)> 150 &&
                me->query_skill("parry",1) > 150 &&
                me->query("force") > 1500 &&
                me->query("kee")>500 &&
                (string)me->query("family/family_name")=="三界散仙") {
                me->add("kee",-20);            
                me->add("force", -50);
                return ([
                "action": HIR "$N把手中$w"+HIR"抖动成圈，绕着$n"+HIR"越转越急，越转越快，$n"+HIR"登时身不由主，被套得连转了几身，眼看就要摔倒"NOR,
                "force": 120,
                "dodge": -60,
                "parry": -60,
                "damage" : 120,
                "damage_type": "抽伤"]);
        }
     //if( me->query("skill_wuwei-fuchen")==0 )
     return action[random(sizeof(action))];
     /*if( random(4) == 1 )
     return m_actions[random(sizeof(m_actions))];
     else
     return action[random(sizeof(action))];*/
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "whip")
               return notify_fail("你使用的武器不对。\n");
       if ((int)me->query_skill("force") < 100)
               return notify_fail("你的内功火候太浅。\n");
       if ((int)me->query("kee") < 50)
               return notify_fail("你的体力不够练无为拂尘。\n");
       me->receive_damage("kee", 15);
       return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weap,weap1;
        weap = victim->query_temp("weapon");
                weap1 = me->query_temp("weapon");
		if( me->query_temp("icefire") || victim->query_temp("icefire") )
			return 1;
		if(( string)me->query("family/family_name") != "三界散仙" )
			return 1;
                if( (me->query_skill("wuwei-fuchen") > 60) && (me->query("force") > 100)
                         && (victim->query_temp("weapon")) 
                         && random(10)>5)
                 {
                        message_vision(HIY "只见$N急速挥舞" + weap1->name() + "，转出无数个大小圈子，以阴柔之劲缠住对方的" + weap->name() +"！\n" NOR, me );
                        victim->start_busy(2+random(2));
                        if (random(me->query_str()) > victim->query_str()/2 )
                        {       
                        message_vision(HIY "$N气运手臂用力一拽，" + weap->name() + "却无法从"+weap1->name()+"的缠绕中脱开，情急之下只好放弃了手中的兵刃。\n" NOR, victim );
                        weap->move(environment(me));
                        victim->reset_action();
                        } else {
                        message_vision(HIY "$N暗运巧劲，" + weap->name() + "顺着方向快速旋转数下，解开了"+weap1->name()+"的缠绕。\n" NOR, victim );
                        victim->add("force",-50);
                        }
                        me->add("force", -50);
                 }
                 return 1;
}

string perform_action_file(string func)
{
return CLASS_D("sanxian") + "/wuwei-fuchen/" + func;
}


