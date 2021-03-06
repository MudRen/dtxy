// 开天辟地
// kugu 2006 反开天
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        int ap,dp,delay;
        object weapon;
        int cd = 10;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招"+HIM"「开天辟地」"+NOR"？\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力不够！\n");
	if(!me->is_fighting(target))
                return notify_fail("你没有在战斗中！\n");
        if((int)me->query("kee") < 1000 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
	if( !me->query("kai_known") )
                return notify_fail("你没有得到开天辟地的口诀！\n");
        if((int)me->query_skill("sanban-axe", 1) <200)
                return notify_fail("你的宣花斧级别还不够！\n");
        if((int)me->query_skill("lengquan-force", 1) <200)
                return notify_fail("你的冷泉神功级别还不够！\n");
        if(me->query("family/family_name") != "将军府")
                return notify_fail(HIR"「开天辟地」"+NOR"是将军府不传之密！\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
	if( time()-(int)me->query_temp("kai_end") < cd )
                return notify_fail("绝招用多了，就不灵了！\n");
        me->start_busy(1);
	ap = me->query("combat_exp")/10000;
	dp = target->query("combat_exp")/12000;
	delay = 3 + random(1+me->query("kai_known"));
	weapon = me->query_temp("weapon");
        message_vision(HIC"\n$N挥动"+ weapon->name() +HIC"斩向$n左侧。\n"NOR,me,target);
        message_vision(CYN"$n脚下用力，连忙右闪。\n" NOR,me,target);
        message_vision(HIC"\n$N将"+ weapon->name() +HIC"横划，从$n右侧挑起。\n"NOR,me,target);
        if( me->query("kai_known") > 1 )
        {
        	message_vision(CYN"$n用力蹬地，就要向上跃起。\n" NOR,me,target);
        	message_vision(HIC"\n$N手腕一翻"+ weapon->name() +HIC"从$n头顶横削而过。\n"NOR,me,target);
        }
        if( me->query("kai_known") > 2 )
        {
        	message_vision(CYN"$n仓促中，脚跟前蹬欲要后跃。\n" NOR,me,target);
        	message_vision(HIC"\n$N腰身一挫，"+ weapon->name() +HIC"贴着$n的后背斩下。\n"NOR,me,target);
        }
        message_vision(HIC"$N这"+ chinese_number(1+me->query("kai_known")) +"斧劈出，实是已经力尽，$N勉力将"+ weapon->name() +HIC"拽回。\n"NOR,me,target);
        if( me->query("gender") == "女性" )
                message_vision(HIC"$N清啸一声，"+ weapon->name() +HIC"上泛起清冷杀气，$N提聚残力向$n迎面劈出最后一斧。\n"NOR,me,target);
        else
        	message_vision(HIC"$N暴喝一声，"+ weapon->name() +HIC"上杀伐之气大盛，$N提聚残力向$n迎面劈出最后一斧。\n"NOR,me,target);
        message_vision(CYN"$n被$N气势震慑，不敢掠$N锋芒，生生错过了正面的生路。\n\n" NOR,me,target);
        if( me->query("kai_known") < 2 && random(ap) < dp/3 )
        {
        	message_vision(CYN"$n用力蹬地，噌的跃起，躲开了$N的攻击。\n" NOR,me,target);
        	return 1;
        }
        if( me->query("kai_known") < 3 && random(ap) < dp/4 )
        {
        	message_vision(CYN"$n矮身一避，借势脚跟前蹬，向后跃开，躲开了$N的攻击。\n" NOR,me,target);
        	return 1;
        }
        if( random(ap) < dp/5 )
        {
        	message_vision(CYN"$n灵机一动，使出五行遁中的土遁从地下遁走，躲开了$N的攻击。\n" NOR,me,target);
        	return 1;
        }
        message_vision(HIC"$n眼见斧头呼啸着扑面而来，又无路可退，只好闭目呆立。\n" NOR,me,target);
        target->start_busy(delay);
        me->set_temp("kai_end",time());
        return 1;
}
