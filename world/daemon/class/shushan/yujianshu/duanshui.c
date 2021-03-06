//Cracked by Roath

//Ansi 99.12
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        int ap,dp,damage,chance;
        string msg;
        object weapon;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「断水无痕」？\n");

        if(!me->is_fighting(target))
                return notify_fail("「断水无痕」只能在战斗中使用！\n");
        if(me->query("family/family_name")!="蜀山派")
                return notify_fail("不是蜀山的不能用「断水无痕」！\n");
//        if(me->query("shushan/duanshui_master")!=1)
//                return notify_fail("你还没领会「断水无痕」！\n");

        if((int)me->query("max_force") < 500 )
                return notify_fail("你的内力不够！\n");

   	if((int)me->query("force") < 500 )
     		return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 300 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("yujianshu", 1) < 50)
                return notify_fail("你的剑法修为还不够，使用这一招会有困难！\n");
	if( time()-(int)me->query_temp("duanshui_end") < 4 )
                return notify_fail("绝招用多了，就不灵了！\n");
        me->set_temp("duanshui_end",time());

        msg = CYN"\n$N手腕晃动如疾风，以砍断三千尺飞流的速度，直逼$n！\n"NOR;
        ap = me->query_skill("sword");
        ap = me->query("combat_exp");
        dp = target->query("combat_exp")/4*5; 
	if ( dp <= 0 ) dp = 1;
        chance = (int)(random( ap + dp ) / dp * 100);
        if (target->is_busy()) chance *= 2;
        if( chance > 40 ) {
                damage = me->query_skill("sword") * 2 + me->query("force_factor");
                if (damage > 800) damage = 750+random(75);
                target->receive_damage("kee",damage,me);
                target->receive_wound("kee",damage/3,me);
		//target->start_busy(random(1)+1);
                msg += CYN"结果$n被$N的「断水无痕」拦腰而过！\n"NOR;
        }
        
        else 
                msg += "但是被$n躲开了。\n"NOR;
        message_vision(msg, me, target);
        if( damage > 0 ) COMBAT_D->report_status(target);
        me->add("force",-damage/2);
        me->start_busy(1);
        return 1;
}
