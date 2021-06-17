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
                return notify_fail("��Ҫ��˭ʩչ��������?\n");
        if(!me->is_fighting(target))
                return notify_fail("��������ֻ����ս����ʹ�ã�\n");
	if (!weapon = me->query_temp("weapon"))
		return notify_fail("��û�ñ��ӣ���ʲô֯������\n");
	 if(!wizardp(me) && me->query("family/family_name") != "�¹�" )
                return notify_fail("���������Ե,���򲻵������ľ���!!\n");
      	//req=(int)me->query_skill("whip", 1)+(int)me->query_skill("juqingbian", 1)+(int)me->query_skill("moonshentong", 1);
	if((int)me->query_skill("spells") < 100 || (int)me->query_skill("jueqingbian",1) < 100)
		return notify_fail("��Ĺ���ȼ���������ʹ����������\n");

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("�����˭ʹ������\n");

	if(target->query_temp("in_qingwang"))
		return notify_fail(target->query("name")+"�Ѿ���������������ˣ�\n");

	if((int)me->query("mana") < 200 )
		return notify_fail("��ķ���������\n");
	if((int)me->query("force") < 200 )
		return notify_fail("�������������\n");
	if((int)me->query("sen") < 10 )
		return notify_fail("���޷����о�����\n");

	me->add("mana", -100);
	me->add("force", -100);
	me->receive_damage("sen", 10);

	msg = HIB"$N�߶�������������"+weapon->query("name")+HIB"���һ�ţ�����һ�Ŵ�������$n��ͷ������\n"NOR;

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
		msg +=  HIB "$n������һƬ���ң���ʹ����ͻȻ���������������˶�������������ͷ��ס��\n" NOR;
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
		msg +=  HIG "$n�������ѣ���Ϊ����������������һԾ�������������Ϯ����\n" NOR;
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


