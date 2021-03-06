#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int i;
  int cd = 10;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展冰火诀？\n");
        if(!wizardp(me) && me->query("family/family_name") != "三界散仙")
                return notify_fail(HIG"「冰火诀」"+NOR"是散仙不传之密！\n");
        if(!me->is_fighting(target))
                return notify_fail("「冰火诀」只能在战斗中使用！\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("你的内力不够！\n");
        if ( !me->query("icefire_known") ) //暂时分为2个阶段 1,2
           return notify_fail("你没有学到的口诀，怎么能领悟到「冰火诀」的奥秘！\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("icefire_end") < cd )
          return notify_fail("你现在内息紊乱，无法使用「冰火诀」！\n");
        if(me->query_skill("whip", 1) < 200 || me->query_skill("wuwei-fuchen", 1) < 200)
                return notify_fail("你的鞭法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("ice_fire_zhang", 1) < 200)
                return notify_fail("你的掌法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("force", 1) < 200 || me->query_skill("butian-force", 1) < 200)
                return notify_fail("你的内功级别还不够，使用这一招会有困难！\n");
        if (me->query_skill_mapped("force")!="butian-force")
                return notify_fail("「冰火诀」必须配合补天心法才能使用。\n");
        if (me->query_skill_mapped("whip")!="wuwei-fuchen")
                return notify_fail("「冰火诀」必须配合无为拂尘才能使用。\n");
    	weapon=me->query_temp("weapon");
    	me->add("force",-500);
    	enhance = me->query_skill("butian-force",1)/10;
    	me->add_temp("apply/damage",enhance*(2+me->query("icefire_known")));
    	me->add_temp("apply/strength",enhance*(1+me->query("icefire_known")));
	target->add_temp("apply/dodge",-enhance*(2+me->query("icefire_known")));
        target->add_temp("apply/parry",-enhance*(1+me->query("icefire_known")));
    	if( me->query("icefire_known") > 1 )
	{
		message_vision(HIC"\n$N同时运转"+HIW"寒冰"+HIR"炎阳"+HIC"心法，真气自丹田涌向双臂。\n"NOR,me,target);
		message_vision(HIC"“哧”的一声"+BLINK+HIW"冰魄刀"+NOR+HIC"在$N左手凝结而成，而"+BLINK+HIR"火焰刀"+NOR+HIC"同时在$N右手熊熊燃起！\n"NOR,me);
	}
	else
	{
		message_vision(HIW"\n$N运转寒冰心法，真气变得异常寒冷，自丹田涌向左臂。\n"NOR,me);
		message_vision(HIC"“哧”的一声"+BLINK+HIW"冰魄刀"+NOR+HIC"在$N左手凝结而成！\n"NOR,me);
	}	
	me->set_temp("icefire",1);
	COMBAT_D->do_attack(me, target, weapon);
	if( me->query("icefire_known") == 1 )
	{
		message_vision(HIR"\n$N运转炎阳心法，真气流转丹田瞬间由至寒化作炽热涌向右臂。\n"NOR,me);
		message_vision(BLINK+HIR"火焰刀"+NOR+HIR"在$N右手熊熊燃起！"+HIC"“哧”的一声"+HIW"冰魄刀"+NOR+HIC"化作水汽消散而去！\n"NOR,me);
	}
	me->set_temp("icefire",2);
	COMBAT_D->do_attack(me, target, weapon);
	if( me->query("icefire_known") > 1 )
	{
		me->set_temp("icefire",3);
		COMBAT_D->do_attack(me, target, weapon);
		message_vision(HIR"\n$N陡然加速运转炎阳心法。\n"NOR,me);
		message_vision(HIC"“哧”的一声"+HIW"冰魄刀"+NOR+HIC"化作水汽，被"+HIR"火焰刀"+NOR+HIC"吸附在四周，"+HIR"火焰刀"+NOR+HIC"声势更盛！\n"NOR,me);
		message_vision(HIR"火焰刀"+NOR+HIC"被白色的水汽包围，伸缩蜿蜒，有如一条"+HIW"冰"+HIR"火"+HIC"长鞭。\n"NOR,me);
		weapon = new("/d/sanxian/obj/icefirewhip");
		me->set_temp("weapon",weapon);
	}
	else
	{
		message_vision(HIR"\n$N陡然加速运转炎阳心法。\n"NOR,me);
		message_vision(HIR"火焰刀声势大盛伸缩蜿蜒，有如一条烈火长鞭。\n"NOR,me);
		weapon = new("/d/sanxian/obj/firewhip");
		me->set_temp("weapon",weapon);
	}
	me->reset_action();
	me->add_temp("apply/damage",damage);
	COMBAT_D->do_attack(me, target, weapon);
	COMBAT_D->do_attack(me, target, weapon);
	COMBAT_D->do_attack(me, target, weapon);
	me->delete_temp("weapon");
	destruct(weapon);
	if( me->query("icefire_known") > 1 )
	{
		message_vision(HIC"\n$N缓了"+HIR"炎阳心法"+HIC"，转而将"+HIW"寒冰心法"+HIC"加速，真气转为至寒。\n"NOR,me);
		message_vision(HIR"火焰刀"+WHT"四周水汽重新凝作"+HIW"冰魄刀"+WHT"，将"+HIR"火焰刀"+WHT"围在中央。\n"NOR,me);
		message_vision(YEL"$n不能相信火生于冰中的怪像，使劲摇摇脑袋，$N趁机刺向$n。\n"NOR,me,target);
		if( random( me->query("combat_exp")+target->query("combat_exp") ) > target->query("combat_exp") /2 )
		{
			message_vision(HIR"\n结果$n躲闪不及，被刺个正着！鲜血从胸口汩汩而出！\n"NOR,me,target);
			damage = me->query_skill("spysword",1);
			damage = damage + random(damage/3);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage,me);
			COMBAT_D->report_status(target,0);
	        	me->add("force",-damage/5);
	        	message_vision(YEL"\n$N将"+HIW"冰魄刀"+YEL"留在$n体内，抽身疾退。\n"NOR,me,target);
	        	message_vision(HIW"冰魄刀"+HIR"失去$N的内力支持，“砰”的炸了开来，$n被炸的血肉模糊，惨不忍睹！\n"NOR,me,target);
	        	damage = me->query_skill("ice_fire_zhang",1);
	        	damage = damage + random(damage/3);
	        	target->receive_damage("kee",damage,me);
        		target->receive_wound("kee",damage,me);
			COMBAT_D->report_status(target,0);
	        	me->add("force",-damage/5);
	        	if( me->query("force") < 0 ) me->set("force",0);
	        	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
		        {
				str=target->name()+HIM"被"+me->name()+HIM"用「"+HIW"冰"+HIR"火"+HIC"诀"+HIM+"」的内力炸成了碎片！";
				message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
			}
		}
		else
		{
			message_vision(RED"\n结果$n还算清醒，纵身跃开，"+HIW"冰魄刀"+NOR+RED"在$n身后炸开，将$n吓得脸色苍白！\n"NOR,me,target);
		}
	}
	else
	{
		message_vision(RED"\n$N缓了炎阳心法，"+HIR"火焰刀"+NOR+RED"渐渐平息了。\n"NOR,me);
	}
        me->add_temp("apply/damage",-enhance*(2+me->query("icefire_known")));
        me->add_temp("apply/strength",-enhance*(1+me->query("icefire_known")));
        target->add_temp("apply/dodge",enhance*(2+me->query("icefire_known")));
        target->add_temp("apply/parry",enhance*(1+me->query("icefire_known")));
	me->delete_temp("icefire");
    	me->reset_action();
	me->start_busy(2);
    	me->set_temp("icefire_end",time());	
  return 1;
}
