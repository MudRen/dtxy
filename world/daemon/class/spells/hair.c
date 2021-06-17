//lestat 2001

#include <ansi.h>
inherit SSERVER;

int cast(object me, object target)
{
        int invocation_time;
        object soldier;
		int num = me->query_skill("spells",1)/400;
		int i;
		if(!me->query("zspfm/zspfm_swk"))
                return notify_fail("你还没有领悟这个技能！\n");
        if( !me->is_fighting() )
                return notify_fail("你都不在战斗，召唤猴子猴孙干嘛？\n");
        if(me->query_skill("spells",1) <400)
                return notify_fail("你的法术等级不够！\n");  
        //invocation_time=30+(300-(int)me->query_skill("spells"));
        if(invocation_time<30) invocation_time=30;
        if((time()-me->query("last_invocation"))<invocation_time)
            return notify_fail("你的毛都快被你拔光了！\n");
        if( (int)me->query("mana") < 1000 )
                return notify_fail("你的法力不够了！\n");

        if( (int)me->query("sen") < 500 )
                return notify_fail("你的精神无法集中！\n");

        message_vision(HIG"$N拔下几根孙猴子送的毫毛，往空中一抛，吹了口气，毫毛竟然变成了美猴王！\n"NOR, me);

        
		me->add("mana", -300);
        me->receive_damage("sen", 100);
        seteuid(getuid());
		for (i=0;i<num;i++) {
        soldier = new("/u/yekai/zspfm/hair_swk.c");
        soldier->move(environment(me));
        soldier->invocation(me);
    	soldier->set_temp("invoker",me);
		}
        me->set("last_invocation",time());
        me->start_busy(1);

        return 1;
}


