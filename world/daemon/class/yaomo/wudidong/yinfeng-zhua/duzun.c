
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	int myexp, yourexp, myskill, yourskill;
	int ap, dp, damage;
       	string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「唯我独尊」只能对战斗中的对手使用。\n");
        if(me->query("family/family_name")!="陷空山无底洞")
 		return notify_fail("“唯我独尊”只有无底洞门人才可以用！\n");
//    if( (int)me->query_skill("yinfeng-zhua",1) < 80)
    	if( (int)me->query_skill("yinfeng-zhua",1) < 150)
    		return notify_fail("你的阴风爪还不够纯熟!\n");
    	//return notify_fail("唯我独尊暂时关闭,等待调整!\n");
    	if( (int)me->query("force") < 1000)
    		return notify_fail("你的内力不够了!\n");
    	if( (int)me->query("max_force") < 1200)
    		return notify_fail("你的内力太弱,无法使出「唯我独尊」.\n");


    if( time()-(int)me->query_temp("duzun_end") < 5 )
	return notify_fail("你现在内息不顺！\n");
     	msg = RED"\n$N双目尽赤,使出最后一招「唯我独尊」,双爪奋力向$n天灵盖戳下.\n" NOR;
	myexp= me->query("combat_exp") /10000;
	yourexp=target->query("combat_exp")/15000;
	myskill=me->query_skill("yinfeng-zhua",1);
	yourskill=target->query_skill("dodge",1);
	ap=myexp*myskill;
	dp=yourexp*yourskill;
	me->add("force",-me->query_str()/3);
	if (random(ap+dp)>dp/2)
	{
	        msg += HIR"\n只听「喀啦」一声,竟是骨折的声音,$n的头顶多了五个指洞!!\n" NOR;
		damage = me->query_skill("unarmed") + me->query_skill("force") + me->query_str();
		damage = damage + random(damage/3);
	 	damage = damage - target->query_temp("apply/armor");
	 	if( damage < myskill ) damage =  myskill;
	        target->receive_damage("kee",damage,me);
	        target->receive_wound("kee",damage/2,me);
	        message_vision(msg, me, target);
	        COMBAT_D->report_status(target);
	}
	else
	{
		msg += HIY "可是$p还是躲过了$P的最后一击！！\n" NOR;
		if( !me->query("lunhui_zhuanshi") )
	        	me->start_busy(1);
		message_vision(msg, me, target);	
	}
        if( wizardp(me) && (string)me->query("env/combat")=="verbose" )                       tell_object(me, sprintf( GRN "AP：%d，DP：%d，伤害力：%d\n" NOR,
                                ap/100, dp/100, damage));
  	me->set_temp("duzun_end",time());
        return 1;
}

