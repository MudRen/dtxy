//created by vikee
//2000.10
//qingwang.c

// fixed overflow issue by emotion, 04/29/2006

#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

void free(object target, int f);

int perform(object me, object target)
{
	object weapon;
	string msg;
	int success, howlong, req, s, f;
	float ap, dp;

	if( !target ) target = offensive_target(me);
	if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「情网」?\n");
        if(!me->is_fighting(target))
                return notify_fail("「情网」只能在战斗中使用！\n");
	if (!weapon = me->query_temp("weapon"))
		return notify_fail("你没拿鞭子，拿什么织网啊？\n");
	 if(!wizardp(me) && me->query("family/family_name") != "月宫" )
                return notify_fail("你与痴梦无缘,领悟不到情网的精髓!!\n");
      	//req=(int)me->query_skill("whip", 1)+(int)me->query_skill("juqingbian", 1)+(int)me->query_skill("moonshentong", 1);
	if((int)me->query_skill("spells") < 100 || (int)me->query_skill("jueqingbian",1) < 100)
		return notify_fail("你的功夫等级还不够，使不出情网！\n");

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("你想对谁使情网？\n");

	if(target->query_temp("in_qingwang"))
		return notify_fail(target->query("name")+"已经被你的情网所困了！\n");

	if((int)me->query("mana") < 200 )
		return notify_fail("你的法力不够！\n");
	if((int)me->query("force") < 200 )
		return notify_fail("你的内力不够！\n");
	if((int)me->query("sen") < 10 )
		return notify_fail("你无法集中精力！\n");

	me->add("mana", -100);
	me->add("force", -100);
	me->receive_damage("sen", 10);

	msg = HIB"$N催动法力，将手中"+weapon->query("name")+HIB"舞成一团，化做一张大网，向$n当头罩来。\n"NOR;

	success = 1;
	ap = 0.0+(me->query_skill("spells")+me->query_skill("whip")) /2 ;
	ap = ap * ap * ap /10 ;
	ap = ap + me->query("daoxing");
	dp =0.0+target->query_skill("spells");
	dp =dp * dp * dp /15;
	dp = dp+target->query("daoxing")/5*4;
	if( (ap+dp)*random(1000)/1000 < dp/2 ) success = 0;
	if(success == 1 )
	{
		msg +=  HIB "$n脑子里一片混乱，鬼使神差般突然发呆，甚至忘记了躲闪，被情网当头罩住。\n" NOR;
		target->set_temp("in_qingwang", 1);
        	howlong = 4 + random(3);
		me->start_busy(1);
		s = me->query("lunhui_zhuanshi");
		if( s > 3 )
			howlong += 2;
		f = 0;
		if( s > 4 && !target->query_temp("no_move") )
		{
			target->set_temp("no_move", 1);
			f = 1;
		}
		call_out("free", howlong, target, f);
	}
	else
	{
		msg +=  HIG "$n神智清醒，不为情所困，轻轻向旁一跃，躲过了情网的袭击。\n" NOR;
		me->start_busy(1 + random(2));
	}

	message_vision(msg, me, target);

	return 1;
}

void free(object target, int f)
{
	if (target)
	{
		target->delete_temp("in_qingwang");
		if( f )
			target->delete_temp("no_move");
	}
	return;
}


