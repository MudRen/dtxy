#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int i,num,skill;
  int cd = 10;
  int force_rate = 12;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展飘雪九式？\n");
        if(!wizardp(me) && me->query("family/family_name") != "大雪山")
                return notify_fail(HIW"「飘雪九式」"+NOR"是大雪山不传之密！\n");
        if(!me->is_fighting(target))
                return notify_fail("「飘雪九式」只能在战斗中使用！\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("你的内力不够！\n");
        if ( me->query("piaoxue_known") < 2 ) //暂时分为2个阶段 2,3
           return notify_fail("你没有学到的口诀，怎么能领悟到「飘雪九式」的奥秘！\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("piaoxue_end") < cd )
          return notify_fail("你现在内息紊乱，无法使用「飘雪九式」！\n");
        if(me->query_skill("blade", 1) < 200 || me->query_skill("bingpo-blade", 1) < 200)
                return notify_fail("你的刀法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("force", 1) < 200 || me->query_skill("ningxie-force", 1) < 200)
                return notify_fail("你的内功级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("spells", 1) < 200 || me->query_skill("dengxian-dafa", 1) < 200)
                return notify_fail("你的法术级别还不够，使用这一招会有困难！\n");
        if( me->query("lunhui_zhuanshi") > 4 )
                  force_rate = 8;
        else if( me->query("lunhui_zhuanshi") > 3 )
                  force_rate = 10;
        if( me->query("force_factor") / 3 > me->query_skill("force") / force_rate )
        	return notify_fail("你加力太大，无法使用如此轻灵的招式！\n");
        weapon=me->query_temp("weapon");
        if( weapon->query("material") != "ice" )
        	return notify_fail("你的武器太重，无法使出轻灵的招式！\n");
        
        me->set_temp("piaoxue_end",time());
   	enhance=me->query_skill("dengxian-dafa",1);
    	damage=me->query_skill("ningxie-force",1);
    		
  	message_vision(HIW"\n$N将手中"+weapon->name()+HIW"冲天扬起，空中忽然降下漫天大雪。\n"NOR,me,target);
  	message_vision(HIW"雪花朵朵迷乱了$n的视线，$N借机遁去身形。\n"NOR,me,target);
	message_vision(WHT"\n$n无法找到$N的踪影，不禁乱了方寸。\n"NOR,me,target);  	
 	message_vision(HIC"\n$N一声长啸，借风雪之力施展出了「"+BLINK+HIW"飘雪九式"+NOR+HIC"」！\n"NOR,me,target);  	
    	
   	if( me->query("piaoxue_known") > 2 && target->query_temp("jldl"))
   	{
        	if( random(enhance) >  target->query_skill("wuxiangforce",1) )
                {
                	target->delete_temp("jldl");
                	target->set_temp("jldl_end", time() );
                	target->receive_wound("kee",damage,me);
 			message_vision(HIR"\n$n欲要借$N之力攻击，突然发现无力可借，经脉中空空荡荡，异常难受！\n"NOR,me,target);
 			COMBAT_D->report_status(target);
 		}
 		else
 		{
 			target->set_temp("jldl_temp",1);
 			target->delete_temp("jldl");
 			message_vision(HIR"\n$N将劲力内敛，让$n的借力打力毫无用武之地！\n"NOR,me,target);
 		}
	}
	if(!target->is_busy()) target->start_busy(1);
	skill = damage + enhance + me->query_skill("bingpo-blade",1) + me->query_skill("blade", 1);
	num = skill/60;
	num = num/3;
	if( num > 9 ) num = 9;
	    
	target->add_temp("apply/dodge",-enhance/2);
	target->add_temp("apply/parry",-damage/2);
	me->add_temp("apply/attack",enhance/2);
	me->add_temp("apply/damage",damage/2);
	    
	for(i=1;i<=num;i++)
	{
		if( me->query("piaoxue_known") > 2 ) me->set_temp("piaoxue",i);
	   	COMBAT_D->do_attack(me, target,weapon);
	}
	if( target->query_temp("jldl_temp") )
	{
		target->set_temp("jldl",1);
	   	target->delete_temp("jldl_temp");
	}
	me->delete_temp("piaoxue");
	me->start_busy(2);
	me->add("force", -(100+num*30));
	target->add_temp("apply/dodge",enhance/2);
	target->add_temp("apply/parry",damage/2);
	me->add_temp("apply/attack",-enhance/2);
	me->add_temp("apply/damage",-damage/2);
	if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
	{ 
		str=me->name()+NOR+HIM"借风雪之力使出「"BLINK+HIW"飘雪九式"NOR+HIM"」，据说"+target->name()+NOR+HIM"被大雪淹没，窒息而亡！";
	    	message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
	return 1;
}
