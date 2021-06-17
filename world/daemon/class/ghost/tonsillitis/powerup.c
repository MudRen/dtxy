//Cracked by Roath
// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        if(me->query("family/family_name")!="���޵ظ�")
                return notify_fail("�㲻�ǵظ����ӣ�����ʹ������ܣ�\n");

        skill = me->query_skill("tonsillit",1);
        
        if( skill > 350 ) {
                skill=350;
	}

        if( target != me ) 
		return notify_fail("��ֻ���÷����������������Լ���ս������\n");

        if( (int)me->query("force") < skill*2 )     
		return notify_fail("�������������\n");
        if( (int)me->query_temp("powerup") ) 
		return notify_fail("���Ѿ����˹����ˡ�\n");

        me->add("force", -skill);
        me->receive_damage("kee", 50);

        message_vision(
                HIR "$N΢һ��������������������ͷ��ð��һ�������������ֳ�һ�����Ρ�����\n" NOR, me);

        me->add_temp("apply/attack", skill/2);
        me->add_temp("apply/strength", skill/2);
        me->set_temp("powerup", 1);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/2 :), skill);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if(!me) return;
        me->add_temp("apply/attack", - amount);
	me->add_temp("apply/strength", - amount);
        me->delete_temp("powerup");
        me->add("bellicosity", amount*2 );
	// mon 3/1/98. move this to after powerup is done.
        tell_object(me, "��ķ���������������һ������ϣ��������ջص��\n");
}

