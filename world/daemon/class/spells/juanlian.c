#include <ansi.h>

inherit SSERVER;

void remove_effect(object me, object target,int amount);

int cast(object me, object target)
{
	int skill;
	me=this_player();

	if( !me->query("zspfm/zspfm_shs") )
		return notify_fail("你还没有领悟「倒卷珠帘」绝学！\n");
	if( (int)me->query_skill("spells", 1) < 100 )
		return notify_fail("你的法术等级不够。\n");
		
	if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这「倒卷珠帘」绝学？\n");

        if(!me->is_fighting(target))
                return notify_fail("「倒卷珠帘」只能在战斗中使用！\n");
	if (target->query_temp("zspfm/in_juanlian"))
		return notify_fail("对方已经中了倒卷珠帘了!\n");
				
	if((int)me->query("mana") < 300 )
                return notify_fail("你的法力不足！\n");
	skill = me->query_skill("spells");
          message_vision(HIW"\n$N默念绝招，大喝一声：倒卷珠帘，顿时一阵黑水涌来，把$n卷了进去\n"NOR,me,target);
	target->set_temp("zspfm/in_juanlian");
	target->add_temp("apply/armor",-skill/3);
          target->add_temp("apply/dodge",-skill/10);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, skill :), skill/100);
	return 3+random(5);
}

void remove_effect(object me, object target, int amount)
{
	if (target) {
        target->add_temp("apply/armor",amount/3);
          target->add_temp("apply/dodge",amount/10);
		target->delete_temp("zspfm/in_juanlian");
        message_vision(HIW"\n$n终于从黑水中走了出来，又酸又臭，狼狈不堪。\n"NOR,me,target);
	}
	return;
}


