#include <ansi.h>
inherit SSERVER;
int cast(object me, object target)
{
        int success_adj, damage_adj;
        success_adj = 100;
        damage_adj = 100;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ������⣿\n");
        if((int)me->query("mana") < 100+2*(int)me->query("mana_factor") )
                return notify_fail("��ķ���������\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("���޷����о�����\n");
        me->add("mana", -25-2*(int)me->query("mana_factor"));
        me->receive_damage("sen", 50);
        if( random(me->query("max_mana")) < 50 )
{
                write("���ˣ����û�ų�����\n");
                return 1;
}
        SPELL_D->attacking_cast(
                me, 
                target, 
                success_adj,
                damage_adj,
                "qi",
                HIC "\n$N�������˾����ģ���������ࡢ�ơ��ࡢ�ס�������⻪��һ����ָ֮�����һ������$n��\n" NOR,
                HIR "\n������͡���һ������ɫ����$n����͸�������\n�ϳ�һ��������Ѫ��������Բ������Ϊƽ�أ�\n" NOR, 
                HIC "����ͣ���һ��$n��������������ֻ����ͷƤ��\n" NOR, 
                HIC "��������ɫ��ⱻ$n�Է�������������$N��ȥ��\n" NOR, 
                HIR "�����ɫ����$n����͸��������ϳ�һ��������Ѫ��������Բ������Ϊƽ�أ�\n" NOR
        );
        me->start_busy(1+random(2));
        return 3+random(6);
}
