// transfer.c
#include <ansi.h>
inherit SSERVER;

//����һ��
int exert(object me, object target)
{
		string msg;
        float ap,dp;
        int success,howlong;
                  int damage = me->query_skill("force");


        if( !target ) target = offensive_target(me);
        if(!me->query("zspfm/zspfm_zbj"))
                return notify_fail("�㻹û������������ܣ�\n");
		/*
		if( time()-(int)me->query_temp("zspfm_zbj_end") < 5 )
			return notify_fail("��ڸ����˵����������\n");
		*/
        if((int)me->query_skill("force") < 100)
                return notify_fail("��ļ��ܵȼ�̫�ͣ�\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("�����˭ʹ�ã�\n");

		if(!me->is_fighting(target))
                  return notify_fail("������һ�ҡ�ֻ����ս����ʹ�ã�\n");
				

				
        if((int)me->query("force") < 500 )
                return notify_fail("�������������\n");

        me->add("force", -100);

        msg = HIC
"$N��Ȼ����������Ԫ˧�ľ��У���װ���У����ϱ������ߡ�\n"NOR;

        success = 1;
		
		if (random(me->query("combat_exp")) < target->query("combat_exp")/8)
			success = 0;

		me->start_busy(2);
        if(success == 1 ){
            msg +=  HIR "���$n�����мƣ���æ׷�ϡ������$N����һ�����Ѫ��ģ��\n" NOR;
          message_vision(msg, me, target);
            target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/2,me);
                          COMBAT_D->report_status(target);
        }
        else {
            msg +=  HIR "$n���������֪��$N�ļƲߣ�����׷�ϡ�\n" NOR;
          message_vision(msg, me, target);
        }

		//me->set_temp("zspfm_ts_end",time());
		return 1;
}

