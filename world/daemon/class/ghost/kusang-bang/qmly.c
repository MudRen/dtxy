#include <ansi.h>


int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, force_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("kusang-bang",1);

 	if(me->query("family/family_name") != "阎罗地府")
		return notify_fail(HIG"「青面獠牙」"+NOR"是冥界不传之密！\n");
        if( !(me->is_fighting(target) ))
                return notify_fail("「青面獠牙」只能对战斗中的对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "stick")             
        	return notify_fail("使用「青面獠牙」时手里必须拿着根棍。\n");

        if( skill < 100)
                return notify_fail("你的「哭丧棒」等级不够, 不能使用「青面獠牙」！\n");

        if( me->query_skill("dodge",1) < 120 )
                return notify_fail("你的轻功不够，无法运用「青面獠牙」！\n");
	if( me->query("force") < 100 )
                return notify_fail("你的内力不足！\n");
        if( target->query("force") < 100 )
                return notify_fail("对方没有内力让你吸了！\n");

        msg = HIC"$N突然脸色变得紫青，欺近$n的身前，张开嘴用两颗尖长的獠牙向$n的咽喉咬去。\n"NOR;
        message_vision(msg, me, target);

 	ap = me->query("combat_exp")/10000;
        dp = target->query("combat_exp")/14000 ;
 	if(random(ap+dp) > dp/2)
        {
                msg = HIG "$n只觉得咽喉一阵剧痛，$N正在狂吸$n的鲜血！\n"NOR;
                force_wound = skill + me->query_skill("force") + me->query_str();
                force_wound = force_wound + random(force_wound/3);
	 	force_wound = force_wound - target->query_temp("apply/armor");
	 	if( force_wound < me->query_skill("stick",1) ) force_wound = me->query_skill("stick",1);
	 	me->add("force",force_wound/5);
	 	if( me->query("force") > me->query("max_force")*2 ) me->set("force",me->query("max_force")*2);
	 	target->add("force",-force_wound/2);
	 	if( target->query("force")<0 ) target->set("force",0);
	        message_vision(msg, me, target);
	        COMBAT_D->report_status(target);
        }
        else
        {
                msg = HIG "只见$n不慌不忙，轻轻一闪，躲过了$N的獠牙！\n"NOR;
                message_vision(msg, me, target);
                me->add("force",-100);
	}
        me->start_busy(1+random(2));
        return 1;
}

