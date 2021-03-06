#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,ap,dp,damage,i;
	object weapon;
	extra = me->query_skill("wugou-jian",1);
        if(!wizardp(me) && me->query("family/family_name")!="昆仑山玉虚洞")
        	return notify_fail("[天外飞仙]只有昆仑山弟子才可以用！\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("[天外飞仙]只能对战斗中的对手使用。\n");
        if( extra < 100 )
        	return notify_fail("你的吴钩剑法还不够纯熟！\n");
        if((int)me->query("force") < extra )
		return notify_fail("你的内力不够！\n");
         
        i = extra  / 100 + 1;
        damage = me->query_skill("sword",1) + me->query_str();
        damage = damage + random(damage/2);
        damage = damage/2;
        if( wizardp(me) ) tell_object(me,HIR"damage="+ damage +"\n"NOR);
      	weapon=me->query_temp("weapon");
      	ap = extra + me->query_skill("lingyunbu",1);
      	dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
      	message_vision(HIC"\n$N左脚踏前，蹬地跃起，借势使出了「天外飞仙」！\n"NOR,me);
	msg = HIC"\n腾空式！\n$N手中"+weapon->query("name")+HIC"幻出朵朵寒光！\n"NOR;
	message_vision(msg,me,target);
	me->add("force",-extra/2);
	if( random(ap) > dp/4 )
	{
		message_vision(HIR"\n$n躲避不及，被数朵寒光透体而过！\n"NOR,me,target);
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		COMBAT_D->report_status(target);
	}
	else
		message_vision(CYN"\n$n轻功过人，将寒光尽数躲过！\n"NOR,me,target);
	if( i > 1 )
	{
		msg = HIW"\n追云式！\n刹那间$n被罩在剑气之中！\n"NOR;
		message_vision(msg,me,target);
		if( random(ap) > dp/4 )
		{
			message_vision(HIR"\n$n无处可逃，被剑气杀的遍体鳞伤！\n"NOR,me,target);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
			COMBAT_D->report_status(target);
		}
		else
			message_vision(WHT"\n$n运起内功，将全身尽数护住！\n"NOR,me,target);
	}
	if(i > 2 )
	{
		msg = HIY"\n追仙式！\n$N剑式宛如飘雪一般潇洒飘逸，$n顿时不知如何接招！\n"NOR;
		message_vision(msg,me,target);
		if( random(ap) > dp/4 )
		{
			message_vision(HIR"\n$n两眼发直，被剑气击飞数丈！\n"NOR,me,target);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
			COMBAT_D->report_status(target);
		}
		else
			message_vision(YEL"\n$n镇定心神，及时避开了剑气！\n"NOR,me,target);
	}
	if(i > 3 )
	{
		msg = HIM"\n飞仙式！\n$N犹如天外飞仙一般，披着雪花从空中落下，挥动"+weapon->name()+HIM"向$n刺去! \n"NOR;
		message_vision(msg,me,target);
		if( random(ap) > dp/5 )
		{
			message_vision(HIR"\n$n呆若木鸡，被剑气穿心而过！\n"NOR,me,target);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
			COMBAT_D->report_status(target);
		}
		else if( random(ap+dp) > dp/3 )
		{
			target->receive_damage("sen",extra,me);
			message_vision(MAG"\n$n拍拍脑袋，勉强避过了剑气！\n"NOR,me,target);
			COMBAT_D->report_sen_status(target);
		}
		else
			message_vision(MAG"\n$n神志清醒，纵身跃开！\n"NOR,me,target);
	}
	if( me->query("lunhui_zhuanshi") > 4 )
		me->start_busy(1);
	else
       		me->start_busy(2);
        return 1;
}
