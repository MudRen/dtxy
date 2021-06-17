
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
                return notify_fail("��Ψ�Ҷ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(me->query("family/family_name")!="�ݿ�ɽ�޵׶�")
 		return notify_fail("��Ψ�Ҷ���ֻ���޵׶����˲ſ����ã�\n");
//    if( (int)me->query_skill("yinfeng-zhua",1) < 80)
    	if( (int)me->query_skill("yinfeng-zhua",1) < 150)
    		return notify_fail("�������צ����������!\n");
    	//return notify_fail("Ψ�Ҷ�����ʱ�ر�,�ȴ�����!\n");
    	if( (int)me->query("force") < 1000)
    		return notify_fail("�������������!\n");
    	if( (int)me->query("max_force") < 1200)
    		return notify_fail("�������̫��,�޷�ʹ����Ψ�Ҷ���.\n");


    if( time()-(int)me->query_temp("duzun_end") < 5 )
	return notify_fail("��������Ϣ��˳��\n");
     	msg = RED"\n$N˫Ŀ����,ʹ�����һ�С�Ψ�Ҷ���,˫צ������$n����Ǵ���.\n" NOR;
	myexp= me->query("combat_exp") /10000;
	yourexp=target->query("combat_exp")/15000;
	myskill=me->query_skill("yinfeng-zhua",1);
	yourskill=target->query_skill("dodge",1);
	ap=myexp*myskill;
	dp=yourexp*yourskill;
	me->add("force",-me->query_str()/3);
	if (random(ap+dp)>dp/2)
	{
	        msg += HIR"\nֻ����������һ��,���ǹ��۵�����,$n��ͷ���������ָ��!!\n" NOR;
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
		msg += HIY "����$p���Ƕ����$P�����һ������\n" NOR;
		if( !me->query("lunhui_zhuanshi") )
	        	me->start_busy(1);
		message_vision(msg, me, target);	
	}
        if( wizardp(me) && (string)me->query("env/combat")=="verbose" )                       tell_object(me, sprintf( GRN "AP��%d��DP��%d���˺�����%d\n" NOR,
                                ap/100, dp/100, damage));
  	me->set_temp("duzun_end",time());
        return 1;
}

