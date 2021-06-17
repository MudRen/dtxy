#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
		return notify_fail("你要对谁施展这一招「逍遥一笑」？\n");
        if(!me->is_fighting(target))
      		return notify_fail("「逍遥一笑」只能在战斗中使用！\n");
        if((int)me->query("max_force") < 800)
                return notify_fail("你的内力不够！\n");
	if((int)me->query("force") < 500 )
     		return notify_fail("你的内力不足！\n");
	if((int)me->query("sen") < 200)
                return notify_fail("你的精神不足，没法子施用外功！\n");
        if((int)me->query_skill("snowsword", 1) < 100)
		return notify_fail("你的风回雪舞剑级别还不够，使用这一招会有困难 !\n");
        me->delete("env/brief_message");
   	target->delete("env/brief_message");
message_vision(HIW"\n"+HIY"$N轻叹道："+HIW"朝闻道，夕死可亦，酒也乐逍 "+HIY"突然诡昧的一笑\n"+
NOR"\n"+HIY"                    对着$n一连发出三道杀手！\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        me->receive_damage("sen", 100);
	me->add("force",-100);
        
	me->start_busy(2);
        return 1;
}
