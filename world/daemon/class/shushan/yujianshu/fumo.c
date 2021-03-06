//Modified by vikee for xlqy-zq station
//2000-12-5 10:19

#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
	int mypot,tapot,damage_pot,damage;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要攻击谁？\n");
                if(me->query("family/family_name") != "蜀山派" )
                return notify_fail("你是哪儿偷学来的武功！\n");

        if(!me->is_fighting(target))
                return notify_fail("你们没有在打架！\n");

        if((int)me->query("max_force") < 200 )
                return notify_fail("你的内功太差。\n");

        if((int)me->query("force") < 100 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 100 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
                
	if((int)me->query_skill("taoism", 1) < 50)
		return notify_fail("你的天师正道等级不够，不能使用这一招！\n");
	if( time()-(int)me->query_temp("fumo_end") < 5 )
                return notify_fail("绝招用多了，就不灵了！\n");
        me->set_temp("fumo_end",time());	

	me->delete("env/brief_message");
	target->delete("env/brief_message");
	message_vision(HIW"\n$N口中默念御剑口诀，手中"+weapon->name()+NOR+HIW"霞光四射，腾空飞起直斩$n！\n\n"NOR,me,target);

	//判断成功失败条件应该带随机性。
	//下面片段代码由一叶知秋(vikee)修改
	mypot = (int)me->query_skill("sword");
        tapot=((int)target->query_skill("dodge")+(int)target->query_skill("parry"))/2;
        
        damage=(int)me->query_skill("yujianshu",1);           
	if (damage > 400) damage = 400;
        damage += me->query("force_factor");
	if ( random(mypot) > random(tapot)/2 )	//main condition vikee 2000-12-5 10:11
	{
	  	target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
	  	me->receive_damage("sen", 100);
          	me->add("force", -100);
          	me->start_busy(1); //busy time is added.    
          	COMBAT_D->report_status(target);
	}
	else
	{
	 	me->add("force", -100);
	 	message_vision(HIW"\n$n连闪了几下好不容易躲开了这几道剑光！\n\n"NOR,me,target);
 	}
        return 1;
}

   
