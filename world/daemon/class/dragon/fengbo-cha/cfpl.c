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
                return notify_fail("你要对谁施展「乘风破浪」？\n");
        if(!wizardp(me) && me->query("family/family_name") != "东海龙宫")
                return notify_fail(HIC"「乘风破浪」"+NOR"是龙宫不传之密！\n");
        if(!me->is_fighting(target))
                return notify_fail("「乘风破浪」只能在战斗中使用！\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("你的内力不够！\n");
        if ( !me->query("cfpl_known") ) //暂时分为2个阶段 1,2
           return notify_fail("你没有口诀，无法领悟到「乘风破浪」的奥秘！\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
	
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("cfpl_end") < cd )
          return notify_fail("你现在内息紊乱，无法使用「乘风破浪」！\n");
        if(me->query_skill("fork", 1) < 200 || me->query_skill("fengbo-cha", 1) < 200)
                return notify_fail("你的叉法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("hammer", 1) < 200 || me->query_skill("huntian-hammer", 1) < 200)
                return notify_fail("你的锤法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("dragonfight", 1) < 200)
                return notify_fail("你的掌法级别还不够，使用这一招会有困难！\n");
        if (me->query_skill_mapped("unarmed")!="dragonfight")
                return notify_fail("「乘风破浪」必须配合龙形搏击才能使用。\n");
        if (me->query_skill_mapped("hammer")!="huntian-hammer")
                return notify_fail("「乘风破浪」必须配合混天锤法才能使用。\n");

    	weapon=me->query_temp("weapon");
    	message_vision(HIC"\n$N运起碧海神通，手中"+weapon->name()+HIC"来来回回连划数划，"+weapon->name()+HIC"上骤起惊涛骇浪。\n"NOR,me,target);
    	message_vision(HIC"\n$N纵声高唱：乘风破浪会有时！全身暴长，手中"+weapon->name()+HIC"排山倒海般击向$n。\n"NOR,me,target);

	if( !target->is_busy() )
		target->start_busy(1);
	
	enhance=me->query_skill("dragonforce",1);
    	damage=me->query_skill("seashentong",1);
	target->add_temp("apply/dodge",-enhance/2);
        target->add_temp("apply/parry",-damage/2);
        me->add_temp("apply/attack",enhance/2);
    	me->add_temp("apply/damage",damage/2);
    	me->set_temp("HTH_perform", 1);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 2);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 3);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 4);
    	COMBAT_D->do_attack(me, target, weapon);
	
	message_vision(HIC"\n$n的身形被$N带起的滔天巨浪渐渐淹没。\n"NOR,me,target);
    	if( me->query("cfpl_known") > 1 )
	{
		//乘风破浪第二段，直挂云帆济沧海
		  me->add("force", -300);
		  message_vision(HIC"\n$N纵声高唱：直挂云帆济沧海！\n"NOR,me,target);
		  message_vision(HIC"\n$n只觉千万股巨浪分合离散，从四面八方狂烈的撞击自己。耳膜轰然作响，仿佛便要炸裂。\n"NOR,me,target);
		  message_vision(HIC"\n$n连忙运气抵抗，那空茫疼痛之意登时稍稍舒缓。\n"NOR,me,target);
		  message_vision(HIC"\n但$n真气越盛，便越是觉得那四面的气浪暴烈汹涌，撞击得自己五脏六腑颠来倒去，经脉仿佛都要错位一般。\n"NOR,me,target);            
		  message_vision(HIC"\n$N左手捏了个法诀，叱声：去！但见"+weapon->name()+HIC"化作一道疾光飞向$n。\n"NOR,me,target);
		  me->set_temp("HTH_perform", 5);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 6);
    	COMBAT_D->do_attack(me, target, weapon);
    	seteuid(getuid());
	    me->set("actions", (: call_other, SKILL_D("dragonfight"), "query_action" :) );
    	weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    	weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    	weapon->set("use_apply_skill",1);
    	weapon->set("apply/skill_type","unarmed");
    	message_vision(HIC"\n$N左手法诀一领，"+weapon->name()+HIC"随着一个巨浪直飞九天。\n"NOR,me,target);
    	message_vision(HIB"\n紧接着$N飞身前扑。\n"NOR, me,target);    
    	COMBAT_D->do_attack(me, target,weapon);
    	message_vision(HIC"\n$N龙吟一声，借力高高跃起，半空中将"+weapon->name()+HIC"倒挽在手中。\n"NOR,me,target);
    	message_vision(HIY"\n$N身形突然倒转而下，有如流星下坠，其快绝伦，掌中"+weapon->name()+HIY"直击$n。\n"NOR,me,target);
    	seteuid(getuid());
    	me->set("actions", (: call_other, SKILL_D("huntian-hammer"), "query_action" :) );
    	weapon->set("use_apply_skill",1);
    	weapon->set("apply/skill_type","hammer");
    	COMBAT_D->do_attack(me, target,weapon);
    	weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    	weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    	me->reset_action();
    	if ( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
      	{ 
      		str=me->name()+"使出龙宫绝学"+NOR+HIC"「乘风破浪」"+NOR+HIM"自九天击下，将"+target->name()+NOR+HIM"活活打成肉饼！";
        	message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
       	}
	}
			me->delete_temp("HTH_perform");
    	me->add("force", -300);
	me->start_busy(2);
	target->add_temp("apply/dodge",enhance/2);
        target->add_temp("apply/parry",damage/2);
        me->add_temp("apply/attack",-enhance/2);
    	me->add_temp("apply/damage",-damage/2);
    	me->set_temp("cfpl_end",time());	
    	
  return 1;
}
