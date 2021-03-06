#include <ansi.h>

inherit SSERVER;
//inherit F_CLEAN_UP;

int perform(object me, object target)
{
        object weapon;
	int i,j,k,damage;
	weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要攻击谁？\n");

        if(!me->is_fighting(target))
                return notify_fail("你们没有在打架！\n");
	if(!wizardp(me) && me->query("family/family_name")!="火云洞")
           return notify_fail("“不悔”只有火云洞门人才可以用！\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内功太差。\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 100 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

	if((int)me->query_skill("pingtian-dafa", 1) < 100)
        	return notify_fail("你的平天大法等级不够，不能使用这一招！\n");
	i=(int)me->query("combat_exp");
       	j=(int)target->query("combat_exp");
        k=(int)me->query_skill("spear");
        if(k<180)        
        	return notify_fail("你的枪法级别还不够，使用这一招会有困难！\n");
        if( time()-(int)me->query_temp("buhui_end") < 4 )
                return notify_fail("绝招用多了，就不灵了！\n");
        me->set_temp("buhui_end",time());
        me->delete("env/brief_message");
	target->delete("env/brief_message");
	message_vision(HIB"\n$N一挺手中"+weapon->name()+NOR+HIB"直刺$n！\n"NOR,me,target);
	if (random(i)>j/2) 
	{
		damage=k+(int)me->query_str();
		target->receive_damage("kee",damage,me);
            	target->receive_wound("kee",damage/2,me);
	 	COMBAT_D->report_status(target);
	}
	else
	{
		message_vision(HIM"\n$N一枪刺空，又是一肘，仍击向$n！\n"NOR,me,target);
		if (random(i)> j/3 ) 
		{
	            	damage=k+random(k)+(int)me->query_str();
			target->receive_damage("kee",damage,me);
	            	target->receive_wound("kee",damage/2,me);
		 	COMBAT_D->report_status(target);
		}
		else
		{
		        message_vision(HIB"\n$N一肘又空，但仍不收着，一头撞向$n！\n"NOR,me,target);
			if (random(i)> j/4) 
			{
				damage=k*2+random(k)+(int)me->query_str();
				target->receive_damage("kee",damage,me);
		            	target->receive_wound("kee",damage/2,me);
			 	COMBAT_D->report_status(target);
			}
			else
			{
				message_vision(HIM"\n$N眼见一头撞空，心中一急运起火魔心法以全身之力撞向$n！\n"NOR,me,target);
				if (random(i)> j/5 ) 
				{
			     		damage=k*3+random(k)+(int)me->query_str();
					target->receive_damage("kee",damage,me);
			            	target->receive_wound("kee",damage/2,me);
				 	COMBAT_D->report_status(target);
				}
				else 
				{
			            	message_vision(HIW"\n$n哈哈大笑，只逞匹夫只勇又有何用，轻松避开。\n"NOR,me,target);
				}	
			}
		}
	}
	if (wizardp(me) && me->query("env/combat")=="verbose")
		tell_object(me, sprintf(HIC "damage: %d\n" NOR, damage));
	me->receive_damage("sen", 50);
        me->add("force", -100-damage/5);
	me->receive_damage("kee", 30); 
	
	me->start_busy(1+random(2));
        return 1;
}
