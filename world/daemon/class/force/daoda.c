// transfer.c
#include <ansi.h>
inherit SSERVER;

//倒打一耙
int exert(object me, object target)
{
		string msg;
        float ap,dp;
        int success,howlong;
                  int damage = me->query_skill("force");


        if( !target ) target = offensive_target(me);
        if(!me->query("zspfm/zspfm_zbj"))
                return notify_fail("你还没有领悟这个技能！\n");
		/*
		if( time()-(int)me->query_temp("zspfm_zbj_end") < 5 )
			return notify_fail("你口干舌燥，说不出话来！\n");
		*/
        if((int)me->query_skill("force") < 100)
                return notify_fail("你的技能等级太低！\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你想对谁使用？\n");

		if(!me->is_fighting(target))
                  return notify_fail("「倒打一耙」只能在战斗中使用！\n");
				

				
        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");

        me->add("force", -100);

        msg = HIC
"$N忽然想起了天蓬元帅的绝招，佯装不敌，倒拖兵器就走。\n"NOR;

        success = 1;
		
		if (random(me->query("combat_exp")) < target->query("combat_exp")/8)
			success = 0;

		me->start_busy(2);
        if(success == 1 ){
            msg +=  HIR "结果$n立刻中计，连忙追赶。结果被$N回身一耙凿的血肉模糊\n" NOR;
          message_vision(msg, me, target);
            target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
                          COMBAT_D->report_status(target);
        }
        else {
            msg +=  HIR "$n明察秋毫，知道$N的计策，并不追赶。\n" NOR;
          message_vision(msg, me, target);
        }

		//me->set_temp("zspfm_ts_end",time());
		return 1;
}

