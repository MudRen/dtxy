//Cracked by Roath
// fixed overflow issue by emotion, 04/29/2006
#include <ansi.h>
inherit SSERVER;
int cast(object me, object target)
{
        string msg;
        int damage;
        float ap, dp;
        int extradam;

        if( !target ) target = offensive_target(me);

        if((int)me->query_skill("gouhunshu",1) < 100 )
                return notify_fail("��Ĺ����������ߣ�\n");
        if(me->query("family/family_name")!="���޵ظ�")
                return notify_fail("�㲻�ǵظ����ӣ�����ʹ������ܣ�\n");
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�����ɢ��\n");

        if((int)me->query("kee") < 25 )
                return notify_fail("�����Ѫ������\n");

        me->receive_wound("kee", 25);
        msg = HIC "$N���в��ϵ��������ģ�ֻ��������ͣ����$n��ȥ��\n\n" NOR;

        ap = 0.0 + me->query_skill("gouhunshu");
        extradam = ap/2;
        ap = ( ap * ap /100 * ap / 4 ) * (int)me->query("sen") ;
        dp = 0.0 + target->query("combat_exp");
        if( (ap + dp)*random(1000)/1000 > dp ) {
                damage = me->query("bellicosity") /50 ;
                        msg +=  RED "�����𽥰�Χ��$p������!\n" NOR;
                         message_vision(msg, me, target);
                         if (damage > 1000) damage = 975 + random(50);
                        target->receive_damage("kee", damage, me);
                        target->receive_wound("kee", damage/3, me);
                        if( damage > 0 ) COMBAT_D->report_status(target);

        } else
                {
                msg += "���Ǳ�$n�����ˣ���\n";
                message_vision(msg, me, target);
                target->kill_ob(me);
                me->kill_ob(target);
                }
        me->start_busy(2);
        return 1;
}

