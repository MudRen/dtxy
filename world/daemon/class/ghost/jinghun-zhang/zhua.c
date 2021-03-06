#include <ansi.h>
#include <skill.h>
inherit SSERVER;
int perform(object me, object target)
{
        int i, j, k, damage, delay;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁使用无常爪？\n");
		if(me->query("family/family_name") != "阎罗地府")
                return notify_fail(HIG"「无常爪」"+NOR"是冥界不传之密！\n");
        if(!me->is_fighting())
                return notify_fail("你们没有在打架！\n");
        if((int)me->query("max_force") < 200 )
                return notify_fail("你的内功太差。\n");
        if((int)me->query("force") < 100 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
	if((int)me->query_skill("jinghun-zhang", 1) < 50)
        	return notify_fail("你的惊魂掌等级不够，不能使用这一招！\n");
	i=(int)me->query("combat_exp")/10000;
       	j=(int)target->query("combat_exp")/12000;
        k=(int)me->query_skill("jinghun-zhang");
        me->delete("env/brief_message");
	target->delete("env/brief_message");
	message_vision(HIB"\n$N口中默念几声：世事无常，死生无常……偏偏今天你撞到我喜怒无常，你任命吧！看爪。"NOR,me,target);
	message_vision(HIB"\n一爪抓向$n\n"NOR,me,target);
        if (random(i+j)>j/2) {
		damage=k+random(k);
		target->receive_damage("kee",damage);
		target->receive_wound("kee",damage/5);
		delay = 3 + random(3);
		if( me->query("lunhui_zhuanshi") > 4 )
			delay -= 1;
		target->start_busy(delay);
             	if (k>160) k=160;
		target->apply_condition("hell_zhua", (int)target->query_condition("hell_zhua")+2+k/20);
                COMBAT_D->report_status(target);
		message_vision(HIG"\n$n身子一晃，背上留下了一个惨绿色的爪痕！\n"NOR,me,target);
	}
	else message_vision(HIY"\n$n身子一闪，躲开了这一抓！\n"NOR,me,target);
	me->receive_damage("sen", 30);
        me->add("force", -100);
	me->receive_damage("kee", 30);
	if( me->query("lunhui_zhuanshi") > 4 )
		me->start_busy(1);
	else
    		me->start_busy(2);
	return 1;
}
