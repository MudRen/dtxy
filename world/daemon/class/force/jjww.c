// transfer.c
#include <ansi.h>
inherit SSERVER;

//
int exert(object me, object target)
{
		string msg;
        float ap,dp;
        int success,howlong;

        if( !target ) target = offensive_target(me);
        if(!me->query("zspfm/zspfm_ts"))
                return notify_fail("你还没有领悟这个技能！\n");
                  if( time()-(int)me->query_temp("zspfm_ts_end") < 10 )
			return notify_fail("你口干舌燥，说不出话来！\n");
        if((int)me->query_skill("force") < 100)
                return notify_fail("你的技能等级太低！\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你想对谁使用？\n");
				
		if(!me->is_fighting(target))
                return notify_fail("「唧唧歪歪」只能在战斗中使用！\n");
        if(target->is_busy())
                return notify_fail(target->query("name")+"已经动弹不得了！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");

        me->add("force", -500);
        
        msg = HIC
"$N苦口婆心的对$n说:你有多少兄弟姐妹？你父母尚在吗？你说句话啊，我只是想在临死之前多交一个朋友而已\n"NOR;

        success = 1;
                  if (random(me->query("combat_exp")) < target->query("combat_exp")/5)
			success = 0;
                  if (random(me->query_skill("force")) < target->query_skill("force")/3)
			success = 0;
        if(success == 1 ){
            msg +=  HIR "结果$n口吐白沫，实在是被烦得不行了...\n" NOR;
              target->start_busy(3);

        }
        else {
            msg +=  HIR "$n努力打起精神，不受影响！\n" NOR;
me->start_busy(1);
        }

        message_vision(msg, me, target);
		me->set_temp("zspfm_ts_end",time());
		return 1;
}

