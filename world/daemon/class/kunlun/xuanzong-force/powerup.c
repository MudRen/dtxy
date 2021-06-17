#include <ansi.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int amount);
int exert(object me, object target)
{
        int skill;
        if( (int)me->query("force") < 500 )     
                return notify_fail("�������������\n");
        if( (int)me->query("kee") < 150 )
                return notify_fail("�����Ѫ���㡣\n");
        if( (int)me->query("sen") < 150 )
                return notify_fail("��ľ����㡣\n");
        if( (int)me->query_temp("powerup") ) 
                return notify_fail("���Ѿ����˹����ˡ�\n");
        skill = me->query_skill("xuanzong-force",1);
        if ( skill>=250 ) skill=250;
        me->add("force", -300);
        me->receive_damage("kee", 130);
        me->receive_damage("sen", 100);
        message_vision(
   HIR"$N����һ�ݣ�����������������⣬��ȫ����ס��\n"NOR,me);
        me->add_temp("apply/armor", skill/5);
        me->add_temp("apply/damage", skill/5);
        me->add_temp("apply/attack", skill/5);
        me->add_temp("apply/strength", skill/5);
        me->set_temp("powerup", 1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/5 :),skill);
        if( me->is_fighting() ) me->start_busy(4);
        return 1;
}
void remove_effect(object me, int amount)
{
        me->add_temp("apply/armor", - amount);
        me->add_temp("apply/damage", -amount);
        me->add_temp("apply/attack", -amount);
        me->add_temp("apply/strength", -amount);
        me->delete_temp("powerup");
        tell_object(me, HIR"������һ�٣�����ĺ����ַɻ����ڡ�\n");
        return;
}
