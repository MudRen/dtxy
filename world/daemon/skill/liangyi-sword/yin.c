// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
	string msg;
	int extra, myexp, hisexp;
	object weapon;
	if( !target ) target = offensive_target(me);
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("［阴字诀］只能对战斗中的对手使用。\n");
        if(me->query("family/family_name") != "方寸山三星洞" )
                return notify_fail("你是哪儿偷学来的武功，也想用「阴字决」?\n");
	if(target->is_busy())
		return notify_fail("对方正忙着呢！！\n");
	extra = me->query_skill("liangyi-sword",1) ;
	if ( extra < 120) return notify_fail("你的[两仪剑法]还不够纯熟！\n");
        if((int)me->query("force") < 150 ) return notify_fail("你的内力不足！\n");
        if((int)me->query("sen") < 150 ) return notify_fail("你无法集中精力！\n");
               me->add("force", -100);
             me->receive_damage("sen", 100);
	weapon = target->query_temp("weapon");
	myexp = me->query_skill("sword");
	hisexp = target->query_skill("dodge",1)+target->query_skill("parry",1);
	extra = extra / 30;
	if( extra > 8 ) extra = 8;
	if(random(hisexp) < myexp && weapon)   
	{	
		message_vision(HIB "\n\n$N使出一式两仪剑法中的［阴字诀］，手中"+(me->query_temp("weapon"))->name()+"将$n的兵刃越缠越紧，$n一个把持不住，手中"+ weapon->name()+  "脱手而飞！\n\n" NOR, me,target);
		target->start_busy(1+extra/4);
	     	weapon->unequip();
		if( weapon->unequip()) weapon->move(environment(target));
	}
	else
	{
		message_vision(HIB "\n\n$N使出一式两仪剑法中的［阴字诀］，手中"+(me->query_temp("weapon"))->name()+  "将$n越缠越紧，逼的$n一阵手忙脚乱！\n\n" NOR, me,target);
		if(random(hisexp) < myexp)
		{
			target->start_busy(1+extra/4+random(extra/2));
		}
		else 
		{
			message_vision(HIB "\n$n不为所惑，站了个马步，凝神拆招！\n" NOR, me, target);
		}
	}
	me->start_busy(1+random(2));
	me->improve_skill("liangyi-sword", 1, 1);
	return 1;
}
