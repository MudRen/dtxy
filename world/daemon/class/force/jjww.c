// transfer.c
#include <ansi.h>
inherit SSERVER;

//
int exert(object me, object target)
{
		string msg;
        float ap,dp;
        int success,howlong;

        if( !target ) target = offensive_target(me);
        if(!me->query("zspfm/zspfm_ts"))
                return notify_fail("�㻹û������������ܣ�\n");
                  if( time()-(int)me->query_temp("zspfm_ts_end") < 10 )
			return notify_fail("��ڸ����˵����������\n");
        if((int)me->query_skill("force") < 100)
                return notify_fail("��ļ��ܵȼ�̫�ͣ�\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("�����˭ʹ�ã�\n");
				
		if(!me->is_fighting(target))
                return notify_fail("���������᡹ֻ����ս����ʹ�ã�\n");
        if(target->is_busy())
                return notify_fail(target->query("name")+"�Ѿ����������ˣ�\n");

        if((int)me->query("force") < 500 )
                return notify_fail("�������������\n");

        me->add("force", -500);
        
        msg = HIC
"$N������ĵĶ�$n˵:���ж����ֵܽ��ã��㸸ĸ��������˵�仰������ֻ����������֮ǰ�ཻһ�����Ѷ���\n"NOR;

        success = 1;
                  if (random(me->query("combat_exp")) < target->query("combat_exp")/5)
			success = 0;
                  if (random(me->query_skill("force")) < target->query_skill("force")/3)
			success = 0;
        if(success == 1 ){
            msg +=  HIR "���$n���°�ĭ��ʵ���Ǳ����ò�����...\n" NOR;
              target->start_busy(3);

        }
        else {
            msg +=  HIR "$nŬ�������񣬲���Ӱ�죡\n" NOR;
me->start_busy(1);
        }

        message_vision(msg, me, target);
		me->set_temp("zspfm_ts_end",time());
		return 1;
}
