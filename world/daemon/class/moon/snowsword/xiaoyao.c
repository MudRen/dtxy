#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
		return notify_fail("��Ҫ��˭ʩչ��һ�С���ңһЦ����\n");
        if(!me->is_fighting(target))
      		return notify_fail("����ңһЦ��ֻ����ս����ʹ�ã�\n");
        if((int)me->query("max_force") < 800)
                return notify_fail("�������������\n");
	if((int)me->query("force") < 500 )
     		return notify_fail("����������㣡\n");
	if((int)me->query("sen") < 200)
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("snowsword", 1) < 100)
		return notify_fail("��ķ��ѩ�轣���𻹲�����ʹ����һ�л������� !\n");
        me->delete("env/brief_message");
   	target->delete("env/brief_message");
message_vision(HIW"\n"+HIY"$N��̾����"+HIW"���ŵ���Ϧ�����࣬��Ҳ���� "+HIY"ͻȻ������һЦ\n"+
NOR"\n"+HIY"                    ����$nһ����������ɱ�֣�\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        me->receive_damage("sen", 100);
	me->add("force",-100);
        
	me->start_busy(2);
        return 1;
}
