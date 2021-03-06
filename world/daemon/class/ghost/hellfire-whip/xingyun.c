//星云锁链
//by lestat 2001五一


#include <ansi.h>

inherit SSERVER;
int perform(object me, object target)
{
    object weapon;
	string who1, who2;
    int damage, lvl, r_lvl, count, form, skill, i;
    string msg;
        if( !target ) target = offensive_target(me);
        
        if( !me->query_skill("hellfire-whip", 1) )
                return notify_fail("你不会星云锁链大法。\n");
if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「星云锁链」？\n");
        if( skill > 300 ) skill=300;
        if(me->query("family/family_name") != "阎罗地府" )
                return notify_fail("你是哪儿偷学来的武功，也想用「星云锁链」?\n");
        if(!me->is_fighting(target))
                return notify_fail("「星云锁链」只能在战斗中使用！\n");
        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
        if((int)me->query_skill("hellfire-whip", 1) < 100)
                return notify_fail("你的烈火鞭级别还不够，小心走火入魔！\n");               
        if (me->query_skill_mapped("force")!="tonsillit")
                return notify_fail("星云锁链必须配合摄气诀才能使用。\n"); 
                if( time()-(int)me->query_temp("xingyun_end") < 5 )
                return notify_fail("绝招用多就不灵了！\n"); 
            me->delete("env/brief_message");
            target->delete("env/brief_message");
    skill = (int)me->query_skill("hellfire-whip", 1);
	lvl = skill/20;
	r_lvl = 3+random(lvl);
if( r_lvl > 9) r_lvl = 9;
	//if( r_lvl < 1) r_lvl = 1;
	count = me->query_str();
	message_vision(HIB"\n$N使出幽冥绝学星云锁链，手中长鞭暴涨,漫天飞舞,瞬间在周身裹成一团星云,$n的攻击被尽数挡回。\n"NOR,me,target);
	tell_object(target, HIW"忽然，你发现有一股奇怪的力量向你袭来,四周一切似乎已经开始凝结！\n"NOR);
 if (random(me->query("force",1)) > 4*target->query("force",1)/5 )
        {
                target->start_busy(random(3));                
                damage = skill/2 + r_lvl*target->query("force_factor",1);                
                target->receive_damage("kee", damage,me);
                target->receive_wound("kee", damage,me);
                me->add("force", -damage/5);
				//msg = CYN "$N默运神功，使出星云锁链大法。\n"NOR;
	        	msg = HIB "星云罩将$n的内力全数反击回去！\n" NOR;                
                if( damage < 70 )
                        msg += HIY"结果$n受到$N的内力反震，闷哼一声。\n"NOR;
        	else if( damage < 100 )
                       msg += HIY"结果$n被$N以内力反震，「嘿」地一声退了两步。\n"NOR;
        	else if( damage < 150 )
                       msg += RED"结果$n被$N以内力一震，胸口有如受到一记重锤，连退了五六步！\n"NOR;
                else
                       msg += HIR"结果$n被$N的内力一震，眼前一黑，象一捆稻草一样飞出去好几丈远！\n"NOR;
                message_vision(msg, me, target);
                COMBAT_D->report_status(target);
        }
else if((random(me->query("combat_exp")) > (int)target->query("combat_exp")/5 ))
        {
		tell_object(target, HIG"你周身不畅，似乎有股奇异的力量，将你的出招竟然反了回来击向自己！\n"NOR);
		message("vision", HIW"\n" + target->name() + "忽然如中魔一般，招招击向自己！\n\n"NOR, environment(me), target);
		for(i = 0; i < r_lvl; i++)
		COMBAT_D->do_attack(target, target, target->query_temp("weapon") );
		target->set_temp("last_damage_from",me);
		me->add("force", -300);
		}

     else
     {
     	message_vision(CYN"\n$n运起内功震碎了星云罩，那股奇怪的力量同时消失了。\n"NOR, me, target);
     	if( me->query("lunhui_zhuanshi") < 4 )
     	{
     		if( me->query("lunhui_zhuanshi") > 1 )
  			me->start_busy(1);
  		else
  			me->start_busy(2);
  	}
     }
        me->set_temp("xingyun_end",time());
        return 1;
}

