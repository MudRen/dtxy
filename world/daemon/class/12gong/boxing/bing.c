// bing.c 

// ȡ��fy3֮���ź���
#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{

        int attackp, defendp;
	if( target == me ) target = offensive_target(me);
	if( !target || !target->is_character() )
		return notify_fail("��Ҫ��˭ʹ�á����ľ�����\n");
	if( !me->is_fighting(target) )
		return notify_fail("�����ľ���ֻ������ս����ʹ�ã�\n");
	if( objectp(me->query_temp("weapon")) )
		return notify_fail("�������ֲ���ʹ�á����ľ�����\n");
//	if( (int)me->query_skill("beiming-zhenqi", 1) < 110 )
//		return notify_fail("��ı�ڤ������������������ʹ�á����ľ�����\n");
	if( (int)me->query("force",1) < 270 )
		return notify_fail("�����������������ʹ�á����ľ�����\n");
	if(target->query("disable_type") == HIW "<������>" NOR)
		return notify_fail("�����ڲ�����Ҫʹ�á����ľ�����\n");
	attackp = me->query_skill("boxing", 1);
	defendp = target->query_skill("force") + target->query_skill("dodge");
	message_vision( HIW"$N���˱�ڤ��������������������Ө��˸�ı������ں�����ҫ�У���$nϮ����\n\n"NOR, me, target );
	if( attackp > defendp / 5 + random(defendp) / 5 ) {
		message_vision( HIW"������ҫ�ı���Χ����$n��ȫ���������۳ɱ��飬��$n�������У�\n"NOR, me, target );
//		seteuid(ROOT_UID);
		target->disable_player(HIW"<������>"NOR);
		target->set_temp("block_msg/all", 1);
                call_out("remove_frozen", 7 + random((int)me->query_skill("boxing", 1) / 10), target);
	}
	else {
		message_vision("���Ǳ�$n�㿪�ˡ�\n", me, target);
	}
	target->kill_ob(me);
	me->add("force", -270);
	me->start_busy(2);
	return 1;
}
void remove_frozen(object me)
{
	me->enable_player();
	me->set_temp("block_msg/all", 0);
	me->set("disable_type", 0);
	if ( !me->is_ghost() )
	message_vision(HIR "$N����һ��ŭ��˫��һ�񣬽��������۵ı�����÷��飡��\n\n" NOR, me);

}

