#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,ap,dp,damage,i;
	object weapon;
	extra = me->query_skill("wugou-jian",1);
        if(!wizardp(me) && me->query("family/family_name")!="����ɽ���鶴")
        	return notify_fail("[�������]ֻ������ɽ���Ӳſ����ã�\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("[�������]ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( extra < 100 )
        	return notify_fail("����⹳�������������죡\n");
        if((int)me->query("force") < extra )
		return notify_fail("�������������\n");
         
        i = extra  / 100 + 1;
        damage = me->query_skill("sword",1) + me->query_str();
        damage = damage + random(damage/2);
        damage = damage/2;
        if( wizardp(me) ) tell_object(me,HIR"damage="+ damage +"\n"NOR);
      	weapon=me->query_temp("weapon");
      	ap = extra + me->query_skill("lingyunbu",1);
      	dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
      	message_vision(HIC"\n$N���̤ǰ���ŵ�Ծ�𣬽���ʹ���ˡ�������ɡ���\n"NOR,me);
	msg = HIC"\n�ڿ�ʽ��\n$N����"+weapon->query("name")+HIC"�ó���亮�⣡\n"NOR;
	message_vision(msg,me,target);
	me->add("force",-extra/2);
	if( random(ap) > dp/4 )
	{
		message_vision(HIR"\n$n��ܲ����������亮��͸�������\n"NOR,me,target);
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		COMBAT_D->report_status(target);
	}
	else
		message_vision(CYN"\n$n�Ṧ���ˣ������⾡�������\n"NOR,me,target);
	if( i > 1 )
	{
		msg = HIW"\n׷��ʽ��\nɲ�Ǽ�$n�����ڽ���֮�У�\n"NOR;
		message_vision(msg,me,target);
		if( random(ap) > dp/4 )
		{
			message_vision(HIR"\n$n�޴����ӣ�������ɱ�ı������ˣ�\n"NOR,me,target);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
			COMBAT_D->report_status(target);
		}
		else
			message_vision(WHT"\n$n�����ڹ�����ȫ������ס��\n"NOR,me,target);
	}
	if(i > 2 )
	{
		msg = HIY"\n׷��ʽ��\n$N��ʽ����Ʈѩһ������Ʈ�ݣ�$n��ʱ��֪��ν��У�\n"NOR;
		message_vision(msg,me,target);
		if( random(ap) > dp/4 )
		{
			message_vision(HIR"\n$n���۷�ֱ���������������ɣ�\n"NOR,me,target);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
			COMBAT_D->report_status(target);
		}
		else
			message_vision(YEL"\n$n�����񣬼�ʱ�ܿ��˽�����\n"NOR,me,target);
	}
	if(i > 3 )
	{
		msg = HIM"\n����ʽ��\n$N�����������һ�㣬����ѩ���ӿ������£��Ӷ�"+weapon->name()+HIM"��$n��ȥ! \n"NOR;
		message_vision(msg,me,target);
		if( random(ap) > dp/5 )
		{
			message_vision(HIR"\n$n����ľ�������������Ķ�����\n"NOR,me,target);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
			COMBAT_D->report_status(target);
		}
		else if( random(ap+dp) > dp/3 )
		{
			target->receive_damage("sen",extra,me);
			message_vision(MAG"\n$n�����Դ�����ǿ�ܹ��˽�����\n"NOR,me,target);
			COMBAT_D->report_sen_status(target);
		}
		else
			message_vision(MAG"\n$n��־���ѣ�����Ծ����\n"NOR,me,target);
	}
	if( me->query("lunhui_zhuanshi") > 4 )
		me->start_busy(1);
	else
       		me->start_busy(2);
        return 1;
}
