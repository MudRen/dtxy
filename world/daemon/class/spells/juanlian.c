#include <ansi.h>

inherit SSERVER;

void remove_effect(object me, object target,int amount);

int cast(object me, object target)
{
	int skill;
	me=this_player();

	if( !me->query("zspfm/zspfm_shs") )
		return notify_fail("�㻹û�����򡸵�����������ѧ��\n");
	if( (int)me->query_skill("spells", 1) < 100 )
		return notify_fail("��ķ����ȼ�������\n");
		
	if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�⡸������������ѧ��\n");

        if(!me->is_fighting(target))
                return notify_fail("������������ֻ����ս����ʹ�ã�\n");
	if (target->query_temp("zspfm/in_juanlian"))
		return notify_fail("�Է��Ѿ����˵���������!\n");
				
	if((int)me->query("mana") < 300 )
                return notify_fail("��ķ������㣡\n");
	skill = me->query_skill("spells");
          message_vision(HIW"\n$NĬ����У����һ����������������ʱһ���ˮӿ������$n���˽�ȥ\n"NOR,me,target);
	target->set_temp("zspfm/in_juanlian");
	target->add_temp("apply/armor",-skill/3);
          target->add_temp("apply/dodge",-skill/10);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, skill :), skill/100);
	return 3+random(5);
}

void remove_effect(object me, object target, int amount)
{
	if (target) {
        target->add_temp("apply/armor",amount/3);
          target->add_temp("apply/dodge",amount/10);
		target->delete_temp("zspfm/in_juanlian");
        message_vision(HIW"\n$n���ڴӺ�ˮ�����˳����������ֳ����Ǳ�������\n"NOR,me,target);
	}
	return;
}


