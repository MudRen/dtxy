#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra;
 	object weapon;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��Է���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        weapon = me->query_temp("weapon");
        if(me->query("family/family_name")!="����ɽ���鶴")
        return notify_fail("��Է���ֻ������ɽ���鶴���˲ſ����ã�\n");
        if (me->query_skill("wugou-jian",1) < 50)
        return notify_fail("����⹳�������������졣\n");
        if (me->query_skill("lingyunbu",1) < 50)
        return notify_fail("������Ʋ����������졣\n");
        if (me->query_skill_mapped("force")!="xuanzong-force")
        return notify_fail("��Է������������ķ���ϡ�\n");
         if((int)me->query("force") < 600 )
                return notify_fail("�������������\n");
        if((int)me->query("kee") < 300 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        if( time()-(int)me->query_temp("fengshen_end") < 5 ) return notify_fail("�����ö�Ͳ����ˣ�\n");
	me->set_temp("fengshen_end",time());        
        extra = me->query_skill("wugou-jian",1) / 8;
        extra += me->query_skill("lingyunbu",1) / 8;
        me->add_temp("apply/attack", extra);
        me->add_temp("apply/damage", extra);
        me->receive_damage("kee", 150);
msg = MAG  "$N��������ؼ�������ޱ�������һʽ"+HIW"���죭�ԣ��⣭�� ��"MAG+"�缱�������$n��\n" NOR;
        message_vision(msg, me, target);
 msg = HIW                                                                  "$N����"+ weapon->name()+  HIW"�ó�����Ĺ⻪����$n��" NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, target,weapon);
msg = HIW  "$N����"+ weapon->name()+  HIW"�����������ǵĺ�Х��$n��ȥ��" NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, target,weapon);
msg = HIW  "$N����"+ weapon->name()+  HIW"��Ȼ��������Ե���������$n��" NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, target,weapon);
        me->add("force",-(1+random(2))*150);
        me->add_temp("apply/attack", -extra);
        me->add_temp("apply/damage", -extra);
       me->start_busy(1+random(1));
        return 1;
}
