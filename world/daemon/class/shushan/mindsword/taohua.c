// taohua.c
//tomcat�޸�  
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon, ob;
        string msg, string1;
        int count;
        int weapon_val = 0; 
      
        if( !target ) target = offensive_target(me);

	if( !me->is_fighting(target) )
		return notify_fail("���һ����衹ֻ����ս����ʹ�á�\n");

        if( me->query_skill("zixia-shengong",1) < 100)
            return notify_fail("�����ϼ�񹦵ȼ�����, ����ʹ�á��һ����衹��\n");

        if( me->query_skill("mindsword",1) < 100)
            return notify_fail("����һ������ȼ�����, ����ʹ�á��һ����衹��\n");

        if( me->query("force") < 250 )
            return notify_fail("��������������޷����á��һ����衹��\n");
        if( time()-(int)me->query_temp("taohua_end") < 5 )
                return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
        me->set_temp("taohua_end",time());
	msg = HIY "$Nʹ���һ������������һ����衹������Ȼ�ӿ졣��Ӣ�ͷף�" NOR;
	
         weapon = me->query_temp("weapon");
                 
	 COMBAT_D->do_attack(me,target, weapon,TYPE_REGULAR);
	 msg =  BLINK""+HIM"�����һ���" NOR;
	 message_vision(msg,me,target);
	 COMBAT_D->do_attack(me,target, weapon,TYPE_REGULAR);
	 msg =  BLINK""+HIR"�����䣡" NOR;
         message_vision(msg,me,target);
	 COMBAT_D->do_attack(me,target, weapon,TYPE_REGULAR);
	 msg =  BLINK""+HIC"���컨�꣡" NOR;
         message_vision(msg,me,target);
         COMBAT_D->do_attack(me,target, weapon,TYPE_REGULAR);
	 msg =  BLINK""+HIG"�仨���⣡" NOR;
	 message_vision(msg,me,target);
	 COMBAT_D->do_attack(me,target, weapon,TYPE_REGULAR);
	me->add("force", -50);
	me->start_busy(2);
	return 1;
}

